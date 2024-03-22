# Monitors

I/O operation monitors, often referred to simply as I/O monitors or event monitors, are mechanisms used in computer systems to efficiently manage and handle I/O (input/output) operations, such as reading from or writing to files, sockets, or other I/O devices. These monitors are crucial for event-driven programming, where applications need to react to various events asynchronously.

There are several types of I/O operation monitors, each with its own implementation and usage characteristics. Some common ones include:

1. **Polling**: In polling-based I/O monitors, the application continuously checks the status of I/O operations to determine if they are ready to perform data transfer. This approach can be inefficient because it involves active waiting and can lead to high CPU utilization.

2. **Select**: The `select` system call is available on many Unix-like operating systems. It allows applications to monitor multiple file descriptors for various types of events (e.g., readability, writability, exceptions) in a single call. However, `select` suffers from certain limitations, such as scalability issues with a large number of file descriptors.

3. **Poll**: The `poll` system call is an alternative to `select` and provides similar functionality. It can monitor multiple file descriptors for events and is more scalable than `select` because it does not have the same limitations on the maximum number of file descriptors.

4. **Epoll**: `epoll` is a scalable I/O event notification mechanism available on Linux systems. It allows applications to monitor large numbers of file descriptors efficiently. Unlike `select` and `poll`, which have O(n) complexity, `epoll` has O(1) complexity, making it suitable for high-performance applications with many file descriptors.

5. **kqueue**: `kqueue` is a similar event notification mechanism available on BSD-based operating systems (e.g., FreeBSD, macOS). It provides efficient monitoring of file descriptors and other kernel events. Like `epoll`, `kqueue` has O(1) complexity, making it suitable for high-performance applications.

These I/O operation monitors are essential for building efficient and scalable event-driven systems, such as network servers, real-time applications, and multimedia applications. The choice of which monitor to use depends on factors such as the operating system, the specific requirements of the application, and performance considerations.

# Monitors Library

Monitors is a C++ library that provides various I/O monitoring mechanisms, each implemented as a separate class. These classes allow developers to efficiently monitor file descriptors for events such as readability or writability.

## Features

- **Poller**: Implements polling-based I/O monitoring.
- **Epoller**: Provides I/O monitoring using the epoll mechanism on Linux systems.
- **Selector**: Implements I/O monitoring using the select system call.
- **KQueuer**: Provides I/O monitoring using the kqueue mechanism on BSD-based systems.

Each monitoring mechanism is encapsulated within its own class and implements the `IMonitor` interface, allowing for a consistent interface across different platforms.

## Usage

### Poller

The `Poller` class provides polling-based I/O monitoring. To use it, follow these steps:

1. Create an instance of the `Poller` class.
2. Use the `push` method to add file descriptors to monitor for events.
3. Use the `pop` method to remove file descriptors from monitoring.
4. Use the `is_readable` and `is_writeable` methods to check for readability and writability of file descriptors.
5. Use the `wait` method to wait for events on monitored file descriptors.
5. Use the `wait` method to wait for events on monitored file descriptors.
6. Event flags for setting events (for all Monitors):
	- EVENT_READ: Set to monitor readability of the file descriptor.
	- EVENT_WRITE: Set to monitor writability of the file descriptor.
	- EVENT_RW: Set to monitor both readability and writability of the file descriptor.



Example:

```cpp
#include "monitors.hpp"

IMonitor* monitor = new Poller();

// Add file descriptor to monitor
monitor->push(fd, EVENT_READ);
// Remove file descriptor from monitor
monitor->pop(fd);

// Wait for events on monitored fds
monitor->wait(timeout_in_sec);

// Check if file descriptor is readable
if (monitor->is_readable(fd)) {
    // Perform read operation
}
// Check if file descriptor is writeable
if (monitor->is_writeable(fd)) {
    // Perform read operation
}
````
