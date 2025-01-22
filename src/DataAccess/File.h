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

private:
    void validateFilePath(const std::filesystem::path& filePath) const;

    [[nodiscard]] std::expected<void, std::string> writeToFile(
        const std::filesystem::path& filePath,
        const std::string& contents,
        std::ofstream::openmode openMode) const;
};