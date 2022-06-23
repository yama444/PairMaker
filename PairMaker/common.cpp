/* _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	FILE	: Common.cpp
	NAME	: kz-matsu

+ ------ Explanation of file --------------------------------------------------------------------------
       
	共通での処理、または汎用性がある関数や変数の実体宣言部

+ _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/ */

#include <windows.h>
#include "Common.h"

/* -----------------------------------------------------------------------------------------
|
|       グローバル関数の実装部
|
+ --------------------------------------------------------------------------------------- */
SCharaInfo charainfo[10];							// キャラクター情報の格納
SCookieInfo cookieinfo[MAX_COOKIE];					// クッキーの情報格納	
SObjectInfo objectinfo[40];							//
int cookie_pic[20];
int anim_natural, cookie_flip, Cookie_flip_Star, Cookie_flip_Heart, Cookie_flip_Square,
	Pmove, Pstay, Pwin, P2move, P2stay, P2win, P3move, P3stay, P3win, rangeanim, bowlanim,
	heatM,
	crosshair[2],
	thunderdown;						// アニメーション
int	Graph[40];
int key ;											// プレイヤー１の取得キーの格納
int key2;											// プレイヤー２の取得キーの格納
BOOL roolflipF[2];										// △が押された際にTRUEとなる
int plate, table, pancake, pancake2, egg, Sfloor[1], cookie[MAX_COOKIE], thunder, thunder2, range, milk, bowl[MAX_BOWL], lack,reizo ;		//	ステージモデル
int soundh[MAX_SOUND];
int getcookiecnt;
int gamemaintimer;
int gamesubtimer;
int characterselect[7];
int efstar[MAX_COOKIE];
//  ２面用クッキー
VECTOR Stg2cookie[MAX_COOKIE];
char resetwaittime = 0;								// ひっくり返すまでの待ち時間


float cookieColl[MAX_COOKIE][2] = {	{168.0f,175.0f},//0左下
									{448.0f,670.0f},//1上
									{728.0f,175.0f},//2右下
									{448.0f,175.0f},//3真ん中
									{613.0f,440.0f},//4中右
									{283.0f,440.0f},//5中左
								};




