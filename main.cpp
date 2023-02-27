#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "RenderWindow.h"
#include "Entity.h"
#include "Ball.h"
#include "Tile.h"
#include "Hole.h"

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
    if (!(TTF_Init()))
        std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    return true;
}

bool SDLinit = init();

RenderWindow window("Golf Game",960, 480);
const int TILE_SIZE = 32;

SDL_Texture* ballTexture = window.loadTexture("res/gfx/ball.png");
SDL_Texture* holeTexture = window.loadTexture("res/gfx/hole.png");
SDL_Texture* pointTexture = window.loadTexture("res/gfx/point.png");
SDL_Texture* tileDarkTexture32 = window.loadTexture("res/gfx/tile32_dark.png");
SDL_Texture* tileDarkTexture64 = window.loadTexture("res/gfx/tile64_dark.png");
SDL_Texture* tileLightTexture32 = window.loadTexture("res/gfx/tile32_light.png");
SDL_Texture* tileLightTexture64 = window.loadTexture("res/gfx/tile64_light.png");
SDL_Texture* ballShadowTexture = window.loadTexture("res/gfx/ball_shadow.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg1.png");
SDL_Texture* uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
SDL_Texture* levelTextBgTexture = window.loadTexture("res/gfx/levelText_bg.png");
SDL_Texture* powerMeterTexture_FG = window.loadTexture("res/gfx/powermeter_fg.png");
SDL_Texture* powerMeterTexture_BG = window.loadTexture("res/gfx/powermeter_bg.png");
SDL_Texture* powerMeterTexture_overlay = window.loadTexture("res/gfx/powermeter_overlay.png");
SDL_Texture* logoTexture = window.loadTexture("res/gfx/logoTex.png");
SDL_Texture* click2start = window.loadTexture("res/gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");
SDL_Texture* boomTexture= window.loadTexture("res/gfx/boom.png");
SDL_Texture* playButtonTexture = window.loadTexture("res/gfx/play_button.png");
SDL_Texture* playButtonClickTexture= window.loadTexture("res/gfx/play_button_click.png");
SDL_Texture* quitButtonTexture= window.loadTexture("res/gfx/quit_button.png");
SDL_Texture* quitButtonClickTexture= window.loadTexture("res/gfx/quit_button_click.png");
SDL_Texture* explosionTextureF1 = window.loadTexture("res/gfx/1.png");
SDL_Texture* explosionTextureF2 = window.loadTexture("res/gfx/2.png");
SDL_Texture* explosionTextureF3 = window.loadTexture("res/gfx/3.png");
SDL_Texture* explosionTextureF4 = window.loadTexture("res/gfx/4.png");
SDL_Texture* explosionTextureF5 = window.loadTexture("res/gfx/5.png");
SDL_Texture* explosionTextureF6 = window.loadTexture("res/gfx/6.png");
SDL_Texture* explosionTextureF7 = window.loadTexture("res/gfx/7.png");
SDL_Texture* explosionTextureF8 = window.loadTexture("res/gfx/8.png");





Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/charge.mp3");
Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/hole.mp3");


SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);

Ball balls = {Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 0)};
std::vector<Hole> holes = {Hole(Vector2f(-50, -50), holeTexture), Hole(Vector2f(-50, -50), holeTexture)};
int level = 0;
// load tile map

std::vector<Tile> loadTiles(int level);
std::vector<Tile> tiles = loadTiles(level);
// load booms
std::vector<Boom> loadBooms(int level);
std::vector<Boom> booms = loadBooms(level);
// explosion
std::vector<Explosion> exploFrame = { Explosion(Vector2f(0,0), explosionTextureF1),
                                        Explosion(Vector2f(0,0), explosionTextureF2),
                                        Explosion(Vector2f(0,0), explosionTextureF3),
                                        Explosion(Vector2f(0,0), explosionTextureF4),
                                        Explosion(Vector2f(0,0), explosionTextureF5),
                                        Explosion(Vector2f(0,0), explosionTextureF6),
                                        Explosion(Vector2f(0,0), explosionTextureF7),
                                        Explosion(Vector2f(0,0), explosionTextureF8),
                                    };




bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;
bool lose = false;
bool swingPlayed = false;
SDL_Event event;
int state = 0; //0 = start screen, 1 = game, 2 = game over

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

