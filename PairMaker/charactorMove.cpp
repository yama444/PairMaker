#include <windows.h>
#include "common.h"

int waittime[2] = {0,0};
int Dnum = 4;

int charactorMove(){

//	key = GetJoypadInputState(DX_INPUT_PAD1) ;
	key = GetJoypadInputState(DX_INPUT_KEY_PAD1	) ;
	roolflipF[0] = FALSE;								// ▲押しフラグを毎度初期化

	if(key & PAD_INPUT_DOWN){
		//
//		cookieinfo[Dnum].cookiepos.y--;
//		cookieinfo[Dnum].cookiepos.z--;
		//
		charainfo[0].move.x = 0.0f ;
		charainfo[0].move.z = -1 * walkspeed ; // 下を押下 手前に移動
		charainfo[0].direction = DOWN ;
		if(key & PAD_INPUT_LEFT){
			charainfo[0].move.x = -1 * walkspeed ; // 左を押下 左に移動
			charainfo[0].direction = DOWNLEFT ;
		}
		if(key & PAD_INPUT_RIGHT){
			charainfo[0].move.x = walkspeed	; // 右を押下 右に移動
			charainfo[0].direction = DOWNRIGHT ;
		}
	}

	if(key & PAD_INPUT_UP){
//		cookieinfo[Dnum].cookiepos.y++;
//		cookieinfo[Dnum].cookiepos.z++;
       //
		charainfo[0].move.x = 0.0f ;
		charainfo[0].move.z = walkspeed	; // 上を押下 奥に移動
		charainfo[0].direction = UP ;
		if(key & PAD_INPUT_LEFT){
			charainfo[0].move.x = -1 * walkspeed ; // 左を押下 左に移動
			charainfo[0].direction = UPLEFT ;
		}
		if(key & PAD_INPUT_RIGHT){
			charainfo[0].move.x = walkspeed ; // 右を押下 右に移動
			charainfo[0].direction = UPRIGHT ;
		}
	}
	if(key & PAD_INPUT_LEFT){
//		Dnum--;
//		cookieinfo[Dnum].cookiepos.x--;
		if(Dnum == -1){
		 Dnum = MAX_COOKIE;
		}
		charainfo[0].move.x = -1 * walkspeed ; // 左を押下 左に移動
		charainfo[0].move.z = 0.0f ;
		charainfo[0].direction = LEFT ;
		if(key & PAD_INPUT_DOWN){
			charainfo[0].move.z = -1 * walkspeed ; // 下を押下 手前に移動
			charainfo[0].direction = DOWNLEFT ;
		}
		if(key & PAD_INPUT_UP){
			charainfo[0].move.z = walkspeed ; // 上を押下 奥に移動
			charainfo[0].direction = UPLEFT ;
		}
	}
	if(key & PAD_INPUT_RIGHT){
//		Dnum++ ;
//		cookieinfo[Dnum].cookiepos.x++;
		if(Dnum == MAX_COOKIE+1){
			Dnum = 0;
		}
		charainfo[0].move.x = walkspeed ; // 右を押下 右に移動
		charainfo[0].move.z = 0.0f ;
		charainfo[0].direction = RIGHT ;
		if(key & PAD_INPUT_DOWN){
			charainfo[0].move.z = -1 * walkspeed ; // 下を押下 手前に移動
			charainfo[0].direction = DOWNRIGHT ;
		}
		if(key & PAD_INPUT_UP){
			charainfo[0].move.z = walkspeed ; // 上を押下 奥に移動
			charainfo[0].direction = UPRIGHT ;
		}
	}

	if(key & PAD_INPUT_A){		//△
//		Dnum++ ;
		if(Dnum == MAX_COOKIE+1){
			Dnum = 0;
		}

		if( waittime[0] == 0){		//	連打防止
			PlaySoundMem( soundh[6] , DX_PLAYTYPE_BACK ) ;
			charainfo[0].bdownF = TRUE;
			waittime[0] = DOWNCOOLTIME;
			if((charainfo[0].Selcookie[0] == 99 || charainfo[0].Selcookie[1] == 99)){
				roolflipF[0] = TRUE;
			}
		}
	}
//	if(key == 3840 || key2 == 3840){							// ResetButton;
//		return -1;
//	}

	// カウントダウン
	if(waittime[0] != 0)waittime[0]--;
	return 0;

}

