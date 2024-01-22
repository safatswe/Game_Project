#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "include/SDL.h"
#include "include/SDL_ttf.h"

#undef main

using namespace std;

void renderPlayer(SDL_Renderer* renderer, SDL_Rect player, int x, int y, int scale, vector<int> tailX, vector<int> tailY, int tailLength) {
    SDL_SetRenderDrawColor(renderer, 255,15,150, 255);
    player.w = scale;
    player.h = scale;

    for (int i = 0; i < tailLength; i++) {
        player.x = tailX[i];
        player.y = tailY[i];
        SDL_RenderFillRect(renderer, &player);
    }
 SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
    player.x = x;
    player.y = y;

    SDL_RenderFillRect(renderer, &player);
}

void renderFood(SDL_Renderer* renderer, SDL_Rect food) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &food);
} 
void renderbonusFood(SDL_Renderer* renderer, SDL_Rect bonusfood) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &bonusfood);
} 

bool checkCollision(int foodx, int foody, int playerx, int playery) {
    return (playerx == foodx && playery == foody);
}
bool checkCollisionbonus(int bfoodx, int bfoody, int playerx, int playery) {
    return (playerx == bfoodx && playery == bfoody);
}




pair<int, int> getFoodSpawn(vector<int> tailX, vector<int> tailY, int playerX, int playerY, int scale, int wScale, int tailLength) {
    bool valid = false;
    int x = 0;
    int y = 0;
  
    x = scale * (rand() % wScale);
    y = scale * (rand() % wScale);
    valid = true;

    for (int i = 0; i < tailLength; i++) {
        if ((x == tailX[i] && y == tailY[i]) || (x == playerX && y == playerY)) {
            valid = false;
        }
    }
  
         
          if(y==scale*2 && (x>=scale*16 && x<=scale*21))
            valid=false;
          if(x==scale*21 && (y>=scale*2 && y<=scale*5+scale*2))
            valid=false;
          if(x==scale*2 && (y>=scale*16&& y<=scale*21))
            valid=false;  
          if(y==scale*21 && (x>=scale*2 && x<=scale*2 +scale*5))
            valid=false;


    if (!valid) {
        pair<int, int> foodLoc;
        foodLoc = make_pair(-100, -100);
        return foodLoc;
    }

    pair<int, int> foodLoc;
    foodLoc = make_pair(x, y);

    return foodLoc;
}



