
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
	void AddBody(Vector3d posArg, Vector3d velArg, Vector3d extForceArg);
	void CreateBond(const int bodyId1, const int bodyId2);
	// DEBUG
	Body & GetBody(const int id);
};
