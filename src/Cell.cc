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

void Cell::CreateBond(const int id1, const int id2) {
	auto newBond = std::make_shared<Bond>(bodies_[id1], bodies_[id2]);
	bonds_.push_back(newBond);
}
