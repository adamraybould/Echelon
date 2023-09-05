#include "Engine/Utils/Commons.h"
#include "SDL.h"

Vector2::operator SDL_Point* () const
{
	SDL_Point point;
	point.x = X;
	point.y = Y;
	return &point;
}

Rectangle::operator SDL_Rect* () const
{
	SDL_Rect rect;
	rect.x = X;
	rect.y = Y;
	rect.w = Width;
	rect.h = Height;
	return &rect;
}
