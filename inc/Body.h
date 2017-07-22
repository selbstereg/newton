#ifndef BODY_H_
#define BODY_H_

#include <memory>
#include <vector>
#include <Eigen/Dense>

using Eigen::Vector3d;

class Body {
private:
        /** Position of the body. */
	Vector3d pos_;
        /** Velocity of the body. */
	Vector3d vel_;
        /** External force acting on the body. */
	Vector3d extForce_;
        /** Interaction force actiong on the body. */
	Vector3d force_;
        /** Mass of the body */
	double mass_;
public:
	/** Constructor
         * 
         */
	Body(Vector3d posArg, Vector3d velArg, Vector3d extForceArg, double massArg = 1.);
	Vector3d GetForce() const;
	Vector3d GetExtForce() const;
	Vector3d GetPosition() const;
	Vector3d GetVelocity() const;
	double GetMass() const;
	void SetInternalForceToZero();
	void AddToVelocity(const Vector3d addVel);
	void AddToPosition(const Vector3d addPos);
	void AddToForce(const Vector3d forceArg);
};

#endif  /* BODY_H_ */
