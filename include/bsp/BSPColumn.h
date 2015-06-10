#ifndef BPSOLVER_BSP_COLUMN_H_
#define BPSOLVER_BSP_COLUMN_H_

#include <ilcplex/ilocplex.h>
#include "base/ColumnGeneratorInterface.h"
#include "base/ColumnInterface.h"

class BSPColumn : public ColumnInterface {
 public:
 	BSPColumn();
  virtual ~BSPColumn() {}

 private:

};

#endif