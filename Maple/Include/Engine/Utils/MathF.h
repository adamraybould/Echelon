#pragma once

class MathF
{
public:
	template<typename T>
	static T Clamp(T value, T minVal, T maxVal)
	{
		return (value < minVal) ? minVal : ((value > maxVal) ? maxVal : value);
	}
};