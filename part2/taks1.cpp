#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <algorithm>

void merge(std::fstream& first, std::fstream& second, std::fstream& res) {
    first.seekg(0);
    second.seekg(0);
    std::string titles;
    std::getline(first, titles);
    std::getline(second, titles);
    std::string line;
    std::unordered_set<std::string> st;
    while (std::getline(first, line) ) {
        std::stringstream ss(line);
        std::getline(ss, line, ',');
        st.insert(ss.str());
    }
    while (std::getline(second, line) ) {
        std::stringstream ss(line);
        std::getline(ss, line, ',');
        st.insert(ss.str());
    }
    res.seekg(0, std::ios::end);
    res << titles << std::endl;
    for(const auto& line : st) {
        res << line << std::endl;
    }
}

std::fstream csvToJson(std::fstream& data) {

    std::vector<std::string> titles;
    std::string line;
    std::getline(data, line);
    line.pop_back();
    std::stringstream str(line);
    while(std::getline(str, line, ',')) 
        titles.push_back(line);
    
    std::fstream out("./people-merge-data.json", std::ios::out);
    if (!out.is_open()) {
        std::cout << "Error: file openning";
        throw std::runtime_error("File opening is failed");
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
    return out;
}

int main() {
    std::fstream file1("./people_data1.csv");
    std::fstream file2("./people_data2.csv");
    std::fstream file3("./people_data3.csv");
    std::fstream merged("merged.csv", std::ios::out);
    if (!file1.is_open()) { 
        throw std::runtime_error("File1 opening is failed");
    }
    if (!file2.is_open()) { 
        throw std::runtime_error("File2 opening is failed");
    }
    if (!file3.is_open()) { 
        throw std::runtime_error("File3 opening is failed");
    }
    if (!merged.is_open()) { 
        throw std::runtime_error("merged opening is failed");
    }

    merge(file1, file2, merged);
    merge(merged, file3, merged);
    std::fstream res = csvToJson(merged);
}