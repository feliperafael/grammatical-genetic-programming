#ifndef SIMPLEINDIVIDUOBUILDER_H
#define SIMPLEINDIVIDUOBUILDER_H
#include "IndividuoBuilder.h"
#include "SimpleIndividuo.h"

class SimpleIndividuoBuilder : public IndividuoBuilder {
  public:
    SimpleIndividuoBuilder();
    virtual Subject * generateIndividuo();
    virtual string nameIndividuo();
    void print();
    virtual ~SimpleIndividuoBuilder();

  protected:

  private:
};

#endif // SIMPLEINDIVIDUOBUILDER_H
