#include "Bond.h"

Bond::Bond(std::shared_ptr<Body> partner1Arg, std::shared_ptr<Body> partner2Arg)
	:  partner1_(partner1Arg),
	   partner2_(partner2Arg) {
}
