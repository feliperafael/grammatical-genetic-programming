#ifndef GENERATIONS_H
#define GENERATIONS_H
#include "StopCriterion.h"

class Generations : public StopCriterion {
  public:
    Generations(int maxGenerations);
    bool Checks();
    void Update();
    virtual ~Generations();

  protected:

  private:
    int generation;
    int maxGenerations;
};

#endif // GENERATIONS_H
