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

    [[nodiscard]] std::string getFileExtension(
        FileExtensionOption fileExtension);

    std::function<std::string(const Inventory::Product&)> getFileFormat(
        FileExtensionOption fileExtension);

    [[nodiscard]] std::filesystem::path getUserFilePath(
        FileExtensionOption fileExtension);
}