#include <Windows.h>
#include "common.h"

float Cfly  = MAX_FLY_HEIGHT;		//Å@Ç´Ç·ÇÁÇ≠ÇΩÅ[ÇÃïÇóV
char  FlyF	= FALSE;
BOOL updownF[MAX_PLAYER] = {FALSE,FALSE};
float ROOL[MAX_PLAYER]  = {0.0f,0.0f};

void PlayerFly(){
	for( char i = 0; i < MAX_PLAYER; i++){
		if(charainfo[i].bdownF == TRUE){
			// à⁄ìÆílÇÃèâä˙âª
			charainfo[i].move.x = 0.0f;
			charainfo[i].move.y = 0.0f;
			charainfo[i].move.z = 0.0f;
			if(updownF[i] == FALSE){
				charainfo[i].pos.y -= 4.0f;
				charainfo[i].bdown += 4.0f;
				ROOL[i]               += 0.26f;
				MV1SetRotationXYZ(charainfo[i].model1,VGet(0.0f,ROOL[i],0.0f));
				if(charainfo[i].bdown > 20.0f){
					updownF[i] = TRUE;				
				}	
			}else{
				charainfo[i].pos.y += 4.0f;
				charainfo[i].bdown -= 4.0f;
				ROOL[i]               += 0.26f;
				MV1SetRotationXYZ(charainfo[i].model1,VGet(0.0f,ROOL[i],0.0f));
				if(charainfo[i].bdown == 0.0f){
					charainfo[i].bdownF = FALSE;
					updownF[i] = FALSE;
				}
			}
		}else{
			if(FlyF == TRUE){
				if(Cfly < MAX_FLY_HEIGHT){
					Cfly += 0.01f;
				}
				else{
					FlyF = FALSE;
					Cfly -= 0.0064f;
				}
			}
			else{
				if(Cfly > -MAX_FLY_HEIGHT){
					Cfly -= 0.0064f;
				}
				else{
					FlyF = TRUE;
					Cfly += 0.01f;
				}
			}
			charainfo[0].pos.y += Cfly; 
			charainfo[1].pos.y += Cfly + 0.0007f; 
		}
	}
//	for(int i = 0; i < MAX_COOKIE; i++)	cookieinfo[i].cookiepos.y += Cfly + 0.02f; 
}