/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMonitor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 05:08:32 by ZakariaElbo       #+#    #+#             */
/*   Updated: 2024/03/21 21:41:09 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class	IMonitor
{
	public:
		virtual ~IMonitor() {};
		virtual	void	push(int fd, short events) = 0;
		virtual void	pop(int fd) = 0;
		virtual bool	is_readable(int fd) = 0;
		virtual bool	is_writeable(int fd) = 0;
		virtual bool	wait(int timeout = 1) = 0;
};

