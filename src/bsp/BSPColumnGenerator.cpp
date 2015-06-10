#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/r_c_shortest_paths.hpp>
#include "base/ProblemDataInterface.h"
#include "base/ColumnInterface.h"
#include "bsp/BSPColumnGenerator.h"
#include "bsp/BSPColumn.h"
#include "bsp/BSPProblemData.h"

using namespace boost;

struct VertexProperty {
  VertexProperty(int n = 0, int min_c = 0, int max_c = 0) 
  : num(n), min_capacity(min_c), max_capacity(max_c) {}
  int num;
  int min_capacity;
  int max_capacity;
};

struct EdgeProperty {
  EdgeProperty(int n = 0, int c = 0, int r = 0) 
  : num(n), cost(c), resource(r) {}
  int num;
  int cost;
  int resource;
};

typedef adjacency_list<vecS, 
                       vecS, 
                       directedS, 
                       VertexProperty, 
                       EdgeProperty> 
  Graph;

struct ResourceContainer {
  ResourceContainer(std::vector<int> s, std::vector<int> ts,
                     int c = 0, int r = 0) : cost( c ), resource( r ), state(s), t_state(ts) {}

  ResourceContainer& operator=(const ResourceContainer& other) {
    if(this == &other)
      return *this;
    this->~ResourceContainer();
    new(this) ResourceContainer(other);
    return *this;
  }

  int cost;
  int resource;
  std::vector<int> state;
  std::vector<int> t_state;
};

bool operator==(const ResourceContainer& res_cont_1, 
                const ResourceContainer& res_cont_2) {
  return (res_cont_1.cost == res_cont_2.cost &&
          res_cont_1.resource == res_cont_2.resource);
}

bool operator<(const ResourceContainer& res_cont_1, 
               const ResourceContainer& res_cont_2) {
  if( res_cont_1.cost > res_cont_2.cost )
    return false;
  if( res_cont_1.cost == res_cont_2.cost )
    return res_cont_1.resource < res_cont_2.resource;
  return true;
}

class ExtensionFunction {
 public:
  inline bool operator()(const Graph& g, 
                         ResourceContainer& new_cont, 
                         const ResourceContainer& old_cont, 
                         graph_traits <Graph>::edge_descriptor ed) const {
    const EdgeProperty& edge_prop = get(edge_bundle, g)[ed];
    const VertexProperty& vert_prop_t = get(vertex_bundle, g)[target( ed, g )];
    const VertexProperty& vert_prop_s = get(vertex_bundle, g)[source( ed, g )];

    new_cont.cost = old_cont.cost + edge_prop.cost;
    
    int& i_resource = new_cont.resource;
    bool ok = true;
    bool balanced = true;
    int taken = edge_prop.resource;
    int new_state_source = old_cont.state[vert_prop_s.num] - taken;
    int new_state_target = old_cont.state[vert_prop_t.num] + taken;

    // Check if new state (number of bicycles in source node) is consistent
    // i.e. no negative ammount of bicycles and beyond capacity
    if (new_state_source < vert_prop_s.min_capacity || 
        new_state_source > vert_prop_s.max_capacity) 
          ok = false;
    
    // Same thing as above, now for target node
    if (new_state_target < vert_prop_t.min_capacity ||
        new_state_target > vert_prop_t.max_capacity) 
        ok = false;

    i_resource = old_cont.resource + edge_prop.resource;

    // If some of the conditions above hold, we cannot extend
    // since we're violating some node capacity
    if (!ok) return false;
    
    // If it's ok to extend, we can exted to any node, unless
    // it is the depot. We can only go back to depot if all nodes
    // have reached balanced state
    if (vert_prop_t.num != 7) {
      new_cont.state[vert_prop_s.num] = new_state_source;
      new_cont.state[vert_prop_t.num] = new_state_target;

      std::cout << "Extending from " << vert_prop_s.num << " to " 
                << vert_prop_t.num << " taking " << taken << std::endl;
      std::cout << "Vertex states:\n";
      for (int i = 0; i < 8; i++) {
        std::cout << i << ": " << new_cont.state[i] << std::endl;
      }

      return true;
    }

    // If it's the depot, we have to check balanced state
    for (int i = 0; i < 8; i++) {
      if (new_cont.t_state[i] != new_cont.state[i]) {
        balanced = false;
        break;
      }
    }
    
    // If it's balanced, it's ok to extend to depot
    if (balanced) {
      return true;
    }

    return false;
  }
};

