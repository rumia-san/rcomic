#pragma once
struct SDL_Window;
struct SDL_Surface;
class Image;
class Window
{
public:
	Window();
	~Window();
	void update();
	int drawImage(Image& image);

private:
	SDL_Window* mWindow;
};
