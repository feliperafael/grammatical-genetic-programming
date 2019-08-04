#include "SimpleReplace.h"

SimpleReplace::SimpleReplace() {

}
void SimpleReplace::Replace(Subject **pop) {

    stable_sort(pop + conf->popSize, pop + conf->popSize * 2, SortMyPop);
    for(int i = conf->popSize * conf->elitism, j = 0; i < conf->popSize; i++, j++) {
        swap(pop[i], pop[conf->popSize + j]);
    }
    stable_sort(pop, pop + conf->popSize, SortMyPop);

    for(int i = conf->popSize; i < conf->popSize * 2; i++) {
        delete pop[i];
    }
}

SimpleReplace::~SimpleReplace() {

}
