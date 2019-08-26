#ifndef PARSER_H
#include "../config/Configures.h"
#define PARSER_H

#include "../individuals/Subject.h"
#include <string>

class Parser {
  public:
    Parser();
    virtual double Evaluate(Subject* s) = 0;
    virtual void Optimize(Subject* s) = 0;
    virtual string nameParser() = 0;
    virtual void printResult(Subject * s) = 0;
    ~Parser();
  protected:
  private:

};

//extern Parser* parser;

#endif // PARSER_H
