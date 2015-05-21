#ifndef BPSOLVER_BASE_PROBLEM_MODEL_INTERFACE_H_
#define BPSOLVER_BASE_PROBLEM_MODEL_INTERFACE_H_

#include "ProblemDataInterface.h"
#include "ColumnInterface.h"

class ProblemModelInterface {
 public:
  virtual ~ProblemModelInterface() {}

  virtual void SetModelData(ProblemDataInterface *problem_model) = 0;
  virtual void Optmize() = 0;
  virtual void GetReducedCost() = 0;
  virtual bool IsIntegerSolution() = 0;
  virtual void KillNonBasicColumns() = 0;
  virtual void AddColumn(ColumnInterface *new_column) = 0;
};

#endif