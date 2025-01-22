#pragma once

#include <ranges>
#include <algorithm>

namespace Algorithms {
	namespace Implementations {
		[[nodiscard]] std::string join(const std::ranges::range auto& collection, const auto& separator) {
			if (collection.empty())
				return {};

			std::ostringstream joinedString{};

			auto beforeLastPosition{ std::prev(std::end(collection)) };

			std::for_each(std::begin(collection), beforeLastPosition,
				[&joinedString, separator](const auto& object) { joinedString << object << separator; });

			joinedString << *beforeLastPosition;

			return joinedString.str();
		}
	}

	[[nodiscard]] std::string join(const std::ranges::range auto& collection, std::string_view separator) {
		return Implementations::join(collection, separator);
	}

	[[nodiscard]] std::string join(const std::ranges::range auto& collection, char separator) {
		return Implementations::join(collection, separator);
	}
}