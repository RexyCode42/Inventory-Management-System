#include "FileManipulation.h"

[[nodiscard]] std::filesystem::path FileHelpers::buildFilePath(
    const std::string& fileName, const std::string& extension) {
    std::filesystem::path path{ fileName };
    path.replace_extension(extension); // Adds extension if it doesn't exist.
    return path;
}

[[nodiscard]] std::string FileHelpers::getFileExtension(
    FileExtensionOption fileExtension) {
    switch (fileExtension) {
    case FileExtensionOption::TXT:
        return ".txt";
    case FileExtensionOption::CSV:
        return ".csv";
    default:
        throw std::logic_error("Unexpected file format chosen.");
    }
}

std::function<std::string(const Inventory::Product&)> FileHelpers::getFileFormat(
    FileExtensionOption fileExtension) {
    switch (fileExtension) {
    case FileExtensionOption::TXT:
        return TxtProductFormat{};
    case FileExtensionOption::CSV:
        return CsvProductFormat{};
    default:
        throw std::logic_error("Unexpected file extension chosen.");
    }
}

[[nodiscard]] std::filesystem::path FileHelpers::getUserFilePath(
    FileExtensionOption fileExtension) {
    const std::string fileName{
        promptUserForAttribute<std::string>(FileNameRequirementsPrinter{}, FileNameValidator{}, "file name")
    };

    const std::string extension{ FileHelpers::getFileExtension(fileExtension) };

    return FileHelpers::buildFilePath(fileName, extension);
}
