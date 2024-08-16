#include "Validators.h"

[[nodiscard]] bool StringValidator::hasValidLength(
	std::string_view str,
	const std::size_t& minLength,
	const std::size_t& maxLength) const {
	return str.length() >= minLength && str.length() <= maxLength;
}

[[nodiscard]] bool StringValidator::containsLetter(std::string_view str) const {
	const auto isAlpha{ [](unsigned char ch) -> unsigned char { return std::isalpha(ch); } };
	return std::ranges::any_of(str, isAlpha);
}

[[nodiscard]] bool StringValidator::containsDigit(std::string_view category) const {
	const auto isDigit{ [](unsigned char ch) -> unsigned char { return std::isdigit(ch); } };
	return std::ranges::any_of(category, isDigit);
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