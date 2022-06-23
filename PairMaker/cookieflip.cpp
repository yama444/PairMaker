#include <windows.h>
#include "Common.h"

BOOL Tflg[3] = {FALSE,FALSE,FALSE};		// 正解時の初期セット

int cookieflip( void ){
	for(int P = 0; P < MAX_PLAYER; P++){
		for(int i = 0; i < MAX_COOKIE ; i++){
			switch(charainfo[P].chara){
				case 0:
					if(TRUE == HitCheck_Sphere_Capsule(VGet(cookieColl[i][0], charainfo[0].pos.y, cookieColl[i][1]), COOKIE_SIZE/2,
															VAdd(VGet(charainfo[P].pos.x,charainfo[0].pos.y,charainfo[P].pos.z),charainfo[P].move), VAdd(VGet(charainfo[P].pos.x,charainfo[0].pos.y,charainfo[P].pos.z),charainfo[P].move),
															charainfo[P].charahitinfo.Width/2)){
						if(cookieinfo[charainfo[P].Selcookie[0]].stay != 1 &&
							cookieinfo[charainfo[P].Selcookie[1]].stay != 1 &&
							 Tflg[P] != TRUE								 &&
							 cookieinfo[i].playtime == 0.0f){			// ひっくり返し中でない
							if(roolflipF[P] == TRUE){									// ボタンが押されている
								if( charainfo[P].Selcookie[0] != 99 && charainfo[P].stay == FALSE){
									if(cookieinfo[i].Flipflag == FALSE){
										if(P == 0){
											MV1SetEmiColorScale( cookie[i], P1COLOR) ;
										}else{
											MV1SetEmiColorScale( cookie[i], P2COLOR) ;
										}
										charainfo[P].Selcookie[1] = i;
									}
									if(charainfo[P].Selcookie[1] == charainfo[P].Selcookie[0]){		//	同じものを選んでいたら初期化
										charainfo[P].Selcookie[1] = 99;
									}
								}else{
									if(cookieinfo[i].Flipflag == FALSE){
										if(P == 0){
											MV1SetEmiColorScale( cookie[i], P1COLOR) ;
										}else{
											MV1SetEmiColorScale( cookie[i], P2COLOR) ;
										}
										charainfo[P].Selcookie[0] = i;
									}
								}
								cookieinfo[i].Flipflag = 1;
								cookieinfo[i].effect = 1;
							}
						}
					}
					break;

				case 1:
					if(TRUE == HitCheck_Sphere_Capsule(VGet(cookieColl[i][0], charainfo[0].pos.y, cookieColl[i][1]), COOKIE_SIZE/2,
															VAdd(VGet(charainfo[P].pos.x,charainfo[0].pos.y,charainfo[P].pos.z),charainfo[P].move), VAdd(VGet(charainfo[P].pos.x,charainfo[0].pos.y,charainfo[P].pos.z),charainfo[P].move),
															charainfo[P].charahitinfo.Width/2)){
						if(cookieinfo[charainfo[P].Selcookie[0]].stay != 1 &&
							cookieinfo[charainfo[P].Selcookie[1]].stay != 1 &&
							 Tflg[P] != TRUE								 &&
							  cookieinfo[i].playtime == 0.0f){			// ひっくり返し中でない
							if(roolflipF[P] == TRUE){
								if( charainfo[P].Selcookie[0] != 99 && charainfo[P].stay == FALSE){
									if(cookieinfo[i].Flipflag == FALSE){
										if(P == 0){
											MV1SetEmiColorScale( cookie[i], P1COLOR) ;
										}else{
											MV1SetEmiColorScale( cookie[i], P2COLOR) ;
										}
										charainfo[P].Selcookie[1] = i;
									}
									if(charainfo[P].Selcookie[1] == charainfo[P].Selcookie[0]){		//	同じものを選んでいたら初期化
										charainfo[P].Selcookie[1] = 99;
									}
								}
								else{
									if(cookieinfo[i].Flipflag == FALSE){
										if(P == 0){
											MV1SetEmiColorScale( cookie[i], P1COLOR) ;
										}else{
											MV1SetEmiColorScale( cookie[i], P2COLOR) ;
										}
										charainfo[P].Selcookie[0] = i;
									}
								}
								cookieinfo[i].Flipflag = 1;
								cookieinfo[i].effect = 1;
							}
						}
					}
					break;

				case 2:
					if(TRUE == HitCheck_Sphere_Capsule(VGet(cookieColl[i][0], charainfo[0].pos.y, cookieColl[i][1]), COOKIE_SIZE/2,
						VAdd(VGet(charainfo[P].pos.x + C3OFFX, charainfo[0].pos.y, charainfo[P].pos.z + C3OFFZ),charainfo[P].move), VAdd(VGet(charainfo[P].pos.x + C3OFFX, charainfo[0].pos.y, charainfo[P].pos.z + C3OFFZ),charainfo[P].move),
														charainfo[P].charahitinfo.Width/2)){
						if(cookieinfo[charainfo[P].Selcookie[0]].stay != 1 &&
							cookieinfo[charainfo[P].Selcookie[1]].stay != 1 &&
							 Tflg[P] != TRUE								 &&
							  cookieinfo[i].playtime == 0.0f){			// ひっくり返し中でない
							if(roolflipF[P] == TRUE){
								if( charainfo[P].Selcookie[0] != 99 && charainfo[P].stay == FALSE){
									if(cookieinfo[i].Flipflag == FALSE){
										if(P == 0){
											MV1SetEmiColorScale( cookie[i], P1COLOR) ;
										}else{
											MV1SetEmiColorScale( cookie[i], P2COLOR) ;
										}
										charainfo[P].Selcookie[1] = i;
									}
									if(charainfo[P].Selcookie[1] == charainfo[P].Selcookie[0]){		//	同じものを選んでいたら初期化
										charainfo[P].Selcookie[1] = 99;
									}
								}
								else{
									if(cookieinfo[i].Flipflag == FALSE){
										if(P == 0){
											MV1SetEmiColorScale( cookie[i], P1COLOR) ;
										}else{
											MV1SetEmiColorScale( cookie[i], P2COLOR) ;
										}
										charainfo[P].Selcookie[0] = i;
									}
								}
								cookieinfo[i].Flipflag = 1;
								cookieinfo[i].effect = 1;
							}
						}
					}
					break;
			}
		}
	}
	return 0;
}

