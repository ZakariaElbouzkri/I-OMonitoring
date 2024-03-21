/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Selector.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ZakariaElbouzkri <elbouzkri9@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:12:11 by ZakariaElbo       #+#    #+#             */
/*   Updated: 2024/03/21 16:42:19 by ZakariaElbo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMonitor.hpp"

#include <sys/select.h>
#include <cstring>

#define MAX_FDS 1000

class	Selector : public IMonitor
{
	private:
		fd_set			_readfds;
		fd_set			_writefds;
		fd_set			_rfds;
		fd_set			_wfds;
		struct timeval	_timout;
	public:
		Selector( void );
		virtual ~Selector( void );
		virtual void	push(int fd, short events);
		virtual void 	pop(int fd);
		virtual bool	is_readable(int fd);
		virtual bool	is_writeable(int fd);
		virtual bool	wait(int timeout = 1);	
};