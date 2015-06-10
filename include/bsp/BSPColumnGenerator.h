#ifndef BPSOLVER_BSP_COLUMN_GENERATOR_H_
#define BPSOLVER_BSP_COLUMN_GENERATOR_H_

#include <ilcplex/ilocplex.h>
#include "base/ColumnGeneratorInterface.h"
#include "base/ColumnInterface.h"

class BSPColumnGenerator : public ColumnGeneratorInterface {
 public:
 	BSPColumnGenerator();
  explicit BSPColumnGenerator(ProblemDataInterface* problem_data);
  virtual ~BSPColumnGenerator() {}

  virtual ColumnInterface* GenerateFirstColumn();
  virtual ColumnInterface* GenerateNewColumn();

 private:
  IloModel model_;
  ProblemDataInterface* problem_data_;
};

#endif