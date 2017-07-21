
#include "Loader.h"

#include <ostream>

#include "Utils.h"


/** Reads positions in a 3d cartesian coordinate system
 * and adds particles at these positions to the cell
 * 
 * \param[in]	posFileName	Path to the file, which contains the particle positions.
 * \param[out]	cell		Cell to which the particles are added.
 */
/*std::unique_ptr<Cell> ReadPositions(std::unique_ptr<Cell> cell, const string posFileName) {
	string curLine;
	PRINT("Reading positions from " << posFileName);

	// Open file.
	std::ifstream posFile(posFileName.c_str());
	if (!posFile.is_open()) {
		PRINT("Could not open " << posFileName);
	}

	// Read file line by line.
	while(std::getline(posFile, curLine)) {
		// Check for comment.
		if ('#' == curLine.front()) {
			continue;
		}
		// Extract cartesian coordinates of the bodies from file.
		double x, y, z;
		std::istringstream iss(curLine);
		if (!(iss >> x >> y >> z)) {
			// Something went wrong interpreting current line.
			PRINT("Something went wrong while reading the following line:\n\t" << iss.str());
			break;
		}

		// Add body to the cell.
		const Vector3d curPos(x, y, z);
		cell->AddBody(curPos);
	}
	if (!posFile.eof()) {
		// We left the line-reading loop but didn't reach end of file.
		PRINT("Error while reading " << posFileName);
		throw MyException("Loader error.");
	}
	posFile.close();
	return std::move(cell);
}*/

/** Reads pair interactions from a file
 * and sets them up between bodies in the cell.
 * 
 * \param[in]	interFileName	Path to the file, which contains the interactions.
 * \param[out]	cell		Cell in which the interactions are set up.
 */
/*std::unique_ptr<Cell> ReadInteractions(std::unique_ptr<Cell> cell, const string interFileName) {
	string curLine;
	PRINT("Reading interactions from " << interFileName);

	// Open file.
	std::ifstream interFile(interFileName.c_str());
	if (!interFile.is_open()) {
		PRINT("Could not open " << interFileName);
	}

	// Read file line by line.
	while(std::getline(interFile, curLine)) {
		// Check for comment.
		if ('#' == curLine.front()) {
			continue;
		}
		// Extract bond partners and bond strength from line.
		int id1, id2;
		double strength;
		std::istringstream iss(curLine);
		if (!(iss >> id1 >> id2 >> strength)) {
			// Something went wrong interpreting current line.
			PRINT("Something went wrong while reading the following line:\n\t" << iss.str());
			break;
		}

		// Add bond between two bodies in cell.
		cell->CreateBond(id1, id2, strength);
	}
	if (!interFile.eof()) {
		// We left the line-reading loop but didn't reach end of file.
		PRINT("Error while reading " << interFileName);
		throw MyException("Loader error.");
	}
	interFile.close();
	return std::move(cell);
}*/

/*std::unique_ptr<Cell> Loader::Load(const string posFileName, const string interFileName) {
	auto cell = std::make_unique<Cell>();

	try {
		cell = ReadFile(std::move(cell), posFileName);
		cell = ReadFile(std::move(cell), interFileName);
	}
	catch (std::exception & e) {
		PRINT(e.what());
	}

	PRINT("Created Cell with " << cell->NumBodies() << " bodies and " << cell->NumBonds() << " bonds");

	return std::move(cell);
}*/


Loader::Loader ()
	: currentInputFile(nullptr),
	  cell(nullptr) {
}

std::unique_ptr<Cell> Loader::CreateCell(const std::initializer_list<string> cellFileNames) {
	cell = std::make_unique<Cell>();

	for (auto fileName : cellFileNames) {
		LoadFileToCell(fileName);
	}
	return std::move(cell);
}

void Loader::LoadFileToCell(const string fileName) {
	PRINT("Reading cell data from " << fileName);
	try {
		OpenCurFile(fileName);
		FileType curFileType = GetFileType();
		ReadFileLines(curFileType);
	}
	catch (MyException & e) {
		std::cout << e.what() << std::endl;
	}
	CloseCurFile();
}

void Loader::ReadFileLines(const FileType fileType) {
	string curLine;
	MakeSureFileIsReady();
	while (std::getline(*currentInputFile, curLine)) {
		// Check for comment.
		if ('#' == curLine.front()) {
			continue;
		}
		if (FileType::BODY_FILE == fileType) {
			HandleLineFromBodyFile(curLine);
		} else if (FileType::BODY_FILE == fileType) {
			HandleLineFromBondFile(curLine);
		}
	}
	if (false == currentInputFile->eof()) {
		THROW_EXCEPTION("Something went wrong before we reached eof.");
	}
}

void Loader::HandleLineFromBodyFile(const string curLine) {
	double x, y, z;
	std::istringstream curLineStream(curLine);
	if (!(curLineStream >> x >> y >> z)) {
		std::stringstream errorMsg;
		errorMsg << "Error handling line from body file:\n\t" << curLine;
		throw MyException(errorMsg.str());
	}
	// Add body at (x, y, z) to cell.
	const Vector3d curPos(x, y, z);
	cell->AddBody(curPos);
}

void Loader::HandleLineFromBondFile(const string curLine) {
	int id1, id2;
	double strength;
	std::istringstream curLineStream(curLine);
	if (!(curLineStream >> id1 >> id2 >> strength)) {
		std::stringstream errorMsg;
		errorMsg << "Error handling line from bond file:\n\t" << curLine;
	}
	// Add bond between bodies with ids id1 and id2.
	cell->CreateBond(id1, id2, strength);
}

void Loader::OpenCurFile(const string fileName) {
	currentInputFile = std::make_unique<std::ifstream>(fileName.c_str());
	MakeSureFileIsReady();
}

FileType Loader::GetFileType() {
// DEBUG
PRINT("GetFileType()");
	string fileHeader("--");
	MakeSureFileIsReady();
	std::getline(*currentInputFile, fileHeader);
	PRINT(fileHeader);
	if ("# BODY_FILE" == fileHeader) {
PRINT("1");
		return FileType::BODY_FILE;
	} else if ("# BOND_FILE" == fileHeader) {
PRINT("2");
		return FileType::BOND_FILE;
	} else {
PRINT("3");
		std::stringstream errorMsg;
		errorMsg << "Unknown file type: " << fileHeader;
		throw MyException(errorMsg.str());
	}
PRINT("GetFileType() done");
}

void Loader::MakeSureFileIsReady() const {
	if (nullptr == currentInputFile) {
		throw MyException("Trying to read file but got nullptr.");
	} else if (false == currentInputFile->is_open()) {
		throw MyException("Trying to read file but it's not open.");
	}
}

void Loader::CloseCurFile() {
	if (nullptr == currentInputFile) {
		throw MyException("Trying to close file, but got nullptr.");
	}
	currentInputFile->close();
}
