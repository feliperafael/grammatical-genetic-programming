#ifndef SEARCH_H
#include "individuals/Subject.h"
#include "Grammar.h"
//#include "individuals/representations/tree/Tree.cpp"
#include "config/Configures.h"
#include "parsers/Parser.h"
#include "parsers/SimpleParser.h"
#include <cmath>
#include <algorithm>
#include <exception>
#include "evolutionaryCycle/populationSelection/Selection.h"
#include "evolutionaryCycle/populationSelection/TournamentSelection.h"
#include "evolutionaryCycle/populationReplacement/PopulationReplacement.h"
#include "evolutionaryCycle/populationReplacement/SimpleReplace.h"
#include "individuals/IndividuoBuilder.h"
#include "individuals/SimpleIndividuoBuilder.h"
#include "evolutionaryCycle/stopCriterion/StopCriterion.h"
#include "evolutionaryCycle/stopCriterion/Generations.h"
#include "operators/Mutation.h"
#include "operators/SimpleMutation.h"

#include "operators/Crossover.h"
#include "operators/SimpleCrossover.h"
#include "ILogger.h"
#include <string>

# include <omp.h>

#define SEARCH_H

class Search {
  public:
    Subject** pop;
    Subject** tmpPop;
    StopCriterion * stopCriterion;
    bool stepByStep = false;
    /**
        Tolerância de otimização. Quando o fitness não está melhorando
        pelo menos {tolerance} para duas iterações consecutivas a população é
        considera adaptada.
    **/
    double tolerance = 0.0001;// quando o fitnesse é menor que tolerance, o individuo está adaptado

    IndividuoBuilder * individuoBuilder;
    Selection * seletor;
    Parser * parser;
    Parser * parserTest;
    Parser * parserValidation;
    PopulationReplacement * replacer;
    Mutation * mutationOperator;
    Crossover * crossoverOperator;

    Search();
    Search(Parser * parser = NULL, PopulationReplacement * populationreplacement = NULL,IndividuoBuilder * individuobuilder = NULL, StopCriterion * stopCriterion = NULL);

    void Operate();
    Subject ** evolve();
    virtual ~Search();

    /** Print functions **/
    void printResult();
    void printParameters();
    void printBestIndividuo();

    /**Set GP Parameters*/
    void setCrossover(Crossover * opCrossover);
    void setMutation(Mutation * opMutation);
    void setIndividuoBuilder(IndividuoBuilder * indBuilder);
    void setPopulationReplace(PopulationReplacement * popReplace);
    void setParser(Parser * parser);
    void setSelection(Selection * seletor);
    void setStopCriterion(StopCriterion * stopCriterion);

    void setParserTest(Parser * p);
    void setParserValidation(Parser * p);

  protected:

  private:
    void replaceAllConst(int initialIndex, int finalIndex );
    void EvaluatePopulation(int initialIndex, int finalIndex, int optimizeRange = 0);
    void EvaluatePopulationValidation(int initialIndex, int finalIndex, int optimizeRange = 0);
    void DetailedEvaluatePopulation(Subject* s);
    static bool SortPopulationFitness(Subject* a, Subject* b);
    static bool SortPopulationFitnessValidation(Subject* a, Subject* b);
    void createsInitialPopulation();
};

#endif // SEARCH_H
