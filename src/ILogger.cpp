#include "ILogger.h"

using namespace std;

/* Null, because instance will be initialized on demand. */
ILogger* ILogger::instance = 0;

ILogger* ILogger::getInstance() {
    if (instance == 0) {
        instance = new ILogger();
    }

    return instance;
}

ILogger::ILogger() {
    //ctor
    logFile.open("log.txt");
}

void ILogger::log(string mensage) {
    time_t now = time(0);  // current date/time based on current system

    char* dt = ctime(&now); // convert now to string form

    logFile << dt <<  mensage << std::endl;
}

ILogger::~ILogger() {
    //dtor
    //this->logFile.close();
}
