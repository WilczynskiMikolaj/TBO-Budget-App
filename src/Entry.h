#ifndef ENTRY_H
#define ENTRY_H


#include <string>
#include <ctime>

enum EntryType{
    expense,
    income
};

struct Entry
{
    double amount;
    EntryType type;
    std::string comment;
    time_t date;
};

#endif