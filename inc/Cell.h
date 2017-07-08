
#include <vector>
#include <memory>

#include "Bond.h"
#include "Body.h"

class Cell {
private:
	std::vector<std::shared_ptr<Bond>> bonds_;
	std::vector<std::shared_ptr<Body>> bodies_;
public:
	Cell();
	Cell(const Cell &) = delete;
	Cell & operator=(const Cell &) = delete;
	void AddBody(int idArg, Vector3d posArg, Vector3d velArg, Vector3d extForceArg, double massArg);
	void CreateBond(const int id1, const int id2);
	// DEBUG
	Body & GetBody(const int id);
};
