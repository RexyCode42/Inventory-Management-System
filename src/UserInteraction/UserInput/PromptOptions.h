#pragma once

#include <functional>
#include "../src/Utils/IOStreamUtils/ClearingInvalidStream.h"

template<class EnumT>
[[nodiscard]] EnumT promptUserForChoice(const std::function<void()>& displayOptions, EnumT minChoice, EnumT maxChoice) {
    const int minChoiceInt{ static_cast<int>(minChoice) };
    const int maxChoiceInt{ static_cast<int>(maxChoice) };

    int userChoice{};

    while (true) {
        displayOptions();

        std::cout << "Enter choice: ";

        if (!(std::cin >> userChoice)) {
            std::cout << "Invalid input. Please enter a number." << '\n';
            IOStreamHelpers::clearFlagsAndIgnoreInvalidInput();
            continue;
        }

        if (userChoice >= minChoiceInt && userChoice <= maxChoiceInt)
            break;

        std::cout << "Choice out of range. Please try again." << '\n';
    }

    // Ensure the stream is cleared for the next I/O operation.
    IOStreamHelpers::clearFlagsAndIgnoreInvalidInput();

    std::cout << '\n';

    return static_cast<EnumT>(userChoice);
}