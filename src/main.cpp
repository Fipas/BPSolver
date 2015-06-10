#include "bsp/BSPProblemData.h"
#include "bsp/BSPProblemModel.h"

int main(int argc, char* argv[]) {
  BSPProblemData* problem_data = new BSPProblemData("teste.in");
  BSPProblemModel* problem_model = new BSPProblemModel(problem_data);

  problem_data->LoadData();
  //problem_data->WriteInstanceData();
  problem_model->SetModelData();
  problem_model->Optmize();

}