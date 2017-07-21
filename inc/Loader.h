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
	std::unique_ptr<std::ifstream> currentInputFile;
	std::unique_ptr<Cell> cell;
	void LoadFileToCell(const string fileName);
	void ReadFileLines(const FileType fileType);
	void AddBodyToCell(const string curLine);
	void CreateBondInCell(const string curLine);
	void OpenCurFile(const string fileName);
	void CloseCurFile();
	void MakeSureFileIsReady() const;
	FileType GetFileType();
public:
	Loader();
	/** Loads particle positions and interactions between particles from files.
	 *
	 * \param[in]	posFileName	Path to the file, which contains the positions.
	 * \param[in]	interFileName	Path to file, which contains the interactions.
	 *
	 * \return	Cell with particles and interactions as described in files.
	 */
	std::unique_ptr<Cell> CreateCell(const std::initializer_list<string> cellFileNames);
};
