#ifndef CSVSTORAGE_H
#define CSVSTORAGE_H

#include <string>
#include <vector>
#include "Entry.h"

class CSVStorage
{
public:
    CSVStorage();
    ~CSVStorage();

    void Save_CSV(std::string path);
    void Load_CSV(std::string path);

    std::vector<Entry> entries;
};

#endif