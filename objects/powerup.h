//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, add names guys
//Nov 17, 2021
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "../global.h"

class powerup{
    int num = 0;
    int mPosX, mPosY; //The X and Y start coordinates of the cloud
    //int mVelX, mVelY;

    public:
        static const int POWERUP_WIDTH = 100; //The dimensions of the Power up
        static const int POWERUP_HEIGHT = 100;
        //Motion of the cloud left to right and vice version
    
        //Initializes the variables
        powerup(){ //Initialize coordinates and velocity
            //mVelX = 0;
            //mVelY = 0;
        }
        ~powerup(){
        }

        //Shows the Power up on the screen
       // void render();

		//friend character;
		
		int getXPOS(){ //Get X Position of the powerup
            return mPosX;
        }
		
		int getYPOS(){ //Get Y position of the powerup
            return mPosY;
        }

        int getNum(){
            return num;
        }
        
        void spawn(){ //Spawn Powerup
            if(num > 0){
                num--;
            }
            
            int xspawncoords = rand() % 1100 + 1; //Get random coordinates
            int yspawncoords = rand() % 700 + 50;
            mPosX = xspawncoords;
            mPosY = yspawncoords;
            return; 
        }

        void numadd(){
            num++;
            return;
        }   

        void numreset(){
            num = 0;
            return;
        }
        
        void render();//Render powerup
};


