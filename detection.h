//CSE165 oHNO3 game
//Tyler Armstrong, Ralphilou Tatoy, Sy Loc Vedaant Vyas
//Nov 29, 2021
#include "objects/powerup.h"
#include "global.h"

int cloudTime = 0;

void detectingCLOUD(BadCloud&BC, character& ch){
	int cloudPOSX, cloudPOSY;
	cloudPOSX = BC.getXPOS();
	cloudPOSY = BC.getYPOS();
	int posPlayerX = ch.getXPOSC();
	int posPlayerY = ch.getYPOSC();

	if(BC.attackIND == 2){		
		int temp = timer;
		if((posPlayerY + 20 > cloudPOSY && posPlayerY + 20 < cloudPOSY + BC.CLOUD_HEIGHT) && (posPlayerX + 20 > cloudPOSX && posPlayerX + 20 < cloudPOSX + BC.CLOUD_WIDTH)){
			if(ch.getLife() > 0 && (temp - (cloudTime + 1)) > 0){
				Mix_PlayChannel(-1, hit, 0);
				if(ch.getShield() > 0){
					ch.dmgShield();
				}
				else{
					ch.damage();
				}
				cloudTime = timer;
			}
			if(ch.getLife() <= 0){
				gameover = true;
				cloudTime = 0;
			}
			else{
				gameover = false;
			}
		}
	}
	return;
}
void detectionPOWERUP(powerup& pu, character& player){
	int xpospu = pu.getXPOS();
	int ypospu = pu.getYPOS();
	int xpospl = player.getXPOSC();
	int ypospl = player.getYPOSC();

	if((ypospl + 20 > ypospu && ypospl + 20 < ypospu + pu.POWERUP_HEIGHT) && (xpospl + 20 > xpospu && xpospl + 20 < xpospu + pu.POWERUP_WIDTH)){
		if(pu.getNum() == 0 && player.getShield() < 50){
			Mix_PlayChannel(-1, umbrella, 0);
			player.addShield();
			pu.numadd();
		}
	}
	return;
} 
