#ifndef SERVER_H
#define SERVER_H

#include <exception>
#include <string>

//
// Server interface for different kinds of Servers.
// author - Wade Bonkowski
// date - 1/31/2016
//


//
// Exception class for any Server operations that fail
// in setup, handling, and tear-down.
//
class Server_error : std::exception {
public:
	// Construct with an erroe message.
	Server_error(const char *msg_) : msg(msg_) {}

	// Prints the exception message.
	const char* what() const override { return msg.c_str(); }

private:
	std::string msg;

};

//
// Abstract Server class that defines the interface to Servers.
//
class Server {
public:
	// To make sure server resources are cleaned up.
	virtual ~Server() {}

	// Run the server.
	virtual void run() = 0;

};

#endif // SERVER_H
