#ifndef POPULATIONREPLACEMENT_H
#define POPULATIONREPLACEMENT_H

#include "../../individuals/Subject.h"
class PopulationReplacement {
  public:
    virtual void Replace(Subject **pop) = 0;
  protected:

  private:
};

#endif // POPULATIONREPLACEMENT_H
