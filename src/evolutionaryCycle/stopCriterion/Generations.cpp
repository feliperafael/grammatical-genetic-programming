#include "Generations.h"

Generations::Generations(int maxGenerations) {
    this->maxGenerations = maxGenerations;
    this->generation = 0;
}

bool Generations::Checks() {
    if( this->generation >= this->maxGenerations )
        return true;
    return false;
}

void Generations::Update() {
    this->generation++;
}

Generations::~Generations() {
    //dtor
}
