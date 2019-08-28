#ifndef STOPCRITERION_H
#define STOPCRITERION_H


class StopCriterion {
  public:
    StopCriterion();
    virtual bool Checks() = 0;
    virtual void Update() = 0;
    virtual ~StopCriterion();

  protected:

  private:
};

#endif // STOPCRITERION_H
