#ifndef BPSOLVER_BSP_PROBLEM_DATA_INTERFACE_H_
#define BPSOLVER_BSP_PROBLEM_DATA_INTERFACE_H_

#include "base/ProblemDataInterface.h"

class BSPProblemData : public ProblemDataInterface {
 public:
  BSPProblemData();
  explicit BSPProblemData(FILE* ptr_file);
  explicit BSPProblemData(string file_name);
  explicit BSPProblemData(BSPProblemData* problem_data);
  virtual ~ProblemDataInterface() {}

  virtual void LoadData(FILE* ptr_file);
  virtual void WriteInstanceData(FILE* ptr_file);

 private:
  // void InternalMethod();

  string file_name       // Name of the file containing problem data
  int num_parkings;      // Number of bike parkings available
  int num_vehicles;      // Number of vehicles available to redistribute bikes
  int vechicle_capacity  // Capacity of each vechicle
  // etc
};


#endif