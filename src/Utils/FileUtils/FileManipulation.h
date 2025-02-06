#pragma once

#include <filesystem>
#include <string>
#include <functional>
#include "../src/Product.h"
#include "../src/DataAccess/FileFormats/Formats.h"
#include "../src/UserInteraction/UserOptions/Options.h"
#include "../src/UserInteraction/ProductAttributeRequirements/Requirements.h"
#include "../src/UserInteraction/UserInput/PromptAttribute.h"

namespace FileHelpers {
    [[nodiscard]] std::filesystem::path buildFilePath(
        const std::string& fileName, const std::string& extension);

    [[nodiscard]] std::string getFileExtensionAsString(
        FileExtensionOption fileExtension);

    [[nodiscard]] std::function<std::string(const Inventory::Product&)> getFileFormat(
        FileExtensionOption fileExtension);

    [[nodiscard]] std::filesystem::path getUserFilePath();

    [[nodiscard]] std::filesystem::path getUserFilePath(FileExtensionOption fileExtension);

    [[nodiscard]] std::optional<char> getDelimiterFromExtension(const std::filesystem::path& filePath);
}