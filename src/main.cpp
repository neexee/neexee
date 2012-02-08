#include "bot/bot.h"
#include "settings/settings.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#define DEFAULT_CONFNAME "config"
extern char* optarg;
bot::bot_t* b;
void sighandler(int sig);
int main( int argc, char* argv[] )
    {
        using settings::Settings;
        Settings  settings;
        char options[] = "f:";  /* valid options */
        signal(SIGINT, sighandler);
        if(argc < 2)
         {   
            // std::cout<<"Picked up settings ";
             settings.get("config");
         }
        else
         {   char c; 
             while ((c = getopt(argc, argv, options)) != EOF)
              {
                  switch (c)
                  {
                      case 'f':
                          //std::cout<<"Picked up settings from"<< optarg<< std::endl;
                          settings.get(std::string(optarg));
                          break;
                      default :
              //            std::cout<<"Unknown argument: "<< c << std::endl;
                          break;
                  }
              }
         }
        b = new bot::bot_t(settings);
        b->connect();
        return 0;  
    }
void sighandler(int sig)
{
   printf("%s", "BYE!\n");
   delete b;
   exit(sig);
}
