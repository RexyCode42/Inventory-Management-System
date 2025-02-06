#pragma once

#include <fstream>
#include <filesystem>
#include <expected>
#include <../src/Utils/ConstantVariableUtils/ConstantUtils.h>

class File {
public:
    File() = default;
    ~File() = default;

    File(const File&) = delete;
    File& operator=(const File&) = delete;
    File(File&&) = default;
    File& operator=(File&&) = default;

    /// Creates a new file, writes the specified string to the file, and then closes the file.
    /// If the target file already exists, it is overwritten.
    ///
    /// \param filePath: The path of the file to write to.
    /// \param contents: The content to write into the file.
    /// 
    /// \return std::expected: Nothing (void).
    /// \return std::unexpected: File could not be opened (std::string).
    /// \return std::unexpected: File could not be written to (std::string).
    /// 
    /// \exception std::invalid_argument: The path is empty.
    /// \exception std::invalid_argument: The path is too large.    
    [[nodiscard]] std::expected<void, std::string> writeAllText(
        const std::filesystem::path& filePath,
        const std::string& contents) const;

    /// Opens a file, appends the specified string to the file, and then closes the file. 
    /// If the file does not exist, this method creates a file, writes the specified string to the file, then closes the file.
    ///
    /// \param filePath: The path of the file to write to. 
    /// \param contents: The content to write into the file. 
    /// 
    /// \return std::expected: Nothing (void). 
    /// \return std::unexpected: File could not be opened (std::string). 
    /// \return std::unexpected: File could not be written to (std::string). 
    /// 
    /// \exception std::invalid_argument: The path is empty. 
    /// \exception std::invalid_argument: The path is too large. 
    [[nodiscard]] std::expected<void, std::string> appendAllText(
        const std::filesystem::path& filePath,
        const std::string& contents) const;

    /// Opens a text file, reads all the text in the file, and then closes the file.
    ///
    /// \param filePath: The path of the file to read from.
    /// 
    /// \return std::expected: All the text in the file (std::string).
    /// \return std::unexpected: File does not exist (std::string).
    /// \return std::unexpected: File could not be opened (std::string).
    /// \return std::unexpected: File could not be read from (std::string).
    /// 
    /// \exception std::invalid_argument: The path is empty.
    /// \exception std::invalid_argument: The path is too large.    
    [[nodiscard]] std::expected<std::string, std::string> readAllText(
        const std::filesystem::path& filePath) const;

    /// Opens a text file, reads all lines of the file, and then closes the file.
    ///
    /// \param filePath: The path of the file to read from.
    /// 
    /// \return std::expected: All lines from the file (std::vector<std::string>).
    /// \return std::unexpected: File does not exist (std::string).
    /// \return std::unexpected: File could not be opened (std::string).
    /// \return std::unexpected: File could not be read from (std::string).
    /// 
    /// \exception std::invalid_argument: The path is empty.
    /// \exception std::invalid_argument: The path is too large.    
    [[nodiscard]] std::expected<std::vector<std::string>, std::string> readAllLines(
        const std::filesystem::path& filePath) const;

private:
    void validateFilePath(const std::filesystem::path& filePath) const;

    [[nodiscard]] std::expected<void, std::string> writeToFile(
        const std::filesystem::path& filePath,
        const std::string& contents,
        std::ofstream::openmode openMode) const;

    template<class Result, typename Function>
        requires std::is_invocable_r_v<Result, Function, std::ifstream&>
    [[nodiscard]] std::expected<Result, std::string> readFromFile(
        const std::filesystem::path& filePath,
        Function&& getContent) const {
        auto createFilePathMessage{
            [&filePath]() { return "File: \"" + filePath.string() + "\""; }
        };

        if (!std::filesystem::exists(filePath))
            return std::unexpected(createFilePathMessage() + " does not exist.");

        if (std::filesystem::is_empty(filePath))
            return std::unexpected(createFilePathMessage() + " is empty.");

        std::ifstream file(filePath, std::ios::in);

        if (!file.is_open())
            return std::unexpected(createFilePathMessage() + " could not be opened.");

        Result contents{ std::forward<Function>(getContent)(file) };

        if (file.bad())
            return std::unexpected(createFilePathMessage() + " could not be read.");

        return contents;
    }
};