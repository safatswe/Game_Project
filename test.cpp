#include<iostream>
#include "include/SDL.h"

#undef main
using namespace std;

void drawFilledCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int x = centerX - radius; x <= centerX + radius; x++) {
        for (int y = centerY - radius; y <= centerY + radius; y++) {
            int distance = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
            if (distance <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

int main(int argc,char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window =nullptr;
    SDL_Renderer* renderer =nullptr;
     
    //SDL_CreateWindowAndRenderer(640,480,0,&window,&renderer);
    window = SDL_CreateWindow("Hello" , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 500, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer,0,150,100,255);
    SDL_RenderClear(renderer);
    SDL_Rect rect;
    rect.w=50;
   rect.h=50;
   rect.x=0;
   rect.y=480/2;
SDL_SetRenderDrawColor(renderer,200,200,150,255);
SDL_RenderFillRect(renderer,&rect);
SDL_RenderDrawRect(renderer,&rect);

SDL_RenderDrawPoint(renderer,640/2,480/2);
SDL_Color color = {255, 0,0};

drawFilledCircle( renderer, 320, 240 ,50, color );
SDL_RenderPresent(renderer);
SDL_Delay(5000);

return 0;

}