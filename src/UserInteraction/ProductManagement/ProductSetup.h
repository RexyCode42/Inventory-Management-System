#pragma once

#include <tuple>
#include <../src/Product.h>
#include "../UserInput/PromptAttribute.h"
#include "../ProductAttributeRequirements/Requirements.h"

[[nodiscard]] std::tuple<std::string, std::string, std::string, double, int>
getProductAttributes(const std::string& lastProductId);

[[nodiscard]] Inventory::Product createProduct(
	const std::tuple<std::string, std::string, std::string, double, int>& attributes);