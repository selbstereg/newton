
#include <vector>
#include <memory>

#include "Bond.h"
#include "Body.h"

class Cell {
private:
	std::vector<Bond> bonds_;
	std::vector<std::shared_ptr<Body>> bodies_;
public:
	Cell();
	Cell(const Cell &) = delete;
	Cell & operator=(const Cell &) = delete;
	void AddBody(int idArg, Vector3d posArg, Vector3d velArg, Vector3d extForceArg, double massArg);
	void CreateBond(const int id, const int bodyId1, const int bodyId2, const double strength);
	// DEBUG
	Body & GetBody(const int id);
};
