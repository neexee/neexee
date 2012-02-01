#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h> //for in_addr_t
#include <netdb.h> //for gethostbyname
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <cstring> // need to memset
#include <cstdlib>
#include <cstdio>
#include <errno.h>

#include "../debug/debug.h"
#include "socket.h"



namespace /* Constants */
{
    /* socket() const */
    const int SOCKET_DOMAIN = AF_LOCAL;   // local
    const int SOCKET_TYPE = SOCK_STREAM; /*
                                          * sequenced, reliable, two-way,
                                          * connection-based byte stream
                                          */
    const int SOCKET_PROTOCOL = 0;       // operating system choose most approproate protocol

    /* listen() const */
    const int LISTEN_BACKLOG = 50;       /*
                                          * limit  the number of outstanding
                                          * connections in the socket's listen queue
                                          */
    /* read() const */
    const int BUFFER_SIZE = 100000;        // size of reading buffer
}

namespace socket_local
{
    using std::string;
    using std::runtime_error;
    using std::stringstream;

    socket_t::socket_t ()
    {
        recv_counter = 0;
        socket_fd = socket (SOCKET_DOMAIN, SOCKET_TYPE, SOCKET_PROTOCOL);
        check_error(socket_fd);
    }

    socket_t::socket_t (const int _socket, struct sockaddr* _socket_addr):
        socket_fd(_socket),
        socket_addr(_socket_addr)
    {}

    socket_t::~socket_t ()
    {

    }

    void socket_t::close ()
    {
        if (socket_fd >= 0) //if socket is valid
        {
            ::close (socket_fd);
        }
    }

    void socket_t::bind (const char* socket_name)
    {
        // Prepare sockaddr
        struct sockaddr_un _socket_addr;
        memset(&_socket_addr, 0, sizeof(_socket_addr));

        _socket_addr.sun_family = AF_LOCAL;
       // _socket_addr.sin_addr.s_addr = get_host(host);
        //_socket_addr.sin_port = htons(port);
        strcpy( _socket_addr.sun_path, socket_name );
        socket_addr = reinterpret_cast<struct sockaddr*>(&_socket_addr);

        int error = 0; 
        error = ::bind(socket_fd, socket_addr, sizeof(_socket_addr));

        check_error(error);
    }

    void socket_t::listen () const
    {
        check_error(::listen(socket_fd, LISTEN_BACKLOG));
    }

    socket_t socket_t::accept() const
    {
        struct sockaddr_un _new_socket_addr;
        memset(&_new_socket_addr, 0, sizeof(_new_socket_addr));
        struct sockaddr* new_socket_addr = reinterpret_cast<struct sockaddr*>(&_new_socket_addr);

        int new_socket_fd;
        int new_socket_len = sizeof(_new_socket_addr);

        new_socket_fd = ::accept(socket_fd, new_socket_addr, reinterpret_cast<socklen_t*>(&new_socket_len));
        check_error(new_socket_fd);

        return socket_t(new_socket_fd, new_socket_addr);
    }
    void socket_t::connect(const char* host, const int port)
    {
        struct sockaddr_un _socket_addr;
        memset(&_socket_addr, 0, sizeof(_socket_addr));

        _socket_addr.sun_family = AF_LOCAL;
       // _socket_addr.sin_addr.s_addr = get_host(host);
       // _socket_addr.sin_port = htons(port);
        socket_addr = reinterpret_cast<struct sockaddr*>(&_socket_addr);

        int error = 0;
        error = ::connect(socket_fd, socket_addr, sizeof(_socket_addr));

        check_error(error);
    }

    void socket_t::check_error (const int error) const
    {
        if (error < 0)
        {
            throw runtime_error(strerror(errno));
        }
    }

    in_addr_t socket_t::get_host(const char* host_name)
    {
        struct hostent* host = gethostbyname(host_name);
        if(host == 0)
        {
            return inet_addr(host_name);
        }
        return inet_addr(inet_ntoa(*((struct in_addr *)host->h_addr)));
    }

    int socket_t::get_socket () const
    {
        return socket_fd;
    }

    void socket_t::send (const char* message, const int size)
    {
        int length = 0;
        int shift = 0;

        while(size - shift != 0)
        {
            length = ::send(socket_fd, message + shift, size - shift, MSG_NOSIGNAL);
            check_error(length);
            shift += length;
        }
    }

    bool socket_t::get(char*& buffer, int& size, const bool check_end_symbols)
    {
        buffer = NULL;
        size = 0;
        int length = 0;

        fd_set set;
        FD_ZERO(&set);
        FD_SET(socket_fd, &set);
        select(socket_fd + 1, &set, NULL, NULL, NULL);
        if(FD_ISSET(socket_fd, &set))
        {
            char* tmp = new char[BUFFER_SIZE];
            length = ::read(socket_fd, tmp, BUFFER_SIZE);
            try
            {
                check_error(length);
            }
            catch(...)
            {
                delete[] tmp;
                throw;
            }
            if(length == 0) //End of message
            {
                delete[] tmp;
                return true;
            }

            size = length;
            if(check_end_symbols)
            {
                buffer = new char[length + 1];
                buffer[length] = 0;
                size++;
            }
            else
            {
                buffer = new char[length];
            }
            std::copy(tmp, tmp + length, buffer);
            delete[] tmp;
        }
        return false;
    }

    socket_t socket_t::operator= (const socket_t& another_socket)
    {
        if(&another_socket == this)
        {
            return *this;
        }

        close();
        socket_fd = another_socket.get_socket();
        return *this;
    }
} /* socket */
