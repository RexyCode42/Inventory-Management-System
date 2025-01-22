#pragma once

#include <string>
#include <algorithm>
#include <ranges>

namespace StringHelpers {
	void toUpperAll(std::string& str);

	// https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
	void trimLeadingWhitespaces(std::string& str);

	void trimTrailingWhitespaces(std::string& str);

	void trimBody(std::string& str);

	void trimEdgesAndBody(std::string& str);

	template<std::ranges::range Collection, typename Formatter>
		requires std::is_invocable_r_v<std::string, Formatter, std::ranges::range_value_t<Collection>>
	std::string getCollectionAsFormattedString(const Collection& collection, Formatter&& formatter) {
		std::ostringstream formattedString{};

		std::ranges::for_each(collection, [&](const auto& object) {
			formattedString << std::forward<Formatter>(formatter)(object) << '\n';
			});

		return formattedString.str();
	}
}
