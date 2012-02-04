#ifndef __SOCKET_H
#define __SOCKET_H

/*
 * Socket wrapper
 * for AF_LOCAL
 */

#include <string>
#include <sstream>
#include <sys/un.h> 
#include <sys/types.h>
#include <sys/socket.h>
//#include <arpa/inet.h> //for in_addr_t

namespace socket_local
{
    class socket_t
    {
        public:
            socket_t (); //make socket for connect or listen
            virtual ~socket_t ();

            socket_t accept () const; //return new socket after accept
            void listen () const;
            void connect(const char* socket_name);
            void bind (const char* socke_name);
            void close();

            int get_socket () const;
            bool get(char*& buffer, int& size, const bool check_end_symbols);
            void send (const char* message, int size); //Block
            socket_t operator= (const socket_t& another_socket);
        private:
            int socket_fd;
            struct sockaddr* socket_addr;
            int recv_counter;
          
            socket_t (const int _socket, struct sockaddr* _socket_addr); //for return client socket
            void check_error(const int error) const;
    };
}

#endif // __SOCKET_H
