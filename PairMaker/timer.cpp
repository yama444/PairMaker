#include <windows.h>
#include "Common.h"

int timer(void){
	if(gamemaintimer == 0){
		return -1;
	}
	else if(gamesubtimer == 60 ){
		gamemaintimer--;
		gamesubtimer = 0;
	}else{
		gamesubtimer++;
	}
	return gamemaintimer;
}