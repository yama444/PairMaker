/* _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	FILE	: Common.cpp
	NAME	: kz-matsu

+ ------ Explanation of file --------------------------------------------------------------------------
       
	���ʂł̏����A�܂��͔ėp��������֐���ϐ��̎��̐錾��

+ _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/ */

#include <windows.h>
#include "Common.h"

/* -----------------------------------------------------------------------------------------
|
|       �O���[�o���֐��̎�����
|
+ --------------------------------------------------------------------------------------- */
SCharaInfo charainfo[10];							// �L�����N�^�[���̊i�[
SCookieInfo cookieinfo[MAX_COOKIE];					// �N�b�L�[�̏��i�[	
SObjectInfo objectinfo[40];							//
int cookie_pic[20];
int anim_natural, cookie_flip, Cookie_flip_Star, Cookie_flip_Heart, Cookie_flip_Square,
	Pmove, Pstay, Pwin, P2move, P2stay, P2win, P3move, P3stay, P3win, rangeanim, bowlanim,
	heatM,
	crosshair[2],
	thunderdown;						// �A�j���[�V����
int	Graph[40];
int key ;											// �v���C���[�P�̎擾�L�[�̊i�[
int key2;											// �v���C���[�Q�̎擾�L�[�̊i�[
BOOL roolflipF[2];										// ���������ꂽ�ۂ�TRUE�ƂȂ�
int plate, table, pancake, pancake2, egg, Sfloor[1], cookie[MAX_COOKIE], thunder, thunder2, range, milk, bowl[MAX_BOWL], lack,reizo ;		//	�X�e�[�W���f��
int soundh[MAX_SOUND];
int getcookiecnt;
int gamemaintimer;
int gamesubtimer;
int characterselect[7];
int efstar[MAX_COOKIE];
//  �Q�ʗp�N�b�L�[
VECTOR Stg2cookie[MAX_COOKIE];
char resetwaittime = 0;								// �Ђ�����Ԃ��܂ł̑҂�����


float cookieColl[MAX_COOKIE][2] = {	{168.0f,175.0f},//0����
									{448.0f,670.0f},//1��
									{728.0f,175.0f},//2�E��
									{448.0f,175.0f},//3�^��
									{613.0f,440.0f},//4���E
									{283.0f,440.0f},//5����
								};




