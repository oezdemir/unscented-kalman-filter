#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

// Calculate the RMSE here
VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
	VectorXd rmse(4);
	rmse << 0,0,0,0;
	float n = estimations.size();
	VectorXd one_div_n(4);
	one_div_n << 1/n, 1/n, 1/n, 1/n;

	// check the validity of the inputs
  if (estimations.size() != ground_truth.size() || ground_truth.size() == 0) {
      cout << "CalculateRMSE: Error, bad input data" << endl;
  }

	// accumulate squared residuals
  VectorXd sq_diff(4);
	for(unsigned i=0; i < estimations.size(); ++i) {
        VectorXd diff = estimations[i] - ground_truth[i];
        sq_diff = diff.array() * diff.array();
        rmse += sq_diff;
	}
  // mean and squareroot
	rmse = one_div_n.array() * rmse.array();
	rmse = rmse.array().sqrt();

	return rmse;
}