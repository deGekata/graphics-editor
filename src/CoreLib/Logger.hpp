#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

#define printError(msg) _printError(msg, __LINE__, __FILE__)

static void _printError(char* msg, int line, char* file) {
    std::cout << "Error msg:\"" << msg << "\" from \n"; 
    std::cout << file << ':' << line << '\n';
}


#endif