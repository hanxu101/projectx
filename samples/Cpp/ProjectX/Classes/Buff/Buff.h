#ifndef  _APP_BUFF_H_
#define  _APP_BUFF_H_

#include "cocos2d.h"
#include "Buff/BuffEnum.h"

USING_NS_CC;

class Buff : public CCNode
{
public:
    Buff();
    Buff(EBuffType type, float lastTime);
    virtual ~Buff();

    virtual void onEnter();
    virtual void onExit();
    void Unspawn();

    virtual void Update(float deltaTime);

    EBuffType GetBuffType() const;

protected:
    EBuffType m_type;
    float m_lastTime;
    float m_elapsedTime;
};

#endif // _APP_BUFF_H_