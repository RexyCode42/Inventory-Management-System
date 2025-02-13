#pragma once

#include <filesystem>
#include <string>
#include <functional>
#include "../../Model/Product.h"
#include "../../DataAccess/Formats.h"
#include "../../UserInteraction/UserOptions/Options.h"
#include "../../UserInteraction/ProductAttributeRequirements/Requirements.h"
#include "../../UserInteraction/UserInput/PromptAttribute.h"

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