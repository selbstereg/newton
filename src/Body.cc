#include "Body.h"

Body::Body(Vector3d posArg, Vector3d velArg, Vector3d extForceArg, double massArg)
	: pos_(posArg),
	  vel_(velArg),
	  extForce_(extForceArg),
	  mass_(massArg) {
}

const Vector3d & Body::Pos() {
	return pos_;
}
