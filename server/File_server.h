#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include "Server.h"

#include <sys/socket.h>
#include <netinet/in.h>

class File_server : public Server {
public:
	// Grab resources and construct the file server.
	File_server(short port_number);

	// Tear down the file server.
	~File_server() override;

	// Run the file server.
	void run() override;

protected:
	// Receive the file name from the client.
	std::string recv_filename(int client);

	// Send the contents of file, via input_stream, over the wire.
	void send_file(int client, const std::string &filename);

private:
	// socket and socket address.
	int sock;
	struct sockaddr_in sock_addr;

};

#endif // FILE_SERVER_H
