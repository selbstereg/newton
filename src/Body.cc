#include "Body.h"

Body::Body(Vector3d posArg, Vector3d velArg, Vector3d extForceArg, double massArg)
	: pos_(posArg),
	  vel_(velArg),
	  extForce_(extForceArg),
	  force_(Vector3d(0.0, 0.0, 0.0)),
	  mass_(massArg) {
}

Vector3d Body::GetForce() const {
	return force_;
}

Vector3d Body::GetExtForce() const {
	return extForce_;
}

Vector3d Body::GetPosition() const {
	return pos_;
}

Vector3d Body::GetVelocity() const {
	return vel_;
}

double Body::GetMass() const {
	return mass_;
}

void Body::SetInternalForceToZero() {
	force_ = Vector3d(0.0, 0.0, 0.0);
}

void Body::AddToVelocity(const Vector3d addVel) {
	vel_ += addVel;
}

void Body::AddToPosition(const Vector3d addPos) {
	pos_ += addPos;
}

void Body::AddToForce(const Vector3d addForce) {
	force_ += addForce;
}
