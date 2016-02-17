#ifndef UTILITY_H
#define UTILITY_H

#include <exception>
#include <string>

class Connection_error : public std::exception {
public:
	// Sets error message.
	Connection_error(const std::string &msg_ = "") : msg(msg_) {}

	// Retrieve the error message.
	const char *what() const noexcept override { return msg.c_str(); }

private:
	const std::string msg;

};

#endif // UTILITY_H
