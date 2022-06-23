#include <windows.h>
#include <stdio.h>	// --- コンソール用
#include "common.h"
#include <time.h>

// 数字入れ替えとFlipflagを初期化
void Mixer( void ){
	// 乱数
	BOOL loopout;
	char temp;													//	ソート用
	int SeedNum[2];												//	ランダムの値
	int saveNum[MAX_COOKIE];	//	数字回す用

	// saveNumに初期値{0,1,2,3,4,5}をセット
	for(char i = 0; i < MAX_COOKIE; i++){ 
		saveNum[i]= i;
	}

	SRand((unsigned int) time(NULL));
	for( char Loop = 0; Loop < MAX_LOOP; Loop++){
		loopout = TRUE;
		SeedNum[0] = GetRand(MAX_COOKIE-1);
		SeedNum[1] = GetRand(MAX_COOKIE-1);
		while(loopout){
			if(SeedNum[0] != SeedNum[1]){
				temp = saveNum[SeedNum[0]];
				saveNum[SeedNum[0]] = saveNum[SeedNum[1]];
				saveNum[SeedNum[1]] = temp;
				loopout = FALSE;
			}else{
				SeedNum[1] = GetRand(MAX_COOKIE-1);
			}
		}
	}

	for( char i = 0; i < MAX_COOKIE ; i++ ){
		cookieinfo[i].Flipflag = 0;					//ひっくり返しフラグの初期化
		cookieinfo[i].cookienum = saveNum[i];
	}
}



