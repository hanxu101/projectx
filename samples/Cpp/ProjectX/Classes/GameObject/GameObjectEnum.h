#ifndef  _APP_GameObjectEnum_H_
#define  _APP_GameObjectEnum_H_

enum EGameObjectType
{
    eGOT_Monster,
    eGOT_Bullet,
    eGOT_Item,

    eGOT_Count,
    eGOT_Invalid
};

enum EElementType
{
    eET_Earth,
    eET_Water,
    eET_Fire,
    eET_Air,

    eET_Count,
    eET_Invalid
};

enum EMonsterType
{
    eMT_StoneMan,
    eMT_Titan,
    eMT_CrazyZombie,
    eMT_WaterElement,
    eMT_Fisherman,
    eMT_Naga,

    eMT_Count,
    eMT_Invalid
};

enum EItemType
{
    eIT_TimeFreezeItem,

    eIT_Count,
    eIT_Invalid
};

#endif //_APP_GameObjectEnum_H_