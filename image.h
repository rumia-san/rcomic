#pragma once
#include <memory>
#include <tuple>

struct SDL_Surface;
struct SDL_Rect;
struct SDL_PixelFormat;

class Image
{
public:
	explicit Image(const char *imagePath);
	~Image();
	void blitTo(SDL_Surface* surface);
	void convertFormat(const SDL_PixelFormat* fmt);
	void moveTo(int x, int y);
	void moveX(int distance);
	void moveY(int distance);
	std::tuple<int, int> getPosition();
	std::tuple<int, int> getSize();
private:
	SDL_Surface* mImageSurface;
	std::unique_ptr<SDL_Rect> mPosition;
};
