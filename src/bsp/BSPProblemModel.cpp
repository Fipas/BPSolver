#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "bsp/BSPProblemModel.h"
#include "base/ProblemDataInterface.h"
#include "bsp/BSPColumnGenerator.h"
#include "base/ColumnGeneratorInterface.h"
#include "bsp/BSPResources.h"

using namespace std;

BSPProblemModel::BSPProblemModel(ProblemDataInterface* problem_data) {
  model_ = IloModel(BSPResources::kEnv);
  problem_data_ = problem_data;
}

void BSPProblemModel::SetModelData() {
  IloEnv env = BSPResources::kEnv;
  IloObjective obj = IloMinimize(env);
  IloRangeArray constraints(env);
  IloNumVarArray variables(env);

  problem_data_->WriteInstanceData();

  int arcs_used[] = {1, 0, 0, 0, 0, 0,
                     1, 0, 0, 0, 0, 1,
                     0, 0, 0, 0, 0, 1,
                     0, 0, 0, 0, 0, 1,
                     0, 0, 0, 0, 0, 1,
                     0, 0, 0, 0, 0, 1,
                     0, 1, 1, 1, 1, 1};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      if (i == j) continue;
        stringstream constraint_name;
        constraint_name << "a_" << i << "_" << j;
        constraints.add(IloRange(env, 0.0, 1.0, constraint_name.str().c_str()));
    }
  }

  IloNumColumn new_column = obj(10);

  for (int i = 0, c = 0; i < constraints.getSize(); i++) {
    new_column += constraints[i](arcs_used[i]);
  }

  IloNumVar new_variable(new_column, 0, 1);
  new_variable.setName("r1");
  variables.add(new_variable);

  model_.add(obj);
  model_.add(constraints);
  model_.add(variables);
  cout << model_ << endl;  
  
  //GenerateInitialBase();
}

void BSPProblemModel::Optmize() {

}

void BSPProblemModel::GetReducedCost() {

}

bool BSPProblemModel::IsIntegerSolution() {
  return false;
}

void BSPProblemModel::KillNonBasicColumns() {

}

void BSPProblemModel::AddColumn(ColumnInterface* new_column) {

}

void BSPProblemModel::GenerateInitialBase() {
  ColumnGeneratorInterface* column_generator = new BSPColumnGenerator(problem_data_);
  column_generator->GenerateFirstColumn();
}