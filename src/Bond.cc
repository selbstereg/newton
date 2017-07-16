#include "Bond.h"
#include "Utils.h"


Bond::Bond(std::shared_ptr<Body> partner1Arg, std::shared_ptr<Body> partner2Arg)
	: partner1_(partner1Arg),
	  partner2_(partner2Arg),
	  strength_(1.) {
	eqDist_ = (partner1_->GetPosition() - partner2_->GetPosition()).norm();
}

Bond::Bond(std::shared_ptr<Body> partner1Arg, std::shared_ptr<Body> partner2Arg, double eqDistArg, double strengthArg)
	: partner1_(partner1Arg),
	  partner2_(partner2Arg),
	  eqDist_(eqDistArg),
	  strength_(strengthArg) {
}

Body & Bond::GetBody(const int partnerNumber) {
	if (0 == partnerNumber) {
		return * partner1_;
	} else if (1 == partnerNumber) {
		return * partner2_;
	} else {
		PRINT("Index out of range.");
	}
}

const double Bond::GetEqDist() const {
	return eqDist_;
}

const double Bond::GetStrength() const {
	return strength_;
}
