#include "SimpleClassifierParser.h"

SimpleClassifierParser::SimpleClassifierParser() {
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            confusion_matrix[i][j] = 0;
        }
    }
}

string SimpleClassifierParser::nameParser() {
    return "SimpleClassifierParser";
}

void SimpleClassifierParser::Optimize(Subject* s) {

}

void SimpleClassifierParser::setDataSet(double ** x,int tam) {
    tamDataset = tam;
    dataset = x;
}

void SimpleClassifierParser::printResult(Subject * s) {}

void SimpleClassifierParser::print_confusion_tree(){
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

void SimpleClassifierParser::class_distribution(){
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

double SimpleClassifierParser::Evaluate(Subject * s) {
    dynamic_cast<SimpleIndividuo*>(s)->erros=0;
    dynamic_cast<SimpleIndividuo*>(s)->acertos=0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            confusion_matrix[i][j] = 0;
        }
    }
    ofstream confusion_matrix_file(".tmp/evolve_log_confusion_matrix.txt");

    double totalFit = 0, fit, r;
    for(int arvore = 0; arvore < conf->numTree; arvore++) {
        s->trees[arvore]->fitness = 0;
        fit = 0;
        for(int j = 0; j <tamDataset; j++) { // para todos os dados do conjunto de treinamento
            r = AuxEvaluate(s,arvore + 1,dataset[j]);
            if(std::isinf(r) || std::isnan(r)) {
                s->trees[arvore]->fitness = INFINITY;
                cout << "isinf ou isnan in simpleClassifierParser" << endl;
                break;
            }

            if(r != dataset[j][data->variables + arvore]) { // errou
                fit += 1;
                dynamic_cast<SimpleIndividuo*>(s)->erros+=1;
                if(r == 0 && dataset[j][data->variables + arvore] == 1){
                     fit+=0.86;
                     fit+=1;
                    confusion_matrix[0][1] += 1; // falso negativo
                }else{
                    confusion_matrix[1][0] += 1; // falso positivo
                }
            } else {
                if(r == 0){
                    confusion_matrix[0][0] += 1; // verdadeiro negativo
                }else{
                    confusion_matrix[1][1] += 1; // verdadeiro positivo
                }
               dynamic_cast<SimpleIndividuo*>(s)->acertos +=1;
            }
        }
        s->trees[arvore]->fitness = fit;
        totalFit += fit;
    }
    confusion_matrix_file << confusion_matrix[0][0] << "," << confusion_matrix[0][1] ;
    confusion_matrix_file << confusion_matrix[1][0] << "," << confusion_matrix[1][1] << endl;
    return totalFit;
}

double SimpleClassifierParser::Operate(int opType, int opValue, double a, double b, double c) {
    double r;
    if(opType == conf->bynaryArithmeticOperators) {
        if(opValue == 0)
            r = a + b;
        else if(opValue == 1)
            r = a - b;
        else if(opValue == 2)
            r = a * b;
        else if(opValue == 3)
            r = a / b;
        else if(opValue == 4)
            r = pow(a, b);
    } else if(opType == conf->unaryArithmeticOperators) {
        if(opValue == 0)
            r = log(a);
        else if(opValue == 1)
            r = exp(a);
        else if(opValue == 2)
            r = sqrt(a);
        else if(opValue == 3)
            r = cos(a);
        else if(opValue == 4)
            r = sin(a);
        else if(opValue == 5)
            r = tan(a);
        else if(opValue == 6)
            r = acos(a);
        else if(opValue == 7)
            r = asin(a);
        else if(opValue == 8)
            r = atan(a);
    } else if(opType == conf->binaryLogicalOperators) {
        if(opValue == 0)
            r = a && b;
        else if(opValue == 1)
            r = a || b;
        else if(opValue == 2)
            r = bool(a) ^ bool(b);
    } else if(opType == conf->unaryLogicalOperators) {
        if(opValue == 0)
            r = !bool(a);
        else if(opValue == 1)
            r = 1;
        else if(opValue == 2)
            r = 0;
    } else if(opType == conf->comparisonOperators) {
        if(opValue == 0)
            r = a < b;
        else if(opValue == 1)
            r = a <= b;
        else if(opValue == 2)
            r = a == b;
        else if(opValue == 3)
            r = a >= b;
        else if(opValue == 4)
            r = a > b;
        else if(opValue == 5)
            r = a != b;
    } else if(opType == conf->programOperators) {
        if(opValue == 0) { // if-else
            if(c)
                r = a;
            else
                r = b;
        }
    }

    if(std::isnan(r) || std::isinf(r)) {
        return -9999;
    }
    return r;
}

double SimpleClassifierParser::AuxEvaluate(Subject* s, int model, double* dat) {
    SimpleIndividuo * s1 = dynamic_cast<SimpleIndividuo*>(s);
    int coeficientCount = 0;
    stack<double> stk;
    for(tuple<double, double> t : s->trees[model - 1]->linearModel) { // -1 because model is the n-1 tree of s and n y ou fn(x)
        int var = (int)get<0>(t);
        if( var == conf->constant ) { // constant
            stk.push(get<1>(t));
        } else if( var == conf->variable ) { // variable;
            stk.push(dat[(int)get<1>(t)]);
        } else if( var == conf->bynaryArithmeticOperators) { // bynaryArithmeticOperators
            double b = stk.top();
            stk.pop();
            double a = stk.top();
            stk.pop();
            stk.push(Operate(get<0>(t), get<1>(t), a, b));
        } else if( var ==  conf->unaryArithmeticOperators) { // unaryArithmeticOperators
            double a = stk.top();
            stk.pop();
            stk.push(Operate(get<0>(t), get<1>(t), a));
        } else if( var == conf->binaryLogicalOperators) { // binaryLogicalOperators
            double b = stk.top();
            stk.pop();
            double a = stk.top();
            stk.pop();
            stk.push(Operate(get<0>(t), get<1>(t), a, b));
        } else if( var == conf->unaryLogicalOperators) { // unaryLogicalOperators
            double a = stk.top();
            stk.pop();
            stk.push(Operate(get<0>(t), get<1>(t), a));
        } else if( var == conf->comparisonOperators) { // comparisonOperators
            double b = stk.top();
            stk.pop();
            double a = stk.top();
            stk.pop();
            stk.push(Operate(get<0>(t), get<1>(t), a, b));
        } else if( var == conf->programOperators) {
            if((int)get<1>(t) == 0) { //if-selse
                double bool_ = stk.top();
                stk.pop();
                double b = stk.top();
                stk.pop();
                double a = stk.top();
                stk.pop();
                stk.push(Operate(get<0>(t), get<1>(t), a, b, bool_));
            }
            //programOperators
        } else if( var == conf->adjustedCoeficient ) { // constant
//            cout << "   " << coeficientCount << endl;
            if(s1->constants != NULL)
                stk.push(s1->constants[model - 1][coeficientCount]);
            else
                stk.push(1);
            coeficientCount++;
        }

    }

    return stk.top();
}

SimpleClassifierParser::~SimpleClassifierParser() {
    //dtor
}


