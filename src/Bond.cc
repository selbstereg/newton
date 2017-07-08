#include "Bond.h"

Bond::Bond(std::shared_ptr<Body> partner1Arg, std::shared_ptr<Body> partner2Arg, double strengthArg)
	: partner1_(partner1Arg),
	  partner2_(partner2Arg),
	  strength_(strengthArg) {
	eqDist_ = (partner1_->Pos() - partner2_->Pos()).norm();
}
