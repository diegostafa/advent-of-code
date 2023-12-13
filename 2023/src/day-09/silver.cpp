#include "../../utils/aoc-utils.cpp"
#include <numeric>

int
main()
{
    auto parse_line = [](const auto& s)
    {
        auto nums = aoc_utils::split_space(s);

        std::vector<int64_t> res;
        for (auto&& n : nums)
            res.push_back(aoc_utils::to_int64(n));
        return res;
    };

    auto input = aoc_utils::read_file_lines("src/day-09/input.txt") | std::views::transform(parse_line);

    auto extrapolate_value = [](const auto& line)
    {
        auto compute_next_layer = [](const auto& currLine)
        {
            std::vector<int64_t> layer;
            layer.reserve(currLine.size() - 2);

            for (size_t i = 0; i < currLine.size() - 1; i++)
                layer.push_back(currLine[i + 1] - currLine[i]);

            return layer;
        };

        auto vec_all_zero = [](const auto& v)
        {
            for (auto&& e : v)
                if (e != 0)
                    return false;

            return true;
        };

        std::vector<std::vector<int64_t>> pyramid;
        pyramid.push_back(line);

        while (!vec_all_zero(pyramid.back()))
            pyramid.push_back(compute_next_layer(pyramid.back()));

        int tempSum = 0;
        for (int i = pyramid.size() - 1; i >= 1; i--)
            tempSum += pyramid[i - 1].back();

        return tempSum;
    };

    int64_t sum = 0;
    for (auto&& line : input)
        sum += extrapolate_value(line);

    std::cout << sum << std::endl;
}
