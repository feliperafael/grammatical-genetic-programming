#ifndef SimpleClassifierParser_H
#define SimpleClassifierParser_H

#include "Configures.h"
#include "Parser.h"
#include "SimpleIndividuo.h"
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


    virtual void setDataSet(double ** x,int tam) {
        tamDataset = tam;
        dataset = x;
    }

    virtual void printResult(Subject * s) {}

    void print_confusion_tree(){
        cout << "print_confusion_tree" << endl;
        for(int i = 0; i < 2; i++){
            cout << "|";
            for(int j = 0; j < 2; j++){
                cout << confusion_matrix[i][j] << " ";
            }
            cout << "|";
            cout << endl;
        }
    }

    void class_distribution(){
        int class_0 = 0;
        int class_1= 0;
        for(int j = 0; j <tamDataset; j++) {
            if(dataset[j][data->variables] == 0){
                class_0 +=1;
            }else{
                class_1 +=1;
            }
        }
        cout << "Class 0: " << class_0 << endl;
        cout << "Class 1: " << class_1 << endl;
        //calcula os pessoas de cada classe, para calculo de fitness
        float maior = max(class_0, class_1);
        float menor = min(class_0, class_1);
        float peso = menor/maior;
    }

    ~SimpleClassifierParser();
    double** dataset;
    int tamDataset;
    double confusion_matrix[2][2];    // depende do numero de classes
  protected:
  private:
    double AuxEvaluate(Subject* s, int model, double* dat);
};

#endif // SimpleClassifierParser_H
