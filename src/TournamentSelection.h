#ifndef TOURNAMENTSELECTION_H
#define TOURNAMENTSELECTION_H
#include "Selection.h"
#include "Subject.h"

class TournamentSelection : public Selection {
  public:
    TournamentSelection();
    virtual Subject * selects(Subject ** pop) {
        int a = rand()%conf->popSize;
        int b = rand()%conf->popSize;

        Subject * x = pop[a];
        Subject * y = pop[b];

        return ( x->fitness > y->fitness) ? x : y ;
    }
    virtual ~TournamentSelection();

  protected:

  private:
};

#endif // TOURNAMENTSELECTION_H
