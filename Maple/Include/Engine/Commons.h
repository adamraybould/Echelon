#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

using UInt = unsigned int;

struct Vector2
{
	float X;
	float Y;

	Vector2()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}

	static Vector2 One()
	{
		return Vector2(1, 1);
	}

	static Vector2 Zero()
	{
		return Vector2(0, 0);
	}
};

struct Transform
{
	Vector2 Position;
	float Rotation;
	Vector2 Scale;

	Transform()
	{
		Position = Vector2(0, 0);
		Rotation = 0.0f;
		Scale = Vector2::One();
	}

	Transform(Vector2 position) : Transform(position, 0.0f, Vector2::One())
	{
	}

	Transform(Vector2 position, Vector2 scale) : Transform(position, 0.0f, scale)
	{
	}

	Transform(Vector2 position, float rotation, Vector2 scale)
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;
	}
};