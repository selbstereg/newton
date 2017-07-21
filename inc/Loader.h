#include <string>
#include <memory>
#include <fstream>

#include "Cell.h"

using std::string;

enum class FileType {
	BODY_FILE,
	BOND_FILE
};

/** Class to load a cell from input files */
class Loader {
private:
	std::ifstream currentFile;
	std::unique_ptr<Cell> LoadFileToCell(std::string fileName, std::unique_ptr<Cell> cell);
	void InitCurFile(std::string fileName);
public:
	/** Loads particle positions and interactions between particles from files.
	 *
	 * \param[in]	posFileName	Path to the file, which contains the positions.
	 * \param[in]	interFileName	Path to file, which contains the interactions.
	 *
	 * \return	Cell with particles and interactions as described in files.
	 */
	std::unique_ptr<Cell> CreateCell(std::initializer_list<string> cellFileNames);
};
