
#include <iostream>

#include "Body.h"
#include "Cell.h"

using std::cout;
using std::endl;

int main() {
	Cell cell;
	cell.AddBody(0, Vector3d(0., 0., 1.), Vector3d(1., 1., 1.), Vector3d(0.0, 0., 0.), 1.);
	cell.AddBody(1, Vector3d(0., 0., 0.), Vector3d(1., 1., 1.), Vector3d(0.0, 0., 0.), 1.);

	cell.CreateBond(0, 0, 1, 1.);

	cout << &cell.GetBody(0) << endl;
	cout << &cell.GetBody(1) << endl;
}
