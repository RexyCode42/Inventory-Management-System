#pragma once

#include <iostream>
#include <../src/ErrorHandling/ProductAttributeValidators/Validators.h>

class NameRequirementsPrinter {
public:
	void print(const NameValidator& nameValidator) const noexcept;
};

class CategoryRequirementsPrinter {
public:
	void print(const CategoryValidator& categoryValidator) const noexcept;
};

class UnitPriceRequirementsPrinter {
public:
	void print(const UnitPriceValidator& unitPriceValidator) const noexcept;
};

class StockRequirementsPrinter {
public:
	void print(const StockValidator& stockValidator) const noexcept;
};