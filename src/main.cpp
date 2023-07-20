#include <iostream>
#include "Database.h"
#include "Grammar.h"
#include "config/Configures.h"
#include "Search.h"
#include "parsers/SimpleParser.h"
#include "parsers/SimpleRegressionParser.h"
#include "individuals/IndividuoBuilder.h"
#include "individuals/Subject.h"
#include <omp.h>
#include "../utils/pugixml-1.9/src/pugixml.hpp"
#include <string>
#include <sstream>
#include "ILogger.h"

using namespace std;


#define simpleParser
Configures * set_configs(char * config_file);

int main(int argc, char** argv) {
    ILogger::getInstance()->log("Programação Genética UFJF iniciada");
    cout << "Hello GP-ufjf!" << endl;
    conf = set_configs(argv[1]);
    

    grammar = new Grammar(conf->grammar_file); //

    conf->numTree = 1; //Database::getInstance().prediction; // seta o numero de variaveis a serem preditas. dependente do problema a ser tratado

    double** dados_treino = Database::getInstance().values;
    //Database::getInstance().print();

    IndividuoBuilder * individuoBuilder = NULL;
    /// Setting parser
    SimpleRegressionParser * parser = new SimpleRegressionParser();
    SimpleRegressionParser * parserTest = new SimpleRegressionParser();
    SimpleRegressionParser * parserValidation = new SimpleRegressionParser();
    individuoBuilder = new SimpleIndividuoBuilder();

    
    parser->setDataSet(Database::getInstance().training,Database::getInstance().totalTraining);
    
    parserTest->setDataSet(Database::getInstance().test,Database::getInstance().totalTest);
    
    parserValidation->setDataSet(Database::getInstance().validation,Database::getInstance().totalValidation);
   
    Search* s = new Search(parser, NULL, individuoBuilder);
    s->printParameters();

    s->setParserTest(parserTest);
    s->setParserValidation(parserValidation);

    Subject ** population = s->evolve();
    Subject * best = population[0];
    best->print();
    cout << "fit " << best->fitness << endl;
    ILogger::getInstance()->log("PGUFJF terminada");
    // frees
    delete s;
    delete parser;

    return 0;
}

Configures * set_configs(char * config_file) {

    Configures * conf = Configures::getInstance();
    pugi::xml_document doc;
    pugi::xml_node config;
    pugi::xml_node operators_rate;
    pugi::xml_node gp_search;
    pugi::xml_node model;
    pugi::xml_node input;

    pugi::xml_parse_result result = doc.load_file(config_file);
    config = doc.child("genetic_programming").child("config");
    operators_rate = config.child("operators_rate");
    gp_search = config.child("search");
    model = config.child("model");
    input = doc.child("genetic_programming").child("input");


    conf->mutationRate = operators_rate.attribute("mutation").as_float();
    conf->crossoverRate = operators_rate.attribute("crossover").as_float();
    conf->elitism = operators_rate.attribute("elitism").as_float();
    conf->popSize =  gp_search.attribute("population").as_int();
    conf->generations =  gp_search.attribute("generation").as_int();
    conf->MAXDEEP =  model.attribute("maxdeep").as_int();

    srand(config.child("seed").attribute("value").as_int()); //seed

    conf->NUM_THREADS = config.child("num_threads").attribute("value").as_int();

    Database& data = Database::getInstance();
   
    data.loadBase(input.child("data").attribute("file").as_string());
    data.loadGroup(input.child("datagroup").attribute("file").as_string());


    conf->grammar_file = input.child("grammatic").attribute("file").as_string();

    return conf;

}
