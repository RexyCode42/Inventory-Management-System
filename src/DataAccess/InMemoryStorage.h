#pragma once

#include "../Product.h"
#include "../UserInteraction/UserOptions/Options.h"
#include "../UserInteraction/UserInput/PromptAttribute.h"
#include "../UserInteraction/ProductAttributeRequirements/RequirementsPrinter.h"
#include "../UserInteraction/ProductAttributeRequirements/Requirements.h"

namespace Inventory {
    class InMemoryProductStorage {
    public:
        using OptionalProductReference = std::optional<std::reference_wrapper<Inventory::Product>>;

        using ExpectedProductAttributes = std::expected<std::tuple<std::string, std::string, double, int>, std::string>;

        explicit InMemoryProductStorage(std::vector<Product> products = {});

        void add(const Product& product);

        void remove(std::string_view productName);

        [[nodiscard]] std::expected<void, std::string> promptAndUpdateProduct(const UpdateOption& userChoice, Inventory::Product& foundProduct);

        [[nodiscard]] bool doesProductNameExist(std::string_view name) const;

        [[nodiscard]] const std::vector<Product>& getProducts() const noexcept;

        [[nodiscard]] OptionalProductReference getProductReferenceById(std::string_view id);

    private:        
        [[nodiscard]] ExpectedProductAttributes promptUserForUpdatedAttributes() const;

        std::vector<Product> products_;
    };
}