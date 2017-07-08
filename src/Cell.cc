#include <Cell.h>


Cell::Cell() {
}

void Cell::AddBody(int idArg, Vector3d posArg, Vector3d velArg, Vector3d extForceArg, double massArg) {
	auto newBody = std::make_shared<Body>(idArg, posArg, velArg, extForceArg, massArg);
	bodies_.push_back(newBody);
}

Body & Cell::GetBody(const int id) {
	return *bodies_[id];
}

void Cell::CreateBond(const int id, const int id1, const int id2, const double strength) {
	auto body1 = bodies_[id1];
	auto body2 = bodies_[id2];

	Bond newBond(id, bodies_[id1], bodies_[id2], strength);
	bonds_.push_back(newBond);
}
