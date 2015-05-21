#ifndef BPSOLVER_BASE_COLUMN_GENERATOR_INTERFACE_H_
#define BPSOLVER_BASE_COLUMN_GENERATOR_H_

#include "ColumnInterface.h"

class ColumnGeneratorInterface {
 public:
  virtual ~ColumnGeneratorInterface() {}

  virtual ColumnInterface GenerateNewColumn() = 0;
};

#endif