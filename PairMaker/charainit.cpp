#include <windows.h>
#include "common.h"

int charainit(){
	// ------------------------------------------------------------------------ // 
	//							キャラ情報セット								//
	// ------------------------------------------------------------------------ //
	charainfo[0].pos = VGet(P1POSX, -120.0f, P1POSZ) ;
	if(charainfo[0].chara == 1){
		charainfo[0].pos.y -= 110.0f;
	}else if(charainfo[0].chara == 2){
		charainfo[0].pos.y -= 130.0f;
	}
	charainfo[0].direction = RIGHT ;
	charainfo[0].charahitinfo.Height = PC_HEIGHT;
	charainfo[0].charahitinfo.Width = PC_WIDTH;
	charainfo[0].charahitinfo.CenterPosition = charainfo[0].pos;
	charainfo[0].move = VGet(0.0f,0.0f,0.0f) ;
	charainfo[0].mode = STAND;
	charainfo[0].Selcookie[0] = 99;
	charainfo[0].Selcookie[1] = 99;
	charainfo[0].bdown = FALSE;
	charainfo[0].stay = FALSE;
	charainfo[0].upper = VGet(0.0f,0.0f,0.0f);
	charainfo[0].getcookie = 0;
	charainfo[0].sunder  = FALSE;

	charainfo[1].pos = VGet(P2POSX,-120.0f,P2POSZ) ;			//chara3	-70
	if(charainfo[1].chara == 1){
		charainfo[1].pos.y -= 110.0f;
	}else if(charainfo[1].chara == 2){
		charainfo[1].pos.y -= 130.0f;
	}
	charainfo[1].direction = LEFT ;
	charainfo[1].charahitinfo.Height = PC_HEIGHT;
	charainfo[1].charahitinfo.Width = PC_WIDTH;
	charainfo[1].charahitinfo.CenterPosition = charainfo[1].pos;
	charainfo[1].move = VGet(0.0f,0.0f,0.0f) ;
	charainfo[1].mode = STAND;
	charainfo[1].Selcookie[0] = 99;
	charainfo[1].Selcookie[1] = 99;
	charainfo[1].bdown = FALSE;
	charainfo[1].stay = FALSE;
	charainfo[1].upper = VGet(0.0f,0.0f,0.0f);
	charainfo[1].getcookie = 0;
	charainfo[1].sunder  = FALSE;

	// ------------------------------------------------------------------------- // 
	//							キャラモデルセット			                     //
	// ------------------------------------------------------------------------- // 
	for(int i = 0; i < MAX_PLAYER; i++){
			switch(charainfo[i].chara){
				case 0:
					charainfo[i].model1 = MV1LoadModel("..\\Player\\chara1.mv1") ;		//	せんくう
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 1, Pstay);
					break;
				case 1:
					charainfo[i].model1 = MV1LoadModel("..\\Player\\chara2.mv1") ;		//	white
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 0, P2stay);
					break;
				case 2:
					charainfo[i].model1 = MV1LoadModel("..\\Player\\chara3.mv1") ;		//	cook
					charainfo[i].attachidx = MV1AttachAnim(charainfo[i].model1, 0, P3stay);
					break;
			}
			if(charainfo[i].model1 == -1) return -1 ;	
			charainfo[i].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[i].model1, charainfo[i].attachidx) ;
			charainfo[i].rootflm = MV1SearchFrame(charainfo[i].model1,"root") ;
			MV1SetFrameUserLocalMatrix(charainfo[i].model1, charainfo[i].rootflm,MGetIdent()) ;
			charainfo[i].playtime = 0.0f ;
			MV1SetEmiColorScale( charainfo[i].model1, NORMALCOLOR) ;
	}

	for(int i = 0; i < MAX_COOKIE ; i++){	
		cookieinfo[i].Flipflag = 0;							//	フラグの初期化
		cookieinfo[i].playtime = 0.0f ;	
		cookieinfo[i].stay	   =   0 ;
		cookieinfo[i].staytime = STAYTIME ;
		cookieinfo[i].fliped   = FALSE;
		cookieinfo[i].deletestaytime;		// クッキーの裏側を表示し続ける時間
		cookieinfo[i].fliped;				// 選ばれたフラグ
		cookieinfo[i].sunder;				// 雷を落とす
		MV1SetEmiColorScale( cookie[i], NORMALCOLOR) ;
	}
	objectinfo[0].playtime = 0.0f ;	

	return 0;
}