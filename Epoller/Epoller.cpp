/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoller.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ZakariaElbouzkri <elbouzkri9@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:03:16 by ZakariaElbo       #+#    #+#             */
/*   Updated: 2024/03/22 05:24:40 by ZakariaElbo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__

#include "Epoller.hpp"

Epoller::Epoller( void )
{
	_epollfd = epoll_create1(0);
	if (_epollfd == -1) {
		throw std::runtime_error("Failed to create epoll instance");
	}
}

Epoller::~Epoller( void )
{
	close(_epollfd);	
}

void	Epoller::push(int fd, short events)
{
	struct epoll_event event;
	uint32_t epollevnts = 0;
	if (events & EVENT_READ)
		epollevnts |= EPOLLIN;
	if (events & EVENT_WRITE)
		epollevnts |= EPOLLOUT;
	memset(&event, 0, sizeof(struct epoll_event));
	event.data.fd = fd;
	event.events = epollevnts;
	if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &event) == -1)
		throw std::runtime_error("Failed to add fd to poll events");
}

void	Epoller::pop(int fd)
{
	if (epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, NULL) == -1) {
		perror("epoll_ctl");
		throw std::runtime_error("Failed to remove fd from poll events");
	}
}

bool	Epoller::is_readable(int fd)
{
	return _readable_fds.find(fd) != _readable_fds.end();		
}

bool	Epoller::is_writeable(int fd)
{
	return _writeable_fds.find(fd) != _writeable_fds.end();
}

bool	Epoller::wait(int timeout)
{

	_readable_fds.clear();
	_writeable_fds.clear();
	int n = epoll_wait(_epollfd, _events, MAX_EVENTS, timeout);
	if (n == -1) {
		return perror("epoll"), false;
	}
	for (int i = 0; i < n; i++) {
		if (_events[i].events & EPOLLIN)
			_readable_fds.insert(_events[i].data.fd);
		if (_events[i].events & EPOLLOUT)
			_writeable_fds.insert(_events[i].data.fd);
	}
	return n > 0;
}

#endif
