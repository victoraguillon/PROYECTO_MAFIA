#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <iostream>

#define RESET   "\033[0m"
#define RED     "\033[31m"    
#define GREEN  "\033[32m"      
#define YELLOW "\033[33m"      
#define BLUE   "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN   "\033[36m"      
#define BOLD    "\033[1m"   

namespace UI {
    inline void clear (){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
inline void draw_line (const std::string& line){
  std::cout << MAGENTA << "==================================================" << RESET << std::endl;
    }

    inline void header (std::string title){
        draw_line();
        std::cout << BOLD << CYAN << title << RESET << std::endl;
        draw_line();
    }
}

#endif // UTILS_H