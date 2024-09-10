#pragma once

#include <tuple>
#include <../src/Product.h>
#include "../UserInput/Prompt.h"
#include "../ProductAttributeRequirements/Requirements.h"

std::tuple<std::string, std::string, std::string, double, int>
getProductAttributes(const std::string& lastProductId);

Inventory::Product createProduct(
	const std::tuple<std::string, std::string, std::string, double, int>& attributes);