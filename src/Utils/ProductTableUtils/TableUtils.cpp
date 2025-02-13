#include "TableUtils.h"

TableHelpers::Widths TableHelpers::calculateColumnWidths(
    const TableHelpers::Table& table, const TableHelpers::Header& header) {
    Widths widths{};

    std::ranges::transform(header, std::begin(widths), [](std::string_view attribute) { return attribute.length(); });

    auto getMaxLength{ [](std::string_view attribute, std::size_t width) {
        return std::max(width, attribute.length());
        }
    };

    auto setWidthToMaxLength{ [&widths, getMaxLength](const auto& row) {
        std::transform(std::begin(row), std::end(row), std::begin(widths), std::begin(widths), getMaxLength);
        }
    };

    std::ranges::for_each(table, setWidthToMaxLength);

    return widths;
}

static void printRowValues(const std::span<const std::string>& row, const TableHelpers::Widths& widths) {
    std::cout << "|";

    auto setWidthAndPrintValue{ [&widths, index = 0](std::string_view value) mutable {
        std::cout << " " << std::setw(widths[index++]) << value << " |";
        }
    };

    std::ranges::for_each(row, setWidthAndPrintValue);

    std::cout << '\n';
};

static void printRowBorder(const TableHelpers::Widths& widths) {
    constexpr std::size_t margin{ 1 };

    std::cout << '+' << std::setfill('-');

    auto setBorderWidth{ [](std::size_t width) {
        std::cout << std::setw(width + margin * 2) << '-' << '+';
        }
    };

    std::ranges::for_each(widths, setBorderWidth);

    std::cout << '\n' << std::setfill(' ');
};

void TableHelpers::printHeader(const TableHelpers::Header& header, const TableHelpers::Widths& widths) {
    printRowBorder(widths);
    printRowValues(header, widths);
    printRowBorder(widths);
}

void TableHelpers::printValues(const TableHelpers::Table& table, const TableHelpers::Widths& widths) {
    std::ranges::for_each(table, [&widths](const auto& row) {
        printRowValues(row, widths);
        }
    );
    printRowBorder(widths);
}