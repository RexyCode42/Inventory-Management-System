#pragma once

enum class SearchOption : int {
    ID = 1,
    NAME,
    CATEGORY,
    PRICE,
    STOCK,
    INVENTORY_VALUE
};

enum class UpdateOption : int {
    NAME = 1,
    CATEGORY,
    PRICE,
    STOCK,
    ALL_OF_THE_ABOVE
};