int cookiechecker(){
	for(int P = 0; P < MAX_PLAYER; P++){
		if(charainfo[P].Selcookie[1] != 99){				// 2つめが選ばれている状態
			switch(cookieinfo[charainfo[P].Selcookie[0]].cookienum){
				case 0:
				case 1:
					if(cookieinfo[charainfo[P].Selcookie[1]].cookienum == 0 || cookieinfo[charainfo[P].Selcookie[1]].cookienum == 1){
						if(Tflg[P] == FALSE) {
							PlaySoundMem( soundh[8] , DX_PLAYTYPE_BACK ) ;
							cookieinfo[charainfo[P].Selcookie[0]].deletestaytime = STAYTIME-10 ;
							cookieinfo[charainfo[P].Selcookie[1]].deletestaytime = STAYTIME-10 ;
							Tflg[P] = TRUE;
						}
						if(cookieinfo[charainfo[P].Selcookie[1]].deletestaytime == 0 && Tflg[P] == TRUE) {
							getcookiecnt++;
							charainfo[P].getcookie++;
							cookieinfo[charainfo[P].Selcookie[0]].fliped = TRUE;
							cookieinfo[charainfo[P].Selcookie[1]].fliped = TRUE;
							charainfo[P].Selcookie[0] = 99;										// クッキーの選択を初期化
							charainfo[P].Selcookie[1] = 99;										// クッキーの選択を初期化
							Tflg[P] = FALSE;
						}else{
							cookieinfo[charainfo[P].Selcookie[0]].deletestaytime--;						
							cookieinfo[charainfo[P].Selcookie[1]].deletestaytime--;						
							MV1SetEmiColorScale( cookie[charainfo[P].Selcookie[0]], GetColorF(1.0f,1.0f,1.0f,1.0f - (cookieinfo[charainfo[P].Selcookie[0]].deletestaytime * 0.3f))) ;
							MV1SetEmiColorScale( cookie[charainfo[P].Selcookie[1]], GetColorF(1.0f,1.0f,1.0f,1.0f - (cookieinfo[charainfo[P].Selcookie[1]].deletestaytime * 0.3f))) ;
						}
					} 
					else if(P == 0){
						return -1;
					}
					else if(P == 1){
						return -2;
					}
					break;

				case 2:
				case 3:
					if(cookieinfo[charainfo[P].Selcookie[1]].cookienum == 2 || cookieinfo[charainfo[P].Selcookie[1]].cookienum == 3){
						if(Tflg[P] == FALSE) {
							PlaySoundMem( soundh[8] , DX_PLAYTYPE_BACK ) ;
							cookieinfo[charainfo[P].Selcookie[0]].deletestaytime = STAYTIME-10 ;
							cookieinfo[charainfo[P].Selcookie[1]].deletestaytime = STAYTIME-10 ;
							Tflg[P] = TRUE;
						}
						if(cookieinfo[charainfo[P].Selcookie[1]].deletestaytime == 0 && Tflg[P] == TRUE) {
							getcookiecnt++;
							charainfo[P].getcookie++;
							cookieinfo[charainfo[P].Selcookie[0]].fliped = TRUE;
							cookieinfo[charainfo[P].Selcookie[1]].fliped = TRUE;
							charainfo[P].Selcookie[0] = 99;										// クッキーの選択を初期化
							charainfo[P].Selcookie[1] = 99;										// クッキーの選択を初期化
							Tflg[P] = FALSE;
						}else{
							cookieinfo[charainfo[P].Selcookie[0]].deletestaytime--;						
							cookieinfo[charainfo[P].Selcookie[1]].deletestaytime--;						
							MV1SetEmiColorScale( cookie[charainfo[P].Selcookie[0]], GetColorF(1.0f,1.0f,1.0f,1.0f - (cookieinfo[charainfo[P].Selcookie[0]].deletestaytime * 0.3f))) ;
							MV1SetEmiColorScale( cookie[charainfo[P].Selcookie[1]], GetColorF(1.0f,1.0f,1.0f,1.0f - (cookieinfo[charainfo[P].Selcookie[1]].deletestaytime * 0.3f))) ;
						}
					} 
					else if(P == 0){
						return -1;
					}
					else if(P == 1){
						return -2;
					}
					break;

				case 4:
				case 5:
					if(cookieinfo[charainfo[P].Selcookie[1]].cookienum == 4 || cookieinfo[charainfo[P].Selcookie[1]].cookienum == 5){
						if(Tflg[P] == FALSE) {
							PlaySoundMem( soundh[10] , DX_PLAYTYPE_BACK ) ;
							cookieinfo[charainfo[P].Selcookie[0]].deletestaytime = STAYTIME-10 ;
							cookieinfo[charainfo[P].Selcookie[1]].deletestaytime = STAYTIME-10 ;
							Tflg[P] = TRUE;

							/* --------------------------------------- //
							//   相手にサンダー落とすために入れ替える //
							// -------------------------------------- */
							switch(P){
								case 0:
									if(charainfo[1].sunder == FALSE){
										charainfo[1].sunder = TRUE;					// 雷揃ったフラグ
									}
									break;
								case 1:
									if(charainfo[0].sunder == FALSE){
										charainfo[0].sunder = TRUE;					// 雷揃ったフラグ
									}
									break;
							}
							objectinfo[THUNDER].playtime = 0.0f;
						}
						if(cookieinfo[charainfo[P].Selcookie[1]].deletestaytime <= 0 && Tflg[P] == TRUE &&
							objectinfo[THUNDER].playtime >= objectinfo[THUNDER].anim_totaltime){
							switch(P){
								case 0:
									charainfo[1].sunder = FALSE;
									objectinfo[THUNDER].playtime = 0.0f;
									charainfo[1].getcookie--;
									break;
								case 1:
									charainfo[0].sunder = FALSE;
									objectinfo[THUNDER].playtime = 0.0f;
									charainfo[0].getcookie--;
									break;
							}
							cookieinfo[charainfo[P].Selcookie[0]].fliped = TRUE;
							cookieinfo[charainfo[P].Selcookie[1]].fliped = TRUE;
							charainfo[P].Selcookie[0] = 99;										// クッキーの選択を初期化
							charainfo[P].Selcookie[1] = 99;										// クッキーの選択を初期化
							SetGlobalAmbientLight(BLACKCOLOR);
							MV1SetEmiColorScale(charainfo[P].model1,NORMALCOLOR);
							Tflg[P] = FALSE;
							getcookiecnt++;															// クッキー自体の取得数
						}else{
							cookieinfo[charainfo[P].Selcookie[0]].deletestaytime--;						
							cookieinfo[charainfo[P].Selcookie[1]].deletestaytime--;						
							// ステージ側の色調整
							if(cookieinfo[charainfo[P].Selcookie[1]].deletestaytime%2 == 0){
								SetGlobalAmbientLight(REDCOLOR);
							}else{
								SetGlobalAmbientLight(BLUECOLOR);
							}
						}
					} 
					else if(P == 0){
						return -1;
					}
					else if(P == 1){
						return -2;
					}
					break;
			}
		}
	}
	return 0;
}



