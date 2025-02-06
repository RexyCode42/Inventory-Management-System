#include "File.h"
 
[[nodiscard]] std::expected<void, std::string> File::writeAllText(
    const std::filesystem::path& filePath,
    const std::string& contents) const {
    validateFilePath(filePath);

    auto wasWriteSuccessful{
        writeToFile(filePath, contents, std::ofstream::out)
    };

    return wasWriteSuccessful;
}

[[nodiscard]] std::expected<void, std::string> File::appendAllText(
    const std::filesystem::path& filePath,
    const std::string& contents) const {
    validateFilePath(filePath);

    auto wasWriteSuccessful{
        writeToFile(filePath, contents, std::ofstream::app)
    };

    return wasWriteSuccessful;
}

[[nodiscard]] std::expected<std::string, std::string> File::readAllText(
    const std::filesystem::path& filePath) const {
    validateFilePath(filePath);

    auto getContentAsString{
        [](std::ifstream& file) {
            return std::string(
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>());
        }
    };

    auto readResult{
        readFromFile<std::string>(filePath, getContentAsString)
    };

    return readResult;
}

[[nodiscard]] std::expected<std::vector<std::string>, std::string> File::readAllLines(
    const std::filesystem::path& filePath) const {
    validateFilePath(filePath);

    auto getContentAsLines{
        [](std::ifstream& file) {
            std::vector<std::string> lines{};

            for (std::string line{}; std::getline(file, line);)
                lines.emplace_back(line);

            lines.shrink_to_fit();

            return lines;
        }
    };

    auto readResult{
        readFromFile<std::vector<std::string>>(filePath, getContentAsLines)
    };

    return readResult;
}

void File::validateFilePath(const std::filesystem::path& filePath) const {
    if (filePath.empty())
        throw std::invalid_argument("File path cannot be empty.");

    if (filePath.string().length() > ConstantHelpers::maxPathLength)
        throw std::invalid_argument(
            "File path length is too large. Path length: " +
            std::to_string(filePath.string().length()) +
            ", Maximum path length: " +
            std::to_string(ConstantHelpers::maxPathLength) + ".");
}

[[nodiscard]] std::expected<void, std::string> File::writeToFile(
    const std::filesystem::path& filePath,
    const std::string& contents,
    std::ofstream::openmode openMode) const {
    auto createFilePathMessage{
        [&filePath]() { return "File: \"" + filePath.string() + "\""; }
    };

    std::ofstream file(filePath, openMode);

    if (!file.is_open())
        return std::unexpected(createFilePathMessage() + " could not be opened.");

    file << contents;

    if (!file.good())
        return std::unexpected(createFilePathMessage() + " could not be written to.");

    return {};
}