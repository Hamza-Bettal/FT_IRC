#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

int main() {
    std::string str = "Hello, World! How are you?";
    std::vector<std::string> sv = split(str, ' ');

    for (std::vector<std::string>::iterator it = sv.begin(); it != sv.end(); ++it)
        std::cout << *it << std::endl;

    return 0;
}
