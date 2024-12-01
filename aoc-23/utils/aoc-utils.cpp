#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace aoc_utils
{
    void
    print_grid(const auto& grid, auto milli, bool clear)
    {
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
                std::cout << grid[i][j];
            std::cout << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(milli));
        if (clear)
            system("clear");
    }

    auto
    manh_distance(const auto& a, const auto& b)
    {
        return std::abs(b.first - a.first) + std::abs(b.second - a.second);
    }

    std::pair<int, int>
    sum_pair(const std::pair<int, int>& p1, const std::pair<int, int>& p2)
    {
        return std::make_pair(p1.first + p2.first, p1.second + p2.second);
    }

    std::pair<int, int>
    sub_pair(const std::pair<int, int>& p1, const std::pair<int, int>& p2)
    {
        return std::make_pair(p1.first - p2.first, p1.second - p2.second);
    }

    bool
    in_bound(const auto& grid, const std::pair<int, int>& pos)
    {
        auto [x, y] = pos;
        return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
    }

    std::vector<std::string>
    split_string(const std::string& str, const std::string& delimiter)
    {
        size_t                   pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string              token;
        std::vector<std::string> res;

        while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos)
        {
            token     = str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(str.substr(pos_start));
        return res;
    }

    std::vector<std::string>
    read_file_lines(const std::string& path)
    {
        std::ifstream            file(path);
        std::string              line;
        std::vector<std::string> lines;

        if (!file)
            std::cerr << "err reading " << path << std::endl;

        while (std::getline(file, line))
            lines.push_back(line);

        return lines;
    }

    std::string
    read_file(const std::string& path)
    {
        std::ifstream ifs(path);
        return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    }

    auto split_space = [](const auto& s)
    { return aoc_utils::split_string(s, " "); };

    auto split_line = [](const auto& s)
    { return aoc_utils::split_string(s, "\n"); };

    auto to_int = [](const auto& s)
    { return static_cast<int32_t>(atoi(s.c_str())); };

    auto to_int64 = [](const auto& s)
    { return static_cast<int64_t>(std::stoll(s.c_str())); };
}