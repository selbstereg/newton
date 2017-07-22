#include "Cell.h"

#include <fstream>

#include "Utils.h"


Cell::Cell() {
}

void Cell::AddBody(Vector3d posArg, Vector3d velArg, Vector3d extForceArg) {
	auto newBody = std::make_shared<Body>(posArg, velArg, extForceArg);
	bodies_.push_back(newBody);
}

void Cell::CreateBond(const int id1, const int id2) {
	auto body1 = bodies_.at(id1);
	auto body2 = bodies_.at(id2);

	Bond newBond(bodies_.at(id1), bodies_.at(id2));
	bonds_.push_back(newBond);
}

void Cell::CreateBond(const int id1, const int id2, const double eqDist, const double strength) {
	auto body1 = bodies_.at(id1);
	auto body2 = bodies_.at(id2);

	Bond newBond(bodies_.at(id1), bodies_.at(id2), eqDist, strength);
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

void Cell::SetInternalForcesToZero() {
	for (auto body : bodies_) {
		body->SetInternalForceToZero();
	}
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

void Cell::PrintBodiesToVtk(std::string fileName) const {
	std::ofstream vtkFile(fileName);
	if (false == vtkFile.is_open()) {
		THROW_EXCEPTION("Unable to open file:\n\t" << fileName);
	}
	vtkFile << "# vtk DataFile Version 2.0\nblablabla\nASCII\nDATASET POLYDATA\n";
	vtkFile << "POINTS " << NumBodies() << " floats\n";
	for (auto body : bodies_) {
		Vector3d pos = body->GetPosition();
		for (int i=0; i<3; i++) {
			vtkFile << pos(i) << " ";
		}
		vtkFile << "\n";
	}
	vtkFile.close();
}

void Cell::PrintConstructionStatus() const {
	PRINT("Cell construction status:");
	PRINT("\tNumber of bodies: " << bodies_.size());
	PRINT("\tNumber of bonds: " << bonds_.size());
}
