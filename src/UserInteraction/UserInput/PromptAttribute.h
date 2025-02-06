#pragma once

#include "../src/Utils/StringUtils/StringFormatting.h"
#include "../src/Utils/IOStreamUtils/ClearingInvalidStream.h"
#include "../src/ErrorHandling/Validators.h"
#include "../ProductAttributeRequirements/RequirementsPrinter.h"

template<typename T>
T prompt(std::string_view attributeName) {
	T attribute{};

	std::cout << "Enter product " << attributeName << ": ";

	if constexpr (std::is_same_v<T, std::string>) {
		// Skip leading whitespace (spaces, tabs, newlines) in the input buffer
		// to avoid issues when switching to line-oriented input (e.g., std::getline).
		std::getline(std::cin >> std::ws, attribute);
	}
	else if constexpr (std::is_arithmetic_v<T>) {
		std::cin >> attribute;
		IOStreamHelpers::clearFlagsAndIgnoreInvalidInput();
	}
	else {
		// Add error logging mechanism here or a static_assert.
		// static_assert(std::is_arithmetic_v<T> || 
		// std::is_same_v<T, std::string>, 
		// "T must be either an arithmetic type or std::string");
	}

	std::cout << '\n';

	return attribute;
}

template<typename T, ValidatorConcept<T> AttributeValidator>
T promptUserForAttribute(
	RequirementsPrinterConcept<AttributeValidator> auto printer,
	const AttributeValidator& attributeValidator,
	std::string_view attributeName) {
	T attribute{};

	do {
		// We pass in a validator to get access 
		// to certain attribute characteristics/requirements,
		// for example: minStringLength or minPrice
		printAttributeRequirements<T>(printer, attributeValidator);
		attribute = prompt<T>(attributeName);
	} while (!attributeValidator.isValid(attribute));

	if constexpr (std::is_same_v<T, std::string>) {
		StringHelpers::trimEdgesAndBody(attribute);
		StringHelpers::toUpperAll(attribute);
	}

	return attribute;
}