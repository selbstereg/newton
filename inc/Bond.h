#ifndef BOND_H_
#define BOND_H_

#include <memory>

#include "Body.h"

class Bond {
private:
	std::shared_ptr<Body> partner1_;
	std::shared_ptr<Body> partner2_;
	double eqDist_;
	double strength_;
	int id_;
public:
	Bond(int idArg, std::shared_ptr<Body> partner1Arg, std::shared_ptr<Body> partner2Arg, double strengthArg);
};

#endif
