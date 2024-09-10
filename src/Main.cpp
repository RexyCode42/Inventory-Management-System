#include <iostream>
#include <functional>
#include <vector>
#include <unordered_set>
#include <limits>
#include <expected>
#include "Product.h"
#include "DataAccess/InMemoryStorage.h"
#include "UserInteraction/ProductManagement/ProductSetup.h"
#include "Utils/IOStreamUtils/SettingStreamAlignment.h"
#include "Utils/ConstantVariableUtils/ConstantUtils.h"
#include "Utils/ProductTableUtils/TableUtils.h"
#include "Utils/ProductTableUtils/ProductUtils.h"

// IMS = Inventory Management System
//class IUserInteraction {
//public:
//	virtual void showMessage(const std::string& message) const = 0;
//
//	virtual ~IIMSUserInteraction() = default;
//};
//
//class ConsoleUserInteraction : IIMSUserInteraction {
//public:
//	void showMessage(const std::string& message) const override {
//		std::cout << message << std::endl;
//	}
//};

void viewAllProducts(const std::span<const Inventory::Product>& products) {
    if (products.empty()) {
        std::cerr << "No products available to display." << '\n';
        return;
    }

    constexpr std::array<std::string_view, ConstantHelpers::countOfColumns> tableHeader{
        "ID", "NAME", "CATEGORY", "PRICE", "STOCK", "INVENTORY VALUE"
    };
    const ProductHelpers::StringProducts stringProducts{ ProductHelpers::convertProductsToStringArrays(products) };
    const TableHelpers::Widths widths{ TableHelpers::calculateColumnWidths(stringProducts, tableHeader) };
    IOStreamHelpers::setOutputAlignment(std::ios::left);
    TableHelpers::printTableHeader(tableHeader, widths);
    TableHelpers::printTableValues(stringProducts, widths);
    IOStreamHelpers::setOutputAlignment(); // Sets the alignment back to the default state
}

void addProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage) {
	const auto lastProductId{ (!inMemoryProductStorage.getProducts().empty()) ?
		inMemoryProductStorage.getProducts().back().getId() : ""
	};
	const auto attributes{ getProductAttributes(lastProductId) };
	const auto product{ createProduct(attributes) };
	inMemoryProductStorage.add(product);
}

class InventoryManagementSystemApplication {
public:
	void Run();

private:
    Inventory::InMemoryProductStorage inMemoryProductStorage_{};
};

void InventoryManagementSystemApplication::Run() {
	addProduct(inMemoryProductStorage_);
	addProduct(inMemoryProductStorage_);

    viewAllProducts(inMemoryProductStorage_.getProducts());
}

int main() {
	 InventoryManagementSystemApplication inventoryManagementSystemApp{};
	 inventoryManagementSystemApp.Run();
}


