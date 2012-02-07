#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring> // need to memset
#include <cstdlib>
#include <cstdio>
#include <errno.h>

#include "../debug/debug.h"
#include "socket.h"



namespace 
{
    const int LISTEN_BACKLOG = 50;
    const int BUFFER_SIZE = 10000;        // size of reading buffer
}

namespace socket_local
{
    using std::string;
    using std::runtime_error;
    using std::stringstream;

    socket_t::socket_t ()
    {
        recv_counter = 0;
        socket_fd = socket (AF_LOCAL, SOCK_STREAM, 0);
        check_error(socket_fd);
    }

    socket_t::socket_t (const int _socket, struct sockaddr* _socket_addr):
        socket_fd(_socket),
        socket_addr(_socket_addr)
    {}
    socket_t::socket_t(int _socket_fd)
    {
        check_error(_socket_fd);
        socket_fd = _socket_fd;
    }
    socket_t::~socket_t ()
    {}

 void socket_t::unlink()
    {
        ::unlink(path);
    }

    void socket_t::close ()
    {
        if (socket_fd >= 0)
        {
            ::close (socket_fd);
        }
    }

    void socket_t::bind (const char* socket_name)
    {
        struct sockaddr_un _socket_addr;
        memset(&_socket_addr, 0, sizeof(_socket_addr));

        _socket_addr.sun_family = AF_LOCAL;
        strcpy( _socket_addr.sun_path, socket_name );
        socket_addr = reinterpret_cast<struct sockaddr*>(&_socket_addr);

        int error = 0; 
        error = ::bind(socket_fd, socket_addr, sizeof(_socket_addr));
        check_error(error);
        path  = socket_name;
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

    void socket_t::connect(const char* socket_name)
    {
        struct sockaddr_un _socket_addr;
        memset(&_socket_addr, 0, sizeof(_socket_addr));

        _socket_addr.sun_family = AF_LOCAL;
        strcpy(_socket_addr.sun_path, socket_name);
        socket_addr = reinterpret_cast<struct sockaddr*>(&_socket_addr);

        int error = 0;
        error = ::connect(socket_fd, socket_addr, sizeof(_socket_addr));
         INFO("Connecting");
        check_error(error);
    }

    void socket_t::check_error (const int error) const
    {
        if (error < 0)
        {
            throw runtime_error(strerror(errno));
        }
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


} /* socket */
