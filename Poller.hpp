/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Poller.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ZakariaElbouzkri <elbouzkri9@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:13:11 by ZakariaElbo       #+#    #+#             */
/*   Updated: 2024/03/21 16:41:10 by ZakariaElbo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IMonitor.hpp"
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
