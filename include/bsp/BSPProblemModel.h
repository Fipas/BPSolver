#ifndef BPSOLVER_BSP_PROBLEM_MODEL_INTERFACE_H_
#define BPSOLVER_BSP_PROBLEM_MODEL_INTERFACE_H_

#include <ilcplex/ilocplex.h>
#include "base/ProblemModelInterface.h"

class BSPProblemModel : public ProblemModelInterface {
 public:
 	BSPProblemModel();
  explicit BSPProblemModel(ProblemDataInterface* problem_data);
  virtual ~BSPProblemModel() {}

  virtual void SetModelData(ProblemDataInterface* problem_data);
  virtual void Optmize();
  virtual void GetReducedCost();
  virtual bool IsIntegerSolution();
  virtual void KillNonBasicColumns();
  virtual void AddColumn(ColumnInterface* new_column);

 private:
  IloEnv env_;
  IloModel model_;
};

#endif