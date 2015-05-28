#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "bsp/BSPProblemModel.h"
#include "base/ProblemDataInterface.h"

using namespace std;

BSPProblemModel::BSPProblemModel() {

}

BSPProblemModel::BSPProblemModel(ProblemDataInterface* problem_data) {
  model_ = IloModel(env_);
}

void BSPProblemModel::SetModelData(ProblemDataInterface* problem_data) {

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