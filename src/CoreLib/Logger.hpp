#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

#define printError(msg) _printError(msg, __LINE__, __FILE__, __PRETTY_FUNCTION__)

enum class Lol;

static void _printError(char* msg, int line, char* file, const char* func_name) {
    std::cout << "Error in '" << func_name << "'msg:\"" << msg << "\" from \n"; 
    std::cout << file << ':' << line << '\n';
}

#endif