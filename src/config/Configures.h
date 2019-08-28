#ifndef CONFIGURES_INCLUDED
#define CONFIGURES_INCLUDED
#include <stdlib.h>
#include <time.h>       /* time */
#include <omp.h>
#include <string>
#include "../Grammar.h"

#define NONTERMINAL -1
#define ERROR -2


#define simpleParser


class Configures {
  private:
    static Configures* instance;
    Configures();

  public:
    static Configures* getInstance();

    int MAXDEEP;
    int popSize;
    int generations;
    double elitism;
    double mutationRate;
    double crossoverRate;
    int numTree;
    int NUM_THREADS = 1;   

    short constant,variable,bynaryArithmeticOperators,unaryArithmeticOperators,
          binaryLogicalOperators,unaryLogicalOperators,comparisonOperators, leastSquareOperator,
          programOperators, adjustedCoeficient;

    double wall_timer;
    std::string grammar_file;
};

extern Configures* conf;

#endif // CONFIGURES_INCLUDED

