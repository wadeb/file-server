#ifndef SERVER_H
#define SERVER_H

//
// Server interface for different kinds of Servers.
// author - Wade Bonkowski
// date - 1/31/2016
//

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
