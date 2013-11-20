#ifndef  _APP_GAMEDATA_H_
#define  _APP_GAMEDATA_H_

USING_NS_CC_EXT;

class GameData
{
    DECLARE_SINGLETON(GameData);

public:
    void SetClinicName(std::string name);
    const std::string& GetClinicName() const;

    void SetDoctorName(std::string name);
    const std::string& GetDoctoName() const;

    void SetHomePageUrl(std::string name);
    const std::string& GetHomePageUrl() const;

    void SetMapPath(std::string name);
    const std::string& GetMapPath() const;

private:
    std::string m_clinicName;
    std::string m_doctorName;
    std::string m_homePageUrl;
    std::string m_mapPath;
};

#endif // _APP_GAMEDATA_H_