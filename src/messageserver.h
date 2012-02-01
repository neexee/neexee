#include "named_socket/socket.h"
class MessageServer
    { 
        public:
            MessageServer();
            void start();
            ~MessageServer();
        private:
             socket_local::socket_t* server_socket;

    }
