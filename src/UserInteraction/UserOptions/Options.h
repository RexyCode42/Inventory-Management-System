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

enum class DeleteOption : int {
    YES = 1,
    NO
};

enum class SaveModeOption : int {
    SAVE_TO_EXTERNAL = 1,
    SAVE_TO_INTERNAL
};

enum class FileExtensionOption : int {
    TXT = 1,
    CSV
};

enum class LoadModeOption : int {
    LOAD_FROM_EXTERNAL = 1,
    LOAD_FROM_INTERNAL
};

enum class InventoryOption : int {
    ADD_PRODUCT = 1,
    REMOVE_PRODUCT,
    UPDATE_PRODUCT,
    SEARCH_PRODUCT,
    VIEW_ALL_PRODUCTS,
    SAVE_PRODUCTS_TO_FILE,
    EXIT
};