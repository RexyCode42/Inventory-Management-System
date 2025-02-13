#pragma once

#include "../UserInteraction/ProductManagement.h"

class InventoryManagementSystem {
public:
    void Run() const;

private:
    template <typename T>
    void handleResult(const std::expected<T, std::string>& result) const {
        if (!result.has_value())
            std::cerr << result.error() << '\n';
    }
};