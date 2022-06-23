#include <windows.h>
#include "common.h"

float rotecnt = 0.0f;

void EffectAct(){

	for(char i = 0; i < MAX_COOKIE; i++){
		if(cookieinfo[i].effect == TRUE){
			if(objectinfo[EFFSTAR + i].playtime < objectinfo[EFFSTAR + i].anim_totaltime){
				objectinfo[EFFSTAR + i].playtime += 0.7f;
				rotecnt += 0.1f;
				MV1SetScale(efstar[i],VGet(1.6f,1.7f,1.6f));				// ¯ƒXƒP[ƒ‹
				MV1SetPosition(efstar[i],VGet(cookieinfo[i].cookiepos.x, cookieinfo[i].cookiepos.y - 120.0f, cookieinfo[i].cookiepos.z));			// ¶‰º
				MV1SetRotationXYZ(efstar[i],VGet(0.0f,rotecnt,1.57f*0));
				MV1SetAttachAnimTime(efstar[i], objectinfo[EFFSTAR + i].attachidx, objectinfo[EFFSTAR + i].playtime) ;
				MV1DrawModel(efstar[i]);
			}else{
				cookieinfo[i].effect = FALSE;
				objectinfo[EFFSTAR + i].playtime = 0.0f;
			}

			if(rotecnt > 100.0f)	rotecnt = 0.0f;
		}
	}
}