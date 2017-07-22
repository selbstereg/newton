#ifndef CELL_H_
#define CELL_H_

#include <vector>
#include <memory>
#include <ostream>

#include "Bond.h"
#include "Body.h"


// TODO: Rename class to Mesh. This is more descriptive.
/** Class represents a collection of bodies, linked by bonds */
class Cell {
private:
        /** Bonds between the bodies. */
	std::vector<Bond> bonds_;
        /** Bodies of the cell. */
	std::vector<std::shared_ptr<Body>> bodies_;

public:
        /** Constructor
         * 
         */
	Cell();
        
        /** Copy constructor
         * 
         * deleted
         */
	Cell(const Cell &) = delete;
        
        /** Copy assignment
         * 
         * deleted
         */ 
	Cell & operator=(const Cell &) = delete;
        
        /** Add a new body to the cell.
         * 
         */
	void AddBody(Vector3d posArg, Vector3d velArg = Vector3d(0., 0., 0.), Vector3d extForceArg = Vector3d(0., 0., 0.));
        
        /** Create a bond between two bodies of the cell.
         * 
         * The equilibrium distance of the bond will be set to the distance between the bond partners at
         * creation of the bond. The bond strength will be set to unity.
         * 
         * \param[in]   bodyId1 Id of the first bond partner.
         * \param[in]   bodyId2 Id of the second bond partner.
         */
	void CreateBond(const int bodyId1, const int bodyId2);
        
        /** Create bond overload with arguments for equilibrium distance and bond strength.
         * 
         * \param[in]   bodyId1     See above overload of the function.
         * \param[in]   bodyId2     See above overload of the function.
         * \param[in]   eqDist      Equillibrium distance between the bond partners.
         * \param[in]   strenght    Strength of the bond (used in product to calculate force).
         */
	void CreateBond(const int bodyId1, const int bodyId2, const double eqDist, const double strength = 1.);
        
        /** Get the bond container.
         * 
         * Allows ranged loops over the bonds.
         */
	const std::vector<Bond> & GetBonds() const;
        
        /** Get the body container.
         * 
         * Allows ranged loops over the bodies.
         */
	const std::vector<std::shared_ptr<Body>> GetBodies() const;

	/** Number of bodies.
	 *
	 */
	int NumBodies() const;

	/** Number of interactions.
	 *
	 */
	int NumBonds() const;

	void SetInternalForcesToZero();

	/** Print positions.
	 *
	 */
	void PrintPositions(std::ostream & out) const;

	/** Print a vtk file containing the bodies positions for
	 *  visualization of the system (e.g. with Paraview).
	 *
	 * \param[in]	fileName	Path and filename of output vtk.
	 */
	void PrintBodiesToVtk(std::string fileName) const;

	/** Print construction status.
	 *
	 */
	void PrintConstructionStatus() const;
};

#endif
