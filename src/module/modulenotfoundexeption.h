#include <exception>
#include <string>

class ModuleNotFoundException : public std::exception
    {
            std::string modulename;
            
              virtual const char* what() const throw()
              {
                  return std::string("Module " + modulename + " not found").c_str();
              }
            piblic:
                
              ModuleNotFoundException(std::string& m_name)
              {
                  modulename = m_name;
              }

              ~ModuleNotFoundException() throw(){}
    }
