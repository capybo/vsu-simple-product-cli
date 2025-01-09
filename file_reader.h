#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include "product.h"

class file_reader {
    static void read(const std::string &file_name, std::vector<product> &products);
};



#endif //FILE_READER_H
