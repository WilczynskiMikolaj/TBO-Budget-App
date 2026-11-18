#include "Recents.h"

#include<QDebug>

Recents::Recents()
{
    paths = std::vector<std::string>();
}

Recents::~Recents(){}

std::vector<std::string> Recents::Get_List()
{
    return paths;
}

void Recents::Add(std::string path)
{
    //TODO
    qDebug( "Recents::Add not implemented yet" );
}

void Recents::Save()
{
    //TODO
    qDebug( "Recents::Save not implemented yet" );
}

void Recents::Load()
{
    //TODO
    qDebug( "Recents::Load not implemented yet" );
}

void Recents::Clear()
{
    //TODO
    qDebug( "Recents::Clear not implemented yet" );
}
