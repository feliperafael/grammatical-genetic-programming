#include "Search.h"
#include <vector>
#include <fstream>
#include <iomanip> //setprecision

/**
* Construtores da função de busca
*   Recebem todos os parametros relativos a busca
*   Parameters
*       Parser - responsavel por avaliar os individuos
*       PopulationReplace - reponsavel pela substituição da população para a proxima geração
*       IndividuoBuilder - responsavel pela criação de individuos
*       Mutation - Operador de mutação
*       Crossover - Operador genetico de mutação
*       Selection - Operador de seleção de indivudos
**/
Search::Search() {
    setParser(NULL);
    setPopulationReplace(NULL);
    setIndividuoBuilder(NULL);
    setMutation(NULL);
    setCrossover(NULL);
    setSelection(NULL);
}


Search::Search(Parser* parser,PopulationReplacement * populationreplace, IndividuoBuilder * individuobuilder, StopCriterion * stopCriterion) {
    setParser(parser);
    setPopulationReplace(populationreplace);
    setIndividuoBuilder(individuobuilder);
    setStopCriterion(stopCriterion);
    setMutation(NULL);
    setCrossover(NULL);
    setSelection(NULL);
}

/**
    Função privada que instancia e preenche a população inicial de individuos
**/
void Search::createsInitialPopulation() {
    ILogger::getInstance()->log("Criando população inicial");
    //    cout << "Create Initial Population..." << endl;
    pop = new Subject*[conf->popSize * 2];

    // #pragma omp parallel for num_threads(conf->NUM_THREADS)
    for(int i = 0; i < conf->popSize; i++) {
        pop[i] = individuoBuilder->generateIndividuo();
    }
}
//Substitui todos os valores constantes por _c_
void Search::replaceAllConst(int initialIndex, int finalIndex) {
    //#pragma omp parallel for num_threads(conf->NUM_THREADS)
    for(int i = initialIndex; i < finalIndex; i++) {
        //if(!pop[i]->optimized) {
        pop[i]->trees[0]->replaceAllConst();
        //}
    }
}

/**
*
*   Realiza a busca atravez do processo evolutivo
*   @return void
**/
Subject ** Search::evolve() {

    this->createsInitialPopulation();

    EvaluatePopulation(0, conf->popSize);

    stable_sort(pop, pop + conf->popSize, SortPopulationFitness);

    //enquanto o criterio de parada não for satisfeito
    while(!stopCriterion->Checks()) {

        Operate();

        EvaluatePopulation(conf->popSize, conf->popSize * 2);

        replacer->Replace(pop);

        stopCriterion->Update();
    }

    return pop;
}


/**
    Parameters
        int initialIndex - indice inicial a ser avaliado
        int finalIndex - indice final a pop sera avaliada até o finalIndex -1
    Percorre o vetor pop (população) avaliando os individuos do indice initialIndex até finalIndex
    @return void
**/
void Search::EvaluatePopulation(int initialIndex, int finalIndex, int optimizeRange) {
    ILogger::getInstance()->log("Avaliando população");
    #pragma omp parallel for num_threads(conf->NUM_THREADS)
    for(int i = initialIndex; i < finalIndex; i++) {
        pop[i]->fitness = parser->Evaluate(pop[i]);
    }

}

void Search::EvaluatePopulationValidation(int initialIndex, int finalIndex, int optimizeRange) {
    #pragma omp parallel for num_threads(conf->NUM_THREADS)
    for(int i = initialIndex; i < finalIndex; i++) {
        pop[i]->fitness = parser->Evaluate(pop[i]);
    }
}