int charactorMove2(){
	key2 = GetJoypadInputState(DX_INPUT_PAD2) ;
//	key2 = GetJoypadInputState(DX_INPUT_KEY_PAD1) ;
	roolflipF[1] = FALSE;								//▲押しフラグを毎度初期化
	if(key2 & PAD_INPUT_DOWN){
		charainfo[1].move.x = 0.0f ;
		charainfo[1].move.z = -1 * walkspeed ; // 下を押下 手前に移動
		charainfo[1].direction = DOWN ;
		if(key2 & PAD_INPUT_LEFT){
			charainfo[1].move.x = -1 * walkspeed ; // 左を押下 左に移動
			charainfo[1].direction = DOWNLEFT ;
		}
		if(key2 & PAD_INPUT_RIGHT){
			charainfo[1].move.x = walkspeed	; // 右を押下 右に移動
			charainfo[1].direction = DOWNRIGHT ;
		}
	}

	if(key2 & PAD_INPUT_UP){
		charainfo[1].move.x = 0.0f ;
		charainfo[1].move.z = walkspeed	; // 上を押下 奥に移動
		charainfo[1].direction = UP ;
		if(key2 & PAD_INPUT_LEFT){
			charainfo[1].move.x = -1 * walkspeed ; // 左を押下 左に移動
			charainfo[1].direction = UPLEFT ;
		}
		if(key2 & PAD_INPUT_RIGHT){
			charainfo[1].move.x = walkspeed ; // 右を押下 右に移動
			charainfo[1].direction = UPRIGHT ;
		}
	}
	if(key2 & PAD_INPUT_LEFT){
		charainfo[1].move.x = -1 * walkspeed ; // 左を押下 左に移動
		charainfo[1].move.z = 0.0f ;
		charainfo[1].direction = LEFT ;
		if(key2 & PAD_INPUT_DOWN){
			charainfo[1].move.z = -1 * walkspeed ; // 下を押下 手前に移動
			charainfo[1].direction = DOWNLEFT ;
		}
		if(key2 & PAD_INPUT_UP){
			charainfo[1].move.z = walkspeed ; // 上を押下 奥に移動
			charainfo[1].direction = UPLEFT ;
		}
	}
	if(key2 & PAD_INPUT_RIGHT){
		charainfo[1].move.x = walkspeed ; // 右を押下 右に移動
		charainfo[1].move.z = 0.0f ;
		charainfo[1].direction = RIGHT ;
		if(key2 & PAD_INPUT_DOWN){
			charainfo[1].move.z = -1 * walkspeed ; // 下を押下 手前に移動
			charainfo[1].direction = DOWNRIGHT ;
		}
		if(key2 & PAD_INPUT_UP){
			charainfo[1].move.z = walkspeed ; // 上を押下 奥に移動
			charainfo[1].direction = UPRIGHT ;
		}
	}

	if(key2 & PAD_INPUT_A){		//△
		if(waittime[1] == 0){		//	連打防止
			PlaySoundMem( soundh[6] , DX_PLAYTYPE_BACK ) ;
			charainfo[1].bdownF = TRUE;
			waittime[1] = DOWNCOOLTIME;
			if((charainfo[1].Selcookie[0] == 99 || charainfo[1].Selcookie[1] == 99)){
				roolflipF[1] = TRUE;
			}
		}
	}
	
	if(key == 3840 || key2 == 3840){									// ResetButton
		return -1;
	}

	// カウントダウン
	if(waittime[1] != 0)waittime[1]--;
	return 0;

}


