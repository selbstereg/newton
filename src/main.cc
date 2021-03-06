
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
	// Create cell with bodies which interact.
	Loader myLoader;
	auto cell = myLoader.Load("/home/mert/Data/cpp/playground/newton/io/tetrahedron.bdy", 
				    "/home/mert/Data/cpp/playground/newton/io/tetrahedron.inter");
	if (nullptr == cell) {
		PRINT("Nullptr");
	}


	// Get integrator instance and initialize it.
	Integrator * integrator = Integrator::GetInstance();
	integrator->Init(0.01);

	// Integrate and write particle positions to a file each frame.
	std::ofstream outFile("/home/mert/Data/cpp/playground/newton/io/out/ort.dat");
	for (int i=0; i < 1000; i++) {
		cell->PrintPositions(outFile);
		cell = integrator->Integrate(std::move(cell));
	}
	outFile.close();
}
