#include <bits/stdc++.h>
int main() {
    std::string str, c = "0";
    while (std::cin >> str) {
        if (str == "end") break;
        std::vector<char> _list(50, 'Z'+1);
        for (auto i : str)
            _list[std::lower_bound(_list.begin(), _list.end(), i) - _list.begin()] = i;
        std::cout << "Case " << (c = std::to_string(std::stoi(c)+1)) << ": " << std::count_if(_list.begin(), _list.end(), [](char ch){ return ch != 'Z'+1; }) << std::endl;
    }
}