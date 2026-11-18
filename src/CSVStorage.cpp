#include "CSVStorage.h"
#include <QDebug>


CSVStorage::CSVStorage()
{
    entries = std::vector<Entry>();
}

CSVStorage::~CSVStorage()
{

}


void CSVStorage::Save_CSV(std::string path)
{
    //TODO
    qDebug( "CSVStorage::Save_CSV not implemented yet" );
}

void CSVStorage::Load_CSV(std::string path)
{
    //TODO
    qDebug( "CSVStorage::Load_CSV not implemented yet" );
}