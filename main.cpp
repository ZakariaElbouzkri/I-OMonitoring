/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ZakariaElbouzkri <elbouzkri9@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 06:47:22 by ZakariaElbo       #+#    #+#             */
/*   Updated: 2024/03/21 19:33:05 by ZakariaElbo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMonitor.hpp"
#include "Poller.hpp"
#include "Selector.hpp"
#include "Epoller.hpp"
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>

#define RES "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nab\r\n"

int main()
{
	IMonitor*	monitor = new Epoller();
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		return 1;
	int opt = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		return 1;
	sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8080);
	if (bind(sock, (sockaddr*)&addr, sizeof(addr)) == -1)
		return 1;
	if (listen(sock, SOMAXCONN) == -1)
		return 1;
	std::cout << "start listening..." << std::endl;
	fcntl(sock, F_SETFL, O_NONBLOCK);
	
	monitor->push(sock, EVENT_READ);

	std::vector<int>	_clients;

	while (true) {
		if (!monitor->wait())
			continue;
		if (monitor->is_readable(sock)) {
			sockaddr_in info;
			socklen_t	len = 0;
			int client = accept(sock, (sockaddr*)&info, &len);
			if (client == -1) {
				perror("accept");
			} else {
				fcntl(client, F_SETFL, O_NONBLOCK);
				_clients.push_back(client);
				monitor->push(client, EVENT_RW);
				std::cout << "new Client accepted" << std::endl;
			}
		}
		for (std::vector<int>::iterator it = _clients.begin(); it != _clients.end(); ) {
			if (monitor->is_readable(*it)) {
				char f[1024] = {0};
				int rd = recv(*it, f, 1024, 0);
				if (rd == -1) {
					perror("recv");
				} else if (rd == 0) {
					std::cout << "Client disconnected" << std::endl;
					monitor->pop(*it);
					close(*it);
					it = _clients.erase(it);
					continue;
				} else {
					// std::cout << "recieved: " << f << std::endl;
					send(*it, RES, strlen(RES), 0);
					std::cout << "Client disconnected" << std::endl;
					monitor->pop(*it);
					close(*it);
					it = _clients.erase(it);
					continue;
				}
			}
			it++;
		}
	}
}