#ifndef  _APP_Monsters_Boss_Shu_MaChao_H_
#define  _APP_Monsters_Boss_Shu_MaChao_H_

#include "GameObject/Monsters/Monster.h"

USING_NS_CC;

//Temp define here. Move to a common define header.
enum EDirection
{
    ED_Down,
    ED_Left,
    ED_Right,
    ED_Up
};

class BossMaChao : public Monster 
{
public:
    BossMaChao();
    virtual ~BossMaChao();

    virtual void onEnter();
    virtual void onExit();

    virtual void Killed();

    virtual int GetDetailTypeIndex();

private:
    void PlayMonsterWalkAnimation(EDirection direction);

    void SetMoveAroundPos();

     OVERLOAD_FSM(BossMaChao);
     DECLARE_VIRTUAL_STATE(Move);
     DECLARE_STATE(CastSkill);
     DECLARE_STATE(MoveAround);

     CCParticleGalaxy* m_pParticle;

     std::vector<CCPoint> m_moveAroundPos;
     unsigned int m_moveNode;
};

#endif // _APP_Monsters_Boss_Shu_MaChao_H_