void loadLevel(int level);

const char* getStrokeText();
const char* getLevelText(int side);

void update();  // update mouse event and ball
void graphics();   // render game
void starScreen();
void reStart(int level);
void game() ;


int main(int argc, char* args[])
{

    loadLevel(level);
    while (gameRunning)
    {
        game();
        std:: cout << level;
    }

    window.cleanUp();
    TTF_CloseFont(font32);
    TTF_CloseFont(font24);
    SDL_Quit();
    TTF_Quit();
    return 0;
}


void loadLevel(int level)
{

    balls.setVelocity(0, 0);

    balls.setScale(1, 1);

    balls.setWin(false);

    tiles = loadTiles(level);
    booms = loadBooms(level);

    switch (level)
    {
    case 0:
        balls.setPos(32, 32);

        holes.at(0).setPos(900, 400);

        break;
    case 1:
        balls.setPos(32,  32*12);

        holes.at(0).setPos( 32*28, 32*14 );

        break;
    case 2:
        balls.setPos(32, 32);

        holes.at(0).setPos(32*13, 32*14);

        break;
    case 3:
        balls.setPos(24 + 32*4, 24 + 32*5);


        holes.at(0).setPos(24 + 32*4, 22 + 32*1);
        holes.at(1).setPos(24 + 32*4 + 32*10, 22 + 32*11);
        break;
    case 4:
        balls.setPos(24 + 32*2, 24 + 32*12);


        holes.at(0).setPos(24 + 32*1, 22 + 32*1);
        holes.at(1).setPos(24 + 32*0 + 32*10, 22 + 32*7);
        break;
    }
}

std::vector<Tile> loadTiles(int level)
{

    //Open the map
    int tileType = -1 ;
    std::vector<Tile> temp = {};
    std::string filepath ="res/gfx/map";
    filepath += std::to_string(level) +".txt";
    std::ifstream Tilemap(filepath);
    //If the map couldn't be loaded
    if( Tilemap.fail() )
    {
        printf( "Unable to load map file!\n" );
    }
    else
    {
        for ( int i = 0 ; i < 480 ; i+= TILE_SIZE )
            for( int j = 0 ; j < 960 ; j += TILE_SIZE)
            {
                Tilemap >> tileType;
                if ( tileType == 1 )
                    temp.push_back(Tile(Vector2f(j,i), tileDarkTexture32));
            }
    }
    Tilemap.close();
    return temp;

}

std::vector<Boom> loadBooms(int level)
{
    //Open the map
    int tileType = -1 ;
    std::vector<Boom> temp = {};
    std::string filepath ="res/gfx/map";
    filepath += std::to_string(level) +".txt";
    std::ifstream Tilemap(filepath);
    //If the map couldn't be loaded
    if( Tilemap.fail() )
    {
        printf( "Unable to load map file!\n" );
    }
    else
    {
        for ( int i = 0 ; i < 480 ; i+= TILE_SIZE )
            for( int j = 0 ; j < 960 ; j += TILE_SIZE)
            {
                Tilemap >> tileType;
                if( tileType == 2)
                    temp.push_back(Boom(Vector2f(j,i), boomTexture));

            }
    }
    Tilemap.close();

    return temp;

}
const char* getStrokeText()
{
    int biggestStroke = 0;
    if (balls.getStrokes())
        biggestStroke = balls.getStrokes();


    std::string s = std::to_string(biggestStroke);
    s = "STROKES: " + s;
    return s.c_str();
}
const char* getLevelText(int side)
{
    int tempLevel = (level + 1)*2 - 1;
    if (side == 1)
    {
        tempLevel++;
    }
    std::string s = std::to_string(tempLevel);
    s = "HOLE: " + s;
    return s.c_str();
}
void update()
{

    lastTick = currentTick;
    currentTick = SDL_GetPerformanceCounter();
    deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

    mousePressed = false;
    //Get our controls and events
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            gameRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseDown = true;
                mousePressed = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseDown = false;
            }
            break;
        }
    }

    if (state == 1)
       {
            balls.update(deltaTime, mouseDown, mousePressed, tiles, holes,booms,chargeSfx, swingSfx, holeSfx, lose);

            if (balls.getScale().x < -1 && balls.getScale().x < -1)
            {
            level++;
            loadLevel(level);
            }

        }
}
void graphics()
{
    window.clear();

    window.render(0, 0, bgTexture);
    for (Hole& h : holes)
        window.render(h);

    if (!balls.isWin())
    {
        window.render(balls.getPos().x, balls.getPos().y + 4, ballShadowTexture);
    }

    for (Entity& e : balls.getPoints())
        window.render(e);

    window.render(balls);

    for (Tile& t : tiles)
        window.render(t);

    for( Boom& b : booms)
        window.render(b);

    for (Entity& e : balls.getPowerBar())
        window.render(e);

    window.render(balls.getPowerBar().at(0).getPos().x, balls.getPowerBar().at(0).getPos().y, powerMeterTexture_overlay);

    if (state != 2 )
    {
        window.render(420, 13, uiBgTexture);
        window.renderCenter(-10, -240 + 16 + 3, getStrokeText(), font24, black);
        window.renderCenter(-10, -240 + 16, getStrokeText(), font24, white);
    }
    else
    {
        window.render(0, 0, endscreenOverlayTexture);
        window.renderCenter(0, 3 - 32, "YOU COMPLETED THE GAME !", font48, black);
        window.renderCenter(0, -32, "YOU COMPLETED THE GAME!", font48, white);
        window.renderCenter(0, 3 + 32, getStrokeText(), font32, black);
        window.renderCenter(0, 32, getStrokeText(), font32, white);
    }

    window.display();
}

