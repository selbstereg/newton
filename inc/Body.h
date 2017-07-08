#ifndef BODY_H_
#define BODY_H_

#include <memory>
#include <vector>
#include <Eigen/Dense>

using Eigen::Vector3d;

class Body {
private:
	/** neighbors which which the body has bonds */
	std::vector<std::shared_ptr<Body>> neighbors_;
	/** bonds, the neighbor is a part of */
	//std::vector<std::shared_ptr<Bond>> bonds_;
	int id_;
	Vector3d pos_;
	Vector3d vel_;
	Vector3d extForce_;
	double mass_;
public:
	/* TODO: Set default values for some of the arguments, like velMass=1 */
	Body(int idArg, Vector3d posArg, Vector3d velArg, Vector3d extForceArg, double massArg);
};

#endif  /* BODY_H_ */
