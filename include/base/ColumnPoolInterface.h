#ifndef BPSOLVER_BASE_COLUMN_POOL_INTERFACE_H_
#define BPSOLVER_BASE_COLUMN_POOL_INTERFACE_H_


class ProblemModelInterface {
 public:
  virtual ~ColumnPoolInterface() {}

  virtual void SetModelData(ProblemDataInterface *problem_model) = 0;
  virtual void Optmize() = 0;
  virtual void GetReducedCost() = 0;
  virtual bool IsIntegerSolution() = 0;
  virtual void KillNonBasicColumns() = 0;
  virtual void CopyColumn(ColumnInterface *new_column) = 0;
};

#endif