//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, add names guys
//Nov 17, 2021
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "../global.h"

int numCLOUDS = 0; //Number of Clouds

class BadCloud{
	
	double mPosX, mPosY; //The X and Y offsets of the cloud
	int id;
	int mVelX, mVelY; //The velocity of the Cloud

    public:
        static const int CLOUD_WIDTH = 200; //The dimensions of the Cloud
        static const int CLOUD_HEIGHT = 200;
        
		double CLOUD_VEL = 6; //Maximum axis velocity of the Cloud
        //Motion of the cloud left to right and vice version
       
		BadCloud(){ //Initializes the variables
			
			mPosY = 15 + numCLOUDS * 150; //initialize position
			mPosX = numCLOUDS * 150;

			directionofCLOUD = 0; //direction of cloud

			attackIND = 0; //attack

			mVelX = CLOUD_VEL; //Initialize the velocity
			mVelY = 0;

			//Number of Attacking Clouds
			//numAttack = 0;
			
			//Id of cloud
			id = numCLOUDS;
			
			numCLOUDS++; //count the clouds present
		}
		~BadCloud(){
		}
		
        int directionofCLOUD;
        int attackIND;
        //Takes key presses and adjusts the Cloud's velocity

        //Moves the Cloud
        void moveBC(){
			
			if(timer % 10 == 0 && CLOUD_VEL < 24){ //move to the right
				//increase clouds velocity through time
				CLOUD_VEL += 1;
				mVelX = CLOUD_VEL;
			}
			//move to the left
			if(directionofCLOUD == 0){
				mPosX += mVelX;

				//If the Cloud went too far to the left or right
				if(mPosX + CLOUD_WIDTH > SCREEN_WIDTH){
					//Move back
					mPosX -= mVelX;
					directionofCLOUD = 1;
				}

			}
			else if(directionofCLOUD == 1){//Move to the right
				mPosX -= mVelX;
				if(mPosX < 0){
					//Move back
					mPosX -= mVelX;
					directionofCLOUD = 0;
				}
			}	
		}

        
        void render(int attack); //renders Cloud to the screen
		
		int getXPOS(){ //Get X Position of the cloud
			return mPosX; //Get X position of object
		}
		
		int getYPOS(){ //Get Y position of the cloud
			return mPosY; //Get Y position of object
		}
		void numReset(){
			numCLOUDS = 0;
		}

		//Switching between good and bad cloud
		void attack(BadCloud& Cloud, character& player){
			//Cloud 1
			if(timerStarted1 == 1 && Cloud.id == 0){
				if(timer1 % 20 > 12 && timer1 % 20 < 16){
					
					Cloud.attackIND = 1;
					
				}
				else if(timer1 % 20 >= 16 && timer1 % 20 < 20){
					if(Cloud.attackIND == 1){
						Cloud.attackIND = 2;
					}
				}
				else{
					Cloud.attackIND = 0;
				}
			}
			//Cloud 2
			if(timerStarted2 == 1 && Cloud.id == 1){
				if(timer2 % 20 > 12 && timer2 % 20 < 16){
					
					Cloud.attackIND = 1;
					
				}
				else if(timer2 % 20 >= 16 && timer2 % 20 < 20){
					if(Cloud.attackIND == 1){
						Cloud.attackIND = 2;
					}
					//leaveONEgood = 0;
					//Cloud.attackIND = 2;
				}
				else{
					Cloud.attackIND = 0;
				}
			}
			//Cloud 3
			if(timerStarted3 == 1 && Cloud.id == 2){
				if(timer3 % 20 > 12 && timer3 % 20 < 16){
					Cloud.attackIND = 1;
				}
				else if(timer3 % 20 >= 16 && timer3 % 20 < 20){
					if(Cloud.attackIND == 1){
						Cloud.attackIND = 2;
					}
					//leaveONEgood = 0;
					//Cloud.attackIND = 2;
				}
				else{
					if(Cloud.attackIND != 1){
						Cloud.attackIND = 0;
					}
					//Cloud.attackIND = 0;
				}
			}
			//Cloud 4
			if(timerStarted4 == 1 && Cloud.id == 3){
				if(timer4 % 20 > 12 && timer4 % 20 < 16){
					Cloud.attackIND = 1;
				}
				else if(timer4 % 20 >= 16 && timer4 % 20 < 20){
					if(Cloud.attackIND == 1){
						Cloud.attackIND = 2;
					}	
				}
				else{
					Cloud.attackIND = 0;
				}
			}
			if(timerStarted5 == 1 && Cloud.id == 4){
				if(timer5 % 20 > 12 && timer5 % 20 < 16){
					
					Cloud.attackIND = 1;
					
				}
				else if(timer5 % 20 >= 16 && timer5 % 20 < 20){
					if(Cloud.attackIND == 1){
						Cloud.attackIND = 2;
					}
				}
				else{
					Cloud.attackIND = 0;
				}
			}	
		}
};