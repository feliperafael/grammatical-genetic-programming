#include "SimpleIndividuoBuilder.h"

SimpleIndividuoBuilder::SimpleIndividuoBuilder() {
    //ctor
}

Subject * SimpleIndividuoBuilder::generateIndividuo(){
	return new SimpleIndividuo(true);
}
string SimpleIndividuoBuilder::nameIndividuo(){
	return "SimpleIndividuo";
}

SimpleIndividuoBuilder::~SimpleIndividuoBuilder() {
    //dtor
}
