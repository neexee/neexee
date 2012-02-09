/*
 * Logging
 * Can be disable. If need, you can be define DEBUG
 * Have three levels: 0 1 2 3
 * 0: do not print anything
 * 1: print type of message and message
 * 2: print "0" and function
 * 3: print "1" and number of line
 */


#ifndef __DEBUG_H
#define __DEBUG_H

/* Colors of type of messages */
#define TYPE_INFO "\033[1;39m[INFO]\033[0m "
#define TYPE_WARNING "\033[1;33m[WARNING]\033[0m "
#define TYPE_ERROR "\033[1;31m[ERROR]\033[0m "
#ifndef DEBUG
#define INFO(message)
#define ERROR(message) (debug::print(TYPE_ERROR, (message)))
#define WARNING(message) (debug::print(TYPE_WARNING, (message)))
#elif DEBUG == 3
#define INFO(message) (debug::print(TYPE_INFO, (message), __func__, __LINE__))
#define WARNING(message) (debug::print(TYPE_WARNING, (message), __func__, __LINE__))
#define ERROR(message) (debug::print(TYPE_ERROR, (message), __func__, __LINE__))
#elif DEBUG == 2
#define INFO(message) (debug::print(TYPE_INFO, (message), __func__))
#define WARNING(message) (debug::print(TYPE_WARNING, (message), __func__))
#define ERROR(message) (debug::print(TYPE_ERROR, (message), __func__))
#elif DEBUG == 1
#define INFO(message) (debug::print(TYPE_INFO, (message)))
#define WARNING(message) (debug::print(TYPE_WARNING, (message)))
#define ERROR(message) (debug::print(TYPE_ERROR, (message)))
#elif DEBUG == 0
#define INFO(message)
#define WARNING(message)
#define ERROR(nessage)
#endif

    class debug
    {
        public:
            static void print(const char* type, const char* message, const char* func = 0, const int line = 0);
        private:
            debug ();
            virtual ~debug ();
    };

#endif //__DEBUG_H
