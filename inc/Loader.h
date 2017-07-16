#include <string>
#include <memory>

#include "Cell.h"

using std::string;

/** Class to load a cell from input files */
class Loader {
public:
	/** Loads particle positions and interactions between particles from files.
	 *
	 * \param[in]	posFileName	Path to the file, which contains the positions.
	 * \param[in]	interFileName	Path to file, which contains the interactions.
	 *
	 * \return	Cell with particles and interactions as described in files.
	 */
	std::unique_ptr<Cell> Load(const string posFileName, const string interFileName);
};
