/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Selector.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ZakariaElbouzkri <elbouzkri9@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:43:56 by ZakariaElbo       #+#    #+#             */
/*   Updated: 2024/03/21 07:02:19 by ZakariaElbo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Selector.hpp"


Selector::Selector( void )
{
	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	FD_ZERO(&_rfds);
	FD_ZERO(&_wfds);
	memset(&_timout, 0, sizeof(struct timeval));
}

Selector::~Selector( void )
{
}

void	Selector::push(int fd, short events)
{
	if (events & EVENT_READ)
		FD_SET(fd, &_readfds);
	if (events & EVENT_WRITE)
		FD_SET(fd, &_writefds);
}


bool	Selector::wait( int timoute )
{
	_rfds = _readfds;
	_wfds = _writefds;
	int ret = ::select(MAX_FDS, &_rfds, &_wfds, NULL, NULL);
	if (ret == -1)
		return false;
	return ret > 0;
}

void	Selector::pop(int fd)
{
	if (FD_ISSET(fd, &_readfds))
		FD_CLR(fd, &_readfds);
	if (FD_ISSET(fd, &_writefds))
		FD_CLR(fd, &_writefds);
}

bool	Selector::is_readable(int fd)
{
	return FD_ISSET(fd, &_rfds);
}

bool	Selector::is_writeable(int fd)
{
	return FD_ISSET(fd, &_wfds);
}