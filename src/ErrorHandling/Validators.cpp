#include "Validators.h"

[[nodiscard]] bool StringValidator::hasValidLength(
	std::string_view str,
	const std::size_t& minLength,
	const std::size_t& maxLength) const {
	return (str.length() >= minLength && str.length() <= maxLength);
}

[[nodiscard]] bool StringValidator::containsLetter(std::string_view str) const {
	const auto isAlpha{ [](unsigned char ch) { return std::isalpha(ch); } };
	return std::ranges::any_of(str, isAlpha);
}

[[nodiscard]] bool StringValidator::containsLetter(std::string_view str, std::size_t letterFrequency) const {
	const auto isAlpha{ [](unsigned char ch) -> bool { return std::isalpha(ch); } };
	// std::int64_t is used to avoid the following compiler error:
	// "conversion from '__int64' to 'int' requires a narrowing conversion"
	std::int64_t letterOccurrence{ std::ranges::count_if(str, isAlpha) };
	return (letterOccurrence % letterFrequency == 0);
}

[[nodiscard]] bool StringValidator::containsDigit(std::string_view str) const {
	const auto isDigit{ [](unsigned char ch) { return std::isdigit(ch); } };
	return std::ranges::any_of(str, isDigit);
}

[[nodiscard]] bool StringValidator::containsDigit(std::string_view str, std::size_t digitFrequency) const {
	const auto isDigit{ [](unsigned char ch) { return std::isdigit(ch); } };
	// std::int64_t is used to avoid the following compiler error:
	// "conversion from '__int64' to 'int' requires a narrowing conversion"
	std::int64_t  digitOccurrence{ std::ranges::count_if(str, isDigit) };
	return (digitOccurrence % digitFrequency == 0);
}

[[nodiscard]] bool StringValidator::containsSpecialCharacter(std::string_view str) const {
	const std::unordered_set<char> illegalCharacters{
		'!', '\"', '#', '$', '%', '&',
		'\'', '(', ')', '*', '+', ',',
		'/', '<', '=', '>', '?', '@',
		'[', '\\', ']', '^', '`', '{',
		'|', '}', '~'
	};

	const auto isSpecialCharacter{ [&illegalCharacters](char ch) { return illegalCharacters.contains(ch); } };

	return std::ranges::any_of(str, isSpecialCharacter);
}

[[nodiscard]] bool StringValidator::containsNoSpecialCharacters(std::string_view str) const {
	const auto isSpecialCharacter{ [](unsigned char ch) { return std::ispunct(ch); } };
	return !std::ranges::any_of(str, isSpecialCharacter);
}

[[nodiscard]] bool FileNameValidator::isValid(std::string_view fileName) const {
	return
		hasValidLength(fileName, minLength_, maxLength_) &&
		!containsReservedCharacters(fileName) &&
		!containsReservedNames(fileName) &&
		!containsNonPrintableCharacters(fileName) &&
		!isInternalFileNameSameAs(fileName);
}

[[nodiscard]] std::size_t FileNameValidator::getMinLength() const noexcept {
	return minLength_;
}

[[nodiscard]] std::size_t FileNameValidator::getMaxLength() const noexcept {
	return maxLength_;
}

[[nodiscard]] bool FileNameValidator::containsReservedCharacters(std::string_view fileName) const noexcept {
	return std::ranges::any_of(fileName, 
		[](unsigned char ch) { return ConstantHelpers::reservedCharacters.contains(ch); });
}

[[nodiscard]] bool FileNameValidator::containsReservedNames(std::string_view fileName) const noexcept {
	return ConstantHelpers::reservedNames.contains(fileName.data());
}

[[nodiscard]] bool FileNameValidator::containsNonPrintableCharacters(std::string_view fileName) const noexcept {
	return std::ranges::any_of(fileName, 
		[maxAsciiControlCharacter = 31, deleteControlCharacter = 127](unsigned char ch) { 
			return ch <= maxAsciiControlCharacter || ch == deleteControlCharacter; });
}

[[nodiscard]] bool FileNameValidator::isInternalFileNameSameAs(std::string_view fileName) const noexcept {
	return fileName == ConstantHelpers::internalFilePath.filename();
}

[[nodiscard]] bool IdValidator::isValid(std::string_view id) const {
	constexpr std::size_t minDigitFrequency{ minLength_ - 2 };
	constexpr std::size_t minLetterFrequency{ minLength_ - 4 };
	return
		StringValidator::hasValidLength(id, minLength_, maxLength_) &&
		StringValidator::containsDigit(id, minDigitFrequency) &&
		StringValidator::containsLetter(id, minLetterFrequency) &&
		StringValidator::containsNoSpecialCharacters(id);
}

[[nodiscard]] std::size_t IdValidator::getMinLength() const noexcept {
	return minLength_;
}

[[nodiscard]] std::size_t IdValidator::getMaxLength() const noexcept {
	return maxLength_;
}

[[nodiscard]] bool NameValidator::isValid(std::string_view name) const
{
	return
		StringValidator::hasValidLength(name, minLength_, maxLength_) &&
		StringValidator::containsLetter(name) &&
		!StringValidator::containsSpecialCharacter(name);
}

[[nodiscard]] std::size_t NameValidator::getMinLength() const noexcept {
	return minLength_;
}

[[nodiscard]] std::size_t NameValidator::getMaxLength() const noexcept {
	return maxLength_;
}

[[nodiscard]] bool CategoryValidator::isValid(std::string_view category) const
{
	return
		StringValidator::hasValidLength(category, minLength_, maxLength_) &&
		!StringValidator::containsDigit(category) &&
		!StringValidator::containsSpecialCharacter(category);
}

[[nodiscard]] std::size_t CategoryValidator::getMinLength() const noexcept {
	return minLength_;
}

[[nodiscard]] std::size_t CategoryValidator::getMaxLength() const noexcept {
	return maxLength_;
}

[[nodiscard]] bool UnitPriceValidator::isValid(double unitPrice) const {
	return (unitPrice > minUnitPrice_ && unitPrice < maxUnitPrice_);
}

[[nodiscard]] double UnitPriceValidator::getMinPrice() const noexcept {
	return minUnitPrice_;
}

[[nodiscard]] double UnitPriceValidator::getMaxPrice() const noexcept {
	return maxUnitPrice_;
}

[[nodiscard]] bool StockValidator::isValid(int stock) const {
	return (stock > minStock_ && stock < maxStock_);
}

[[nodiscard]] int StockValidator::getMinStock() const noexcept {
	return minStock_;
}

[[nodiscard]] int StockValidator::getMaxStock() const noexcept {
	return maxStock_;
}

[[nodiscard]] bool InventoryValueValidator::isValid(long double inventoryValue) const {
	return (inventoryValue > minInventoryValue_ && inventoryValue < maxInventoryValue_);
}

[[nodiscard]] long double InventoryValueValidator::getMinInventoryValue() const noexcept {
	return minInventoryValue_;
}

[[nodiscard]] long double InventoryValueValidator::getMaxInventoryValue() const noexcept {
	return maxInventoryValue_;
}