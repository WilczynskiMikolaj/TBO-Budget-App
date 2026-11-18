#ifndef RECENTS_H
#define RECENTS_H

#include <string>
#include <vector>

class Recents
{
    std::vector<std::string> paths;
    void Save();
public:
    Recents();
    ~Recents();
    std::vector<std::string> Get_List();
    void Add(std::string path);
    void Load();
    void Clear();
};

#endif // RECENTS_H
