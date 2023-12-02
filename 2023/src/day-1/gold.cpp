#include "../../utils/aoc-utils.cpp"
#include "unordered_map"

std::unordered_map<std::string, int> stringToNum = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

int
get_number(const std::string& s)
{
    int n1 = 0;
    int n2 = 0;

    for (int i = 0; i < s.length() && !n1; ++i)
    {
        if (isdigit(s[i]))
            n1 = s[i] - '0';
        else
        {
            std::string tmp;
            for (int j = 0; j < 5 && i + j < s.length() && !n1; ++j)
            {
                tmp.push_back(s[i + j]);
                if (stringToNum.count(tmp))
                    n1 = stringToNum[tmp];
            }
        }
    }

    for (int i = s.length() - 1; i >= 0 && !n2; --i)
    {
        if (isdigit(s[i]))
            n2 = s[i] - '0';
        else
        {
            std::string tmp;
            for (int j = 0; j < 5 && i - j >= 0 && !n2; ++j)
            {
                tmp.insert(tmp.begin(), s[i - j]);
                if (stringToNum.count(tmp))
                    n2 = stringToNum[tmp];
            }
        }
    }

    return n1 * 10 + n2;
}

int
main()
{
    auto lines   = read_file_lines("src/day-1/input.txt");
    auto numbers = map_vector<std::string, int>(lines, get_number);
    auto sum     = 0;

    for (auto&& n : numbers)
        sum += n;

    std::cout << sum << std::endl;
}