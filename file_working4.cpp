#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

char* encrypt(char* data) {
    char* tmp = data;
    while(*tmp) {
        if (isalpha(*tmp)) {
            char base;
            base = isupper(*tmp) ? 'A' : 'a';
            *tmp = base + ((*tmp - base + 1) % 26);
        }
        std::cout << *tmp;
        ++tmp;
    }
    return data;
}

int main() {
    std::ifstream data("./file4.txt", std::ios::ate);

    if (!data.is_open()) {
        std::cout << "Error: file openning";
        return 1;
    }

    size_t size = data.tellg();
    char* buf = new char[size + 1];
    data.seekg(0);
    data.read(buf, size);
    buf[size] = '\0';
    
    // std::cout << buf << std::endl;

    std::ofstream out("./out.txt", std::ios::app);
    if (!out.is_open()) {
        std::cout << "Error: file openning";
        return 1;
    }

    out << encrypt(buf);

    delete[] buf;
}