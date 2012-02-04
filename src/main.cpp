#include "bot.h"
#include <unistd.h>
#include <stdio.h>
#define DEFAULT_CONFNAME "config"
int main( int argc, char* argv[] )
    {
        Settings  settings;
        char options[] = "f::";  /* valid options */
        if(argc < 2)
         {   
             std::cout<<"Picked up settings\n ";
             settings.get("config");
         }
        else
         {   char c; 
             while ((c = getopt(argc, argv, options)) != EOF)
              {
                  switch (c)
                  {
                      case 'f':
                          settings.get(std::string(optarg));
                          std::cout<<"Picked up settings from"<< optarg<< std::endl;
                          break;
                      default :
                          std::cout<<"Unknown argument: "<< c << std::endl;
                          break;
                  }
              }
         }
        bot::bot_t b(settings);
        b.connect();
      return 0;  
    }
