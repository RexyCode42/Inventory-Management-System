#include "Requirements.h"

void NameRequirementsPrinter::print(const NameValidator& nameValidator) const noexcept {
	 std::cout << "Name requirements:" << '\n';
	 std::cout << "- Special characters allowed: :;-_." << '\n';
	 std::cout << "- Must contain at least one letter" << '\n';
	 std::cout << "- Must be lesser than or equal to " << nameValidator.getMaxLength() << " characters" << '\n';
	 std::cout << "- Must be greater than or equal to " << nameValidator.getMinLength() << " characters" << '\n';
}

void CategoryRequirementsPrinter::print(const CategoryValidator& categoryValidator) const noexcept {
	std::cout << "Category Requirements: " << '\n';
	std::cout << "- Special characters allowed: :;-_." << '\n';
	std::cout << "- Must not have any numbers" << '\n';
	std::cout << "- Must have at minimum " << categoryValidator.getMinLength() << " characters" << '\n';
	std::cout << "- Must have at maximum " << categoryValidator.getMaxLength() << " characters" << '\n';	
}

void UnitPriceRequirementsPrinter::print(const UnitPriceValidator& unitPriceValidator) const noexcept {
	std::cout << "Price Requirements: " << '\n';
	std::cout << "- Must be greater than " << unitPriceValidator.getMinPrice() << '\n';
	std::cout << "- Must be lesser than " << unitPriceValidator.getMaxPrice() << '\n';
}

void StockRequirementsPrinter::print(const StockValidator& stockValidator) const noexcept {
	std::cout << "Stock Requirements: " << '\n';
	std::cout << "- Must be greater than " << stockValidator.getMinStock() << '\n';
	std::cout << "- Must be lesser than " << stockValidator.getMaxStock() << '\n';
}