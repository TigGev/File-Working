#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream data("file.txt");
    std::string line;
    std::vector<std::string> vec;
    while (std::getline(data, line)) {
        vec.push_back(line);
    }
    
}