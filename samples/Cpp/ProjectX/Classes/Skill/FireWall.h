#ifndef  _APP_FireWall_H_
#define  _APP_FireWall_H_

#include "Skill/SkillBase.h"


class FireWall : public SkillBase, public CCNode, public CCTargetedTouchDelegate
{
    class Unit : public CCSprite
    {
    public:
        Unit();

        static Unit* create(const char *pszFileName);
        virtual void draw(void);
        
    };
public:
    FireWall();
    virtual ~FireWall();

    virtual void Init();
    virtual void OnUpdate(float deltaTime);
    virtual void Uninit();

    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
private:
    float m_collisionUnitRadius;
    std::vector<CCPoint> m_collisionUnits;
    float m_unitDistance;
    UINT8 m_comboAttackCount;

};

#endif // _APP_FireWall_H_