/**
    Aplica os operadores genéticos de mutação e cruzamento
    @return void
**/
void Search::Operate() {
    int num_individuos = seletor->tam_selection;
    Subject ** selecionados;

    //#pragma omp parallel for private(selecionados)
    for(int i = conf->popSize; i < conf->popSize * 2; i += num_individuos) {

        selecionados = new Subject*[num_individuos];

        for(int j = 0; j < num_individuos; j++) {
            selecionados[j] = seletor->selects(pop)->clone();
            pop[i+j] = selecionados[j];
        }

        crossoverOperator->cross(selecionados,num_individuos);

        for(int j = 0; j < num_individuos; j++) {
            mutationOperator->mutate(selecionados[j]);
        }

        for(int j = 0; j < num_individuos; j++) {
            selecionados[j] = NULL;
        }
        delete selecionados;
    }

}

/**
    Set Parameters
**/
void Search::setParser(Parser * parser) {
    if(parser==NULL) {
        SimpleParser * avaliador  = new SimpleParser();
        avaliador->setDataSet(data->training,data->totalTraining);
        this->parser = avaliador;
    } else {
        this->parser = parser;
    }
}

void Search::setPopulationReplace(PopulationReplacement * popReplace) {
    if(popReplace == NULL) {
        this->replacer = new SimpleReplace();
    } else {
        this->replacer = popReplace;
    }
}

void Search::setIndividuoBuilder(IndividuoBuilder * indBuilder) {
    if(indBuilder == NULL) {
        this->individuoBuilder = new SimpleIndividuoBuilder();
    } else {
        this->individuoBuilder = indBuilder;
    }
}

void Search::setMutation(Mutation * opMutation) {
    if(opMutation==NULL) {
        mutationOperator = new SimpleMutation();
    } else {
        mutationOperator = opMutation;
    }
}

void Search::setCrossover(Crossover * opCrossover) {
    if(opCrossover==NULL) {
        crossoverOperator = new SimpleCrossover();
    } else {
        crossoverOperator = opCrossover;
    }
}

void Search::setSelection(Selection * seletor) {
    if(seletor==NULL) {
        this->seletor = new TournamentSelection();
    } else {
        this->seletor = seletor;
    }
}

void Search::setStopCriterion(StopCriterion * stopCriterion) {
    if(stopCriterion == NULL) {
        this->stopCriterion = new Generations(conf->generations);
    } else {
        this->stopCriterion = stopCriterion;
    }
}

/** Print Functions **/
void Search::printParameters() {
    cout << endl;
    cout << "************* PARAMETERS **************" << endl;
    cout << "*   GENERATIONS    " << conf->generations << endl;
    cout << "*   POP SIZE       " << conf->popSize << endl;
    cout << "*   ELITISM        " << conf->elitism << endl;
    cout << "*   MAXDEEP        " << conf->MAXDEEP << endl;
    cout << "*   CROSSOVER RATE " << conf->crossoverRate << endl;
    cout << "*   MUTATION RATE  " << conf->mutationRate << endl;
    cout << "*   INDIVIDUO      " << individuoBuilder->nameIndividuo() << endl;
    cout << "*   PARSER         " << parser->nameParser() << endl;
    cout << "***************************************" << endl << endl;
}

void Search::printResult() {
    cout << "--------------Results--------------" << endl;
    pop[0]->print();

    parser->printResult(pop[0]);

    parserValidation->printResult(pop[0]);

    parserTest->printResult(pop[0]);
}

void Search::printBestIndividuo() {

    pop[0]->print();
    cout << endl;
}

bool Search::SortPopulationFitness(Subject* a, Subject* b) {
    //cout << "FITNESS: " << a->trees[0]->fitness << " - " << b->trees[0]->fitness << endl;
    return a->trees[0]->fitness < b->trees[0]->fitness;
}
bool Search::SortPopulationFitnessValidation(Subject* a, Subject* b) {
    return a->fitnessValidation < b->fitnessValidation;
}

void Search::setParserTest(Parser * p) {
    parserTest = p;
}
void Search::setParserValidation(Parser * p) {
    parserValidation = p;
}

Search::~Search() {
    //dtor
    for(int i = 0; i < conf->popSize; i++) {
        delete pop[i];
    }
}
