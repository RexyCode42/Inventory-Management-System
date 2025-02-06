#pragma once

#include <iostream>
#include <filesystem>
#include <unordered_set>

namespace ConstantHelpers {
    constexpr std::size_t columnSize{ 6 };

    constexpr char internalFileDelimiter{ ',' };

    const std::filesystem::path internalFilePath{ "inventory.csv" };

    #if defined(_WIN32) || defined(_WIN64)
        constexpr std::size_t maxPathLength = 260;

        const std::unordered_set<char> reservedCharacters{ '<','>',':','\"','/','\\','|','?','*' };

        const std::unordered_set<std::string> reservedNames{
            "CON","PRN","AUX","NUL",
            "COM0","COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9",
            "LPT0","LPT1","LPT2","LPT3","LPT4","LPT5","LPT6","LPT7","LPT8","LPT9",
        };
    #elif defined(__APPLE__) || defined(__MACH__)
        constexpr std::size_t maxPathLength = 1024;

        const std::unordered_set<char> reservedCharacters{ ':','/' };

        const std::unordered_set<std::string> reservedNames{};
    #elif defined(__linux__)
        constexpr std::size_t maxPathLength = 4096;

        const std::unordered_set<char> reservedCharacters{ '/' };

        const std::unordered_set<std::string> reservedNames{ ".", ".." };
    #else
        #error "Unsupported platform: Please define maxPathLength for this platform."
    #endif
}