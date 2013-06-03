
#ifndef TEST_H
#define TEST_H

#define    RAND_LIMIT    32767

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

inline float GetDistance(float point1x, float point1y, float point2x, float point2y)
{
	return std::sqrt((std::abs(point1x - point2x) * std::abs(point1x - point2x)) + (std::abs(point1y - point2y) * std::abs(point1y - point2y)));
}

#endif
