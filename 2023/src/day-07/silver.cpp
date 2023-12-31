#include "../../utils/aoc-utils.cpp"

std::unordered_map<char, int> labelToValue{
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14},
};

int
hand_value(const std::string& s)
{
    auto cmp_labels = [](auto p1, auto p2)
    { return p1.second < p2.second; };

    auto labelToFreq = std::unordered_map<char, int>();

    for (auto&& c : s)
        labelToFreq[c]++;

    auto maxkv = std::max_element(labelToFreq.begin(), labelToFreq.end(), cmp_labels);
    return maxkv->second - labelToFreq.size();
}

bool
sort_hand(const std::pair<std::string, int>& x, const std::pair<std::string, int>& y)
{
    auto s1    = x.first;
    auto s2    = y.first;
    auto s1val = hand_value(s1);
    auto s2val = hand_value(s2);

    if (s1val < s2val)
        return true;
    if (s1val > s2val)
        return false;

    for (int i = 0; i < s1.size(); i++)
        if (s1[i] != s2[i])
            return labelToValue[s1[i]] < labelToValue[s2[i]];

    return false;
}

int
main()
{
    auto parse_line = [](const auto& s)
    {
        auto split = aoc_utils::split_space(s);
        return std::make_pair(split[0], aoc_utils::to_int(split[1]));
    };

    auto input = aoc_utils::read_file_lines("src/day-07/input.txt") | std::views::transform(parse_line);
    auto vec   = std::vector<std::pair<std::string, int>>();

    for (auto&& e : input)
        vec.push_back(e);
    std::sort(vec.begin(), vec.end(), sort_hand);

    int64_t sum = 0;
    for (int i = 0; i < vec.size(); i++)
        sum += (i + 1) * vec[i].second;

    std::cout << sum << std::endl;
}