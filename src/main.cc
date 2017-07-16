
#include <iostream>

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

	for (int i=0; i < 1000; i++) {
		cout << i;
		cout << " ";
		cout << cell->GetBody(0).GetPosition()[2];
		cout << " ";
		cout << cell->GetBody(1).GetPosition()[2] << endl;
		cell = integrator->Integrate(std::move(cell));
	}
}
