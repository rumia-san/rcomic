#include "image.h"
#include "SDL.h"
#include <memory>
#include <stdexcept>
#include <string>
Image::Image(const char* imagePath)
{
	mPosition = std::make_unique<SDL_Rect>();
	mImageSurface = SDL_LoadBMP(imagePath);
	if (!mImageSurface) {
		using namespace std::string_literals;
		throw std::runtime_error("Failed to load image: "s + SDL_GetError());
	}
		
}

Image::~Image()
{
	if (mImageSurface)
		SDL_FreeSurface(mImageSurface);
}

int Image::blitTo(SDL_Surface* surface)
{
	// SDL_BlitSurface will modify the last parameter, so we need a copy...
	SDL_Rect temp = *mPosition;
	return SDL_BlitSurface(mImageSurface, nullptr, surface, &temp);
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
