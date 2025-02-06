#include "FileManipulation.h"

[[nodiscard]] std::filesystem::path FileHelpers::buildFilePath(
    const std::string& fileName, const std::string& extension) {
    std::filesystem::path path{ fileName };
    path.replace_extension(extension); // Adds extension if it doesn't exist.
    return path;
}

[[nodiscard]] std::string FileHelpers::getFileExtensionAsString(
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

[[nodiscard]] std::function<std::string(const Inventory::Product&)> FileHelpers::getFileFormat(
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

[[nodiscard]] std::filesystem::path FileHelpers::getUserFilePath() {
    std::string filePath{};

    std::cout << "Enter file path: ";
    std::getline(std::cin >> std::ws, filePath);

    return filePath;
}

[[nodiscard]] std::filesystem::path FileHelpers::getUserFilePath(FileExtensionOption fileExtension) {
    const std::string fileName{
        promptUserForAttribute<std::string>(FileNameRequirementsPrinter{}, FileNameValidator{}, "file name")
    };

    const std::string extension{ FileHelpers::getFileExtensionAsString(fileExtension) };

    return FileHelpers::buildFilePath(fileName, extension);
}

[[nodiscard]] std::optional<char> FileHelpers::getDelimiterFromExtension(const std::filesystem::path& filePath) {
    static const std::unordered_map<std::filesystem::path, char> mapExtensionToDelimiter{
        { ".txt",',' },
        { ".csv",',' }
    };

    const auto extension{ filePath.extension() };

    return mapExtensionToDelimiter.contains(extension) ?
        std::optional{ mapExtensionToDelimiter.at(extension) } : std::nullopt;
}