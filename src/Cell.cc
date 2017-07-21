#include "Cell.h"

#include "Utils.h"


Cell::Cell() {
}

void Cell::AddBody(Vector3d posArg, Vector3d velArg, Vector3d extForceArg) {
	auto newBody = std::make_shared<Body>(posArg, velArg, extForceArg);
	bodies_.push_back(newBody);
}

void Cell::CreateBond(const int id1, const int id2) {
	auto body1 = bodies_[id1];
	auto body2 = bodies_[id2];

	Bond newBond(bodies_[id1], bodies_[id2]);
	bonds_.push_back(newBond);
}

void Cell::CreateBond(const int id1, const int id2, const double eqDist, const double strength) {
	auto body1 = bodies_[id1];
	auto body2 = bodies_[id2];

	Bond newBond(bodies_[id1], bodies_[id2], eqDist, strength);
	bonds_.push_back(newBond);
}

const std::vector<Bond> & Cell::GetBonds() const {
	return bonds_;
}

const std::vector<std::shared_ptr<Body>> Cell::GetBodies() const {
	return bodies_;
}

int Cell::NumBodies() const {
	return bodies_.size();
}

int Cell::NumBonds() const {
	return bonds_.size();
}

void Cell::PrintPositions(std::ostream & out) const {
	for (auto body : bodies_) {
		Vector3d pos = body->GetPosition();
		for (int i=0; i<3; i++) {
			out << " " << pos(i);
		}
	}
	out << std::endl;
}

void Cell::PrintConstructionStatus() const {
	PRINT("Cell construction status:");
	PRINT("\tNumber of bodies: " << bodies_.size());
	PRINT("\tNumber of bonds: " << bonds_.size());
}
