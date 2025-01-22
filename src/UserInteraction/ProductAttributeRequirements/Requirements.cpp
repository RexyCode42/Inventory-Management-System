#include "Requirements.h"

void IdRequirementsPrinter::print(const IdValidator& idValidator) const noexcept {
	std::cout << "Id requirements:" << '\n';
	std::cout << "- Must not contain any special characters" << '\n';
	std::cout << "- Must start with at least four digits" << '\n';
	std::cout << "- Must end with at least two letters" << '\n';
	std::cout << "- Must be " << idValidator.getMinLength() << " characters long at minimum" << '\n';
	std::cout << "- Must be " << idValidator.getMaxLength() << " characters long at maximum" << '\n';
}

void NameRequirementsPrinter::print(const NameValidator& nameValidator) const noexcept {
	 std::cout << "Name requirements:" << '\n';
	 std::cout << "- Special characters allowed: : ; - _ ." << '\n';
	 std::cout << "- Must contain at least one letter" << '\n';
	 std::cout << "- Must be " << nameValidator.getMinLength() << " characters long at minimum" << '\n';
	 std::cout << "- Must be " << nameValidator.getMaxLength() << " characters long at maximum" << '\n';
}

void CategoryRequirementsPrinter::print(const CategoryValidator& categoryValidator) const noexcept {
	std::cout << "Category Requirements: " << '\n';
	std::cout << "- Special characters allowed: : ; - _ ." << '\n';
	std::cout << "- Must not have any numbers" << '\n';
	std::cout << "- Must be " << categoryValidator.getMinLength() << " characters long at minimum" << '\n';
	std::cout << "- Must be " << categoryValidator.getMaxLength() << " characters long at maximum" << '\n';	
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

void InventoryValueRequirementsPrinter::print(const InventoryValueValidator& inventoryValueValidator) const noexcept {
	std::cout << "Inventory Value Requirements: " << '\n';
	std::cout << "- Must be greater than " << inventoryValueValidator.getMinInventoryValue() << '\n';
	std::cout << "- Must be lesser than " << inventoryValueValidator.getMaxInventoryValue() << '\n';
}

void FileNameRequirementsPrinter::print(const FileNameValidator& fileNameValidator) const noexcept {
	std::cout << "File name requirements:" << '\n';
	std::cout << "- Must not contain reserved characters: " << Algorithms::join(ConstantHelpers::reservedCharacters, ' ') << '\n';
	std::cout << "- Must not contain reserved names: " << Algorithms::join(ConstantHelpers::reservedNames, ' ') << '\n';
	std::cout << "- Must not contain non-printable characters" << '\n';
	std::cout << "- Must not be called " << ConstantHelpers::internalFilePath.filename() << '\n';
	std::cout << "- Must be " << fileNameValidator.getMinLength() << " characters long at minimum" << '\n';
	std::cout << "- Must be " << fileNameValidator.getMaxLength() << " characters long at maximum" << '\n';
}