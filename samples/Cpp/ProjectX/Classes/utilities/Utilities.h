#ifndef Utilities_H
#define Utilities_H

#define MAX_LEN         (cocos2d::kMaxLogLen + 1)

#define XAssert(cond, format, ...)      \
    if(!cond)                           \
    {                                   \
        CCLOG(format, ##__VA_ARGS__);   \
        CCAssert(false,"");             \
    }

#define RAND_LIMIT    32767

#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1<<(b)))
#define BIT_CHECK(a,b) ((a) & (1<<(b)))

/// Random number in range [-1,1]
inline float RandomFloat()
{
    float r = (float)(std::rand() & (RAND_LIMIT));
    r /= RAND_LIMIT;
    r = 2.0f * r - 1.0f;
    return r;
}

/// Random floating point number in range [lo, hi]
inline float RandomFloat(float lo, float hi)
{
    float r = (float)(std::rand() & (RAND_LIMIT));
    r /= RAND_LIMIT;
    r = (hi - lo) * r + lo;
    return r;
}

#endif //Utilities_H
