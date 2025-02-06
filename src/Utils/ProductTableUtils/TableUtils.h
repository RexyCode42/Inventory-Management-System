#pragma once

#include <iostream>
#include <iomanip>
#include <string_view>
#include <algorithm>
#include <array>
#include <span>
#include "../ConstantVariableUtils/ConstantUtils.h"

namespace TableHelpers {
    using Widths = std::array<std::size_t, ConstantHelpers::columnSize>;
    using Row = std::span<const std::array<std::string, ConstantHelpers::columnSize>>;
    using TableHeader = std::span<const std::string_view, ConstantHelpers::columnSize>;

    Widths calculateColumnWidths(const Row& stringProducts, const TableHeader& tableHeader);

    template<typename T>
    concept StringConvertable = std::convertible_to<std::ranges::range_value_t<T>, std::string_view>;

    template<StringConvertable Container>
    void printRowValues(const Container& row, const Widths& widths) {
        std::cout << "|";
        auto setWidthAndPrintValue{ [&widths, index = 0](std::string_view value) mutable {
            std::cout << " " << std::setw(widths[index++]) << value << " |";
            }
        };
        std::ranges::for_each(row, setWidthAndPrintValue);
        std::cout << '\n';
    };

    void printRowBorder(const Widths& widths);

    void printTableHeader(const TableHeader& tableHeader, const Widths& widths);

    void printTableValues(const Row& productsAsStrings, const Widths& widths);
}