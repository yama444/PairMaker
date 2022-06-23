#include <windows.h>
#include "common.h"

int SelCharaInclude(){
	charainfo[6].model1 = MV1LoadModel("..\\Player\\chara_lose.mv1") ;
	charainfo[6].attachidx = MV1AttachAnim(charainfo[6].model1, 0, heatM) ;
	charainfo[6].direction = DOWN ;
	charainfo[6].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[6].model1, charainfo[6].attachidx) ;
	charainfo[6].rootflm = MV1SearchFrame(charainfo[6].model1,"root") ;
	MV1SetFrameUserLocalMatrix(charainfo[6].model1, charainfo[6].rootflm,MGetIdent()) ;
	charainfo[6].playtime = 0.0f ;

	charainfo[7].model1 = MV1DuplicateModel(charainfo[6].model1) ;
	charainfo[7].attachidx = MV1AttachAnim(charainfo[7].model1, 0, heatM) ;
	charainfo[7].direction = DOWN ;
	charainfo[7].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[7].model1, charainfo[7].attachidx) ;
	charainfo[7].rootflm = MV1SearchFrame(charainfo[7].model1,"root") ;
	MV1SetFrameUserLocalMatrix(charainfo[7].model1, charainfo[7].rootflm,MGetIdent()) ;
	charainfo[7].playtime = 0.0f ;

	for(int cnt = MAX_PLAYER; cnt < 5; cnt++){
		switch(cnt){
		   case MAX_PLAYER:
			charainfo[2].model1 = MV1LoadModel("..\\Player\\chara1.mv1") ;  // ‚¹‚ñ‚­‚¤2
			charainfo[2].attachidx = MV1AttachAnim(charainfo[2].model1, 1, Pstay) ;
		   break;
		   case MAX_PLAYER + 1:
			charainfo[3].model1 = MV1LoadModel("..\\Player\\chara2.mv1") ;  // ‚¹‚ñ‚­‚¤3
			charainfo[3].attachidx = MV1AttachAnim(charainfo[3].model1, 0, P2stay) ;
		   break;
		   case MAX_PLAYER + 2:
			charainfo[4].model1 = MV1LoadModel("..\\Player\\chara3.mv1") ;  // ‚¹‚ñ‚­‚¤4
			charainfo[4].attachidx = MV1AttachAnim(charainfo[4].model1, 0, P3stay) ;
		   break;
		}
		if(charainfo[cnt].model1 == -1) return -1 ;	
		charainfo[cnt].direction = DOWN ;
		charainfo[cnt].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[cnt].model1, charainfo[cnt].attachidx) ;
		charainfo[cnt].rootflm = MV1SearchFrame(charainfo[cnt].model1,"root") ;
		MV1SetFrameUserLocalMatrix(charainfo[cnt].model1, charainfo[cnt].rootflm,MGetIdent()) ;
		charainfo[cnt].playtime = 0.0f ;
	}
	return 0;
}