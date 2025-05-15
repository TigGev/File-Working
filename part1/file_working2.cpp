#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("./system_log.txt");
    std::ofstream out("./out.txt", std::ios::app);
    out << "TASK2" << std::endl;

    if (!file.is_open() || !out.is_open()) { 
        std::cout << "Error: file openning";
        return 1;
    }

    int counts[3] = {0};
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream data(line);
        std::string type;
        data >> type;
        
        if (type == "[INFO]") ++counts[0];
        else if (type == "[WARNING]") ++counts[1];
        else ++counts[2];
    }
    out << "[INFO]: "  << counts[0] << "\n" << "[WARNING]: " << counts[1] << "\n" << "[ERROR]: " << counts[2] << std::endl;
    file.close();
    out.close();
}