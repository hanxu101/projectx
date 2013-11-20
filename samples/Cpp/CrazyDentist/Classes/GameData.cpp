#include "CommonHeaders.h"

#include "GameData.h"

IMPLEMENT_SINGLETON(GameData);

GameData::GameData()
{

}

GameData::~GameData()
{

}

void GameData::SetClinicName(std::string name)
{
    m_clinicName = name;
}

const std::string& GameData::GetClinicName() const
{
    return m_clinicName;
}

void GameData::SetDoctorName(std::string name)
{
    m_doctorName = name;
}

const std::string& GameData::GetDoctoName() const
{
    return m_doctorName;
}

void GameData::SetHomePageUrl(std::string name)
{
    m_homePageUrl = name;
}

const std::string& GameData::GetHomePageUrl() const
{
    return m_homePageUrl;
}

void GameData::SetMapPath(std::string name)
{
    m_mapPath = name;
}

const std::string& GameData::GetMapPath() const
{
    return m_mapPath;
}

