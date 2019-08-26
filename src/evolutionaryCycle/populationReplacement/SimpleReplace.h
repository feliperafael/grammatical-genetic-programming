#ifndef SIMPLEREPLACE_H
#define SIMPLEREPLACE_H
#include "../../individuals/Subject.h"
#include "PopulationReplacement.h"
#include "../../config/Configures.h"
#include <iostream>
#include <algorithm>// std::sort



using namespace std;
class SimpleReplace : public PopulationReplacement {
  public:
    SimpleReplace();

    virtual void Replace(Subject **pop);
    virtual ~SimpleReplace();

  protected:

  private:
    static bool SortMyPop(Subject* a, Subject* b);
};

#endif // SIMPLEREPLACE_H
