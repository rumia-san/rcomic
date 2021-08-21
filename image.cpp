#include "image.h"
#include "SDL.h"
#include "SDL_image.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include "imageUtils.h"

using namespace std::string_literals;

Image::Image(const char *imagePath, SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mImagePath = imagePath;
	mPosition = std::make_unique<SDL_Rect>();

	auto [w, h] = ImageUtils::getImageSize(imagePath);
	mPosition->w = w;
	mPosition->h = h;
}

bool Image::load()
{
	if (mImageTexture)
		return false;
	SDL_Surface *tempSurface = IMG_Load(mImagePath.c_str());
	if (!tempSurface)
		throw std::runtime_error("Failed to load image: "s + SDL_GetError());
	mPosition->w = tempSurface->w;
	mPosition->h = tempSurface->h;
	mImageTexture = SDL_CreateTextureFromSurface(mRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	if (!mImageTexture)
		throw std::runtime_error("Failed to load image: "s + SDL_GetError());
	return true;
}

bool Image::unload()
{
	if (mImageTexture) {
		SDL_DestroyTexture(mImageTexture);
		mImageTexture = nullptr;
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
		load();
	} else {
		unload();
		return;
	}
	if (mImageTexture) {
		SDL_RenderCopy(mRenderer, mImageTexture, nullptr, mPosition.get());
	}
}

void Image::draw()
{
	if (mImageTexture) {
		SDL_RenderCopy(mRenderer, mImageTexture, nullptr, mPosition.get());
	}
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
