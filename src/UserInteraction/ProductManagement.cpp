#include "ProductManagement.h"

[[nodiscard]] static std::expected<std::vector<Inventory::Product>, std::string> loadFromExternal() {
    const std::filesystem::path filePath{ FileHelpers::getUserFilePath() };

    auto readResult{ File{}.readAllLines(filePath) };

    if (!readResult.has_value())
        return std::unexpected(readResult.error());

    auto delimiterOpt{ FileHelpers::getDelimiterFromExtension(filePath) };

    if (!delimiterOpt.has_value())
        return std::unexpected("Could not determine delimiter for file extension: \"" +
            filePath.extension().generic_string() + "\".");

    return process(readResult.value(), delimiterOpt.value());
}

[[nodiscard]] static std::expected<std::vector<Inventory::Product>, std::string> loadFromInternal() {
    auto readResult{ File{}.readAllLines(ConstantHelpers::internalFilePath) };

    if (!readResult.has_value())
        return std::unexpected(readResult.error());

    return process(readResult.value(), ConstantHelpers::internalFileDelimiter);
}

[[nodiscard]] std::expected<std::vector<Inventory::Product>, std::string> Inventory::loadProductsFromFile() {
    constexpr LoadModeOption minLoadMode{ LoadModeOption::LOAD_FROM_EXTERNAL };
    constexpr LoadModeOption maxLoadMode{ LoadModeOption::LOAD_FROM_INTERNAL };
    const LoadModeOption loadMode{
        promptUserForChoice(UserSelection::displayLoadModeOptions, minLoadMode, maxLoadMode)
    };

    switch (loadMode) {
    case LoadModeOption::LOAD_FROM_EXTERNAL:
        return loadFromExternal();
    case LoadModeOption::LOAD_FROM_INTERNAL:
        return loadFromInternal();
    [[unlikely]] default:
        throw std::logic_error("Unexpected loading mode chosen.");
    }
}

void Inventory::addProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage) {
    const auto& products{ inMemoryProductStorage.getProducts() };

    const auto lastProductId{ (!products.empty()) ?
        products.back().getId() : ""
    };

    const auto attributes{ getProductAttributes(lastProductId) };

    const auto product{ createProduct(attributes) };

    inMemoryProductStorage.add(product);
}

[[nodiscard]] std::expected<void, std::string> Inventory::removeProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage) {
    if (inMemoryProductStorage.getProducts().empty())
        return std::unexpected("No products available to remove.");

    const std::string id{
        promptUserForAttribute<std::string>(
            IdRequirementsPrinter{},
            IdValidator{},
            "id")
    };

    const auto foundProductOpt{ inMemoryProductStorage.getProductReferenceById(id) };

    if (!foundProductOpt.has_value())
        return std::unexpected("Product ID: " + id + " could not be found.");

    const auto& product{ foundProductOpt->get() };

    if (const auto viewResult{ viewAllProducts(std::span{ &product, 1 }) }; !viewResult.has_value())
        return viewResult;

    constexpr DeleteOption minChoice{ DeleteOption::YES };
    constexpr DeleteOption maxChoice{ DeleteOption::NO };

    const DeleteOption userChoice{
        promptUserForChoice(
            UserSelection::displayProductRemoveOptions,
            minChoice,
            maxChoice)
    };

    switch (userChoice) {
    case DeleteOption::YES:
        inMemoryProductStorage.remove(product);
        return {};
    case DeleteOption::NO:
        return {};
    [[unlikely]] default:
        throw std::logic_error("Unexpected delete option chosen.");
    }
}

