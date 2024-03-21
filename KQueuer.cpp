/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KQueuer.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:52:30 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/21 21:08:27 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__

#include "KQueuer.hpp"

KQueuer::KQueuer( void )
{
	_kq = kqueue();
	memset(&_ts, 0, sizeof(struct timespec));
	if (_kq == -1)
		throw std::runtime_error("Failed to create kqueu instance");
}

KQueuer::~KQueuer( void ) {
	close(_kq);
}

void KQueuer::push(int fd, short events)
{
    struct kevent kev;
	uint16_t	kevents = 0;
	if (events & EVENT_READ)
		kevents |= EVFILT_READ;
	if (events & EVENT_WRITE)
		kevents |= EVFILT_WRITE;
	_fd_events[fd] = kevents;
	EV_SET(&kev, fd, kevents, EV_ADD, 0, 0, NULL);
	if (kevent(_kq, &kev, 1, NULL, 0, NULL) == -1) {
		throw std::runtime_error("Failed to add fd to kqueue for read events");
	}
}


void	KQueuer::pop(int fd)
{
    struct kevent kev_read, kev_write;
    int nevents = 0;

	std::unordered_map<int, uint16_t>::iterator it = _fd_events.find(fd);
	if (it == _fd_events.end())
		throw std::runtime_error("file descriptor not regestred");

    EV_SET(&kev_read, fd, it->second, EV_DELETE, 0, 0, NULL);
    if (kevent(_kq, &kev_read, 1, NULL, 0, NULL) == -1) {
        throw std::runtime_error("Failed to remove read event from kqueue");
    }
	_fd_events.erase(it);
}


bool	KQueuer::is_readable(int fd)
{
	return _readable_fds.find(fd) != _readable_fds.end();
}

bool	KQueuer::is_writeable(int fd)
{
	return _writeable_fds.find(fd) != _writeable_fds.end();
}

bool	KQueuer::wait(int timeout)
{
	_ts.tv_sec = timeout;
	_readable_fds.clear();
	_writeable_fds.clear();
	int num_events = kevent(_kq, NULL, 0, _events, MAX_EVENTS, &_ts);
	if (num_events == -1) {
		perror("kevent");
		return false;
	}
	for (int i = 0; i < num_events; ++i) {
		int fd = _events[i].ident;
		if (_events[i].filter & EVFILT_READ) {
			_readable_fds.insert(fd);
		}
		if (_events[i].filter & EVFILT_WRITE) {
			_writeable_fds.insert(fd);
		}
	}
	return num_events > 0;
}

#endif
