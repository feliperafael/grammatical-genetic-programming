#ifndef SimpleClassifierParser_H
#define SimpleClassifierParser_H

#include "../config/Configures.h"
#include "Parser.h"
#include "../individuals/SimpleIndividuo.h"
#include <vector>
#include <stack>
#include <tuple>
#include <cmath>

class SimpleClassifierParser : public Parser {
  public:
    SimpleClassifierParser();
    virtual string nameParser();
    virtual double Evaluate(Subject* s);
    virtual void Optimize(Subject* s);
    virtual double Operate(int opType, int opValue, double a, double b = -9999, double c = -9999);


    virtual void setDataSet(double ** x,int tam);

    virtual void printResult(Subject * s);

    void print_confusion_tree();

    void class_distribution();

    ~SimpleClassifierParser();
    double** dataset;
    int tamDataset;
    double confusion_matrix[2][2];    // depende do numero de classes
  protected:
  private:
    double AuxEvaluate(Subject* s, int model, double* dat);
};

#endif // SimpleClassifierParser_H
