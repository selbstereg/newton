
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

std::unique_ptr<Cell> Integrator::Integrate(std::unique_ptr<Cell> cell) {

	// TODO: Move calculation of internal forces into Bond class.
	// This will be greatly beneficial if you want to introduce different
	// kinds of Bonds.
	/* Calculate the interaction forces. */
	for (auto bond: cell->GetBonds()) {
		Body & body1 = bond.GetBody(0);
		Body & body2 = bond.GetBody(1);
		const Vector3d relVec = body1.GetPosition() - body2.GetPosition();
		const double forceMag = bond.GetStrength() * (relVec.norm() - bond.GetEqDist());
		const Vector3d force = - forceMag * relVec.normalized();
		body1.SetForce(force);
		body2.SetForce(-force);
	}

	/* Update the velocities. */
	for (auto body: cell->GetBodies()) {
		const Vector3d totalForce = body->GetForce() + body->GetExtForce();
		const Vector3d accelleration = totalForce / body->GetMass();
		body->AddToVelocity( accelleration * dt_ );
	}

	/* Update the positions. */
	for (auto body: cell->GetBodies()) {
		body->AddToPosition( body->GetVelocity() * dt_ );
	}
	return std::move(cell);
}
