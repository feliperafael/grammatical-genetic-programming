#include <iostream>
#include "Database.h"
#include "Grammar.h"
#include "No.h"
#include "Configures.h"
#include "Search.h"
#include "SimpleParser.h"
#include "SimpleClassifierParser.h"
#include "IndividuoBuilder.h"
#include "Subject.h"
#include <omp.h>
#include "../utils/pugixml-1.9/src/pugixml.hpp"
#include <string>
#include <sstream>

using namespace std;

#define simpleParser
Configures * set_configs(char * config_file);

int main(int argc, char** argv) {

    cout << "Hello GP-ufjf!" << endl;
    conf = set_configs(argv[1]);

    grammar = new Grammar(conf->grammar_file); //


    conf->numTree = data->prediction; // seta o numero de variaveis a serem preditas. dependente do problema a ser tratado

    double** dados_treino = data->values;
    //cout << "total training " << data->totalTraining << " total test " << data->totalTest << " total validation "<< data->totalValidation << endl;

    IndividuoBuilder * individuoBuilder = NULL;
    /// Setting parser
    SimpleClassifierParser * parser = new SimpleClassifierParser();
    SimpleClassifierParser * parserTest = new SimpleClassifierParser();
    SimpleClassifierParser * parserValidation = new SimpleClassifierParser();
    individuoBuilder = new SimpleIndividuoBuilder();

    parser->setDataSet(data->training,data->totalTraining);
    parserTest->setDataSet(data->test,data->totalTest);
    parserValidation->setDataSet(data->validation,data->totalValidation);

    Search* s = new Search(parser, NULL, individuoBuilder);
    s->printParameters();

    s->setParserTest(parserTest);
    s->setParserValidation(parserValidation);

    Subject ** population = s->evolve();
    Subject * best = population[0];
    best->print();

    // frees
    delete s;
    delete parser;
    delete data;

    return 0;
}

Configures * set_configs(char * config_file){

    Configures * conf = new Configures();
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

    conf->NUM_THREADS = 3;

    data = new Database(input.child("data").attribute("file").as_string());
    data->loadGroup(input.child("datagroup").attribute("file").as_string()); // 1000.grp pra 1000, pgDE pra 50
    //data->print();
    conf->grammar_file = input.child("grammatic").attribute("file").as_string();
    //grammar = new Grammar(input.child("grammatic").attribute("file").as_string()); //
    return conf;

}
