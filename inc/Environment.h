
#include "Body.h"
#include <Eigen/Dense>

using Eigen::Vector3d;

class Environment {
private:
	double frictionCoeff;
	Vector3d gravityForce;
public:
	Environment(const double, const Vector3d);
	Vector3d CalcExtForce(const Body &) const;
};
