/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poller.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:13:11 by ZakariaElbo       #+#    #+#             */
/*   Updated: 2024/03/21 21:41:56 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../monitors.hpp"
#include <unordered_set>
#include <vector>
#include <sys/poll.h>

class	Poller : public IMonitor
{
	private:
		std::vector<struct pollfd>	_pfds;
		std::unordered_set<int>		_readable_fds;
    	std::unordered_set<int>		_writeable_fds;
	public:
		Poller( void );
		virtual ~Poller( void );
		virtual void	push(int fd, short events);
		virtual void 	pop(int fd);
		virtual bool	is_readable(int fd);
		virtual bool	is_writeable(int fd);
		virtual bool	wait(int timeout = 1);
};
