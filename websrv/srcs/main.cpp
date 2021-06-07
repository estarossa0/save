#include "websrv.h"
#define PORT 80
int main()
{
	char buffer[1024] = {0};
	char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 5\r\n\r\nhello";
	Server sv(PORT);
	std::vector <struct pollfd> poll_set;


	poll_set.push_back((struct pollfd){sv.get_fd(), POLLIN, 0});int p;

	while (1)
	{
		bzero(buffer, 1024);
		log "+" line;
		p = poll(&poll_set[0], poll_set.size(), -1);
		log "---" << p line;
		if (p < 0)
			break ;
		for (size_t i = 0; i < poll_set.size(); i++)
		{
			log i << " " << poll_set[i].fd <<  " " << poll_set[i].revents line;
			if (poll_set[i].revents == 0)
				continue ;
			if ((poll_set[i].revents & POLLNVAL) || (poll_set[i].revents & POLLERR))
			{
				perror("");
				exit(1);
			}
			if (poll_set[i].revents & POLLIN)
			{
				if (poll_set[i].fd == sv.get_fd())
				{
					log "NEW" line;
					poll_set.push_back((struct pollfd){sv.connect(), POLLIN, 0});
				}
				else
				{
					sv[i].read();
					poll_set[i].events = POLLOUT | POLLIN;
					log sv[i].getRequest() line;
					if (poll_set[i].revents & POLLHUP)
					{
						sv.erase(i);
						poll_set.erase(poll_set.begin() + i);
						log "DELETE" line;
					}
				}
			}
			if (poll_set[i].revents & POLLOUT)
			{
				sv[i].setResponse(response);
				sv[i].send();
				poll_set[i].events = POLLIN;
				printf("Hello message sent\n");
			}
		}
	}
	return 0;
}