#pragma once

#include "../Model/Product.h"
#include "../DataAccess/InMemoryStorage.h"
#include "../DataAccess/File.h"
#include "../DataAccess/Process.h"
#include "../DataAccess/Formats.h"
#include "../UserInteraction/ProductSetup.h"
#include "../UserInteraction/ProductSearch.h"
#include "../UserInteraction/UserInput/PromptOptions.h"
#include "../Utils/IOStreamUtils/SettingStreamAlignment.h"
#include "../Utils/ConstantVariableUtils/ConstantUtils.h"
#include "../Utils/ProductTableUtils/TableUtils.h"
#include "../Utils/ProductTableUtils/ProductUtils.h"
#include "../Utils/FileUtils/FileManipulation.h"

namespace Inventory {
    [[nodiscard]] std::expected<std::vector<Inventory::Product>, std::string> loadProductsFromFile();

    void addProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage);

    [[nodiscard]] std::expected<void, std::string> removeProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage);

    [[nodiscard]] std::expected<void, std::string> updateProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage);

    [[nodiscard]] std::expected<void, std::string> searchProducts(const std::span<const Inventory::Product>& products);

    [[nodiscard]] std::expected<void, std::string> viewAllProducts(const std::span<const Inventory::Product>& products);

    [[nodiscard]] std::expected<void, std::string> saveProductsToFile(const std::span<const Inventory::Product>& products);
}