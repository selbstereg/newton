#include "Environment.h"

Environment::Environment(const double frictionCoeffArg, const Vector3d gravityForceArg) 
	: frictionCoeff(frictionCoeffArg),
	  gravityForce(gravityForceArg) {
}

Vector3d Environment::CalcExtForce(const Body & body) const {
	Vector3d extForce(0.0, 0.0, 0.0);

	/* Calc friction force. */
	extForce += - body.GetVelocity() * frictionCoeff;

	/* Add gravity force */
	extForce += gravityForce;

	return extForce;
}
