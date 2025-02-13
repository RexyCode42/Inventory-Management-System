#pragma once

#include <algorithm>
#include <vector>
#include <array>
#include <span>
#include <string>
#include "../../Model/Product.h"
#include "../ConstantVariableUtils/ConstantUtils.h"

namespace ProductHelpers {
    using StringProducts = std::vector<std::array<std::string, ConstantHelpers::columnSize>>;

    StringProducts productsAsStrings(const std::span<const Inventory::Product>& products);
}