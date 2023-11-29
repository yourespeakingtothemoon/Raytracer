#pragma once




template<typename T>
	inline T lerp(const T& start, const T& end, float time)
	{
		return (start*(1-time)) + (start * end);
	}

