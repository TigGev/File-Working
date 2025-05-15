#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

std::string addTwoNumbers(std::string& first, std::string& second) {
    std::string res;
    auto f = first.rbegin();
    auto s = second.rbegin();
    int carry = 0;
    while (f != first.rend() && s != second.rend()) {
        int num = ((*f - '0') + (*s - '0') + carry);
        if (num >= 10) {
            num %= 10;
            carry = 1;
        }
        else carry = 0;
        res.insert(0, 1, num + '0');
        f++;
        s++;
    }

    std::string::reverse_iterator it = f;
    std::string& str = first;
    if (f == first.rend()) {
        it = s;
        str = second;
    }

    std::cout << "SECOND LOOP" << std::endl;
    while (it < str.rend()) {
        char ch = *it;
        if (carry) {
            int num = ((*it - '0') + carry);
            if (num >= 10) {
                ch = (num % 10) + '0';
                carry = 1;
            }
            else {
                carry = 0;
                ch = num + '0';
            }
        }
        std::cout << "insert\n";
        res.insert(0, 1, ch);
        ++it;
    }
    if (carry) res.insert(0, 1, '1');
    return res;
}

int main() {
    std::ifstream data("file5.txt");
    if (!data.is_open()) {
        std::cout << "Error: file openning";
        return 1;
    }
    std::string line;
    std::vector<std::string> vec;
    while (std::getline(data, line)) {
        if(line.empty()) continue;
        vec.push_back(line);
    }
    line = vec[0];
    int i = 1;
    for(auto it = vec.begin() + 1; it != vec.end(); ++it) {
        std::cout << "sum: " << line << std::endl;
        line = addTwoNumbers(line, *it);
        std::cout << " aa\n";
    }

    std::ofstream out("./out.txt", std::ios::app);
    if (!out.is_open()) {
        std::cout << "Error: file openning";
        return 1;
    }
    out << "\n" << "task5: " << line << std::endl;

}