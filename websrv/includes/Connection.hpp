#pragma once

#include "websrv.h"

class	Server;

class	Connection
{
	int				fd;
	const Server	*server;
	std::string		request;
	std::string		response;

public:
	Connection(int _fd, Server *_sv) : fd(_fd), server(_sv) { request.reserve(1024); response.reserve(1024);}
	~Connection() { close(fd);}
	int					read() { return recv(fd , (void *)request.data(), request.capacity(), 0);}
	int					send() { return ::send(fd, (void *)response.data(), response.size(), 0);}
	inline std::string	&getRequest() { return request;}
	inline std::string	&getResponse() { return response;}
	inline void			setRequest(char *str) { request = str;}
	inline void			setResponse(char *str) { response = str;}

	inline operator int() {return fd;};
};