void starScreen()
{
    if (SDL_GetTicks() < 2000)
    {
        if (!swingPlayed)
        {
            Mix_PlayChannel(-1, swingSfx, 0);
            swingPlayed = true;
        }
        //Get our controls and events
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameRunning = false;
                break;
            }
        }

        window.clear();
        window.render(0, 0, bgTexture);
        window.render(170, 20, splashBgTexture);
        window.renderCenter(-20, 0 + 3, "NvHung", font32, black);
        window.renderCenter(-20, 0, "NvHung", font32, white);

    }
    else
    {

        lastTick = currentTick;
        currentTick = SDL_GetPerformanceCounter();
        deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

        window.clear();
        window.render(0, 0, bgTexture);
        window.render(275, 125 + 8*SDL_sin(SDL_GetTicks()*(3.14/1500)), logoTexture);
        window.render(400, 220, playButtonTexture);
        window.render(400, 370, quitButtonTexture);
        bool playInside = false ;
        bool quitInside = false ;
        int x, y;
        SDL_GetMouseState( &x, &y );

        if( x >= 400 && x <= 550 && y >= 220 && y <= 280)
            playInside = true;
        if( playInside )
            window.render(400,220,playButtonClickTexture);

        if( x >= 400 && x <= 550 && y >= 370 && y <= 530)
            quitInside = true;
        if( quitInside )
            window.render(400,370,quitButtonClickTexture);

        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                // into game
                if (event.button.button == SDL_BUTTON_LEFT && playInside)
                {
                    Mix_PlayChannel(-1, holeSfx, 0);
                    state =1 ;
                }
                if (event.button.button == SDL_BUTTON_LEFT && quitInside)
                    gameRunning = false;
                break;

            }
        }
    }

    window.display();
}
void reStart(int level)
{

    loadLevel(level);
}
void game()
{
    if (state == 0)
    {
        starScreen();
    }
    else if ( lose )
    {
        float tempPosX = balls.getPos().x;
        float tempPosY = balls.getPos().y;
        balls.setVelocity(0 ,0 );
        for ( Explosion& e : exploFrame )
        {
                e.setPos( tempPosX -16 , tempPosY -16 );
                window.render(e);
                window.display();
                SDL_Delay(100);
        }
        balls.setPos(-100, -100);

        window.clear();
        window.render(0, 0, endscreenOverlayTexture);
        window.renderCenter(-50, 3 - 32, "Game Over!", font48, black);
        window.renderCenter(-50, -32, "Game Over!", font48, white);
        window.renderCenter(0, 3 + 32, getStrokeText(), font32, black);
        window.renderCenter(0, 32, getStrokeText(), font32, white);
        window.display();
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                state = 0 ;
                lose = false;
                reStart(0);
            }


        }
    }
    else
    {
        update();
        graphics();
    }
}
