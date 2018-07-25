#pragma once
// This structure contains the data which we want to dump in the binary file
#pragma once

namespace SDBMS
{
	struct ReadWrite
	{
		std::string mStudentName;
		int mClassRommNumber;
		int mRollNo;
		int mEnglish;
		int mPhysics;
		int mChemistry;
		int mMaths;
		int mCompSci;
		int mNoOfStudents;          // Added for future use if not needed will be removed
		int mNoOfClassRoom;         // Added for future use if not needed will be removed
	};

}
