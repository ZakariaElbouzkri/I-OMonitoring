/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KQueuer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:47:55 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/21 21:41:41 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef __APPLE__

#include "../monitors.hpp"
#include <unordered_set>
#include <sys/event.h>
#include <unistd.h>
#include <unordered_map>

#define MAX_EVENTS 1024

class KQueuer : public IMonitor
{
	private:
		int									_kq;
		std::unordered_set<int>				_readable_fds;
		std::unordered_set<int>				_writeable_fds;
		std::unordered_map<int, uint16_t>	_fd_events;
		struct kevent						_events[MAX_EVENTS];
		struct timespec						_ts;

	public:
		KQueuer( void );
		virtual ~KQueuer();
		virtual	void	push(int fd, short events);
		virtual	void	pop(int fd);
		virtual	bool	is_readable(int fd);
		virtual	bool	is_writeable(int fd);
		virtual	bool	wait(int timeout = 1);
};


#endif
