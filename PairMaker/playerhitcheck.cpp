#include <windows.h>
#include "common.h"
void playerhitcheck(){
	if(charainfo[0].chara == 2){
		if(HitCheck_Capsule_Capsule(VAdd(VGet(charainfo[0].pos.x + C3OFFX, charainfo[0].pos.y, charainfo[0].pos.z + C3OFFZ), charainfo[0].move),VAdd(VGet(charainfo[0].pos.x + C3OFFX, charainfo[0].pos.y, charainfo[0].pos.z + C3OFFZ), charainfo[0].move),
									charainfo[0].charahitinfo.Width/2,
									VAdd(VGet(charainfo[1].pos.x,charainfo[0].pos.y,charainfo[1].pos.z),charainfo[1].move),VAdd(VGet(charainfo[1].pos.x,charainfo[0].pos.y,charainfo[1].pos.z),charainfo[1].move),
									charainfo[1].charahitinfo.Width/2) == TRUE){
			PlaySoundMem( soundh[5] , DX_PLAYTYPE_BACK ) ;
			upper();
		}
	}
	else if(charainfo[0].chara == 1){
		if(HitCheck_Capsule_Capsule(VAdd(charainfo[0].pos,charainfo[0].move),VAdd(charainfo[0].pos,charainfo[0].move),
									charainfo[0].charahitinfo.Width/2,
									VAdd(VGet(charainfo[1].pos.x,charainfo[0].pos.y,charainfo[1].pos.z),charainfo[1].move),VAdd(VGet(charainfo[1].pos.x,charainfo[0].pos.y,charainfo[1].pos.z),charainfo[1].move),
									charainfo[1].charahitinfo.Width/2) == TRUE){
			PlaySoundMem( soundh[5] , DX_PLAYTYPE_BACK ) ;
			upper();
		}
	}
	else{
		if(HitCheck_Capsule_Capsule(VAdd(charainfo[0].pos,charainfo[0].move),VAdd(charainfo[0].pos,charainfo[0].move),
									charainfo[0].charahitinfo.Width/2,
									VAdd(VGet(charainfo[1].pos.x,charainfo[0].pos.y,charainfo[1].pos.z),charainfo[1].move),VAdd(VGet(charainfo[1].pos.x,charainfo[0].pos.y,charainfo[1].pos.z),charainfo[1].move),
									charainfo[1].charahitinfo.Width/2) == TRUE){
			PlaySoundMem( soundh[5] , DX_PLAYTYPE_BACK ) ;
			upper();
		}
	}
}