class DominanceFunction {
 public:
  inline bool operator()(const ResourceContainer& res_cont_1, 
                         const ResourceContainer& res_cont_2) const {
    return res_cont_1.resource <= res_cont_2.resource;
  }
};

const int num_nodes = 8;

BSPColumnGenerator::BSPColumnGenerator() {

}

BSPColumnGenerator::BSPColumnGenerator(ProblemDataInterface* problem_data) {
  problem_data_ = problem_data;
}

ColumnInterface* BSPColumnGenerator::GenerateFirstColumn() {
  Graph g;
  BSPProblemData* problem_data = dynamic_cast<BSPProblemData*>(problem_data_);
  std::vector<int> vertex_state;
  std::vector<int> vertex_target_state;

  for (int i = 0; i < problem_data->GetNumOfVertex(); i++) {
    int vertex_capacity = problem_data->GetVertexCapacity(i);
    add_vertex(VertexProperty(i, 0, vertex_capacity), g);
    vertex_state.push_back(problem_data->GetVertexInitialState(i));
    vertex_target_state.push_back(problem_data->GetVertexTargetState(i));
  }

  for (int i = 1, edge_num = 0; i < problem_data->GetNumOfVertex() - 1; i++) {
    add_edge(0, i, EdgeProperty(edge_num++, problem_data->GetEdgeCost(0, i), 0), g);
    add_edge(i, 7, EdgeProperty(edge_num++, problem_data->GetEdgeCost(i, 7), 0), g);
    for (int j = 1; j < problem_data->GetNumOfVertex() - 1; j++) {
      if (i == j) continue;

      for (int c = 0; c <= problem_data->GetVertexCapacity(i); c++) {
        int arc_cost = problem_data->GetEdgeCost(i, j);
        add_edge(i, j, EdgeProperty(edge_num++, arc_cost, c), g);
      }
    }
  }

  graph_traits<Graph>::vertex_descriptor s = 0;
  graph_traits<Graph>::vertex_descriptor t = 7;
  
  std::vector
    <std::vector
      <graph_traits<Graph>::edge_descriptor> > 
        opt_solutions;
  std::vector<ResourceContainer> pareto_opt_rcs;

  r_c_shortest_paths
  ( g, 
    get( &VertexProperty::num, g), 
    get( &EdgeProperty::num, g), 
    s, 
    t, 
    opt_solutions, 
    pareto_opt_rcs, 
    ResourceContainer(vertex_state, vertex_target_state, 0, 0), 
    ExtensionFunction(), 
    DominanceFunction(), 
    std::allocator
      <r_c_shortest_paths_label
        <Graph, ResourceContainer> >(), 
          default_r_c_shortest_paths_visitor());

  std::cout << "Number of optimal solutions: ";
  std::cout << static_cast<int>(opt_solutions.size()) << std::endl;

  for(int i = 0; i < static_cast<int>(opt_solutions.size()); i++) {
    std::cout << "The " << i + 1 << "th shortest route is: " << std::endl;

    for(int j = static_cast<int>(opt_solutions[i].size()) - 1; j >= 0; j--)
      std::cout << source(opt_solutions[i][j], g) << std::endl;
    std::cout << "7" << std::endl;
    std::cout << "Cost: " << pareto_opt_rcs[i].cost << std::endl;
    std::cout << "Resource consumption: " << pareto_opt_rcs[i].resource << std::endl;
  }

  return 0;
  return new BSPColumn();
} 

ColumnInterface* BSPColumnGenerator::GenerateNewColumn() {
  return new BSPColumn();
}