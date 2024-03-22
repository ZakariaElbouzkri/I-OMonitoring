/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoller.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ZakariaElbouzkri <elbouzkri9@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:47:39 by ZakariaElbo       #+#    #+#             */
/*   Updated: 2024/03/22 05:24:56 by ZakariaElbo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef __linux__

#include "../monitors.hpp"
#include <sys/epoll.h>
#include <unordered_set>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <cstring>


#define MAX_EVENTS 1755314

class	Epoller : public IMonitor
{
	private:
		int		_epollfd;
		std::unordered_set<int>	_readable_fds;	
		std::unordered_set<int>	_writeable_fds;
		struct epoll_event		_events[MAX_EVENTS];
	public:
		Epoller( void );
		virtual ~Epoller( void );
		virtual void	push(int fd, short events);
		virtual void 	pop(int fd);
		virtual bool	is_readable(int fd);
		virtual bool	is_writeable(int fd);
		virtual bool	wait(int timeout = 1);
};


#endif