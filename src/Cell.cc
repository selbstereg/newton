#include <Cell.h>


Cell::Cell() {
}

void Cell::AddBody(Vector3d posArg, Vector3d velArg, Vector3d extForceArg) {
	auto newBody = std::make_shared<Body>(posArg, velArg, extForceArg);
	bodies_.push_back(newBody);
}

Body & Cell::GetBody(const int id) {
	return *bodies_[id];
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