int main(int argc, char* argv[]) {

    int t=0;
    int c=0;
    int score=0;
    
    bool redox=false;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    SDL_Rect player;
    player.x = 0;
    player.y = 0;
    player.h = 0;
    player.w = 0;


    int tailLength = 0;
    vector<int> tailX;
    vector<int> tailY;
    int scale = 24;
    int wScale = 24;
    int x = 0;
    int y = 0;
    int prevX = 0;
    int prevY = 0;


    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    bool inputThisFrame = false;
    bool redo = false;


    SDL_Rect obstacle;
    obstacle.w=scale*5;
    obstacle.h=scale;
    obstacle.x = scale*16;
    obstacle.y=scale*2;
    SDL_Rect obstaclee;
    obstaclee.w=scale;
    obstaclee.h=scale*6;
    obstaclee.x = scale*21;
    obstaclee.y=scale*2;
    
    SDL_Rect obstacl;
    obstacl.w=scale;
    obstacl.h=scale*5;
    obstacl.x = scale*2;
    obstacl.y=scale*16;
    SDL_Rect obstacll;
    obstacll.w=scale*6;
    obstacll.h=scale;
    obstacll.x = scale*2;
    obstacll.y=scale*21;
  
    int flag=0; 
    
    SDL_Rect food;
    food.w = scale;
    food.h = scale;
    food.x = 0;
    food.y = 0;
    SDL_Rect bonusfood;
   bonusfood.w = scale;
  bonusfood.h = scale;
   bonusfood.x = -200;
  bonusfood.y = -200;
      

    pair<int, int> foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
    food.x = foodLoc.first;
    food.y = foodLoc.second;

    
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scale * wScale + 1, scale * wScale + 1, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    float time = SDL_GetTicks() / 100;



    while (true) {
         
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
            SDL_RenderFillRect(renderer, &obstacle);
            SDL_RenderFillRect(renderer, &obstaclee);
            SDL_RenderFillRect(renderer, &obstacl);
            SDL_RenderFillRect(renderer, &obstacll);


        float newTime = SDL_GetTicks() / 100; 
        float delta = newTime - time;
        time = newTime;

        inputThisFrame = false;

    
        if (tailLength >= 575) {
          std::cout<<"YOU WIN!";
            x = 0;
            y = 0;
            up = false;
            left = false;
            right = false;
            down = false;
            tailX.clear();
            tailY.clear();
            tailLength = 0;
            redo = false;
            foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);

            if (food.x == -100 && food.y == -100) {
                redo = true;
            }

            food.x = foodLoc.first;
            food.y = foodLoc.second;
        }

    
        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                exit(0);
            }

            if (event.type == SDL_KEYDOWN && inputThisFrame == false) {
                 if (down == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    up = true;
                    left = false;
                    right = false;
                    down = false;
                    inputThisFrame = true;
                } else if (right == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    up = false;
                    left = true;
                    right = false;
                    down = false;
                    inputThisFrame = true;
                } else if (up == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                    up = false;
                    left = false;
                    right = false;
                    down = true;
                    inputThisFrame = true;
                } else if (left == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    up = false;
                    left = false;
                    right = true;
                    down = false;
                    inputThisFrame = true;
                }
            }
        }

        prevX = x;
        prevY = y;

        if (up) {
            y -= delta * scale;
        } else if (left) {
            x -= delta * scale;
        } else if (right) {
            x += delta * scale;
        } else if (down) {
            y += delta * scale;
        }

        if (redo == true) {
            redo = false;
            foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            food.x = foodLoc.first;
            food.y = foodLoc.second;

            if (food.x == -100 && food.y == -100) {
                redo = true;
            }
        }
    
         

    
        
           if (checkCollision(food.x, food.y, x, y)) {
            c++;
        
            foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            food.x = foodLoc.first;
            food.y = foodLoc.second;

            if (food.x == -100 && food.y == -100) {
                redo = true;
            }

            if(c%3==0)
            {   foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            bonusfood.x = foodLoc.first;
            bonusfood.y = foodLoc.second;

            if (bonusfood.x == -100 && bonusfood.y == -100) {
                redox = true;

            }
            }

            tailLength++;
        
        }


     if (redox == true) {
            redox = false;
            foodLoc = getFoodSpawn(tailX, tailY, x, y, scale, wScale, tailLength);
            bonusfood.x = foodLoc.first;
            bonusfood.y = foodLoc.second;

            if (bonusfood.x == -100 && bonusfood.y == -100) {
                redox = true;
            }
        }
      if(checkCollisionbonus(bonusfood.x,bonusfood.y,x,y))
       { tailLength++;
        bonusfood.x=-300;
        bonusfood.y=-300;
        score=score+10;

       }
    

    
        if (delta * scale ==24)
         {  
            if (tailX.size() != tailLength) {
                tailX.push_back(-100);
                tailY.push_back(-100);
            }

            for (int i = 0; i < tailLength; i++) {
                if (i > 0) {
                    tailX[i - 1] = tailX[i];
                    tailY[i - 1] = tailY[i];
                }
            }

            if (tailLength > 0) {
                tailX[tailLength - 1] = prevX;
                tailY[tailLength - 1] = prevY;
            }
        }


        for (int i = 0; i < tailLength; i++)
        {
           if (x == tailX[i] && y == tailY[i]) 
           {
            t=1;
           }
        }  
        if(t==1)
        break;



    
    if(x>scale*wScale-scale)
         x=0;
    else if(y>scale*wScale-scale)
         y=0;
    else if(x<0)
         x=scale*wScale-scale;
    else if(y<0)
         y=scale*wScale-scale;

    
          if(y==scale*2 && (x>=scale*16 && x<=scale*21))
              flag=1;
          if(x==scale*21 && (y>=scale*2 && y<=scale*5+scale*2))
              flag=1;
          if(x==scale*2 && (y>=scale*16&& y<=scale*21))
              flag=1;  
          if(y==scale*21 && (x>=scale*2 && x<=scale*2 +scale*5))
              flag=1;

         if(flag==1)
         break;
   

    renderFood(renderer, food);
    renderbonusFood(renderer,bonusfood);
    renderPlayer(renderer, player, x, y, scale, tailX, tailY, tailLength);
   SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    }
   std:: cout <<"GAME OVER!"<<endl;
   std:: cout <<"TOTAL SCORE :"<<c+score;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}