#ifndef SIMPLEMUTATION_H
#define SIMPLEMUTATION_H
#include "Mutation.h"


class SimpleMutation : public Mutation {
  public:
    SimpleMutation();
    virtual void mutate(Subject * individuo);
    virtual ~SimpleMutation();

  protected:

  private:
    void auxMutate(Tree* t);
    bool checkRate(double rate);
};

#endif // SIMPLEMUTATION_H
