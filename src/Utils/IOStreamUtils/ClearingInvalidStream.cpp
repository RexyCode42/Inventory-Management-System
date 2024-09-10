#include "ClearingInvalidStream.h"

void IOStreamHelpers::clearFlagsAndIgnoreInvalidInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}