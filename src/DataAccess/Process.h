#pragma once

#include <sstream>
#include <expected>
#include <span>
#include <array>
#include <vector>
#include "../Product.h"

[[nodiscard]] std::expected<std::vector<Inventory::Product>, std::string> process(
    const std::span<const std::string>& lines, const char delimiter);