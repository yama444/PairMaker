#include <windows.h>
#include <stdio.h>	// --- �R���\�[���p
#include "common.h"
#include <time.h>

// ��������ւ���Flipflag��������
void Mixer( void ){
	// ����
	BOOL loopout;
	char temp;													//	�\�[�g�p
	int SeedNum[2];												//	�����_���̒l
	int saveNum[MAX_COOKIE];	//	�����񂷗p

	// saveNum�ɏ����l{0,1,2,3,4,5}���Z�b�g
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
		cookieinfo[i].Flipflag = 0;					//�Ђ�����Ԃ��t���O�̏�����
		cookieinfo[i].cookienum = saveNum[i];
	}
}



