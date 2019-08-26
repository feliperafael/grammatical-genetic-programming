#include "SimpleMutation.h"

SimpleMutation::SimpleMutation() {
    //ctor
}

void SimpleMutation::mutate(Subject * individuo) {
    for(Tree* t : individuo->trees) {
        if(checkRate(conf->mutationRate)) {
            auxMutate(t);
        }
    }
}

bool SimpleMutation::checkRate(double rate) {
    return (rand()%100 < rate*100);
}

void SimpleMutation::auxMutate(Tree* t) {
    No* n = t->subTree();
    n->erase();
    grammar->derivate(n);
    t->update();
}

SimpleMutation::~SimpleMutation() {
    //dtor
}
