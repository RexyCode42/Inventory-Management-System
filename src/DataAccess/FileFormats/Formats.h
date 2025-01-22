#pragma once

#include <sstream>
#include "../src/Product.h"

class TxtProductFormat {
public:
    std::string operator()(const Inventory::Product& product) const;

private:
    static constexpr inline char separator_{ ',' };
};

class CsvProductFormat {
public:
    std::string operator()(const Inventory::Product& product) const;

private:
    static constexpr inline char separator_{ ',' };
};