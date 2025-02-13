#include "Formats.h"

std::string TxtProductFormat::operator()(const Inventory::Product& product) const {
    std::ostringstream oss{};

    oss <<
        product.getId() <<
        separator_ <<
        product.getName() <<
        separator_ <<
        product.getCategory() <<
        separator_ <<
        product.getPrice() <<
        separator_ <<
        product.getStock() <<
        separator_ <<
        product.calculateInventoryValue();

    return oss.str();
}

std::string CsvProductFormat::operator()(const Inventory::Product& product) const {
    std::ostringstream oss{};

    oss <<
        product.getId() <<
        separator_ <<
        product.getName() <<
        separator_ <<
        product.getCategory() <<
        separator_ <<
        product.getPrice() <<
        separator_ <<
        product.getStock() <<
        separator_ <<
        product.calculateInventoryValue();

    return oss.str();
}