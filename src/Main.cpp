#include "DataAccess/InMemoryStorage.h"
#include "DataAccess/File.h"
#include "DataAccess/Process.h"
#include "DataAccess/FileFormats/Formats.h"
#include "UserInteraction/ProductManagement/ProductSetup.h"
#include "UserInteraction/ProductManagement/ProductSearch.h"
// Reintroduce the displayProduct function 
// once the viewAllProducts function is placed inside its own file
// #include "UserInteraction/ProductManagement/ProductDisplay.h"
#include "UserInteraction/UserInput/PromptOptions.h"
#include "Utils/IOStreamUtils/SettingStreamAlignment.h"
#include "Utils/ConstantVariableUtils/ConstantUtils.h"
#include "Utils/ProductTableUtils/TableUtils.h"
#include "Utils/ProductTableUtils/ProductUtils.h"
#include "Utils/FileUtils/FileManipulation.h"

[[nodiscard]] std::expected<std::vector<Inventory::Product>, std::string> loadFromExternal() {
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

[[nodiscard]] std::expected<std::vector<Inventory::Product>, std::string> loadFromInternal() {
    auto readResult{ File{}.readAllLines(ConstantHelpers::internalFilePath) };

    if (!readResult.has_value())
        return std::unexpected(readResult.error());

    return process(readResult.value(), ConstantHelpers::internalFileDelimiter);
}

[[nodiscard]] std::expected<std::vector<Inventory::Product>, std::string> loadProductsFromFile() {
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

[[nodiscard]] std::expected<void, std::string> saveProductsToFile(const std::span<const Inventory::Product>& products) {
    if (products.empty())
        return std::unexpected("No products available to save to file.");

    constexpr SaveModeOption minSaveMode{ SaveModeOption::SAVE_TO_NEW };
    constexpr SaveModeOption maxSaveMode{ SaveModeOption::SAVE_TO_INTERNAL };
    const SaveModeOption saveMode{
        promptUserForChoice(UserSelection::displaySaveModeOptions, minSaveMode, maxSaveMode)
    };

    switch (saveMode) {
    case SaveModeOption::SAVE_TO_NEW:
    {
        constexpr FileExtensionOption minFileExtension{ FileExtensionOption::TXT };
        constexpr FileExtensionOption maxFileExtension{ FileExtensionOption::CSV };
        const FileExtensionOption fileExtension{
            promptUserForChoice(UserSelection::displayFileExtensionOptions, minFileExtension, maxFileExtension)
        };

        const std::filesystem::path filePath{ FileHelpers::getUserFilePath(fileExtension) };

        const std::string contents{
            StringHelpers::getCollectionAsFormattedString(products, FileHelpers::getFileFormat(fileExtension))
        };

        auto writeResult{ File{}.writeAllText(filePath, contents) };

        return writeResult;
    }
    case SaveModeOption::SAVE_TO_INTERNAL:
    {
        const std::string contents{
            StringHelpers::getCollectionAsFormattedString(products, CsvProductFormat{})
        };

        auto writeResult{ File{}.appendAllText(ConstantHelpers::internalFilePath, contents) };

        return writeResult;
    }
    [[unlikely]] default:
        throw std::logic_error("Unexpected saving mode chosen.");
    }
}

[[nodiscard]] std::expected<void, std::string> updateProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage) {
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

    const auto isUpdateSuccessful{ inMemoryProductStorage.promptAndUpdate(userChoice, foundProduct) };

    if (!isUpdateSuccessful.has_value())
        return isUpdateSuccessful;

    return {}; // Success case
}

void addProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage) {
    const auto lastProductId{ (!inMemoryProductStorage.getProducts().empty()) ? 
        inMemoryProductStorage.getProducts().back().getId() : 
        "" };
	const auto attributes{ getProductAttributes(lastProductId) };
	const auto product{ createProduct(attributes) };

	inMemoryProductStorage.add(product);
}

void viewAllProducts(const std::span<const Inventory::Product>& products) {
    if (products.empty()) {
        std::cout << "No products available to display." << '\n';
        return;
    }

    constexpr std::array<std::string_view, ConstantHelpers::columnSize> tableHeader{
        "ID", "NAME", "CATEGORY", "PRICE", "STOCK", "INVENTORY VALUE"
    };

    const ProductHelpers::StringProducts stringProducts{ ProductHelpers::convertProductsToStringArrays(products) };

    const TableHelpers::Widths widths{ TableHelpers::calculateColumnWidths(stringProducts, tableHeader) };

    IOStreamHelpers::setOutputAlignment(std::ios::left);

    TableHelpers::printTableHeader(tableHeader, widths);

    TableHelpers::printTableValues(stringProducts, widths);

    IOStreamHelpers::setOutputAlignment(); // Sets the alignment back to the default state
}

[[nodiscard]] std::expected<void, std::string> removeProduct(Inventory::InMemoryProductStorage& inMemoryProductStorage) {
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

    viewAllProducts(std::span{ &product, 1 });

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

void displayFoundProducts(const std::optional<std::vector<Inventory::Product>>& foundProducts) {
    if (!foundProducts.has_value()) {
        std::cout << "Product(s) could not be found." << '\n';
        return;
    }

    viewAllProducts(foundProducts.value());
}

void searchAndDisplayProducts(const std::span<const Inventory::Product>& products) {
    if (products.empty()) {
        std::cout << "No products available to search." << '\n';
        return;
    }

    const auto foundProducts{ searchForProducts(products) };

    displayFoundProducts(foundProducts);
}

class InventoryManagementSystemApp {
public:
	void Run();

private:
    Inventory::InMemoryProductStorage inMemoryProductStorage_{};
};

void InventoryManagementSystemApp::Run() {
	// addProduct(inMemoryProductStorage_);
	// addProduct(inMemoryProductStorage_);

    // searchAndDisplayProducts(inMemoryProductStorage_.getProducts());

    inMemoryProductStorage_.add({ "0000AA","carrot","food",0.99,30 });
    inMemoryProductStorage_.add({ "0001AA","apple","food",0.99,30 });

    if (auto saveResult{ saveProductsToFile(inMemoryProductStorage_.getProducts()) }; saveResult.has_value())
        std::cout << "Success" << '\n';

    viewAllProducts(inMemoryProductStorage_.getProducts());
}

int main() {
    try {
        InventoryManagementSystemApp{}.Run();
    }
    catch (const std::exception& ex) {
        std::cout <<
            "We're sorry, but it seems that the program encountered an unexpected issue. " <<
            "The program will now close." <<
            "Error: " <<
            ex.what();
    }
}


