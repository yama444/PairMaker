#include <Windows.h>
#include "common.h"

int FlipCnt(){
	for( char P = 0; P < MAX_PLAYER; P++){
		roolflipF[P] = FALSE;
		charainfo[P].upper  = VGet(0.0f,0.0f,0.0f);
		charainfo[P].move.x = 0.0f;
		charainfo[P].move.y = 0.0f;
		charainfo[P].move.z = 0.0f;
	}

	if(resetwaittime == 35){								// 1•bwait
		if(charainfo[0].sunder != TRUE && charainfo[1].sunder != TRUE){
			for(char i = 0; i < MAX_COOKIE; i++){
					cookieinfo[i].playtime = 0.0f;
					cookieinfo[i].fliped   = FALSE;
					cookieinfo[i].Flipflag = FALSE;
					cookieinfo[i].stay = FALSE;
					cookieinfo[i].staytime = STAYTIME;
					cookieinfo[i].deletestaytime = 0;
					MV1SetEmiColorScale(cookie[i], NORMALCOLOR) ;
			}
			charainfo[0].Selcookie[0] = 99;
			charainfo[0].Selcookie[1] = 99;
			charainfo[1].Selcookie[0] = 99;
			charainfo[1].Selcookie[1] = 99;
			getcookiecnt = 0;
			resetwaittime = 0;
			SetGlobalAmbientLight(BLACKCOLOR);
			Mixer();
			return 1;
		}
	}else if(resetwaittime == 1){
		PlaySoundMem( soundh[11] , DX_PLAYTYPE_BACK ) ;
		resetwaittime++;
	}else{
		resetwaittime++;
		SetGlobalAmbientLight( GetColorF(resetwaittime * 0.025f,resetwaittime * 0.025f,resetwaittime * 0.025f,1.0f) );
	}
	return 0;
}