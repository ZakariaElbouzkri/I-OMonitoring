/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 21:38:27 by zel-bouz          #+#    #+#             */
/*   Updated: 2024/03/21 21:41:13 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include "IMonitor/IMonitor.hpp"
#define EVENT_READ 1 << 0
#define EVENT_WRITE 1 << 1
#define EVENT_RW (EVENT_WRITE | EVENT_READ)

#include "Poller/Poller.hpp"
#include "Selector/Selector.hpp"
#ifdef __APPLE__ 
    #include "KQueuer/KQueuer.hpp"
#else
    #include "Epoller/Epoller.hpp"
#endif


