#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/poll.h>
#include <fcntl.h>

#define vibe std::cout << "v" << std::endl;
class	Connection;

class	Server
{
	int			fd;
	std::vector<Connection> connection;
	struct sockaddr_in	addr;
public:
	Server(int);
	~Server();
	int				connect();
	int				get_fd();
	void			erase(int );
	Connection		&operator[](int );
};

class	Connection
{
	int				fd;
	const Server	*server;
	std::string		request;
	std::string		response;

public:
	Connection(int _fd, Server *_sv) : fd(_fd), server(_sv) {};
	int				read() { request.reserve(1000); return recv(fd , (void *)request.data(), request.capacity(), 0);}
	int				send() { return ::send(fd, (void *)response.data(), response.size(), 0);}
	std::string		&getRequest() { return request;}
	std::string		&getResponse() { return response;}
	void			setRequest(char *str) { request = str;}
	void			setResponse(char *str) { response = str;}
	void			close() { ::close(fd);};
	operator int() {return fd;};
};

#define log std::cout <<
#define line << std::endl
