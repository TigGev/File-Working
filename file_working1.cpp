#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>

int main() {
    std::ifstream input("data.txt");
    std::ofstream output("out.txt");
    if (!input.is_open() || !output.is_open()) {
        std::cout << "Error: file openning";
        return 1;
    }

    std::string data;
    while (std::getline(input, data)) {
        std::stringstream str(data);
        std::string name;
        std::array<int, 3> points;
        char delim;
        std::getline(str, name, ',');

        str >> delim >> points[0] >> delim >> points[1] >> delim >> points[2];

        std::cout << name << ": " << points[0] << " " << points[1] << " " << points[2] << std::endl;
        int av = 0.3 * points[0] + 0.3 * points[1] + 0.4 * points[2];

        output << name << ": " << av << std::endl;
    }

}