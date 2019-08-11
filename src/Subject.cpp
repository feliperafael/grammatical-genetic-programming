#include "Subject.h"

Subject::Subject() {
    fitness = INFINITY;
    fitnessTest = INFINITY;
    fitnessValidation = INFINITY;
}

void Subject::addTree(Tree* t) {
    trees.push_back(t);
}

Subject::~Subject() {
    for(Tree* t : trees)
        delete t;
    trees.clear();
}
