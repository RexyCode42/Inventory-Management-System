#include "ProductSearch.h"

[[nodiscard]] std::function<bool(const Inventory::Product&)> getProductSearchPredicate() {
    constexpr SearchOption minChoice{ SearchOption::ID };
    constexpr SearchOption maxChoice{ SearchOption::INVENTORY_VALUE };

    const SearchOption userChoice{ promptUserForChoice(
        UserSelection::displayProductSearchOptions,
        minChoice,
        maxChoice)
    };

    // Using enums for improved clarity and type safety over raw integers

    switch (userChoice) {
    case SearchOption::ID:
        // Prompt the user to enter an attribute (e.g., ID in this case)
        // Return a lambda that captures the entered value for comparison
        return [id = promptUserForAttribute<std::string>(
            IdRequirementsPrinter{},
            IdValidator{},
            "id")]
            (const Inventory::Product& product) {
            return product.getId() == id;
            };
    case SearchOption::NAME:
        // Prompt for name and return a comparison lambda
        return [name = promptUserForAttribute<std::string>(
            NameRequirementsPrinter{},
            NameValidator{},
            "name")]
            (const Inventory::Product& product) {
            return product.getName() == name;
            };
    case SearchOption::CATEGORY:
        // Prompt for category and return a comparison lambda
        return [category = promptUserForAttribute<std::string>(
            CategoryRequirementsPrinter{},
            CategoryValidator{},
            "category")]
            (const Inventory::Product& product) {
            return product.getCategory() == category;
            };
    case SearchOption::PRICE:
        // Prompt for price and return a comparison lambda
        return [unitPrice = promptUserForAttribute<double>(
            UnitPriceRequirementsPrinter{},
            UnitPriceValidator{},
            "price")]
            (const Inventory::Product& product) {
            return product.getPrice() == unitPrice;
            };
    case SearchOption::STOCK:
        // Prompt for stock and return a comparison lambda
        return [stock = promptUserForAttribute<int>(
            StockRequirementsPrinter{},
            StockValidator{},
            "stock")]
            (const Inventory::Product& product) {
            return product.getStock() == stock;
            };
    case SearchOption::INVENTORY_VALUE:
        // Prompt for inventory value and return a comparison lambda
        return [inventoryValue = promptUserForAttribute<long double>(
            InventoryValueRequirementsPrinter{},
            InventoryValueValidator{},
            "inventory value")]
            (const Inventory::Product& product) {
            return product.calculateInventoryValue() == inventoryValue;
            };
    default:
        throw std::logic_error("Unexpected search predicate chosen.");
    }
}

[[nodiscard]] std::optional<std::vector<Inventory::Product>>
searchProductsByAttribute(
    const std::span<const Inventory::Product>& products,
    std::function<bool(const Inventory::Product&)> searchPredicate) {
    if (products.empty())
        return std::nullopt;

    // Future Improvement:
    // If the search predicate is expected to filter out many products, 
    // this could lead to an over-allocation. 
    std::vector<Inventory::Product> productsFound;
    productsFound.reserve(products.size());

    std::ranges::copy_if(
        products,
        std::back_inserter(productsFound),
        searchPredicate);

    productsFound.shrink_to_fit();

    return (!productsFound.empty()) ?
        std::make_optional(std::move(productsFound)) : std::nullopt;
}

[[nodiscard]] std::optional<std::vector<Inventory::Product>> searchForProducts(const std::span<const Inventory::Product>& products) {
    if (products.empty())
        return std::nullopt;

    const auto searchPredicate{ getProductSearchPredicate() };

    return searchProductsByAttribute(products, searchPredicate);
}