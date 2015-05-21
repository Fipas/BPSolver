#ifndef BPSOLVER_BASE_PROBLEM_DATA_INTERFACE_H_
#define BPSOLVER_BASE_PROBLEM_DATA_INTERFACE_H_

class ProblemDataInterface {
 public:
  virtual ~ProblemDataInterface() {}

  virtual void LoadData(FILE* ptr_file) = 0;
  virtual void WriteInstanceData(FILE* ptr_file) = 0;
};

#endif