#pragma once
struct SDL_Window;
struct SDL_Surface;
struct SDL_PixelFormat;
struct SDL_Renderer;
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
	SDL_Renderer* getRenderer();
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
};
