#include <windows.h>
#include "common.h"

void Animset(){
	// 移動か静止判定
	for(int i = 0; i < MAX_PLAYER; i++ ){
		if(charainfo[i].move.x == 0.0f && charainfo[i].move.y == 0.0f && charainfo[i].move.z == 0.0f && charainfo[i].mode == RUN){			//	止まっているとき
			switch(charainfo[i].chara){
				case 0:								//	せんくう
					MV1DetachAnim(charainfo[i].model1, charainfo[i].attachidx) ;
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 1, Pstay) ;
					break;
				case 1:
					MV1DetachAnim(charainfo[i].model1, charainfo[i].attachidx) ;
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 0, P2stay) ;
					break;
				case 2:
					MV1DetachAnim(charainfo[i].model1, charainfo[i].attachidx) ;
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 0, P3stay) ;
					break;
			}
			charainfo[i].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[i].model1, charainfo[i].attachidx) ;
			charainfo[i].rootflm = MV1SearchFrame(charainfo[i].model1,"root") ;
			MV1SetFrameUserLocalMatrix(charainfo[i].model1, charainfo[i].rootflm,MGetIdent()) ;
			charainfo[i].playtime = 0.0f ;	
			charainfo[i].mode = STAND;

		}else if(charainfo[i].mode == STAND && (charainfo[i].move.x != 0.0f || charainfo[i].move.y != 0.0f || charainfo[i].move.z != 0.0f)){
			switch(charainfo[i].chara){
				case 0:								//	せんくう
					MV1DetachAnim(charainfo[i].model1, charainfo[i].attachidx) ;
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 0, Pmove) ;
					break;
				case 1:								//	いちご
					MV1DetachAnim(charainfo[i].model1, charainfo[i].attachidx) ;
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 0, P2move) ;
					break;
				case 2:								//	くろ
					MV1DetachAnim(charainfo[i].model1, charainfo[i].attachidx) ;
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 0, P3move) ;
					break;
			}
			charainfo[i].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[i].model1, charainfo[i].attachidx) ;
			charainfo[i].rootflm = MV1SearchFrame(charainfo[i].model1,"root") ;
			MV1SetFrameUserLocalMatrix(charainfo[i].model1, charainfo[i].rootflm,MGetIdent()) ;
			charainfo[i].playtime = 0.0f ;
			charainfo[i].mode = RUN;
		}

		//  アニメーションの値を加算
		if(charainfo[i].playtime < charainfo[i].anim_totaltime){
			charainfo[i].playtime += 0.5f;
		}
		else
		{
			charainfo[i].playtime = 0.0f;
		}
	}

	// アニメーション動作
	for(int i = 0; i < MAX_COOKIE; i++){
		if( cookieinfo[i].Flipflag == 1 && cookieinfo[i].playtime < cookieinfo[i].anim_totaltime ){
				cookieinfo[i].playtime += 2.5f;											//	クッキーをひっくり返す
		}
	}

	for(char i = 0; i < MAX_BOWL; i++){
		if(objectinfo[BOWL + i].playtime < objectinfo[BOWL].anim_totaltime){
			if(i == 0){
				objectinfo[BOWL + i].playtime += 0.8f ;
			}
			if(i == 1){
				objectinfo[BOWL + i].playtime += 1.8f ;
			}
			if(i == 2){
				objectinfo[BOWL + i].playtime += 0.1f ;
			}
			if(i == 3){
				objectinfo[BOWL + i].playtime += 0.8f ;
			}
			if(i == 4){
				objectinfo[BOWL + i].playtime += 0.8f ;
			}
		}else{
			objectinfo[BOWL + i].playtime = 0.0f ;
		}
		MV1SetAttachAnimTime(bowl[i], objectinfo[BOWL].attachidx, objectinfo[BOWL + i].playtime) ;
	}

	// アニメーションの実行
	for( int i = 0; i < MAX_COOKIE; i++){
		MV1SetAttachAnimTime(cookie[i], cookieinfo[i].attachidx, cookieinfo[i].playtime) ;
	}

	MV1SetAttachAnimTime(charainfo[0].model1, charainfo[0].attachidx, charainfo[0].playtime) ;
	MV1SetAttachAnimTime(charainfo[1].model1, charainfo[1].attachidx, charainfo[1].playtime) ;
}