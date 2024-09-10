#include "SettingStreamAlignment.h"

void IOStreamHelpers::setOutputAlignment(std::ios_base::fmtflags alignment) {
	std::cout.setf(alignment, std::ios::adjustfield);
}