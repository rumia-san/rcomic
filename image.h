#pragma once
#include <memory>
#include <tuple>
#include <string>

struct SDL_Surface;
struct SDL_Rect;
struct SDL_PixelFormat;
struct SDL_Texture;
struct SDL_Renderer;

class Image
{
public:
	explicit Image(const char *imagePath, SDL_Renderer* renderer);
	~Image();
	void blitTo(SDL_Surface* surface);
	void draw();
	void moveTo(int x, int y);
	void moveX(int distance);
	void moveY(int distance);
	std::tuple<int, int> getPosition();
	std::tuple<int, int> getSize();
private:
	std::string mImagePath;
	SDL_Texture* mImageTexture = nullptr;
	SDL_Renderer* mRenderer = nullptr;
	std::unique_ptr<SDL_Rect> mPosition;
	bool load();
	bool unload();
};
