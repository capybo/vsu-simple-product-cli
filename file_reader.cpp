#include "file_reader.h"

#include <fstream>
#include <iostream>

bool validate_content(const std::string &line) {
    size_t pos = 0;
    int field_count = 0;

    try {
        std::string temp;
        while (pos != std::string::npos) {
            pos = line.find(' ', pos + 1);
            ++field_count;
        }

        if (field_count < 4) return false;
    } catch (...) {
        return false;
    }

    return true;
}

void file_reader::read(const std::string &file_name, std::vector<product> &products) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!validate_content(line)) {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }

        product product;
        size_t pos = 0;

        try {
            pos = line.find(' ');
            product.cost = std::stod(line.substr(0, pos));

            size_t prevPos = pos + 1;
            pos = line.find(' ', prevPos);
            product.quantity = std::stoi(line.substr(prevPos, pos - prevPos));

            prevPos = pos + 1;
            pos = line.find(' ', prevPos);
            product.category = line.substr(prevPos, pos - prevPos);

            product.name = line.substr(pos + 1);

            products.push_back(product);
        } catch (...) {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    file.close();
}
