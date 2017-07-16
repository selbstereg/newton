
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
	Cell & cell = myLoader.Load("/home/mert/Data/cpp/playground/newton/io/tetrahedron.bdy", 
				    "/home/mert/Data/cpp/playground/newton/io/tetrahedron.inter");
	PRINT(&cell);

	PRINT("Cell has " << cell.NumBodies() << " bodies and " << cell.NumBonds() << " bonds");

	// Get integrator instance and initialize it.
	Integrator * integrator = Integrator::GetInstance();
	integrator->Init(0.01);

	/*Cell cell;
	cell.AddBody(Vector3d(0., 0., 1.));
	cell.AddBody(Vector3d(0., 0., 0.));

	cell.CreateBond(0, 1, 2.);*/

		cout << " ";
		cout << cell.GetBody(0).GetPosition()[2];
		cout << " ";
		cout << cell.GetBody(1).GetPosition()[2] << endl;
		integrator->Integrate(cell);
}
