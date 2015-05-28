#ifndef BPSOLVER_BASE_PROBLEM_DATA_INTERFACE_H_
#define BPSOLVER_BASE_PROBLEM_DATA_INTERFACE_H_

class ProblemDataInterface {
 public:
  virtual ~ProblemDataInterface() {}

  virtual void LoadData() = 0;
  virtual void WriteInstanceData() = 0;
};

#endif