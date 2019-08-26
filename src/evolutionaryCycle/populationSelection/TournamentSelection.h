#ifndef TOURNAMENTSELECTION_H
#define TOURNAMENTSELECTION_H
#include "Selection.h"
#include "../../individuals/Subject.h"

class TournamentSelection : public Selection {
  public:
    TournamentSelection();
    virtual Subject * selects(Subject ** pop);
    virtual ~TournamentSelection();

  protected:

  private:
};

#endif // TOURNAMENTSELECTION_H
