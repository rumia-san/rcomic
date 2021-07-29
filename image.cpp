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
	mImagePath = imagePath;
	mPosition = std::make_unique<SDL_Rect>();
	load();
	mPosition->w = mImageSurface->w;
	mPosition->h = mImageSurface->h;
	unload(); // Dirty workaround, just for getting the width and height...
}

bool Image::load()
{
	if (mImageSurface)
		return false;
	mImageSurface = IMG_Load(mImagePath.c_str());
	if (!mImageSurface)
		throw std::runtime_error("Failed to load image: "s + SDL_GetError());
	return true;
}

bool Image::unload()
{
	if (mImageSurface) {
		SDL_FreeSurface(mImageSurface);
		mImageSurface = nullptr;
		return true;
	}
	return false;
}

Image::~Image()
{
	unload();
}

bool rectInScreen(const SDL_Rect* rect, int screenWidth, int screenHeight)
{
	return (rect->x + rect->w > 0 &&
		rect->x < screenWidth &&
		rect->y + rect->h > 0 &&
		rect->y < screenHeight);
}

void Image::blitTo(SDL_Surface* surface)
{
	if (rectInScreen(mPosition.get(), surface->w, surface->h)) {
		if (load())
			convertFormat(surface->format);
	} else {
		unload();
		return;
	}
	// SDL_BlitSurface will modify the last parameter, so we need a copy...
	SDL_Rect temp = *mPosition;
	if (SDL_BlitSurface(mImageSurface, nullptr, surface, &temp) != 0)
		throw std::runtime_error("Failed to blit image: "s + SDL_GetError());
}

void Image::convertFormat(const SDL_PixelFormat* fmt)
{
	SDL_Surface* converted = SDL_ConvertSurface(mImageSurface, fmt, 0);
	if (!converted)
		throw std::runtime_error("Failed to convert image: "s + SDL_GetError());
	SDL_FreeSurface(mImageSurface);
	mImageSurface = converted;
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
	return { mPosition->x, mPosition->y };
}

std::tuple<int, int> Image::getSize()
{
	return { mPosition->w, mPosition->h };
}
