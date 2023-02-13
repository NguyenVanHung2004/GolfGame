#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>


#include "Entity.h"


class RenderWindow
{

public:

	RenderWindow(const char* p_title, int p_w, int p_h);  // create window
	SDL_Texture* loadTexture(const char* p_filePath);    //  load image from file
	void cleanUp();   // destroy window
	void clear();
	//void render(Entity& p_entity);
	void render(int x, int y, SDL_Texture* p_tex);
	void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

