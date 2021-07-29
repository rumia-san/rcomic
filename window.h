#pragma once
struct SDL_Window;
struct SDL_Surface;
struct SDL_PixelFormat;
class Image;
class ImageList;

class Window
{
public:
	Window();
	~Window();
	void update();
	void clear();
	void drawImage(Image& image);
	void drawImage(ImageList& imageList);
	const SDL_PixelFormat* getWindowPixelFormat();
private:
	SDL_Window* mWindow;
};
