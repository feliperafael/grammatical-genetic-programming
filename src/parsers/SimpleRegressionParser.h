#ifndef SIMPLEREGRESSIONPARSER_H
#define SIMPLEREGRESSIONPARSER_H

#include "../config/Configures.h"
#include "Parser.h"
#include "../individuals/SimpleIndividuo.h"
#include <vector>
#include <stack>
#include <tuple>
#include <cmath>

class SimpleRegressionParser : public Parser {
  public:
    SimpleRegressionParser();
    virtual string nameParser();
    virtual double Evaluate(Subject* s);
    virtual void Optimize(Subject* s);
    //virtual double Operate(int opType, int opValue, double a, double b = NULL, double c = NULL);
    virtual double Operate(int opType, int opValue, double a, double b = -9999, double c = -9999);


    virtual void setDataSet(double ** x,int tam);

    virtual void printResult(Subject * s);

    ~SimpleRegressionParser();
  protected:
    double** dataset;
    int tamDataset;
  private:
    double AuxEvaluate(Subject* s, int model, double* dat);
};

#endif // SIMPLEREGRESSIONPARSER_H
