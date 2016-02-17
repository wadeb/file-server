#ifndef RECEIVER_H
#define RECEIVER_H

#include "Utility.h"

//
// A hopefully reusable interface for making interprocess connections
// both local and over the network.
//
// author - Wade Bonkowski
// date - 2/3/2016
//

class Connection;

//
// Receiver class that receives incoming connection requests and establishes
// them into Connection objects.
//
class Receiver {
public:
	// Creates a socket and binds it to the provided port number.
	// Throws Connection_error on failure.
	Receiver(int port_number);

	// Tells the receiver to listen for incoming connections.
	// num_requests in the total number of allowed outstanding requests
	// on the receiver at any given time.
	// It is important to have this function separate from the
	// initial setup so the private file descriptor can change on fork
	// if the user desires to fork the process, in the style of a simple
	// server.
	void listen(int num_requests = MAX_REQUESTS);

	// Accepts a new connection and returns a Connection object that can
	// then be used for 2-way communication.
	// Throws Connection_error on failure.
	Connection accept();

private:
	// BSD socket that is used to accept incoming connections.
	int sock;

};

#endif // RECEIVER_H
