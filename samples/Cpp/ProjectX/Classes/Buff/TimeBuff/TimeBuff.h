#ifndef  _APP_TIMEBUFF_H_
#define  _APP_TIMEBUFF_H_

#include "Buff/Buff.h"

USING_NS_CC;

class TimeBuff : public Buff
{
public:
    TimeBuff();
    TimeBuff(float lastTime);
    virtual ~TimeBuff();

    virtual void ExcuteBuff();
    virtual void EndBuff();
};

#endif // _APP_TIMEBUFF_H_