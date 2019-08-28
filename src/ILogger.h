#ifndef ILOGGER_H
#define ILOGGER_H
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
class ILogger {
  public:
    static ILogger* getInstance();
    void log(string mensage);
    virtual ~ILogger();

  protected:

  private:
    ofstream logFile;
    static ILogger* instance;
    ILogger();
};

#endif // ILOGGER_H
