
#include <iostream>
#include <fstream>

#include "Body.h"
#include "Cell.h"
#include "Loader.h"
#include "Integrator.h"

#include "Utils.h"

using std::cout;
using std::endl;

int main() {

	Environment environment(0.1, Vector3d(0., 0., -0.0005));
	// Create cell with bodies which interact.
	Loader myLoader;
	auto cell = myLoader.CreateCell(
		  {"/home/mert/Data/cpp/playground/newton/io/t05120_a5.0Sphere/bodies.bdy",
		   "/home/mert/Data/cpp/playground/newton/io/t05120_a5.0Sphere/pairs.inter"}
		);
	if (nullptr == cell) {
		PRINT("Nullptr");
	}


	// Get integrator instance and initialize it.
	Integrator * integrator = Integrator::GetInstance();
	integrator->Init(0.01);

	// Integrate and write particle positions to a file each frame.
	std::ofstream outFile("/home/mert/Data/cpp/playground/newton/io/out/ort.dat");
	for (int i=0; i < 200000; i++) {
		if (0 == (i % 10)) {
			std::stringstream vtkFileName;
			vtkFileName << "/home/mert/Data/cpp/playground/newton/io/out/pos_";
			vtkFileName << i << ".vtk";
			cell->PrintBodiesToVtk(vtkFileName.str());
		}
		cell->PrintPositions(outFile);
		cell = integrator->Integrate(std::move(cell), environment);
	}
	outFile.close();
}
