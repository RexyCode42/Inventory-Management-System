#include "ProductSetup.h"

std::tuple<std::string, std::string, std::string, double, int>
getProductAttributes(const std::string& lastProductId) {
	const std::string id{
		Inventory::IdGenerator{}.generateId(lastProductId)
	};
	const std::string name{
		promptUserForAttribute<std::string>(NameRequirementsPrinter{}, NameValidator{}, "name")
	};
	const std::string category{
		promptUserForAttribute<std::string>(CategoryRequirementsPrinter{}, CategoryValidator{}, "category")
	};
	const double unitPrice{
		promptUserForAttribute<double>(UnitPriceRequirementsPrinter{}, UnitPriceValidator{}, "price")
	};
	const int stock{
		promptUserForAttribute<int>(StockRequirementsPrinter{}, StockValidator{}, "stock")
	};
	return { id, name, category, unitPrice, stock };
}

Inventory::Product createProduct(
	const std::tuple<std::string, std::string, std::string, double, int>& attributes) {
	const auto [id, name, category, unitPrice, stock] {attributes};
	return Inventory::Product{ id, name, category, unitPrice, stock };
}