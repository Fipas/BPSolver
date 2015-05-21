#ifndef BPSOLVER_BASE_BRANCH_AND_PRICE_MANAGER_INTERFACE_H_
#define BPSOLVER_BASE_BRANCH_AND_PRICE_MANAGER_INTERFACE_H_

class BranchAndPriceManagerInterface {
 public:
  virtual ~BranchAndPriceManagerInterface() {}

  virtual void BranchCriteria() = 0;
  virtual void RestoreBounds() = 0;
  virtual void SetActiveColumn(SubproblemInterface* subproblem) = 0;
  virtual void CopySubproblem(SubproblemInterface* from_subproblem,
  							  SubproblemInterface* to_subproblem) = 0;
  virtual void GetLeastFractionalVariable(SubproblemInterface* subproblem) = 0;
  virtual SubproblemInterface* NextSubproblem() = 0;
  virtual void StoreSubproblem(SubproblemInterface* subproblem) = 0;
  virtual void RemoveSubproblem(SubproblemInterface* subproblem) = 0;
};

#endif