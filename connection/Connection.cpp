#include "Connection.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

using std::string;
using std::vector;
using std::stoi;
using std::to_string;

// Highest port number on linux systems.
const int MAX_PORT = 65535;

// Size of initial receive buffer.
const int BUFFER_SIZE = 10;

//
// Create a connection to the process at the specified
// IP address and port number.
// Throws Connection_error on failure.
//
Connection::Connection(const string &ip_addr, int port_number)
{
	// Sanity check.
	if (port_number < 0 || port_number > MAX_PORT) {
		throw Connection_error("Bad port number.");
	}

	// Create the TCP socket.
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		throw Connection_error("Error creating the socket.");
	}

	// setup IP.
	struct sockaddr_in addr;
	addr.sin_len = 0;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_number);
	// Extract and enter the desired IP address.
	vector<int> ip = parse_ip(ip_addr);
	addr.sin_addr.s_addr = htonl((((((ip[0] << 8) |
					  ip[1]) << 8) |
					  ip[2]) << 8) |
					  ip[3]);

	// Make the connection.
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		close(sock);
		throw Connection_error("Error making connection");
	}
}

//
// Close the connection.
//
Connection::~Connection()
{
	close(sock);
}

//
// Send a message over this Connection.
//
Connection &Connection::operator<<(const string &msg)
{
	send_data(msg);
	return *this;
}

//
// Send a stream of bytes over this Connection.
//
Connection &Connection::operator<<(const vector<char> &data)
{
	send_data(string(data.begin(), data.end()));
	return *this;
}

//
// Receive a message over this Connection.
//
Connection &Connection::operator>>(string &msg)
{
	msg = recv_data();
	return *this;
}

//
// Receive a stream of bytes from this Connection.
//
Connection &Connection::operator>>(vector<char> &data)
{
	string result = recv_data();
	data = vector<char>(result.begin(), result.end());
	return *this;
}

//
// Creates a Connection object from a file descriptor that is
// already open for a socket.
// Only to be used by Receiver when accepting a connection.
//
Connection::Connection(int fd)
{
	// TODO: Implement me!
}

//
// HELPER FUNCTIONS
//

//
// Extract the 4 bytes out of the string IP address.
// Input is an IP address in the form of "x.x.x.x"
// where each x is an 8-bit integer.
// No error checking is done here. Saved for when the connection attempt
// is made.
//
vector<int> Connection::parse_ip(const string &ip_addr)
{
	vector<int> result;
	result.reserve(4);
	int current_byte = 0;
	vector<string> byte_strings(4);
	// Loop to split the strings on '.'
	for (const char glyph : ip_addr) {
		if (glyph == '.') {
			current_byte++;
			continue;
		}

		byte_strings[current_byte].push_back(glyph);
	}

	// Loop to convert to unsigned chars.
	for (string &str : byte_strings) {
		result.push_back(stoi(str));
	}

	return result;
}

//
// Send data of size over the socket. Throw Connection_error
// if there are any local errors that occur.
//
void Connection::send_data(const string &data)
{
	string length(to_string(data.size()));
	string message(length.size() + data.size() + 1, '\0');
	for (int i = 0; i < length.size(); i++) {
		message[i] = length[i];
	}

	message[length.size()] = ' ';
	for (int i = 0; i < data.size(); i++) {
		message[length.size() + i + 1] = data[i];
	}

	send(sock, message.data(), message.size(), MSG_NOSIGNAL);
}

//
// Receive data using the defined protocol from the socket.
//
string Connection::recv_data()
{
	string header, result;
	recv_header(header, result);
	int total = stoi(header);
	int leftover = total - result.size();
	result.reserve(total);
	recv(sock, result.data() + result.size(), leftover, MSG_WAITALL);
}

//
// Receives the header of the message, this is returned through
// the reference parameter header. Any beginning part of the actual
// message is returned throught the reference parameter result.
//
void Connection::recv_header(string &header, string &result)
{
	string buffer(BUFFER_SIZE, '\0');
	header_recvd = false;
	while (!header_recvd) {
		int size = recv(sock, buffer.data(), BUFFER_SIZE, 0);
		for (int i = 0; i < size; i++) {
			if (buffer[i] == ' ') {
				header_recvd = true;
				continue;
			}

			if (header_recvd) {
				result.push_back(buffer[i]);
			} else {
				header.push_back(buffer[i]);
			}
		}
	}
}
