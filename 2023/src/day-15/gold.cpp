#include "../../utils/aoc-utils.cpp"
#include <array>
#include <deque>

auto
hash(const auto& str)
{
    int res = 0;
    for (auto&& c : str)
        res = ((res + c) * 17) % 256;
    return res;
}

void
set_focus(const auto& label, const auto& value, auto& boxes)
{
    auto same_label = [&label](auto& p)
    { return p.first == label; };

    auto& vec = boxes[hash(label)];
    auto  it  = std::find_if(vec.begin(), vec.end(), same_label);

    if (value < 0)
    {
        if (it != vec.end())
            vec.erase(it);
        return;
    }

    if (it == vec.end())
        vec.push_back({label, value});
    else
        it->second = value;
}

int
main()
{
    auto parse_line = [](auto s)
    {
        if (s.back() == '-')
        {
            s.pop_back();
            return std::make_pair(s, -1);
        }

        auto parts = aoc_utils::split_string(s, "=");
        return std::make_pair(parts[0], aoc_utils::to_int(parts[1]));
    };

    auto input = aoc_utils::split_string(aoc_utils::read_file("src/day-15/input.txt"), ",") |
                 std::views::transform(parse_line);

    std::array<std::vector<std::pair<std::string, int>>, 256> boxes;

    for (auto&& [label, value] : input)
        set_focus(label, value, boxes);

    int sum = 0;
    for (int i = 0; i < boxes.size(); i++)
        for (int j = 0; j < boxes[i].size(); j++)
            sum += (i + 1) * (j + 1) * boxes[i][j].second;

    std::cout << sum << std::endl;
}