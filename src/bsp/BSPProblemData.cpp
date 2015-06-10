#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "bsp/BSPProblemData.h"

using namespace std;

BSPProblemData::BSPProblemData(std::string file_name) {
  file_name_ = file_name;
}

void BSPProblemData::LoadData() {
  ifstream file;
  file.open(("src/" + file_name_).c_str());

  file >> num_nodes_;
  file >> vechicle_capacity_;

  cost_.assign(num_nodes_, vector<double> ());
  node_coord_.assign(num_nodes_, pair<double, double> ());
  node_initial_state_.assign(num_nodes_, 0);
  node_target_state_.assign(num_nodes_, 0);
  node_capacity_.assign(num_nodes_, 0);

  for (int i = 0; i < num_nodes_; i++)
    cost_[i].assign(num_nodes_, 0.0);

  for (int i = 0; i < num_nodes_; i++) {
    file >> node_coord_[i].first;
    file >> node_coord_[i].second;
  }

  for (int i = 0; i < num_nodes_; i++) {
    for (int j = i + 1; j < num_nodes_; j++) {
      double dx = node_coord_[i].first - node_coord_[j].first;
      double dy = node_coord_[i].second - node_coord_[j].second;
      double cost = sqrt(pow(dx, 2) + pow(dy, 2));

      cost_[i][j] = cost;
      cost_[j][i] = cost;
    }
  }

  for (int i = 0; i < num_nodes_; i++) {
    file >> node_capacity_[i];
  }

  for (int i = 0; i < num_nodes_; i++) {
    file >> node_initial_state_[i];
    file >> node_target_state_[i];
  }

  file.close();
}

void BSPProblemData::WriteInstanceData() {
  cout << "INSTANCE NAME: " << file_name_ << endl;
  cout << "NUMBER OF NODES: " << num_nodes_ << endl;
  cout << "VEHICLE CAPACITY: " << vechicle_capacity_ << endl;
  cout << "NODES COORDINATES: " << endl;

  for (int i = 0; i < node_coord_.size(); i++) {
    cout << "NODE " << (i + 1) << ": ";
    cout << setfill(' ') << setw(10) << fixed << setprecision(2)
         << node_coord_[i].first;
    cout << setfill(' ') << setw(10) << fixed << setprecision(2)
         << node_coord_[i].second << endl;
  }

  cout << "NODE STATE (Initial, Target): " << endl;

  for (int i = 0; i < node_initial_state_.size(); i++) {
    cout << "NODE " << (i + 1) << ": ";
    cout << setfill(' ') << setw(10) << fixed << setprecision(2)
         << node_initial_state_[i];
    cout << setfill(' ') << setw(9) << fixed << setprecision(2)
         << node_target_state_[i] << endl;
  }

}