#include "TournamentSelection.h"

TournamentSelection::TournamentSelection() {
    this->tam_selection = 2;
}

Subject * TournamentSelection::selects(Subject ** pop) {
    int a = rand()%conf->popSize;
    int b = rand()%conf->popSize;

    Subject * x = pop[a];
    Subject * y = pop[b];

    return ( x->fitness > y->fitness) ? x : y ;
}

TournamentSelection::~TournamentSelection() {
    //dtor
}
