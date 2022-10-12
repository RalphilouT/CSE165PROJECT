//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc, Vedaant Vyas
//Nov 17, 2021
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LTexture.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class character{
	LTexture gPlayerTexture; 
	int mPosX, mPosY; //The X and Y offsets of the player
	int mVelX, mVelY; //The velocity of the player
	int defaultX;
	int life = 25;
	int shield = 0; 

    public:
        static const int PLAYER_WIDTH = 80; //The dimensions of the player aka(hitbox)
        static const int PLAYER_HEIGHT = 80;
        static const int PLAYER_VEL = 10; //Maximum axis velocity of the dot

        character(){//Initializes the variables
			gPlayerTexture.loadFromFile("images/player/playerUp.png");
			mPosX = 550; //player start location
			mPosY = 700;
			defaultX = mPosX;
			mVelX = 0;//Initialize the velocity
			mVelY = 0;
		}
        
        void handleEvent(SDL_Event& e){//Takes key presses and adjusts the player's velocity
			if(e.type == SDL_KEYDOWN && e.key.repeat == 0){ //If a key was pressed
				switch(e.key.keysym.sym){ //Adjust the velocity
				case SDLK_UP:
				case SDLK_w: 
					mVelY -= PLAYER_VEL; 
					gPlayerTexture.loadFromFile("images/player/playerUp.png");
					break;
				case SDLK_DOWN:
				case SDLK_s: 
					mVelY += PLAYER_VEL;
					gPlayerTexture.loadFromFile("images/player/playerDown.png");
					break;
				case SDLK_LEFT:
				case SDLK_a: 
					mVelX -= PLAYER_VEL; 
					gPlayerTexture.loadFromFile("images/player/playerLeft.png");
					break;
				case SDLK_RIGHT:
				case SDLK_d: 
					mVelX += PLAYER_VEL; 
					gPlayerTexture.loadFromFile("images/player/playerRight.png");
					break;
				}
			}
			else if(e.type == SDL_KEYUP && e.key.repeat == 0){ //If a key was released
				switch (e.key.keysym.sym){ //Adjust the velocity
				case SDLK_UP: 
				case SDLK_w:
					mVelY += PLAYER_VEL;
					break;
				case SDLK_DOWN:
				case SDLK_s:
					mVelY -= PLAYER_VEL; 
					break;
				case SDLK_LEFT:
				case SDLK_a:
					mVelX += PLAYER_VEL; 
					break;
				case SDLK_RIGHT: 
				case SDLK_d:
					mVelX -= PLAYER_VEL;	
					break;
				}

			}
		}

        void move(){ //Moves the player
			mPosX += mVelX; //Move the dot left or right

			//If the dot went too far to the left or right
			if((mPosX < 0) || (mPosX + PLAYER_WIDTH > SCREEN_WIDTH)){
				mPosX -= mVelX;//Move back
			}

			mPosY += mVelY; //Move the dot up or down

			//If the dot went too far up or down
			if((mPosY < 45) || (mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT)){
				mPosY -= mVelY; //Move back
			}
		}
        
        void render(); //renders player to screen
		
		int getXPOSC(){ //Get the position of character in x direction
			return mPosX;
		}
		
		int getYPOSC(){//Get the position of character in y direction
			return mPosY;
		}

		int getLife(){
			return life;
		}
		
		void damage(){
			life -= 5;
			return;
		}

		int getShield(){
			return shield;
		}

		void dmgShield(){
			shield -= 5;
			return;
		}

		void addShield(){
			shield += 10;
			return;
		}
};