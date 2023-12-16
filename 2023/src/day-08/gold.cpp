#include "../../utils/aoc-utils.cpp"
#include <algorithm>
#include <numeric>
#include <unordered_map>

int
main()
{
    auto idToNext   = std::unordered_map<std::string, std::pair<std::string, std::string>>();
    auto parse_line = [&idToNext](const auto& s)
    {
        auto split = aoc_utils::split_string(s, " = ");
        auto rest  = aoc_utils::split_string(split[1], ", ");
        auto id    = split[0];
        auto sx    = rest[0];
        auto dx    = rest[1];

        sx.erase(sx.begin());
        dx.pop_back();
        idToNext[id] = {sx, dx};
    };

    auto input        = aoc_utils::read_file_lines("src/day-08/input.txt");
    auto instructions = input[0];
    std::for_each(input.begin() + 2, input.end(), parse_line);

    auto follow_map = [&idToNext, &instructions](const std::string& start)
    {
        int  steps       = 0;
        int  iter        = 0;
        auto pos         = start;
        auto reset_steps = [&steps, &iter]()
        { steps = 0; iter++; };

        while (pos.back() != 'Z')
        {
            if (steps == instructions.size())
                reset_steps();
            pos = instructions[steps++] == 'L' ? idToNext[pos].first : idToNext[pos].second;
        }
        return steps + steps * iter;
    };

    auto starts = std::vector<std::string>();
    for (auto&& [k, v] : idToNext)
        if (k.back() == 'A')
            starts.push_back(k);

    auto steps = std::vector<int64_t>();
    for (auto&& s : starts)
        steps.push_back(follow_map(s));

    int64_t lcm = 1;
    for (auto&& s : steps)
        lcm = std::lcm(lcm, s);

    std::cout << lcm << std::endl;
}
