#ifndef CONNECTION_H
#define CONNECTION_H

//
// A hopefully reusable interface for making interprocess connections
// both local and over the network.
//
// author - Wade Bonkowski
// date - 2/3/2016
//

// TODO: Add support for sending and receiving data to and from
// 	 input and output streams.

#include "Utility.h"

#include <vector>

class Receiver;

//
// Connection class that represents a connection to another process.
// Data can be received and sent over the connection.
// NOTE: Currently support is only for IPv4.
//
// Format used is: <# of bytes of data> <data>
//
class Connection {
public:
	// Create a connection to the process at the specified
	// IP address and port number.
	// Throws Connection_error on failure.
	Connection(const std::string &ip_addr, int port_number);

	// Close the connection.
	~Connection();

	// Send a message over this Connection.
	Connection &operator<<(const std::string &msg);

	// Send a stream of bytes over this Connection.
	Connection &operator<<(const std::vector<char> &bytes);

	// Receive message over this connection.
	Connection &operator>>(std::string &msg);

	// Receive a stream of bytes from this Connection.
	Connection &operator>>(std::vector<char> &input);

private:
	// BSD socket that is used to maintain the connection.
	int sock;

	friend class Receiver;
	// Creates a Connection object from a file descriptor that is
	// already open for a socket.
	// Only to be used by Receiver when accepting a connection.
	Connection(int fd);

	// Helper functions.

	// Extract the 4 bytes out of the string IP address.
	std::vector<int> parse_ip(const std::string &ip_addr);

	// Send data of size over the socket. Throw Connection_error if
	// there are any local errors reported.
	void send_data(const std::string &data);

	// Receive data using the defined protocol from the socket.
	std::string recv_data();

	// Receives the header of the message, this is returned through
	// the reference parameter header. Any beginning part of the actual
	// message that was prematurely grabbed is returned in the reference
	// parameter result.
	void recv_header(std::string &header, std::string &result);

};

#endif // CONNECTION_H
