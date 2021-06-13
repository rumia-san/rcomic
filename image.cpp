#include "image.h"
#include "SDL.h"
#include "SDL_image.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
using namespace std::string_literals;

Image::Image(const char* imagePath)
{
	mPosition = std::make_unique<SDL_Rect>();
	mImageSurface = IMG_Load(imagePath);
	if (!mImageSurface)
		throw std::runtime_error("Failed to load image: "s + SDL_GetError());
}

Image::~Image()
{
	if (mImageSurface)
		SDL_FreeSurface(mImageSurface);
}

void Image::blitTo(SDL_Surface* surface) const
{
	// SDL_BlitSurface will modify the last parameter, so we need a copy...
	SDL_Rect temp = *mPosition;
	if (SDL_BlitSurface(mImageSurface, nullptr, surface, &temp) != 0)
		throw std::runtime_error("Failed to blit image: "s + SDL_GetError());
}

void Image::moveTo(int x, int y)
{
	mPosition->x = x;
	mPosition->y = y;
}

void Image::moveX(int distance)
{
	mPosition->x += distance;
}

void Image::moveY(int distance)
{
	mPosition->y += distance;
}

std::tuple<int, int> Image::getPosition()
{
	return std::make_tuple(mPosition->x, mPosition->y);
}

std::tuple<int, int> Image::getSize()
{
	return std::make_tuple(mImageSurface->w, mImageSurface->h);
}
