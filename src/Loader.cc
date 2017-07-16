
#include "Loader.h"

#include <fstream> 

#include "Utils.h"


/** Reads positions in a 3d cartesian coordinate system
 * and adds particles at these positions to the cell
 * 
 * \param[in]	posFileName	Path to the file, which contains the particle positions.
 * \param[out]	cell		Cell to which the particles are added.
 */
std::unique_ptr<Cell> ReadPositions(std::unique_ptr<Cell> cell, const string posFileName) {
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
}

/** Reads pair interactions from a file
 * and sets them up between bodies in the cell.
 * 
 * \param[in]	interFileName	Path to the file, which contains the interactions.
 * \param[out]	cell		Cell in which the interactions are set up.
 */
std::unique_ptr<Cell> ReadInteractions(std::unique_ptr<Cell> cell, const string interFileName) {
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
}

std::unique_ptr<Cell> Loader::Load(const string posFileName, const string interFileName) {
	auto cell = std::make_unique<Cell>();

	try {
		cell = ReadPositions(std::move(cell), posFileName);
		cell = ReadInteractions(std::move(cell), interFileName);
	}
	catch (std::exception & e) {
		PRINT(e.what());
	}

	PRINT("Created Cell with " << cell->NumBodies() << " bodies and " << cell->NumBonds() << " bonds");

	return std::move(cell);
}
