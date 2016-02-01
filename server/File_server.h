#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include "Server.h"

#include <sys/socket.h>
#include <netinet/in.h>

class File_server : public Server {
public:
	// Grab resources and construct the file server.
	File_server(int port_number);

	// Tear down the file server.
	~File_server() override;

	// Run the file server.
	void run() override;

private:
	// socket and socket address.
	int sock;
	struct sockaddr_in sock_addr;

};

#endif // FILE_SERVER_H
