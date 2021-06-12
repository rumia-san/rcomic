#pragma once
#include <memory>
struct SDL_Surface;
struct SDL_Rect;

class Image
{
public:
	explicit Image(const char *imagePath);
	~Image();
	int blitTo(SDL_Surface* surface);
	void moveTo(int x, int y);
	void moveX(int distance);
	void moveY(int distance);
private:
	SDL_Surface* mImageSurface;
	std::unique_ptr<SDL_Rect> mPosition;
};
