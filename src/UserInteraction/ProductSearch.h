#pragma once 

#include <functional>
#include <string>
#include "../src/Model/Product.h"
#include "ProductAttributeRequirements/Requirements.h"
#include "ProductAttributeRequirements/RequirementsPrinter.h"
#include "UserOptions/Options.h"
#include "UserOptions/DisplayOptions.h"
#include "UserInput/PromptOptions.h"
#include "UserInput/PromptAttribute.h"

[[nodiscard]] std::function<bool(const Inventory::Product&)> getProductSearchPredicate();

[[nodiscard]] std::optional<std::vector<Inventory::Product>>
searchProductsByAttribute(
    const std::span<const Inventory::Product>& products,
    std::function<bool(const Inventory::Product&)> searchPredicate);

[[nodiscard]] std::optional<std::vector<Inventory::Product>> searchForProducts(
    const std::span<const Inventory::Product>& products);