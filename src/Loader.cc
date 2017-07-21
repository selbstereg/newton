
#include "Loader.h"

#include <ostream>

#include "Utils.h"

Loader::Loader ()
	: currentInputFile(nullptr),
	  cell(nullptr) {
}

std::unique_ptr<Cell> Loader::CreateCell(const std::initializer_list<string> cellFileNames) {
	cell = std::make_unique<Cell>();

	for (auto fileName : cellFileNames) {
		LoadFileToCell(fileName);
		cell->PrintConstructionStatus();
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
			AddBodyToCell(curLine);
		} else if (FileType::BOND_FILE == fileType) {
			CreateBondInCell(curLine);
		}
	}
	if (false == currentInputFile->eof()) {
		THROW_EXCEPTION("Something went wrong before we reached eof.");
	}
}

void Loader::AddBodyToCell(const string curLine) {
	double x, y, z;
	std::istringstream curLineStream(curLine);
	if (!(curLineStream >> x >> y >> z)) {
		THROW_EXCEPTION("Error handling line from body file:\n\t" << curLine);
	}
	// Add body at (x, y, z) to cell.
	const Vector3d curPos(x, y, z);
	cell->AddBody(curPos);
}

void Loader::CreateBondInCell(const string curLine) {
	int id1, id2;
	double eqDistance;
	std::istringstream curLineStream(curLine);
	if (!(curLineStream >> id1 >> id2 >> eqDistance)) {
		std::stringstream errorMsg;
		errorMsg << "Error handling line from bond file:\n\t" << curLine;
	}
	// Add bond between bodies with ids id1 and id2.
	cell->CreateBond(id1, id2, eqDistance);
}

void Loader::OpenCurFile(const string fileName) {
	currentInputFile = std::make_unique<std::ifstream>(fileName.c_str());
	MakeSureFileIsReady();
}

FileType Loader::GetFileType() {
	string fileHeader("--");
	MakeSureFileIsReady();
	std::getline(*currentInputFile, fileHeader);
	PRINT("File header: " << fileHeader);
	if ("# BODY_FILE" == fileHeader) {
		return FileType::BODY_FILE;
	} else if ("# BOND_FILE" == fileHeader) {
		return FileType::BOND_FILE;
	} else {
		THROW_EXCEPTION("Unknown file type: " << fileHeader);
	}
}

void Loader::MakeSureFileIsReady() const {
	if (nullptr == currentInputFile) {
		THROW_EXCEPTION("Trying to read file but got nullptr.");
	} else if (false == currentInputFile->is_open()) {
		THROW_EXCEPTION("File is not open.");
	}
}

void Loader::CloseCurFile() {
	if (nullptr == currentInputFile) {
		THROW_EXCEPTION("Trying to close file, but got nullptr.");
	}
	currentInputFile->close();
}
