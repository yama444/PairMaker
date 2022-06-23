#include <windows.h>
#include "common.h"

char waittime = 0;
char rote = 0;

void upper( void ){
	if(charainfo[0].upper.x == 0.0f){
		if(waittime == 0){
			waittime = 0;
			if(charainfo[0].direction == charainfo[1].direction ){
				switch(charainfo[0].direction){
					case DOWNRIGHT:
						if(charainfo[0].pos.x > charainfo[1].pos.x){
							charainfo[0].direction = UPLEFT;
						}else{
							charainfo[1].direction = UPLEFT;
						}
						break;
					case DOWN:     //2 
						if(charainfo[0].pos.z < charainfo[1].pos.z){
							charainfo[0].direction = UP;
						}else{
							charainfo[1].direction = UP;
						}
						break;
					case DOWNLEFT: //3
						if(charainfo[0].pos.x < charainfo[1].pos.x){
							charainfo[0].direction = UPRIGHT;
						}else{
							charainfo[1].direction = UPRIGHT;
						}
						break;
					case LEFT:     //4   2
						if(charainfo[0].pos.x < charainfo[1].pos.x){
							charainfo[0].direction = RIGHT;
						}else{
							charainfo[1].direction = RIGHT;
						}
						break;
					case UPLEFT:   //5
						if(charainfo[0].pos.x < charainfo[1].pos.x){
							charainfo[0].direction = DOWNRIGHT;
						}else{
							charainfo[1].direction = DOWNRIGHT;
						}
						break;
					case UP:       //6
						if(charainfo[0].pos.z > charainfo[1].pos.z){
							charainfo[0].direction = DOWN;
						}else{
							charainfo[1].direction = DOWN;
						}
						break;
					case UPRIGHT:  //7
						if(charainfo[0].pos.x > charainfo[1].pos.x){
							charainfo[0].direction = DOWNLEFT;
						}else{
							charainfo[1].direction = DOWNLEFT;
						}
						break;
					case RIGHT:     //8
						if(charainfo[0].pos.x > charainfo[1].pos.x){
							charainfo[0].direction = LEFT;
						}else{
							charainfo[1].direction = LEFT;
						}
						break;
				}
			}
			for(int P = 0; P < MAX_PLAYER; P++){
				if((charainfo[P].direction - 4) <= 0){
	/*				switch(charainfo[P].direction - 4){
						case -3:
							rote = UPLEFT;
							break;
						case -2:
							rote = UP;
							break;
						case -1:
							rote = UPRIGHT;
							break;
						case  0:
							rote = RIGHT;
							break;
					}
	*/				rote = charainfo[P].direction + 4;
				}else{
					rote = charainfo[P].direction - 4;
				}
				switch(rote){
					case DOWN:
						charainfo[P].upper.z = -1 * upperspeed * BACKMULTI ;
						break;

					case DOWNLEFT:
						charainfo[P].upper.z = -1 * upperspeed * BACKMULTI ;
						charainfo[P].upper.x = -1 * upperspeed * BACKMULTI ;
						break;

					case LEFT:
						charainfo[P].upper.x = -1 * upperspeed * BACKMULTI ;
						break;

					case UPLEFT:
						charainfo[P].upper.x = -1 * upperspeed * BACKMULTI ;
						charainfo[P].upper.z = upperspeed * BACKMULTI ;
						break;

					case UP:
						charainfo[P].upper.z = upperspeed * BACKMULTI ;
						break;

					case UPRIGHT:
						charainfo[P].upper.x = upperspeed * BACKMULTI ;
						charainfo[P].upper.z = upperspeed * BACKMULTI ;
						break;

					case RIGHT:
						charainfo[P].upper.x = upperspeed * BACKMULTI ;
						break;

					case DOWNRIGHT:
						charainfo[P].upper.x = upperspeed * BACKMULTI ;
						charainfo[P].upper.z = -upperspeed * BACKMULTI ;
						break;
				}
			}
		}else{
			waittime-- ;
		}
	}
}
