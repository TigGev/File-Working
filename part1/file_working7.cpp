#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
    std::ifstream data("./people-100.csv");
    if (!data.is_open()) {
        std::cout << "Error: file openning";
        return 1;
    }

    std::vector<std::string> titles;
    std::string line;
    std::getline(data, line);
    line.pop_back();
    std::stringstream str(line);
    while(std::getline(str, line, ',')) 
        titles.push_back(line);
    //     if (line.back() == '\n'){
    //          line.pop_back();
    //         std::cout << "hello" << std::endl;
    //     }         
    //     if (!line.empty()) titles.push_back(line);
    // }
    // if (titles.back() == "\n") titles.pop_back();
    
    std::ofstream out("./people-100.json", std::ios::trunc);
    if (!out.is_open()) {
        std::cout << "Error: file openning";
        return 1;
    }
    out << "[\n";

    while (std::getline(data, line)) {
        line.pop_back();
        out << "\t{\n";
        str = std::stringstream(line);
        for(int i = 0; i < titles.size(); ++i) {
            out << "\t\t";
            std::string value;
            if ((i == titles.size() - 1) && str.peek() == '"') {
                str.ignore();
                std::getline(str, value, '"');
            }
            else {
                std::getline(str, value, ',');
            }

            if (value.back() == '\n') value.pop_back();

            out << "\"" << titles[i] << "\" : ";
            if (titles[i] == "Index") {
                out << std::stoi(value);
            }
            else out << "\"" << value << "\"";

            if (titles[i] != "Job Title") out << ",";

            out << "\n";
        }
        out << "    },\n";
    }
    out.seekp(-2, std::ios::cur);
    out << "\n]";
}
