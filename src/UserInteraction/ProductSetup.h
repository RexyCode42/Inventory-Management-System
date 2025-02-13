#pragma once

#include <tuple>
#include "../Model/Product.h"
#include "UserInput/PromptAttribute.h"
#include "ProductAttributeRequirements/Requirements.h"

[[nodiscard]] std::tuple<std::string, std::string, std::string, double, int>
getProductAttributes(const std::string& lastProductId);

[[nodiscard]] Inventory::Product createProduct(
	const std::tuple<std::string, std::string, std::string, double, int>& attributes);