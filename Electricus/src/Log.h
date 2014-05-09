#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include "global.h"

namespace Log
{
  static void info(std::string msg) {
    std::cout << "[INFO]: " << msg << std::endl;
  }
  static void warning(std::string msg) {
    std::cout << "[WARNING]: " << msg << std::endl;
  }
  static void error(std::string msg) {
    std::cout << "[ERROR]: " << msg << std::endl;
  }
  static void fatalError(std::string msg) {
    std::cout << "[FATAL ERROR]: " << msg << std::endl;
  }
}

#endif