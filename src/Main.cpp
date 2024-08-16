// #include "ManagementSystem.h"
#include <iostream>
#include <functional>
#include <vector>
#include <unordered_set>
#include <limits>
#include <expected>
#include "Product.h"
#include "DataAccess/InMemoryStorage.h"
#include "UserInteraction/ProductManagement/ProductSetup.h"

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
	void Run() const;
};

void InventoryManagementSystemApplication::Run() const {
	Inventory::InMemoryProductStorage inMemoryProductStorage{};
	addProduct(inMemoryProductStorage);
	addProduct(inMemoryProductStorage);
	
	const auto& products{ inMemoryProductStorage.getProducts() };

	for (const auto& product : products) {
		std::cout 
			<< product.getId() << ", "
			<< product.getName() << ", "
			<< product.getCategory() << ", "
			<< product.getPrice() << ", "
			<< product.getStock() << ", "
			<< product.calculateInventoryValue() << '\n';
	}		
}

int main() {
	 InventoryManagementSystemApplication inventoryManagementSystemApp{};
	 inventoryManagementSystemApp.Run();
}


