#ifndef BPSOLVER_BSP_RESOURCES_H_
#define BPSOLVER_BSP_RESOURCES_H_

#include <ilcplex/ilocplex.h>

class BSPResources {
 public:
 	static const IloEnv kEnv;

 private:
  BSPResources();
  virtual ~BSPResources() {}

};

#endif