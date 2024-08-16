#include "ClearingInvalidStream.h"

void UserInputHelpers::clearFlagsAndIgnoreInvalidInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}