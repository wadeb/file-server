#include "File_server.h"

#include <cstdlib>
#include <fstream>

using std::string;
using std::itoa;
using std::ifstream;

// size of the initial receive buffer.
const int RECV_BUFFER_SIZE = 20;

//
// Creates socket and binds to the provided port number.
//
File_server::File_server(short port_number)
{
	if (sock = socket(PF_INET, SOCK_STREAM, 0) < 0) {
		throw Server_error("Couldn't instantiate socket");
	}

	// Initialize the sock address structure.
	sock_addr.sin_len = 0;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(port_number);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind the socket to the port number.
	if (bind(sock, (struct sockaddr *) &sock_addr, sizeof(sock_addr) < 0)) {
		string e_msg = "Couldn't bind socket to port: ";
		e_msg += itoa(port_number);
		throw Server_error(e_msg);
	}
}

//
// Close the socket for good measure.
//
File_server::~File_server()
{
	close(sock);
}

//
// List on the port, accept and server requests.
//
void File_server::run()
{
	while (true) {
		int sa_size = sizeof(sock_addr);
		int client = accept(sock, (struct sockaddr *) &sock_addr,
								&sa_size);

		if (client < 0) {
			throw Server_error("Error when accepting client");
		}

		string filename = recv_filename(client);
		send_file(client, filename);
		input_stream.close();
	}
}

//
// Receive the filename from the client as a stream of chars.
//
string File_server::recv_filename(int client)
{
	// TODO: Implement me!
	return string();
}

//
// Send the contents of file, which have been opened via the input
// stream input_stream, over the wire back to the client.
//
void File_server::send_file(int client, const string &filename)
{
	// TODO: Implement me!
}
