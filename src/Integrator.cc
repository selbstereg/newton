
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

std::unique_ptr<Cell> Integrator::Integrate(std::unique_ptr<Cell> cell, const Environment & environment) const {
	// TODO: Move calculation of internal forces into Bond class.
	// This will be greatly beneficial if you want to introduce different
	// kinds of Bonds.
	/* Calculate the forces acting on the bodies. */
	cell->SetInternalForcesToZero();
	for (auto bond: cell->GetBonds()) {
		// Forces due to bonds.
		Body & body1 = bond.GetBody(0);
		Body & body2 = bond.GetBody(1);
		const Vector3d relVec = body1.GetPosition() - body2.GetPosition();
		const double forceMag = bond.GetStrength() * (relVec.norm() - bond.GetEqDist());
		const Vector3d force = - forceMag * relVec.normalized();
		body1.AddToForce(force);
		body2.AddToForce(-force);
	}

	for (auto body: cell->GetBodies()) {
		const Vector3d extForce = environment.CalcExtForce(*body);
		body->AddToForce(extForce);
	}

	// TODO: Move the calculation into the body class.
	/* Update the velocities. */
	for (auto body: cell->GetBodies()) {
		const Vector3d totalForce = body->GetForce() + body->GetExtForce();
		const Vector3d accelleration = totalForce / body->GetMass();
		body->AddToVelocity( accelleration * dt_ );
	}

	bool first = true;
	// TODO: Move the calculation into the body class.
	/* Update the positions. */
	for (auto body: cell->GetBodies()) {
if (false == first)
		body->AddToPosition( body->GetVelocity() * dt_ );
first = false;
	}
	return std::move(cell);
}
