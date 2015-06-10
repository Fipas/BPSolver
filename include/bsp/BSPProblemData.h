#ifndef BPSOLVER_BSP_PROBLEM_DATA_H_
#define BPSOLVER_BSP_PROBLEM_DATA_H_

#include <iostream>
#include <vector>
#include "base/ProblemDataInterface.h"

class BSPProblemData : public ProblemDataInterface {
 public:
  explicit BSPProblemData(std::string file_name);
  virtual ~BSPProblemData() {}

  virtual void LoadData();
  virtual void WriteInstanceData();

  int GetNumOfVertex() { return num_nodes_; }
  double GetEdgeCost(int i, int j) { return cost_[i][j]; }
  int GetVertexCapacity(int i) { return node_capacity_[i]; }
  int GetVertexInitialState(int i) { return node_initial_state_[i]; }
  int GetVertexTargetState(int i) { return node_target_state_[i]; }

 private:
  std::string file_name_;                               // Name of the file containing problem data
  int num_nodes_;                                       // Number of bike parkings available
  int vechicle_capacity_;                               // Vehicle capacity used during distribution
  // matrix<double> cost_;                              // cost_(i, j) -> cost to travel from node i to node j
  std::vector<std::pair<double, double> > node_coord_;  // Coordination pair for each node
  std::vector<std::vector<double> > cost_;              // cost[i][j] -> cost to travel from node i to node j
  std::vector<int> node_initial_state_;                 // node_initial_state_[i] -> initial number of bikes in node i
  std::vector<int> node_target_state_;                  // node_target_state_[i] -> target number of bikes in node i
  std::vector<int> node_capacity_;                      // nodes_capacity_[i] -> capacity of node i
};


#endif