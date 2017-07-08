#include "Body.h"

Body::Body(int idArg, Vector3d posArg, Vector3d velArg, Vector3d extForceArg, double massArg)
	: id_(idArg),
	  pos_(posArg),
	  vel_(velArg),
	  extForce_(extForceArg),
	  mass_(massArg) {
}
