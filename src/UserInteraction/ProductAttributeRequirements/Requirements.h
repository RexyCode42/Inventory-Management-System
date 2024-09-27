#pragma once

#include <iostream>
#include <../src/ErrorHandling/ProductAttributeValidators/Validators.h>

class IdRequirementsPrinter {
public:
	void print(const IdValidator& nameValidator) const noexcept;
};

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

class InventoryValueRequirementsPrinter {
public:
	void print(const InventoryValueValidator& nameValidator) const noexcept;
};