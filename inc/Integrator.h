#ifndef INTEGRATOR_H_
#define INTEGRATOR_H_

#include "Cell.h"
#include "Environment.h"

/** Singleton which integrates the trajectories of the cell's bodies. */
class Integrator {
private:
	Integrator();
	Integrator(const Integrator &) = delete;
	Integrator & operator=(const Integrator &) =delete;
	static Integrator * instance_;
	double dt_;
public:
        /** Get a pointer to the singleton
         * 
         */
	static Integrator * GetInstance();

        /** Set integrator properties.
         * 
         * \param[in] dtArg Time step dt.
         */
	void Init(const double dtArg);
        
        /** Integrates the trajectories of the bodies in the cell.
         * 
         * (1) F_i(t) = -grad[U_i({x_j(t)})] + F_i^ext
         * (2) a_i(t) = F_i(t)/m_i;
         * (3) v_i(t+1) = v_i(t) + a_i(t)
         * (4) x_i(t+1) = x_i(t) + v_i(t+1)
         * It would be nice to calculate x_i(t+1) = x_i(t) + v_i(t), but the result of (3) would have
         * to be cached and the program would loose simplicity.
         */
	std::unique_ptr<Cell> Integrate(std::unique_ptr<Cell> cell, const Environment & environment) const;
};

#endif
