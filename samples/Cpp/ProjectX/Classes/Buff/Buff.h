#ifndef  _APP_BUFF_H_
#define  _APP_BUFF_H_

#include "Buff/BuffEnum.h"

USING_NS_CC;

class Buff : public CCNode
{
public:
    Buff();
    Buff(EBuffType type, float lastTime, float elapsedTime);
    virtual ~Buff();

    virtual void onEnter();
    virtual void onExit();
    void Unspawn();

    virtual void Update(float deltaTime);

    EBuffType GetBuffType() const;

    virtual void ExcuteBuff() = 0;
    virtual void EndBuff() = 0;

protected:
    EBuffType m_type;
    float m_lastTime;
    float m_elapsedTime;
};

#endif // _APP_BUFF_H_