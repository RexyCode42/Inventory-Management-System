#include "TableUtils.h"

TableHelpers::Widths TableHelpers::calculateColumnWidths(const Row& stringProducts, const TableHeader& tableHeader) {
    Widths widths{};

    auto setWidthToDefaultLength{ [](std::string_view header) { return header.length(); } };
    std::ranges::transform(tableHeader, std::begin(widths), setWidthToDefaultLength);

    auto getMaxLength{ [](std::string_view strAttribute, std::size_t width) {
        return std::max(width, strAttribute.length());
        }
    };
    auto setWidthToMaxLength{ [&widths, getMaxLength](const auto& strAttributes) {
        std::transform(std::begin(strAttributes), std::end(strAttributes),
        std::begin(widths), std::begin(widths), getMaxLength);
        }
    };
    std::ranges::for_each(stringProducts, setWidthToMaxLength);

    return widths;
}

void TableHelpers::printRowBorder(const Widths& widths) {
    constexpr std::size_t margin{ 1 };

    std::cout << '+' << std::setfill('-');

    auto setBorderWidth{ [](std::size_t width) {
        std::cout << std::setw(width + margin * 2) << '-' << '+';
        }
    };
    std::ranges::for_each(widths, setBorderWidth);

    std::cout << '\n' << std::setfill(' ');
};

void TableHelpers::printTableHeader(const TableHeader& tableHeader, const Widths& widths) {
    printRowBorder(widths);
    printRowValues(tableHeader, widths);
    printRowBorder(widths);
}

void TableHelpers::printTableValues(const Row& productsAsStrings, const Widths& widths) {
    std::ranges::for_each(productsAsStrings, [&widths](const auto& productAsStrings) {
        printRowValues(productAsStrings, widths);
        }
    );
    printRowBorder(widths);
}