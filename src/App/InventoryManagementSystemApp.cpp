#include "InventoryManagementSystemApp.h"

void InventoryManagementSystem::Run() const {
    const auto loadResult{ Inventory::loadProductsFromFile() };

    handleResult(loadResult);

    Inventory::InMemoryProductStorage inMemoryStorage(
        std::move(loadResult.value_or(std::vector<Inventory::Product>{})));

    constexpr InventoryOption minChoice{ InventoryOption::ADD_PRODUCT };
    constexpr InventoryOption maxChoice{ InventoryOption::EXIT };

    bool shallExit{ false };

    while (!shallExit) {
        switch (promptUserForChoice(
            UserSelection::displayInventoryOptions, minChoice, maxChoice)) {
        case InventoryOption::ADD_PRODUCT:
            Inventory::addProduct(inMemoryStorage);
            break;
        case InventoryOption::REMOVE_PRODUCT:
            handleResult(Inventory::removeProduct(inMemoryStorage));
            break;
        case InventoryOption::UPDATE_PRODUCT:
            handleResult(Inventory::updateProduct(inMemoryStorage));
            break;
        case InventoryOption::SEARCH_PRODUCT:
            handleResult(Inventory::searchProducts(inMemoryStorage.getProducts()));
            break;
        case InventoryOption::VIEW_ALL_PRODUCTS:
            handleResult(Inventory::viewAllProducts(inMemoryStorage.getProducts()));
            break;
        case InventoryOption::SAVE_PRODUCTS_TO_FILE:
            handleResult(Inventory::saveProductsToFile(inMemoryStorage.getProducts()));
            break;
        case InventoryOption::EXIT:
            shallExit = true;
            break;
        [[unlikely]] default:
            throw std::logic_error("Unexpected inventory management option chosen.");
        }
    }
}
