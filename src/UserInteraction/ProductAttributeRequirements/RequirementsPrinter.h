#pragma once

#include "../../ErrorHandling/Validators.h"

// Ensure that an attribute requirements printer has a print function
// that takes an attribute validator as a parameter and throws no exceptions.
template<class Printer, class Validator>
concept RequirementsPrinterConcept = requires(const Printer & printer, const Validator & validator) {
	{ printer.print(validator) } noexcept;
};

template<typename T, ValidatorConcept<T> Validator>
void printAttributeRequirements(
	const RequirementsPrinterConcept<Validator> auto& printer,
	const Validator& validator) {
	printer.print(validator);
}