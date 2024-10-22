#include <util/ConsoleLog.h>

void printError(const char* message) {
    std::cout << "[\033[31mERROR\033[0m]    " << message << std::endl;
}

void printWarning(const char* message) {
    std::cout << "[\033[33mWARNING\033[0m]    " << message << std::endl;
}

void printInfo(const char* message) {
    std::cout << "[\033[34mINFO\033[0m]    " << message << std::endl;
}
void printSuccess(const char* message) {
    std::cout << "[\033[32mSUCCESS\033[0m]    " << message << std::endl;
}

void em_printError(const char* message) {
    std::cout << "[\033[31mEM_ERROR\033[0m]    " << message << std::endl;
}

void em_printWarning(const char* message) {
    std::cout << "[\033[33mEM_WARNING\033[0m]    " << message << std::endl;
}

void em_printInfo(const char* message) {
    std::cout << "[\033[34mEM_INFO\033[0m]    " << message << std::endl;
}
void em_printSuccess(const char* message) {
    std::cout << "[\033[32mEM_SUCCESS\033[0m]    " << message << std::endl;
}
