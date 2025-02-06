#include "Process.h"

using namespace std::string_literals;

class ProductProcessor {
public:
    [[nodiscard]] std::expected<std::vector<Inventory::Product>, std::string> operator()(
        const std::span<const std::string>& lines, const char delimiter) {
        std::vector<Inventory::Product> products;
        products.reserve(lines.size());

        auto createErrorMessage{ []() { return "Could not process products. Error: "s; } };

        for (const auto& line : lines) {
            const auto& [id, name, category, unitPriceStr, stockStr] { processLine(line, delimiter) };

            if (isAnyAttributeEmpty({ id, name, category, unitPriceStr, stockStr }))
                return std::unexpected(createErrorMessage() + "missing value(s).");

            try {
                products.emplace_back(
                    id, name, category, std::stod(unitPriceStr), std::stoi(stockStr));
            }
            catch (const std::invalid_argument& ia) {
                return std::unexpected(createErrorMessage() + ia.what());
            }
            catch (const std::out_of_range& oor) {
                return std::unexpected(createErrorMessage() + oor.what());
            }
        }

        return products;
    }

private:
    using StringAttributes = std::array<std::string, 5>;

    [[nodiscard]] StringAttributes processLine(const std::string& line, const char delimiter) const {
        std::istringstream iss{ line };

        std::string id{};
        std::string name{};
        std::string category{};
        std::string unitPriceStr{};
        std::string stockStr{};

        std::getline(iss, id, delimiter);
        std::getline(iss, name, delimiter);
        std::getline(iss, category, delimiter);
        std::getline(iss, unitPriceStr, delimiter);
        std::getline(iss, stockStr, delimiter);

        return { id,name,category,unitPriceStr,stockStr };
    }

    [[nodiscard]] bool isAnyAttributeEmpty(const StringAttributes& stringAttributes) const {
        const auto& [id, name, category, unitPriceStr, stockStr] { stringAttributes };

        return
            id.empty() ||
            name.empty() ||
            category.empty() ||
            unitPriceStr.empty() ||
            stockStr.empty();
    }
};

[[nodiscard]] std::expected<std::vector<Inventory::Product>, std::string> process(
    const std::span<const std::string>& lines, const char delimiter) {
    return ProductProcessor{}(lines, delimiter);
}