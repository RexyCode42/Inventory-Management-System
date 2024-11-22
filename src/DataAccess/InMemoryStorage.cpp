#include "InMemoryStorage.h"

using namespace Inventory;

InMemoryProductStorage::InMemoryProductStorage(std::vector<Product> products) : 
	products_{ std::move(products) } {}

void InMemoryProductStorage::add(const Product& product) {
	const std::string name{ product.getName() };

	if (doesProductNameExist(name)) {
		std::cout << "Product name: " + name + " already exists." << '\n';
		return;
	}

	products_.emplace_back(product);
}

void InMemoryProductStorage::remove(const Product& product) {
	products_.erase(std::ranges::find(products_, product));
}

[[nodiscard]] std::expected<void, std::string> InMemoryProductStorage::promptAndUpdate(
	const UpdateOption& userChoice, Product& foundProduct)
{
	switch (userChoice) {
	case UpdateOption::NAME: {
		const std::string name{
			promptUserForAttribute<std::string>(
				NameRequirementsPrinter{},
				NameValidator{},
				"name")
		};

		if (doesProductNameExist(name))
			return std::unexpected("Product name: " + name + " already exists.");

		foundProduct.setName(name);
	}
		break;
	case UpdateOption::CATEGORY: {
		const std::string category{
			promptUserForAttribute<std::string>(
				CategoryRequirementsPrinter{},
				CategoryValidator{},
				"category")
		};

		foundProduct.setCategory(category);
	}
		break;
	case UpdateOption::PRICE: {
		const double unitPrice{
			promptUserForAttribute<double>(
				UnitPriceRequirementsPrinter{},
				UnitPriceValidator{},
				"unit price")
		};

		foundProduct.setPrice(unitPrice);
	}
		break;
	case UpdateOption::STOCK: {
		const int stock{
			promptUserForAttribute<int>(
				StockRequirementsPrinter{},
				StockValidator{},
				"stock")
		};

		foundProduct.setStock(stock);
	}
		break;
	case UpdateOption::ALL_OF_THE_ABOVE: {
		auto isPromptSuccessful{ promptUserForUpdatedAttributes() };

		if (!isPromptSuccessful.has_value())
			return std::unexpected(isPromptSuccessful.error());

		const auto [name, category, unitPrice, stock] {isPromptSuccessful.value()};

		foundProduct.setAll(name, category, unitPrice, stock);
	}
		break;
	default: {
		throw std::runtime_error("Unexpected update option chosen.");
	}
	}

	return std::expected<void, std::string>();
}

[[nodiscard]] const std::vector<Product>& InMemoryProductStorage::getProducts() const noexcept {
	return products_;
}

[[nodiscard]] InMemoryProductStorage::OptionalProductReference 
InMemoryProductStorage::getProductReferenceById(std::string_view id) {
	auto isTargetId{ [&id](const Product& product) { return product.getId() == id; } };
	const auto foundProduct{ std::ranges::find_if(products_, isTargetId) };

	return (foundProduct != std::end(products_)) ? 
		InMemoryProductStorage::OptionalProductReference(*foundProduct) : std::nullopt;
}

[[nodiscard]] bool InMemoryProductStorage::doesProductNameExist(std::string_view name) const {
	auto isTargetName{ [&name](const Product& product) { return product.getName() == name; } };
	return std::ranges::any_of(products_, isTargetName);
}

[[nodiscard]] InMemoryProductStorage::ExpectedProductAttributes
InMemoryProductStorage::promptUserForUpdatedAttributes() const {
	const std::string name{
		promptUserForAttribute<std::string>(
			NameRequirementsPrinter{}, 
			NameValidator{}, 
			"name")
	};

	if (doesProductNameExist(name))
		return std::unexpected("Product name: " + name + " already exists.");

	const std::string category{
		promptUserForAttribute<std::string>(
			CategoryRequirementsPrinter{},
			CategoryValidator{},
			"category")
	};

	const double unitPrice{
		promptUserForAttribute<double>(
			UnitPriceRequirementsPrinter{},
			UnitPriceValidator{},
			"unit price")
	};

	const int stock{
		promptUserForAttribute<int>(
			StockRequirementsPrinter{},
			StockValidator{},
			"stock")
	};

	return std::tuple{ name,category,unitPrice,stock };
}
