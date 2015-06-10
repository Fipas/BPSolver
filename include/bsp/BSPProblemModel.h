#ifndef BPSOLVER_BSP_PROBLEM_MODEL_H_
#define BPSOLVER_BSP_PROBLEM_MODEL_H_

#include <ilcplex/ilocplex.h>
#include "base/ProblemModelInterface.h"

class BSPProblemModel : public ProblemModelInterface {
 public:
  explicit BSPProblemModel(ProblemDataInterface* problem_data);
  virtual ~BSPProblemModel() {}

  virtual void SetModelData();
  virtual void Optmize();
  virtual void GetReducedCost();
  virtual bool IsIntegerSolution();
  virtual void KillNonBasicColumns();
  virtual void AddColumn(ColumnInterface* new_column);

 private:
  void GenerateInitialBase();

  IloModel model_;
  ProblemDataInterface* problem_data_;
};

#endif