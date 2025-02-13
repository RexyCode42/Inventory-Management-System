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
    using Table = std::span<const std::array<std::string, ConstantHelpers::columnSize>>;
    using Header = std::span<const std::string, ConstantHelpers::columnSize>;

    Widths calculateColumnWidths(const Table& table, const Header& header);

    void printHeader(const Header& header, const Widths& widths);

    void printValues(const Table& table, const Widths& widths);
}