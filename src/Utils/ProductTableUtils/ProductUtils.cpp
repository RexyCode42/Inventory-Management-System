#include "ProductUtils.h"

ProductHelpers::StringProducts ProductHelpers::convertProductsToStringArrays(const std::span<const Inventory::Product>& products) {
    StringProducts stringProducts;
    stringProducts.reserve(products.size());

    std::ranges::for_each(products, [&stringProducts](const Inventory::Product& product) {
        std::array<std::string, ConstantHelpers::columnSize> strProduct{
            product.getId(),
            product.getName(),
            product.getCategory(),
            // {:.2f} formats the floating-point value with 2 decimal places (precision of 2)
            // Example std::format: std::format("{:.2f}", 3.14594) -> "3.14"
            std::format("{:.2f}", product.getPrice()),
            std::to_string(product.getStock()),
            std::format("{:.2f}", product.calculateInventoryValue())
        };

        stringProducts.emplace_back(strProduct);
        }
    );

    return stringProducts;
}