[[nodiscard]] std::expected<void, std::string> Inventory::updateProduct(
    Inventory::InMemoryProductStorage& inMemoryProductStorage) {
    if (inMemoryProductStorage.getProducts().empty())
        return std::unexpected("No products available to update.");

    const std::string id{
        promptUserForAttribute<std::string>(
            IdRequirementsPrinter{},
            IdValidator{},
            "id")
    };

    const auto foundProductOpt{ inMemoryProductStorage.getProductReferenceById(id) };

    if (!foundProductOpt.has_value())
        return std::unexpected("Product ID: " + id + " could not be found.");

    constexpr UpdateOption minChoice{ UpdateOption::NAME };
    constexpr UpdateOption maxChoice{ UpdateOption::ALL_OF_THE_ABOVE };

    const UpdateOption userChoice{
        promptUserForChoice(
            UserSelection::displayProductUpdateOptions,
            minChoice,
            maxChoice)
    };

    auto& foundProduct{ foundProductOpt->get() };

    return inMemoryProductStorage.promptAndUpdate(userChoice, foundProduct);
}

[[nodiscard]] std::expected<void, std::string> Inventory::searchProducts(const std::span<const Inventory::Product>& products) {
    if (products.empty())
        return std::unexpected("No products available to search.");

    const auto foundProducts{ searchForProducts(products) };

    if (!foundProducts.has_value())
        return std::unexpected("Product(s) could not be found.");

    return viewAllProducts(foundProducts.value());
}

static void printTable(
    const std::array<std::string, ConstantHelpers::columnSize>& header,
    const ProductHelpers::StringProducts& stringProducts,
    const TableHelpers::Widths& widths) {
    IOStreamHelpers::setOutputAlignment(std::ios::left);

    TableHelpers::printHeader(header, widths);

    TableHelpers::printValues(stringProducts, widths);

    IOStreamHelpers::setOutputAlignment(); // Sets the alignment back to the default state
}

[[nodiscard]] std::expected<void, std::string> Inventory::viewAllProducts(const std::span<const Inventory::Product>& products) {
    if (products.empty())
        return std::unexpected("No products available to view.");

    const std::array<std::string, ConstantHelpers::columnSize> header{
        "ID", "NAME", "CATEGORY", "PRICE", "STOCK", "INVENTORY VALUE"
    };

    const ProductHelpers::StringProducts stringProducts{ ProductHelpers::productsAsStrings(products) };

    const TableHelpers::Widths widths{ TableHelpers::calculateColumnWidths(stringProducts, header) };

    printTable(header, stringProducts, widths);

    return {};
}

[[nodiscard]] static std::expected<void, std::string> saveToExternal(
    const std::span<const Inventory::Product>& products) {
    constexpr FileExtensionOption minFileExtension{ FileExtensionOption::TXT };
    constexpr FileExtensionOption maxFileExtension{ FileExtensionOption::CSV };
    const FileExtensionOption fileExtension{
        promptUserForChoice(UserSelection::displayFileExtensionOptions, minFileExtension, maxFileExtension)
    };

    const std::filesystem::path filePath{ FileHelpers::getUserFilePath(fileExtension) };

    const std::string contents{
        StringHelpers::getCollectionAsFormattedString(products, FileHelpers::getFileFormat(fileExtension))
    };

    return File{}.writeAllText(filePath, contents);
}

[[nodiscard]] static std::expected<void, std::string> saveToInternal(
    const std::span<const Inventory::Product>& products) {
    const std::string contents{
            StringHelpers::getCollectionAsFormattedString(products, CsvProductFormat{})
    };

    return File{}.writeAllText(ConstantHelpers::internalFilePath, contents);
}

[[nodiscard]] std::expected<void, std::string> Inventory::saveProductsToFile(
    const std::span<const Inventory::Product>& products) {
    if (products.empty())
        return std::unexpected("No products available to save to file.");

    constexpr SaveModeOption minSaveMode{ SaveModeOption::SAVE_TO_EXTERNAL };
    constexpr SaveModeOption maxSaveMode{ SaveModeOption::SAVE_TO_INTERNAL };
    const SaveModeOption saveMode{
        promptUserForChoice(UserSelection::displaySaveModeOptions, minSaveMode, maxSaveMode)
    };

    switch (saveMode) {
    case SaveModeOption::SAVE_TO_EXTERNAL:
        return saveToExternal(products);
    case SaveModeOption::SAVE_TO_INTERNAL:
        return saveToInternal(products);
    [[unlikely]] default:
        throw std::logic_error("Unexpected saving mode chosen.");
    }
}