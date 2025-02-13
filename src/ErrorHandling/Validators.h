#pragma once

#include <string>
#include <string_view>
#include <algorithm>
#include <ranges>
#include <unordered_set>
#include "../Utils/ConstantVariableUtils/ConstantUtils.h"

template<class Validator, typename T>
concept ValidatorConcept = requires(const Validator& validator, const T& t) {
	{ validator.isValid(t) } -> std::same_as<bool>;
};

class StringValidator {
protected:
	[[nodiscard]] bool hasValidLength(
		std::string_view str,
		const std::size_t& minLength,
		const std::size_t& maxLength) const;

	[[nodiscard]] bool containsLetter(std::string_view str) const;

	[[nodiscard]] bool containsLetter(std::string_view str, std::size_t letterFrequency) const;

	[[nodiscard]] bool containsDigit(std::string_view str) const;

	[[nodiscard]] bool containsDigit(std::string_view str, std::size_t digitFrequency) const;

	[[nodiscard]] bool containsSpecialCharacter(std::string_view str) const;

	[[nodiscard]] bool containsNoSpecialCharacters(std::string_view str) const;
};

class FileNameValidator : public StringValidator {
public:
	[[nodiscard]] bool isValid(std::string_view fileName) const;

	[[nodiscard]] std::size_t getMinLength() const noexcept;

	[[nodiscard]] std::size_t getMaxLength() const noexcept;

private:
	// Windows file name rules: https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file

	[[nodiscard]] bool containsReservedCharacters(std::string_view fileName) const noexcept;

	[[nodiscard]] bool containsReservedNames(std::string_view fileName) const noexcept;

	[[nodiscard]] bool containsNonPrintableCharacters(std::string_view fileName) const noexcept;

	[[nodiscard]] bool isInternalFileNameSameAs(std::string_view fileName) const noexcept;

	static constexpr std::size_t minLength_{ 1 };
	static constexpr std::size_t maxLength_{ ConstantHelpers::maxPathLength };
};

class IdValidator : public StringValidator {
public:
	[[nodiscard]] bool isValid(std::string_view id) const;

	[[nodiscard]] std::size_t getMinLength() const noexcept;

	[[nodiscard]] std::size_t getMaxLength() const noexcept;

private:
	static constexpr std::size_t minLength_{ 6 };
	static constexpr std::size_t maxLength_{ 12 };
};

class NameValidator : public StringValidator {
public:
	[[nodiscard]] bool isValid(std::string_view name) const;

	[[nodiscard]] std::size_t getMinLength() const noexcept;

	[[nodiscard]] std::size_t getMaxLength() const noexcept;

private:
	static constexpr std::size_t minLength_{ 2 };
	static constexpr std::size_t maxLength_{ 50 };
};

class CategoryValidator : public StringValidator {
public:
	[[nodiscard]] bool isValid(std::string_view category) const;

	[[nodiscard]] std::size_t getMinLength() const noexcept;

	[[nodiscard]] std::size_t getMaxLength() const noexcept;

private:
	static constexpr std::size_t minLength_{ 2 };
	static constexpr std::size_t maxLength_{ 50 };
};

class UnitPriceValidator {
public:
	[[nodiscard]] bool isValid(double unitPrice) const;

	[[nodiscard]] double getMinPrice() const noexcept;

	[[nodiscard]] double getMaxPrice() const noexcept;

private:
	static constexpr double minUnitPrice_{ 0 };
	static constexpr double maxUnitPrice_{ 500'000 };
};

class StockValidator {
public:
	[[nodiscard]] bool isValid(int stock) const;

	[[nodiscard]] int getMinStock() const noexcept;

	[[nodiscard]] int getMaxStock() const noexcept;

private:
	static constexpr int minStock_{ 0 };
	static constexpr int maxStock_{ 250'000 };
};

class InventoryValueValidator {
public:
	[[nodiscard]] bool isValid(long double inventoryValue) const;

	[[nodiscard]] long double getMinInventoryValue() const noexcept;

	[[nodiscard]] long double getMaxInventoryValue() const noexcept;

private:
	static constexpr long double minInventoryValue_{ 0 };
	static constexpr long double maxInventoryValue_{ 125'000'000'000 };
};