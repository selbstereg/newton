
#include "Integrator.h"

#include "Utils.h"

Integrator * Integrator::instance_ = nullptr;

Integrator::Integrator () {
}

Integrator * Integrator::GetInstance() {
	if (nullptr == instance_) {
		instance_ = new Integrator();
	}
	return instance_;
}

void Integrator::Init(const double dtArg) {
	PRINT("Init");
	dt_ = dtArg;
}

void Integrator::Integrate(Cell & cell) {
	PRINT("Integrating")
	/* Calculate the interaction forces. */
	for (auto bond: cell.GetBonds()) {
		Body & body1 = bond.GetBody(0);
		Body & body2 = bond.GetBody(1);
		const Vector3d relVec = body1.GetPosition() - body2.GetPosition();
		const double forceMag = bond.GetStrength() * (relVec.norm() - bond.GetEqDist());
		const Vector3d force = - forceMag * relVec.normalized();
		body1.SetForce(force);
		body2.SetForce(-force);
	}

	/* Update the velocities. */
	for (auto body: cell.GetBodies()) {
		const Vector3d totalForce = body->GetForce() + body->GetExtForce();
		const Vector3d accelleration = totalForce / body->GetMass();
		body->AddToVelocity( accelleration * dt_ );
	}

	/* Update the positions. */
	for (auto body: cell.GetBodies()) {
		body->AddToPosition( body->GetVelocity() * dt_ );
	}
}