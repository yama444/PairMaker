
#include <windows.h>
#include "Common.h"		// --- �S�t�@�C���ł̋��ʃw�b�_�[
#include <time.h>

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){

	// -------------------------------------------------------------------------------------------- //
	//                                             �ϐ��錾                                         //
	// -------------------------------------------------------------------------------------------- //
	// �S�̓I�ȃQ�[���̊Ǘ�
	int gamemode = eSceneBlank ;
	// �X�e�[�W�Ǘ�
	int stageflg = 0;
	//  �ǉ����C�g�n���h��
	int LightHandle;
	// �^�C�}�[
	int maintimer;
	//	�N�b�L�[���O�ꂽ�Ƃ��̂Ђ�����Ԃ��t���O
	BOOL offF[3] = {FALSE, FALSE, FALSE}; 				
	// �L����������΂��̃J�E���^�[
	static char upperNum = 0;						
	// �L�����I��ԍ�
	char charasel[2] = {0,0};
	//  �N�b�L�[��]
	float Trote = 0.12f;
	//  �N�b�L�[��]�t���O
	int  TroteC = 0;
	//  �N�b�L�[��]�t���O
	BOOL  TroteF = FALSE;
	// �L�����I���ŘA�����͂����Ȃ��悤��
	BOOL first[2] = {FALSE, FALSE};						
	// �t���X�N�Ǘ�
	BOOL fullscreen = 1;								
	//  �V���h�E�}�b�v�n���h��
	int ShadowMapHandle ;
	//  �V�[���؂�ւ�����
	char sceentime = 0;
	// �N�b�L�[�f���[�g�^�C��
	char delettime = 0;										
	//  �p���P�[�L�A�j���[�V��������
	float pancakeA = 0.0f;
	// �p���P�[�L�A�j���؂�ւ��t���O
	BOOL  pancakeAF = FALSE;			
	//  �N�b�L�[�ړ��p�x(2��)
	int   circleAngle;
	//  reset
	int resetcnt = 0;
	//  ?
	int fl[2] = {0,0};
	// charasel���̃��[�e�[�V����
	float chararote[2] = {0,0};
	// charasel���̃��[�e�[�V����
	float chararote1[2] = {0,0};
	// charasel���̃��[�e�[�V����
	float chararote2[2] = {0,0};
	char titleF = FALSE;
	long titlecnt = 0;

	// �_�Œx�点
	int delay = 0;
	int delay2 = 20;
	int cnt = 0 ;
	int cnt2 = 0 ;
	BOOL flipdraw[2] = {FALSE,FALSE};
	// �I���J�[�\���̈ړ�
	BOOL charactersetcheck[2] = {FALSE,FALSE};
	// �L�[���������܂őI���J�[�\�����łȂ�
	BOOL selectdrawflg[2]= {FALSE,FALSE};
	// �n�߂邩�̃`�F�b�N
	BOOL okflg[2] = {FALSE,FALSE};
	BOOL plyblin[2] = {FALSE,FALSE};
	BOOL seleweight[2] ={FALSE,FALSE};

	int waittimer = 0 ;
	int cookiestaytime = 0 ;
	BOOL resultsetflg = FALSE;

	//�X�e�[�W�̃|�W�V����
	VECTOR pancakepos  = VGet(440.0f,-555.0f,690.0f) ;
	VECTOR pancake2pos = VGet(2500.0f,-675.0f,600.0f) ;
	VECTOR platepos    = VGet(90.0f,-1000.0f,900.0f) ;
	VECTOR tablepos    = VGet(600.0f,-10050.0f,5200.0f) ;
	VECTOR eggpos	   = VGet(-800.0f,-805.0f,1800.0f) ;
	VECTOR milkpos	   = VGet(-690.0f,-1205.0f,4400.0f) ;
	VECTOR bowlpos[MAX_BOWL];
	VECTOR Sfloorpos[MAX_WALL];
	Sfloorpos[0]   = VGet(440.0f,-475.0f,5000.0f) ;
	VECTOR rangepos = VGet(600.0f,50.0f,900.0f);	// �����W

	// ------------------------------------------------------------------------ // 
	//							�E�B���h�E�ݒ�									//
	// ------------------------------------------------------------------------ //
	SetWindowIconID(111);
	SetMainWindowText("PairMaker");
	if(fullscreen == TRUE){
		SetGraphMode(1280, 720, 32);
		SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_NATIVE);
	}else{
		ChangeWindowMode( TRUE ) ;
		SetGraphMode(640, 480 , 32);
		SetWindowSize(1280, 960) ;
	}

	// DX���C�u�����̏�����
	if(DxLib_Init() == -1) return -1 ;

	// ------------------------------------------------------------------------- // 
	//						�J�����|�W�V�����Z�b�g			                     //
	// ------------------------------------------------------------------------- // 
	VECTOR cpos,ctgt;
	VECTOR cpos2,ctgt2;
	VECTOR cpos3,ctgt3;
	VECTOR cpos4,ctgt4;
	VECTOR cpos5,ctgt5;

	cpos3 = VGet(550.0f,-80.0f,-380.0f) ;
	ctgt3 = VGet(550.0f,-100.0f,50.0f) ;
	cpos2 = VGet(440.0f,100.0f,-320.0f) ;
	ctgt2 = VGet(440.0f,-150.0f,50.0f) ;
	cpos = VGet(440.0f,500.0f,-10020.0f) ;
	ctgt = VGet(440.0f,-150.0f,50.0f) ;

	while(ProcessMessage() == 0){
		switch(gamemode){
			case eSceneBlank :
				// ------------------------------------------------------------------------- // 
				//							�t�H���g�ǂݍ���					             //
				// ------------------------------------------------------------------------- // 
				SetFontThickness(7); //0-9 
				SetFontSize(64);
				ChangeFont("Wide Latin");

				// �T�E���h�f�[�^�^�C�v
				SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);

				// Loading
				ClearDrawScreen();
				DrawString(700,600,"Loading...",RGB(255,255,255),TRUE);
				ScreenFlip();

				// �V���h�E�}�b�v�n���h���̍쐬
				ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

				// �`�悷�鉜�s�������͈̔͂�ݒ�
				SetCameraNearFar( 1.000f, 20000.000f );

				// ���C�g�̕�����ݒ�
				SetLightDirection( VGet( 0.6f, -0.5f, 0.5f ) );

				// �V���h�E�}�b�v���z�肷�郉�C�g�̕������Z�b�g
				SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.5f, -0.5f, 0.5f ) ) ;

				// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ�
				SetShadowMapDrawArea( ShadowMapHandle, VGet( -1000.0f, -1.0f, -1000.0f ), VGet( 1000.0f, 1000.0f, 1000.0f )) ;
				
				// �����Z�b�g
				InitSet();
				SelCharaInclude();
				gamemode = eSceneBlank2 ;
				break ;

			case eSceneBlank2:
				 WaitTimer( 2500 ) ;
				gamemode = eSceneTitleInit ;
				break;

			case eSceneTitleInit:				
			    PlaySoundMem( soundh[0] , DX_PLAYTYPE_LOOP ) ;
				gamemode = eSceneTitle;
				break;

			case eSceneTitle:
				//�^�C�g������
				if( CheckHitKeyAll() != 0 ){ 
					if(titleF != TRUE){
						PlaySoundMem( soundh[1] , DX_PLAYTYPE_BACK ) ;
						titlecnt = 0;
					}
					titleF = TRUE;
				}

				titlecnt++;
				ClearDrawScreen();
				if(	titleF != TRUE){
					DrawGraph(0,0,Graph[2],TRUE);
					if(titlecnt%30 == 0){
					}else{
						DrawGraph(0,0,Graph[3],TRUE);
					}
					if(titlecnt == 601){
						titlecnt = 0;
					}
				}else{
					DrawGraph(0,0,Graph[2],TRUE);	
					if(titlecnt%5 == 0){
					}else{
						DrawGraph(0,0,Graph[3],TRUE);
					}

					if(titlecnt == 50){
						titlecnt = 0;
						titleF = FALSE;
						ClearDrawScreen();
						DrawString(700,600,"Loading...",RGB(255,255,255),TRUE);
						gamemode = eSceneInit ;
					}
				}
				ScreenFlip();
				break;

			case eSceneInit:
				// ------------------------------------------------------------------------- // 
				//						�N�b�L�[�|�W�V�����Z�b�g		                     //
				// ------------------------------------------------------------------------- // 
				// �N�b�L�[�̃|�W�V����
				// ��
				cookieinfo[0].cookiepos  = VGet(100.0f, CookieY - 000.0f, 275.0f);		// ����
				cookieinfo[1].cookiepos  = VGet(450.0f, CookieY + 000.0f, 921.0f);		// ��
				cookieinfo[2].cookiepos  = VGet(800.0f, CookieY - 000.0f, 275.0f);		// �E��

				// ��
				cookieinfo[3].cookiepos  = VGet(450.0f, CookieY - 000.0f, 275.0f);		// �^��	
				cookieinfo[4].cookiepos  = VGet(650.0f, CookieY - 000.0f, 598.0f);		// ���E
				cookieinfo[5].cookiepos  = VGet(250.0f, CookieY - 000.0f, 598.0f);		// ����

				// �Q�[���̃^�C�}�[�ݒ�
				gamemaintimer = 93;
/**/
//gamemaintimer = 65;
//gamemaintimer = 1;
//gamemaintimer = 2;
/**/				gamesubtimer = 0;
				// �X�e�[�W�Ǘ�
				stageflg = 0;
				// �^�C�}�[
				maintimer = 90;
				//	�N�b�L�[���O�ꂽ�Ƃ��̂Ђ�����Ԃ��t���O
				offF[0] = FALSE; 				
				offF[1] = FALSE; 				
				offF[2] = FALSE; 				
				// �L����������΂��̃J�E���^�[
				upperNum = 0;						
				// �L�����I��ԍ�
				charasel[0] = 0;
				charasel[1] = 0;
				//  �N�b�L�[��]
				Trote = 0.12f;
				//  �N�b�L�[��]�t���O
				TroteC = 0;
				//  �N�b�L�[��]�t���O
				TroteF = FALSE;
				// �L�����I���ŘA�����͂����Ȃ��悤��
				first[0] = FALSE;
				first[1] = FALSE;
				// �t���X�N�Ǘ�
				fullscreen = 1;								
				//  �V�[���؂�ւ�����
				sceentime = 0;
				// �N�b�L�[�f���[�g�^�C��
				delettime = 0;										
				//  �p���P�[�L�A�j���[�V��������
				pancakeA = 0.0f;
				// �p���P�[�L�A�j���؂�ւ��t���O
				pancakeAF = FALSE;
				key = 0;
				key2 = 0;
				platepos = VGet(90.0f,-1000.0f,900.0f) ;
				// stage1cam�Z�b�g
				cpos3 = VGet(550.0f,-80.0f,-380.0f) ;
				ctgt3 = VGet(550.0f,-100.0f,50.0f) ;
				cpos2 = VGet(440.0f,100.0f,-320.0f) ;
				ctgt2 = VGet(440.0f,-150.0f,50.0f) ;
				cpos = VGet(440.0f,500.0f,-10020.0f) ;
				ctgt = VGet(440.0f,-150.0f,50.0f) ;
				// �^�C�}�[�̏����Z�b�g
				maintimer = 9999;
				getcookiecnt = 0;
				//	�N�b�L�[���O�ꂽ�Ƃ��̂Ђ�����Ԃ��t���O
				offF[0] = FALSE; 
				offF[1] = FALSE; 
				offF[2] = FALSE; 
				//�X�e�[�W�̃|�W�V����
				pancakepos  = VGet(440.0f,-555.0f,690.0f) ;
				pancake2pos = VGet(2500.0f,-675.0f,600.0f) ;
				platepos    = VGet(90.0f,-1000.0f,900.0f) ;
				tablepos    = VGet(600.0f,-10050.0f,5200.0f) ;
				eggpos	   = VGet(-800.0f,-805.0f,1800.0f) ;
				milkpos	   = VGet(-690.0f,-1205.0f,4400.0f) ;
				for(char i = 0; i < MAX_BOWL; i++){
					bowlpos[i] = VGet(1000.0f + (i * 100.0f),-315.0f,-10000.0f) ;
				}

				bowlpos[0] = VGet(1000.0f,-315.0f,1800.0f) ;
				bowlpos[1] = VGet(-690.0f,-315.0f,1000.0f) ;
				bowlpos[2] = VGet(-590.0f,-315.0f,3000.0f) ;
				upperNum = 0;
				charasel[0] = 0;
				charasel[1] = 0;
				delay = 0;
				delay2 = 20;
				cnt = 0 ;
				cnt2 = 0 ;
				for( char P = 0; P < MAX_PLAYER; P++){
					flipdraw[P] = FALSE;
						// �I���J�[�\���̈ړ�
					charactersetcheck[P] = FALSE;
						// �L�[���������܂őI���J�[�\�����łȂ�
					selectdrawflg[P] = FALSE;
						// �n�߂邩�̃`�F�b�N
					okflg[P] = FALSE;
					plyblin[P] = FALSE;
					seleweight[P] =FALSE;
				}
				waittimer = 0 ;
				cookiestaytime = 0 ;
				resultsetflg = FALSE;

				StopSoundMem(soundh[0]);
			    PlaySoundMem( soundh[2] , DX_PLAYTYPE_LOOP ) ;
				gamemode = eSceneCharasel ;
				break;

			/* ---------------------------------------------------------------------- //
			//	 	 	 	 	 	 	 	 �L�����I����� 	 	 	 	 	 	  //
			// ---------------------------------------------------------------------- */
			case eSceneCharasel:
				// �J�����ݒ�
				SetCameraPositionAndTargetAndUpVec(cpos3,ctgt3,VGet(0.0f,0.0f,1.0f)) ;
				while(1){		
					// �������[�v
					key = GetJoypadInputState(DX_INPUT_KEY_PAD1);				// 1P 
				//	key = GetJoypadInputState(DX_INPUT_PAD1) ;
					key2 = GetJoypadInputState(DX_INPUT_PAD2);					// 2P

					if((key & PAD_INPUT_LEFT || key & PAD_INPUT_RIGHT) && (first[0] == FALSE && first[1] == FALSE)){
						PlaySoundMem( soundh[14] , DX_PLAYTYPE_BACK ) ;
					}
					if((key2 & PAD_INPUT_LEFT || key2 & PAD_INPUT_RIGHT) && (first[0] == FALSE && first[1] == FALSE)){
						PlaySoundMem( soundh[14] , DX_PLAYTYPE_BACK ) ;
					}
					
					if(key & PAD_INPUT_LEFT && first[0] == FALSE && seleweight[0] != TRUE ){				// 1P�����͎�
						charasel[0]++;
 						if(charasel[0] == 3){
							charasel[0] = 0;
						}
						first[0] = TRUE;
					}else if(key & PAD_INPUT_LEFT && first[0] == FALSE && seleweight[0] != FALSE){			// �Q�[�����n�߂邩����
						if(selectdrawflg[0] != FALSE && okflg[0] != TRUE){
							charactersetcheck[0]++;
							if(charactersetcheck[0] == 2){
								charactersetcheck[0] = 0;
							}
							first[0] = TRUE;
						}
						selectdrawflg[0] = 1;
					}
					if(key & PAD_INPUT_RIGHT && first[0] == FALSE && seleweight[0] != TRUE){				// 1P�E���͎�
						charasel[0]--;
						if(charasel[0] == -1){
							charasel[0] = 2;
						}
						first[0] = TRUE;
					}else if(key & PAD_INPUT_RIGHT && first[0] == FALSE && seleweight[0] != FALSE){			// �Q�[�����n�߂邩����
						if(selectdrawflg[0] != FALSE && okflg[0] != TRUE){
							charactersetcheck[0]--;
							if(charactersetcheck[0] == -1){
								charactersetcheck[0] = 1;
							}
							first[0] = TRUE;
						}
						selectdrawflg[0] = 1;
					}
					if(key & PAD_INPUT_B && first[0] == FALSE){		//��
						if(	seleweight[1] == TRUE && charasel[1] == charasel[0] ){		// ����Ɠ����L������������I�ׂȂ�
							PlaySoundMem( soundh[20] , DX_PLAYTYPE_BACK ) ;					// cancel							
						}else{
							PlaySoundMem( soundh[13] , DX_PLAYTYPE_BACK ) ;
							seleweight[0] =	TRUE; 
							plyblin[0] = TRUE;
							if(selectdrawflg[0] != FALSE){
								okflg[0] = TRUE;
							}
						}
						first[0] = TRUE;
					}
					if(key & PAD_INPUT_C && first[0] == FALSE){		// X 1P
						if(seleweight[1] != TRUE && seleweight[0] == TRUE){
							seleweight[0] = FALSE ;
							plyblin[0] = FALSE;
						}
					}

					if(key2 & PAD_INPUT_LEFT && first[1] == FALSE && seleweight[1] != TRUE){				// 2P�����͎�
						charasel[1]++;
 						if(charasel[1] == 3){
							charasel[1] = 0;
						}
						first[1] = TRUE;
					}else if(key2 & PAD_INPUT_LEFT && first[1] == FALSE && seleweight[1] != FALSE){			// �Q�[�����n�߂邩����
						if(selectdrawflg[1] != FALSE && okflg[1] != TRUE){
							charactersetcheck[1]++;
							if(charactersetcheck[1] == 2){
								charactersetcheck[1] = 0;
							}
							first[1] = TRUE;
						}
						selectdrawflg[1] = 1;
					}

					if(key2 & PAD_INPUT_RIGHT && first[1] == FALSE && seleweight[1] != TRUE){			// 2P�E���͎�
						charasel[1]--;
						if(charasel[1] == -1){
							charasel[1] = 2;
						}
						first[1] = TRUE;
					}else if(key2 & PAD_INPUT_RIGHT && first[1] == FALSE && seleweight[1] != FALSE){	// �Q�[�����n�߂邩����
						if(selectdrawflg[1] != FALSE && okflg[1] != TRUE){
							charactersetcheck[1]--;
							if(charactersetcheck[1] == -1){
								charactersetcheck[1] = 1;
							}
							first[1] = TRUE;
						}
						selectdrawflg[1] = 1;
					}
					if(key2 & PAD_INPUT_B && first[1] == FALSE){		//��
						if(	seleweight[0] == TRUE && charasel[0] == charasel[1] ){		// ����Ɠ����L������������I�ׂȂ�
							PlaySoundMem( soundh[20] , DX_PLAYTYPE_BACK ) ;					// cancel							
						}else{
							PlaySoundMem( soundh[13] , DX_PLAYTYPE_BACK ) ;
							seleweight[1] =	TRUE; 
							plyblin[1] = TRUE;
							if(selectdrawflg[1] != FALSE){
								okflg[1] = TRUE;
							}
						}
						first[1] = TRUE;
					}
					if(key2 & PAD_INPUT_C && first[1] == FALSE){		// X 2P
						if(seleweight[0] != TRUE && seleweight[1] == TRUE){
							seleweight[1] = FALSE ;
							plyblin[1] = FALSE;
						}
					}

					if(first[0] == TRUE && key == 0x0000){
						first[0] = FALSE;
					}
					if(first[1] == TRUE && key2 == 0x0000){					
						first[1] = FALSE;
					}


					charainfo[0].chara = charasel[0];									// 1P����L�������
					charainfo[1].chara = charasel[1];									// 2P����L�������

					// �Q�[����ʂɈڍs
						// Coment
					if((okflg[0] == TRUE && okflg[1] == TRUE) && (charactersetcheck[0] == FALSE && charactersetcheck[1] == FALSE)){
//					if((okflg[0] == TRUE) && (charactersetcheck[0] == FALSE)){
						StopSoundMem(soundh[2]);
						PlaySoundMem( soundh[13] , DX_PLAYTYPE_BACK ) ;
						ClearDrawScreen();
						DrawString(700,600,"Loading...",RGB(255,255,255),TRUE);
						ScreenFlip();
						Mixer();
						if(charainit() == -1) return -1;
						gamemode = eScenePlay ;
						break;
					}else if((okflg[0] == TRUE && okflg[1] == TRUE) &&
						(charactersetcheck[0] == TRUE || charactersetcheck[1] == TRUE)){		// ���Z�b�g
						for(int i = 0; i < 2 ; i++){
								charasel[i] = 0;
								fl[i] = 0;
							// charasel���̃��[�e�[�V����
							chararote[i] = 0;
							// charasel���̃��[�e�[�V����
							chararote1[i] = 0;
							// charasel���̃��[�e�[�V����
							chararote2[i] = 0;
							// �L�����N�^�[�I��flag
							seleweight[i] = FALSE;
							// 1P�@2P�̓_��flag
							plyblin[i] = FALSE;
							// �_�Œx�点
							flipdraw[i] = FALSE;
							charactersetcheck[i] = FALSE;
							selectdrawflg[i]= FALSE;
							okflg[i] = FALSE;
						}
						delay = 0;
						delay2 = 20;
						cnt = 0 ;
						cnt2 = 0 ;
					}

					for(int i = MAX_PLAYER; i < MAX_PLAYER + 3; i++ ){
						// �X�P�[���ݒ�
						switch(i){
							case MAX_PLAYER:
									MV1SetScale(charainfo[2].model1,VGet(1.4f, 1.4f, 1.4f));			// chara1
								break;
						   case MAX_PLAYER + 1:
									MV1SetScale(charainfo[3].model1,VGet(1.4f, 1.5f, 1.4f));			// chara2
								break;
						   case MAX_PLAYER + 2:
									MV1SetScale(charainfo[4].model1,VGet(1.4f,1.4f,1.4f));				// chara3
								break;
						}
						if(stageflg == 0){
							MV1SetScale(Sfloor[0],VGet(23.0f,12.0f,20.0f));								//	��
						}else{
							MV1SetScale(Sfloor[0],VGet(23.0f,13.0f,20.0f));								//	��
						}
						MV1SetScale(cookie[1],VGet(1.0f,1.8f,1.0f));									//	1P�N�b�L�[
						MV1SetScale(cookie[2],VGet(1.0f,1.8f,1.0f));									//	2P�N�b�L�[

						//  �A�j���[�V�����̒l�����Z
						for(char P = 0; P < MAX_PLAYER; P++){
							if(charainfo[charasel[P] + 2].playtime <= charainfo[charasel[P] + 2].anim_totaltime){
								charainfo[charasel[P] + 2].playtime += 0.8f;
							}else{
								charainfo[charasel[P] + 2].playtime = 0.0f;
							}
						}
						// �A�j���[�V�����̃A�^�b�`
						MV1SetAttachAnimTime(charainfo[charasel[0] + 2].model1, charainfo[charasel[0] + 2].attachidx, charainfo[charasel[0] + 2].playtime) ;
						MV1SetAttachAnimTime(charainfo[charasel[1] + 2].model1, charainfo[charasel[1] + 2].attachidx, charainfo[charasel[1] + 2].playtime) ;

						// �L�����N�^�[�̑I�𒆃��[�e�[�V����
						for(char P = MAX_PLAYER; P < MAX_PLAYER + 3; P++){							
							if(charasel[0] + 2 == P){
								switch(P) {
									case 2:
										MV1SetPosition(cookie[1],Selectpos_1);
										chararote1[0] = 0.0f;
										chararote2[0] = 0.0f;
										chararote[0] += 0.01f;
										MV1SetRotationXYZ(charainfo[2].model1,VGet(0.0f,1.5f + chararote[0],0.0f)) ;			//	���񂭂��L�����N�^�[�̈ړ���] & �N�b�L�[�̈ړ�
										break;
									case 3:
										MV1SetPosition(cookie[1],Selectpos1_1);
										chararote[0] = 0.0f;
										chararote2[0] = 0.0f;
										chararote1[0] += 0.01f;
										MV1SetRotationXYZ(charainfo[3].model1,VGet(0.0f,1.2f + chararote1[0],0.0f)) ;			//	�C�`�S�L�����N�^�[�̈ړ���] & �N�b�L�[�̈ړ�
										break;
									case 4:
										MV1SetPosition(cookie[1],Selectpos2_1);
										chararote[0] = 0.0f;
										chararote1[0] = 0.0f;
										chararote2[0] += 0.01f;
										MV1SetRotationXYZ(charainfo[4].model1,VGet(0.0f,1.9f + chararote2[0],0.0f)) ;			//	�R�b�N�L�����N�^�[�̈ړ���] & �N�b�L�[�̈ړ�
										break;
								}
							}else{
								switch(P) {
									case 2:
										MV1SetPosition(charainfo[2].model1, VGet(76.935f* 7,90.111f,80.785f ) );
										break;
									case 3:
										MV1SetPosition(charainfo[3].model1,	VGet(40.935f* 7,-190.1111f,80.785f ) );
										break;
									case 4:
										MV1SetPosition(charainfo[4].model1,VGet(116.935f* 7,-210.1111f,80.785f ));
										break;
								}
							}

							if(charasel[1] + 2 == P){
								switch(P) {
									case 2:
										MV1SetPosition(cookie[2],Selectpos_2);
										chararote1[1] = 0.0f;
										chararote2[1] = 0.0f;
										chararote[1] += 0.01f;
										MV1SetRotationXYZ(charainfo[2].model1,VGet(0.0f,1.5f + chararote[1],0.0f)) ;			//	�L�����N�^�[�̈ړ���]
										break;
									case 3:
										MV1SetPosition(cookie[2],Selectpos1_2);
										chararote[1] = 0.0f;
										chararote1[1] += 0.01f;
										chararote2[1] = 0.0f;
										MV1SetRotationXYZ(charainfo[3].model1,VGet(0.0f,1.2f + chararote1[1],0.0f)) ;			//	�L�����N�^�[�̈ړ���]
										break;
									case 4:
										MV1SetPosition(cookie[2],Selectpos2_2);
										chararote[1] = 0.0f;
										chararote1[1] = 0.0f;
										chararote2[1] += 0.01f;
										MV1SetRotationXYZ(charainfo[4].model1,VGet(0.0f,1.9f + chararote2[1],0.0f)) ;			//	�L�����N�^�[�̈ړ���]
										break;
								}
							}else{
								switch(P) {
									case 2:
										MV1SetPosition(charainfo[2].model1, VGet(76.935f* 7,90.111f,80.785f ) );
										break;
									case 3:
										MV1SetPosition(charainfo[3].model1,	VGet(40.935f* 7,-190.1111f,80.785f ) );
										break;
									case 4:
										MV1SetPosition(charainfo[4].model1,VGet(116.935f* 7,-210.1111f,80.785f ));
										break;
								}
							}

							if(charasel[0] + 2 != P && charasel[1] + 2 != P){
								switch(P) {
									case 2:
										chararote[0] = 0.0f;
										chararote[1] = 0.0f;
										MV1SetRotationXYZ(charainfo[2].model1,VGet(0.0f,1.5f + chararote[0],0.0f)) ;			//	�L�����N�^�[�̈ړ���]
										break;
									case 3:
										chararote1[0] = 0.0f;
										chararote1[1] = 0.0f;
										MV1SetRotationXYZ(charainfo[3].model1,VGet(0.0f,1.2f + chararote1[0],0.0f)) ;			//	�L�����N�^�[�̈ړ���]
										break;
									case 4:
										chararote2[0] = 0.0f;
										chararote2[1] = 0.0f;
										MV1SetRotationXYZ(charainfo[4].model1,VGet(0.0f,1.9f + chararote2[0],0.0f)) ;			//	�L�����N�^�[�̈ړ���]
										break;
								}
							}
						}

						MV1SetRotationXYZ(cookie[1],VGet(0.4f,0.0f,0.0f)) ;			//	�L�����N�^�[�̈ړ���]
						MV1SetRotationXYZ(cookie[2],VGet(0.4f,0.0f,0.0f)) ;			//	�L�����N�^�[�̈ړ���]
						for(int i = 0;i < MAX_WALL; i++){
							MV1SetRotationXYZ(Sfloor[i],VGet(0.0f,1.57f*2,0.0f)) ;											//	�ǂ̉�]
						}
						MV1SetPosition(charainfo[2].model1, VGet(76.935f* 7,90.111f,80.785f ) );
						MV1SetPosition(charainfo[3].model1,	VGet(37.935f* 7,-190.1111f,80.785f ) );
						MV1SetPosition(charainfo[4].model1, VGet(119.935f* 7,-210.1111f,80.785f ));
						MV1SetPosition(Sfloor[0],VGet(119.935f* 7,2210.1111f,5000.785f ));

						ClearDrawScreen() ;
						for(char i = 0; i < 1;i++){
							MV1DrawModel(Sfloor[i]) ;
						}
						MV1DrawModel(charainfo[2].model1) ;				// ���񂭂����ǂ�
						MV1DrawModel(charainfo[3].model1) ;				// �C�`�S
						MV1DrawModel(charainfo[4].model1) ;				// �R�b�N

						if(cnt == 599){
							cnt = 0;
						}else{
							cnt++ ;
						}
						// 1P 2P�̑I�𒆓_��
						if(cnt%15 == 0){
							for(char i = 0; i  < MAX_PLAYER; i++){
								if( flipdraw[i] == TRUE){
									flipdraw[i] = FALSE;
								}else{
									flipdraw[i] = TRUE;
								}
							}
						}									

						// �����L������I�����Ă����ꍇ�̏���
						switch(charasel[0]){							// select����
							case 0:										// ���񂭂���\��
								if(charasel[0] == 0 && charasel[1] == 0)
								{
									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(470,20,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(470,20,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(620,20,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(620,20,"P2",GetColor(255,60,0));
									}

								}else{
									if(plyblin[0] != TRUE){				// 1P�P��
										if(flipdraw[0] == FALSE){
											DrawString(540,20,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(540,20,"P1",GetColor(0,20,255));		
									}
								}
								break;
							case 1:										// �C�`�S��\��
								if(charasel[0] == 1 && charasel[1] == 1)
								{

									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(100,200,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(100,200,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(250,200,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(250,200,"P2",GetColor(255,60,0));
									}

								}else{
									if(plyblin[0] != TRUE){
										if(flipdraw[0] == FALSE){
											DrawString(180,200,"P1",GetColor(0,20,255));
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(180,200,"P1",GetColor(0,20,255));
									}
								}
								break;
							case 2:										// �R�b�N��\��
								if(charasel[0] == 2 && charasel[1] == 2)
								{
									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(890,200,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(890,200,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(1040,200,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(1040,200,"P2",GetColor(255,60,0));
									}

								}else{
								if(plyblin[0] != TRUE){
										if(flipdraw[0] == FALSE){
											DrawString(965,200,"P1",GetColor(0,20,255));
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(965,200,"P1",GetColor(0,20,255));
									}
								}
								break;
						}
						switch(charasel[1]){							// 2P
							case 0:										// ���񂭂���\��
								if(charasel[0] == 0 && charasel[1] == 0)
								{
									if(plyblin[0] != TRUE){
										if(flipdraw[0] == FALSE){
											DrawString(470,20,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(470,20,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){
										if(flipdraw[1] == FALSE){
											DrawString(620,20,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(620,20,"P2",GetColor(255,60,0));
									}
								}else{
									if(plyblin[1] != TRUE){
										if(flipdraw[1] == FALSE){
											DrawString(540,20,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(540,20,"P2",GetColor(255,60,0));
									}
								}
								break;
							case 1:										// �C�`�S��\��
								if(charasel[0] == 1 && charasel[1] == 1)
								{
									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(100,200,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(100,200,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(250,200,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(250,200,"P2",GetColor(255,60,0));
									}

									if(plyblin[1] != TRUE){
										if(flipdraw[1] == FALSE){
											DrawString(250,200,"P2",GetColor(255,60,0));		
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(250,200,"P2",GetColor(255,60,0));		
									}

								}else{
									if(plyblin[1] != TRUE){
										if(flipdraw[1] == FALSE){
											DrawString(180,200,"P2",GetColor(255,60,0));		
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(180,200,"P2",GetColor(255,60,0));		
									}
								}
								break;
							case 2:										// �R�b�N��\��
								if(charasel[0] == 2 && charasel[1] == 2)
								{
									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(890,200,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//�@����{�^��������
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(890,200,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(1040,200,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(1040,200,"P2",GetColor(255,60,0));
									}
								}else{
									if(plyblin[1] != TRUE){
										if(flipdraw[1] == FALSE){
											DrawString(965,200,"P2",GetColor(255,60,0));		
										}
										if(seleweight[1] != FALSE){						//�@����{�^��������
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(965,200,"P2",GetColor(255,60,0));		
									}
								}
								break;
						}

						// Coment
						if(seleweight[0] == TRUE && seleweight[1] == TRUE ){						// �Q�[���O�̍ŏI�`�F�b�N
//						if(seleweight[0] == TRUE){						// �Q�[���O�̍ŏI�`�F�b�N
							DrawGraph(0,0,characterselect[0],TRUE);

							if(selectdrawflg[0] != FALSE){
								switch(charactersetcheck[0]){
									case 0:
										DrawGraph(0,0,characterselect[1],TRUE);	
										break;
									case 1:
										DrawGraph(0,0,characterselect[3],TRUE);	
										break;
								}
							}
							if(selectdrawflg[1] != FALSE){
								switch(charactersetcheck[1]){
									case 0:
										DrawGraph(0,0,characterselect[2],TRUE);	
										break;
									case 1:
										DrawGraph(0,0,characterselect[4],TRUE);	
										break;
								}
							}
							DrawGraph(0,0,characterselect[5],TRUE);	
						}

						MV1SetEmiColorScale( cookie[1], P1COLOR) ;
						MV1DrawModel(cookie[1]);
						MV1SetEmiColorScale( cookie[2], P2COLOR) ;
						MV1DrawModel(cookie[2]);
						ScreenFlip();
					}
				}
				break;

			case eScenePlayInit:
				gamemode = eScenePlay;
				break;

			/*
				���C������
			*/
			case eScenePlay :
				if(charainfo[0].getcookie < 0){
					charainfo[0].getcookie = 0;
				}
				if(charainfo[1].getcookie < 0){
					charainfo[1].getcookie = 0;
				}

				SetDrawScreen(DX_SCREEN_BACK) ;
				ClearDrawScreen() ;

				if( CheckSoundMem(soundh[3]) == 0 ){
					PlaySoundMem( soundh[3] , DX_PLAYTYPE_LOOP);
				}


				// �J�����ړ�
				if(stageflg == 1){	// �ʂ�ʂ�J�����̂ق�	
					if(cpos.z < cpos2.z){
						cpos.z += 35.0f;
					}
					if(cpos.y > cpos2.y){
						cpos.y -= 2.5f;
					}
					if(cpos.y <= cpos2.y && cpos.z >= cpos2.z){
						cpos = cpos2;
					}
				}else{
					if(cpos.z < cpos2.z){
						cpos.z += 33.0f;
					}else if(cpos.y > cpos2.y){
						cpos.y -= 14.0f;
					}else{
						cpos = cpos2;
					}
				}
			
				// �ړ��l�̏�����
				charainfo[0].move.x = 0.0f;
				charainfo[0].move.y = 0.0f;
				charainfo[0].move.z = 0.0f;
				charainfo[1].move.x = 0.0f;
				charainfo[1].move.y = 0.0f;
				charainfo[1].move.z = 0.0f;

/*
				// �ꖇ�ł��\�ł���ΐi��ł���Ƃ����t���O
				for(char i = 0; i < MAX_PLAYER; i++){
					if(resetF != TRUE){
						if(cookieinfo[i].Flipflag == TRUE){
							resetF = TRUE;
						}
					}
				}
*/
				if(getcookiecnt >= 1 && resetcnt < RESETTIME){
					resetcnt++;
//	    			DrawFormatString(0,0,RGB(255,255,255),"Reset..%03d",120 - resetcnt);
				}

				// ���Z�b�gReset
				if(resetcnt >= RESETTIME){
					if(resetcnt != RESETTIME+MAX_COOKIE){
						for(char i = 0; i < MAX_COOKIE; i++){
							if(cookieinfo[i].stay == FALSE &&
								offF[0] != TRUE && offF[1] != TRUE){
									resetcnt++;
							}else{
									resetcnt = RESETTIME;
							}
						}
					}
					if(resetcnt == RESETTIME+MAX_COOKIE){
						if( 1 ==FlipCnt()){
							resetcnt = 0;
						}
					}
				}else if(resetcnt > RESETTIME-30){
					for(char P = 0; P < MAX_PLAYER; P++){
					if(P == 0){
						charainfo[0].pos = VGet(P1POSX, -120.0f, P1POSZ) ;
					}
					else{
						charainfo[1].pos = VGet(P2POSX,-120.0f,P2POSZ) ;			//chara3	-70
					}
						if(charainfo[P].chara == 1){
							charainfo[P].pos.y -= 110.0f;
						}else if(charainfo[P].chara == 2){
							charainfo[P].pos.y -= 130.0f;
						}
					}
					charainfo[0].direction = RIGHT;
					charainfo[1].direction = LEFT;
				}else{
					 if(charainfo[0].upper.z == 0.0f){
						if(maintimer <= 90 && maintimer != SCEENWAIT && maintimer != -1){
							if(charainfo[0].upper.x == 0.0f || charainfo[0].upper.z == 0.0f){
								if(charactorMove() == -1){								// ���Z�b�g����
//									gamemode = eSceneTitleInit;
								}
							}
							if(charainfo[1].upper.x == 0.0f || charainfo[1].upper.z == 0.0f){
								if(charactorMove2() == -1){								// ���Z�b�g����
//									gamemode = eSceneTitleInit;
								}
							}
						}
					}
					cookieflip();													// �N�b�L�[�̃t���b�v����
				}
				switch(cookiechecker()){														//  �N�b�L�[�̐��딻��
					case -1:
						MV1SetEmiColorScale( cookie[charainfo[0].Selcookie[0]], NORMALCOLOR) ;
						MV1SetEmiColorScale( cookie[charainfo[0].Selcookie[1]], NORMALCOLOR) ;
						offF[0] = TRUE;
						break;
					case -2:
						MV1SetEmiColorScale( cookie[charainfo[1].Selcookie[0]], NORMALCOLOR) ;
						MV1SetEmiColorScale( cookie[charainfo[1].Selcookie[1]], NORMALCOLOR) ;
						offF[1] = TRUE;
						break;
				}

				// �L�[����				
				if(charainfo[0].mode == STAND || charainfo[0].mode == RUN){
					Animset();														// �A�j���[�V��������
					// Player1s
					if(offF[0] == TRUE){
						if(cookieinfo[charainfo[0].Selcookie[1]].stay == 0 && cookieinfo[charainfo[0].Selcookie[1]].playtime >= cookieinfo[charainfo[0].Selcookie[1]].anim_totaltime){ // �Ђ�����Ԃ��I�������
							PlaySoundMem( soundh[9] , DX_PLAYTYPE_BACK ) ;
							cookieinfo[charainfo[0].Selcookie[1]].stay = 1;
							cookieinfo[charainfo[0].Selcookie[0]].Flipflag = 0;
							cookieinfo[charainfo[0].Selcookie[1]].Flipflag = 0;
							charainfo[0].stay = TRUE;
						}
						if(cookieinfo[charainfo[0].Selcookie[1]].stay == 1){
							if(cookieinfo[charainfo[0].Selcookie[1]].staytime <= 0){
								// �N�b�L�[�������ɖ߂�
								if(cookieinfo[charainfo[0].Selcookie[1]].playtime >= 0.0f){
									cookieinfo[charainfo[0].Selcookie[0]].playtime -= 2.5f ;
									cookieinfo[charainfo[0].Selcookie[1]].playtime -= 2.5f ;
								}
								else if(cookieinfo[charainfo[0].Selcookie[0]].playtime <= 0.0f && cookieinfo[charainfo[0].Selcookie[1]].playtime <= 0.0f){							// �v���C�^�C����0.0f
									cookieinfo[charainfo[0].Selcookie[1]].stay = 0;
									for(int i= 0; i < 2; i++){
										cookieinfo[charainfo[0].Selcookie[i]].playtime = 0.0f;
										cookieinfo[charainfo[0].Selcookie[i]].staytime = STAYTIME;
										charainfo[0].Selcookie[i] = 99;
									}
									charainfo[0].stay = FALSE;
									offF[0] = FALSE;
								}
							}
							else{
								cookieinfo[charainfo[0].Selcookie[1]].staytime-- ;													// �҂����Ԃ̃J�E���g�_�E��
							}																				// �҂����Ԃ��I�����瓮����߂�
						}
					}

					 // Player2
					if(offF[1] == TRUE){
						if(cookieinfo[charainfo[1].Selcookie[1]].stay == 0 && cookieinfo[charainfo[1].Selcookie[1]].playtime >= cookieinfo[charainfo[1].Selcookie[1]].anim_totaltime){ // �Ђ�����Ԃ��I�������
							PlaySoundMem( soundh[9] , DX_PLAYTYPE_BACK ) ;
							cookieinfo[charainfo[1].Selcookie[1]].stay = 1;
							cookieinfo[charainfo[1].Selcookie[0]].Flipflag = 0;
							cookieinfo[charainfo[1].Selcookie[1]].Flipflag = 0;
							charainfo[1].stay = TRUE;
						}
						if(cookieinfo[charainfo[1].Selcookie[1]].stay == 1){
							if(cookieinfo[charainfo[1].Selcookie[1]].staytime <= 0){
								// �N�b�L�[�������ɖ߂�
								if(cookieinfo[charainfo[1].Selcookie[1]].playtime >= 0.0f){
									cookieinfo[charainfo[1].Selcookie[0]].playtime -= 2.5f ;
									cookieinfo[charainfo[1].Selcookie[1]].playtime -= 2.5f ;
								}
								else if(cookieinfo[charainfo[1].Selcookie[0]].playtime < 0.0f && cookieinfo[charainfo[1].Selcookie[1]].playtime < 0.0f){							// �v���C�^�C����0.0f
									cookieinfo[charainfo[1].Selcookie[1]].stay = 0;
									for(int i= 0; i < 2; i++){
										cookieinfo[charainfo[1].Selcookie[i]].playtime = 0.0f;
										cookieinfo[charainfo[1].Selcookie[i]].staytime = STAYTIME;
										charainfo[1].Selcookie[i] = 99;
									}
									charainfo[1].stay = FALSE;
									offF[1] = FALSE;
								}
							}
							else{
								cookieinfo[charainfo[1].Selcookie[1]].staytime-- ;							// �҂����Ԃ̃J�E���g�_�E��
							}																				// �҂����Ԃ��I�����瓮����߂�
						}
					}

					PlayerFly();		//�@�v���C���[�̕��V�A�j���[�V����
				}

				playerhitcheck();		// Hitcheck


				for(int P = 0; P < MAX_PLAYER; P++){
					if(charainfo[P].upper.x != 0.0f){
						if(charainfo[P].upper.x > 0.0f){
							charainfo[P].upper.x -= upperspeed;
						}else{					
							charainfo[P].upper.x += upperspeed;
						}
						charainfo[P].move.x = charainfo[P].upper.x;
					}
					if(charainfo[P].upper.z != 0.0f){
						if(charainfo[P].upper.z > 0.0f){
							charainfo[P].upper.z -= upperspeed;
						}else{					
							charainfo[P].upper.z += upperspeed;
						}
						charainfo[P].move.z = charainfo[P].upper.z;
					}
				}

				// �J�����ݒ�
				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,0.0f,1.0f)) ;

				// �V���h�E�}�b�v�ւ̕`��̏���
				ShadowMap_DrawSetup( ShadowMapHandle ) ;

				// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
				MV1DrawModel( charainfo[0].model1 ) ;

				// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
				MV1DrawModel( charainfo[1].model1 ) ;
				MV1DrawModel( egg ) ;

				// �V���h�E�}�b�v�ւ̕`����I��
				ShadowMap_DrawEnd() ;

				// �`��Ɏg�p����V���h�E�}�b�v��ݒ�
				SetUseShadowMap( 0, ShadowMapHandle ) ;

				// �X�P�[���ݒ�//
				// �v���C���[1
				switch(charainfo[0].chara){
					case 0:
						MV1SetScale(charainfo[0].model1,VGet(1.0f, 1.0f, 1.0f));			// chara1
						break;
					case 1:
						MV1SetScale(charainfo[0].model1,VGet(1.0f, 1.0f, 1.0f));			// chara1
						break;
					case 2:
						MV1SetScale(charainfo[0].model1,VGet(0.9f,0.9f,0.9f));		// chara3
						break;
				}

				// �v���C���[2
				switch(charainfo[1].chara){
					case 0:
						MV1SetScale(charainfo[1].model1,VGet(1.0f, 1.0f, 1.0f));			// chara1
						break;
					case 1:
						MV1SetScale(charainfo[1].model1,VGet(1.0f, 1.0f, 1.0f));			// chara1
						break;
					case 2:
						MV1SetScale(charainfo[1].model1,VGet(0.9f,0.9f,0.9f));			// chara3
						break;
				}

				for( int i = 0 ; i < MAX_COOKIE ; i++ ){
					if(MAX_COOKIE/2 > i){									
						MV1SetScale(cookie[i],VGet(1.6f,3.4f,1.6f));			// cookie circle
					}
					else{
						MV1SetScale(cookie[i],VGet(1.02f,1.5f,1.02f));			// cookie squear
					}

					if(i == MAX_COOKIE - 1 || i == MAX_COOKIE - 2){
						MV1SetScale(cookie_pic[i],VGet(0.42f,0.49f,0.42f));				// �N�b�L�[�̔w�ʃ��f�� kaminari
					}else{
						MV1SetScale(cookie_pic[i],VGet(0.29f,0.39f,0.29f));				// �N�b�L�[�̔w�ʃ��f��     normal
					}
				}

				MV1SetScale(crosshair[0],VGet(0.2f,1.0f,0.2f));					// �M
				MV1SetScale(crosshair[1],VGet(0.2f,1.0f,0.2f));					// �M
				MV1SetScale(plate,VGet(3.5f,2.5f,3.5f));						// �M
				MV1SetScale(table,VGet(1.0f,1.2f,1.6f));						// �e�[�u��
//				MV1SetScale(pancake,VGet(0.64f,0.58f,0.50f));					// �p���P�[�L
				if(pancakeA <= 0.006f && pancakeAF == FALSE){
					pancakeA += 0.00001f;
				}else{
					pancakeAF = TRUE;
				}
				if(pancakeA >= 0.0f && pancakeAF == TRUE){
					pancakeA -= 0.00002f;
				}else{
					pancakeAF = FALSE;
				}

				// �X�P�[��
				MV1SetScale(pancake,VGet(0.64f + pancakeA,0.58f,0.50f + pancakeA));					// �p���P�[�L
//				MV1SetScale(pancake2,VGet(0.55f,0.55f,0.55f));										// �p���P�[�L
				MV1SetScale(egg,VGet(0.58f,0.58f,0.58f));											//��
				MV1SetScale(milk,VGet(1.9f,1.7f,1.9f));												//bowlanim
				for(char i = 0; i < MAX_BOWL; i++){
					MV1SetScale(bowl[i],VGet(1.6f,1.6f,1.6f));												//bowlanim
				}
				if(stageflg == 0){
					MV1SetScale(Sfloor[0],VGet(23.0f,10.0f,20.0f));								//	��
				}else{
					MV1SetScale(Sfloor[0],VGet(23.0f,13.0f,20.0f));								//	��
					MV1SetScale(reizo,VGet(23.0f,13.0f,20.0f));									//	�①��
				}


				// XYZRotation
				if(charainfo[0].bdownF == FALSE){
					MV1SetRotationXYZ(charainfo[0].model1,VGet(0.0f,0.785f * charainfo[0].direction,0.0f)) ;			//	�L�����N�^�[�̈ړ���]
				}
				if(charainfo[1].bdownF == FALSE){
					MV1SetRotationXYZ(charainfo[1].model1,VGet(0.0f,0.785f * charainfo[1].direction,0.0f)) ;			//	�L�����N�^�[�̈ړ���]
				}
				MV1SetRotationXYZ(crosshair[0],VGet(1.57f * 4,0.0f,0.0f)) ;												//	�p���P�[�L���f���̉�]
				MV1SetRotationXYZ(crosshair[1],VGet(1.57f * 4,0.0f,0.0f)) ;												//	�p���P�[�L���f���̉�]
				MV1SetRotationXYZ(egg,VGet(0.0f,1.57f * 1.1f,0.0f)) ;												//	�p���P�[�L���f���̉�]
				MV1SetRotationXYZ(pancake,VGet(3.0f,0.0f,0.0f)) ;													//	�p���P�[�L���f���̉�]
				MV1SetRotationXYZ(pancake2,VGet(0.0f,0.0f,0.0f)) ;													//	�p���P�[�L���f���̉�]
				MV1SetRotationXYZ(milk,VGet(0.0f,2.45f,0.0f)) ;												//	�����p�b�N���f���̉�]
				for(int i = 0;i < MAX_WALL; i++){
					MV1SetRotationXYZ(Sfloor[i],VGet(0.0f,1.57f*2,0.0f)) ;											//	�p���P�[�L���f���̉�]
				}

				//Position
				// ���f���̈ړ�(�z�u)
				MV1SetPosition(charainfo[0].model1,charainfo[0].pos);
				MV1SetPosition(charainfo[1].model1,charainfo[1].pos);

				// �n��(�z�u)���`��
				MV1SetPosition(crosshair[0],VGet(charainfo[0].pos.x,-320.0f,charainfo[0].pos.z));
				MV1SetPosition(crosshair[1],VGet(charainfo[1].pos.x,-320.0f,charainfo[1].pos.z));
				MV1SetPosition(plate,platepos);
				MV1SetPosition(table,tablepos);
				MV1SetPosition(pancake,pancakepos);
				MV1SetPosition(egg,eggpos);
				MV1SetPosition(milk,milkpos);

//				MV1SetRotationXYZ(efstar[1],VGet(1.0f,1.4f,4.11f));

				for(char i = 0; i < MAX_BOWL; i++){
					MV1SetPosition(bowl[i],bowlpos[i]);
				}
				MV1SetPosition(Sfloor[0],Sfloorpos[0]);
				MV1SetPosition(reizo,VGet(Sfloorpos[0].x,Sfloorpos[0].y + 250.0f,Sfloorpos[0].z -50.0f));

				if(stageflg != 1){							// 1��
					for( int i = 0 ; i < MAX_COOKIE ; i++ ){
						MV1SetPosition(cookie[i],cookieinfo[i].cookiepos);
						MV1SetPosition(cookie_pic[cookieinfo[i].cookienum],VGet(cookieinfo[i].cookiepos.x, cookieinfo[i].cookiepos.y + 40.0f, cookieinfo[i].cookiepos.z - 15.0f));
						MV1SetRotationXYZ(cookie[i],VGet(0.0f,0.0f,0.0f));
					}
				}
				else{										// 2��
					for( int i = 0 ; i < MAX_COOKIE ; i++ ){
						MV1SetPosition(cookie[i],VGet(Stg2cookie[i].x,cookieinfo[i].cookiepos.y,Stg2cookie[i].z));
						MV1SetPosition(cookie_pic[cookieinfo[i].cookienum],VGet(Stg2cookie[i].x, cookieinfo[i].cookiepos.y + 40.0f, Stg2cookie[i].z - 15.0f));
						MV1SetRotationXYZ(cookie[i],VGet(0.0f,0.0f,0.0f));
					}
				}

				// Draw
				MV1DrawModel(charainfo[0].model1) ;
				MV1DrawModel(charainfo[1].model1) ;

				if (stageflg != 1)
				{
					// ���f���̕`��
					MV1DrawModel(plate) ;
					MV1DrawModel(table) ;
//					MV1DrawModel(milk);
					for(char i = 0; i < MAX_BOWL; i++){
						MV1DrawModel(bowl[i]);
					}
					MV1DrawModel(pancake) ;
					MV1DrawModel(egg) ;
					for(char i = 0; i < 1;i++){
						MV1DrawModel(Sfloor[i]) ;
					}

				}else// 2��
				{
					if(objectinfo[0].playtime <= objectinfo[0].anim_totaltime){
						objectinfo[0].playtime += 0.25f;
					}
//					SetGlobalAmbientLight(METALCOLOR);
//					for(char i = 0; i < MAX_COOKIE; i++){
//						MV1SetEmiColorScale( cookie[i], METALCOLOR) ;
//					}	
					platepos    = VGet(90.0f,-740.0f,900.0f) ;
					MV1SetAttachAnimTime(range, objectinfo[0].attachidx, objectinfo[0].playtime) ;	
					MV1SetScale( range ,VGet(1.0f,1.0f,1.0f));				// �d�q�����W
					MV1SetRotationXYZ(range,VGet(0.0f,1.6f,0.0f)) ;				// �����W�̉�]
					MV1SetRotationXYZ(lack,VGet(0.0f,1.6f,0.0f)) ;				// �����W�̉�]
					MV1SetPosition(plate,platepos);
					MV1SetPosition(range,rangepos);
					MV1SetPosition(lack,rangepos);


					// �N�b�L�[���ӂ�ӂ퓮���A�j���[�V����
					for(int i = 0; i < MAX_COOKIE; i++){
						if(TroteF == TRUE){
							cookieinfo[i].cookiepos.y -= Trote;
						}else{
							cookieinfo[i].cookiepos.y += Trote;
						}
						Stg2cookie[i].x = (cos( (circleAngle)/2 * 3.141f / 180 ) * 25.7f) + cookieinfo[i].cookiepos.x ;
						Stg2cookie[i].z = (sin( (circleAngle)/2 * 3.141f / 180 ) * 25.7f) + cookieinfo[i].cookiepos.z ;		//	2.0����ɂ���Ƒȉ~�@	
					}
					circleAngle += 10;
					if(circleAngle > 720){
						circleAngle = 0;
					}
					TroteC++;
					if(TroteC == 60){											// ���[�v���J�E���g
						if(TroteF == TRUE){
							TroteF = FALSE;
						}
						else if(TroteF == FALSE){
							TroteF = TRUE;
						}
						TroteC = 0;
					}

					// ���f���̕`��
					MV1DrawModel(plate) ;
					MV1DrawModel(range) ;
					MV1DrawModel(lack);
					MV1DrawModel(Sfloor[0]) ;
					MV1DrawModel(reizo) ;
				}

				// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
				SetUseShadowMap( 0, -1 ) ;

				/*  ------------------------------------------------ //
				//                      �����̏���                   //
				// ------------------------------------------------- */
				for(int P = 0; P < MAX_PLAYER; P++ ){
					if( charainfo[P].sunder == TRUE ){
						if(objectinfo[THUNDER].playtime < objectinfo[THUNDER].anim_totaltime){
							objectinfo[THUNDER].playtime += 0.17f;
							// �ړ��̐���
							charainfo[P].move.x = 0.0f;
							charainfo[P].move.y = 0.0f;
							charainfo[P].move.z = 0.0f;

							// �����f���̒���
							MV1SetPosition(thunder,VGet(charainfo[P].pos.x + 30.0f,-220.0f,charainfo[P].pos.z - 60.0f));
							MV1SetScale(thunder,VGet(0.5f,0.1f,0.5f));
							MV1SetEmiColorScale(thunder,THUNDERMODELCOLOR);
							MV1SetRotationXYZ(thunder,VGet(0.0f,1.57f*1,0.0f)); 												//	�p���P�[�L���f���̉�]
							MV1SetAttachAnimTime(thunder, objectinfo[THUNDER].attachidx, objectinfo[THUNDER].playtime) ;
							MV1SetEmiColorScale(charainfo[P].model1,BLACKCOLOR);
							MV1DrawModel(thunder) ;
						}
					}else{
						MV1SetEmiColorScale(charainfo[0].model1,NORMALCOLOR);
						MV1SetEmiColorScale(charainfo[1].model1,NORMALCOLOR);
					}
				}

				/*
				*/
//				if(cookieinfo[i].Flipflag
//EffectAct(
				EffectAct();

				//for( int i = DEBUGC-1 ; i < DEBUGC ; i++ ){
				for(int i = 0; i < MAX_COOKIE; i++){
					if(cookieinfo[i].fliped != TRUE)	MV1DrawModel(cookie[i])	;		// �N�b�L�[�\��

					if((cookieinfo[i].Flipflag == 1 || cookieinfo[i].staytime != 0) &&
						cookieinfo[i].playtime > 40.0f &&
						cookieinfo[i].fliped != TRUE){
						MV1SetRotationXYZ(cookie_pic[cookieinfo[i].cookienum],VGet(0.0f,1.57f*2,1.57f*0));
						MV1DrawModel(cookie_pic[cookieinfo[i].cookienum]) ;				// �N�b�L�[�}���\��
					}
				}
				MV1DrawModel(crosshair[0]) ;
				MV1DrawModel(crosshair[1]) ;


				// �L�����N�^�[�̈ړ����� //
//	    			DrawFormatString(0,0,RGB(255,255,255),"Reset..%03d",120 - resetcnt);
				if((charainfo[0].pos.x + charainfo[0].move.x) > MAXLEFT &&
					(charainfo[0].pos.x + charainfo[0].move.x) < MAXRIGHT &&
					(charainfo[0].pos.z + charainfo[0].move.z) < MAXUP &&
					(charainfo[0].pos.z + charainfo[0].move.z) > MAXDOWN){
						charainfo[0].pos.x += charainfo[0].move.x ;
						charainfo[0].pos.y += charainfo[0].move.y ;
						charainfo[0].pos.z += charainfo[0].move.z ;
				}

				if((charainfo[1].pos.x + charainfo[1].move.x) > MAXLEFT &&
				    (charainfo[1].pos.x + charainfo[1].move.x) < MAXRIGHT &&
					(charainfo[1].pos.z + charainfo[1].move.z) < MAXUP &&
					(charainfo[1].pos.z + charainfo[1].move.z) > MAXDOWN){
						charainfo[1].pos.x += charainfo[1].move.x ;
						charainfo[1].pos.y += charainfo[1].move.y ;
						charainfo[1].pos.z += charainfo[1].move.z ;
				}

				/* ------------------------------------------------------------------------------ //
				//                            ���Ԃ��Ƃ̃C�x���g����                              //
				// ------------------------------------------------------------------------------ */
				if(cpos.z == cpos2.z && cpos.y == cpos2.y){
					if(gamemaintimer <= 10 && gamemaintimer >= 1){
						if(0 == CheckSoundMem(soundh[22])){
							PlaySoundMem( soundh[22] , DX_PLAYTYPE_BACK ) ;
						}
					}else if(0 != CheckSoundMem(soundh[22])){
						StopSoundMem(soundh[22]) ;
					}

					if(maintimer == (SCEENWAIT + 5)){
						if(0 == CheckSoundMem(soundh[12])){
							PlaySoundMem( soundh[12] , DX_PLAYTYPE_BACK ) ;
						}
					}

					/* -------------------------------------- //
					//			�X�e�[�W�`�F���W�\��		  //
					// -------------------------------------- */
					if(maintimer > SCEENWAIT && maintimer < (SCEENWAIT + 5) ){
						 DrawGraph(0,0,Graph[11],TRUE);
					}

					/* -------------------------------------- //
					//			�X�e�[�W�ړ�����			 //
					// -------------------------------------- */
					if(maintimer == SCEENWAIT && stageflg != 1){
						getcookiecnt = 0;
						if(0 == CheckSoundMem(soundh[19])){
							PlaySoundMem( soundh[19] , DX_PLAYTYPE_BACK ) ;
						}

						/* --------------------------- //
						//           ��������          //
						// --------------------------- */
						charainfo[0].pos.y += 5.0f;
						charainfo[1].pos.y += 5.0f;
						if(0 == ChangeScreen()){
							DrawBillboard3D(VGet(343.2f, -120.0f, 10.4f),0.5f,0.5f,1200.0f,0.0f,Graph[0],TRUE);
						}else{
							/* ---------------- //
							// �Q�ʃ��C���J���� // 
							// ---------------- */
							cpos = VGet(440.0f,500.0f,-10020.0f) ;
							ctgt = VGet(440.0f,-150.0f,50.0f) ;
							/* //
							// �T���_�[���L���������ꍇ�������I��点��  //
							// */
							// comeme
							if(charainfo[0].sunder != 0){
								charainfo[0].getcookie--;
								charainfo[0].sunder = FALSE;
								objectinfo[THUNDER].playtime = 0.0f;
							}else if(charainfo[1].sunder != 0){
								charainfo[1].getcookie--;								
								charainfo[1].sunder = FALSE;
								objectinfo[THUNDER].playtime = 0.0f;
							}

							for( char P = 0; P < MAX_PLAYER; P++){
								roolflipF[P] = FALSE;
								charainfo[P].upper  = VGet(0.0f,0.0f,0.0f);
								charainfo[P].move.x = 0.0f;
								charainfo[P].move.y = 0.0f;
								charainfo[P].move.z = 0.0f;
								charainfo[P].sunder = FALSE;
								charainfo[P].Selcookie[0] = 99;
								charainfo[P].Selcookie[1] = 99;
								if(P == 0)	charainfo[0].pos = VGet(P1POSX, -120.0f, P1POSZ) ;
								else		charainfo[1].pos = VGet(P2POSX,-120.0f,P2POSZ) ;			//chara3	-70

								if(charainfo[P].chara == 1){
									charainfo[P].pos.y -= 110.0f;
								}else if(charainfo[P].chara == 2){
									charainfo[P].pos.y -= 130.0f;
								}
							}
							charainfo[0].direction = RIGHT;
							charainfo[1].direction = LEFT;

							for(char i = 0; i < MAX_COOKIE; i++){
								cookieinfo[i].playtime = 0.0f;
								cookieinfo[i].fliped   = FALSE;
								cookieinfo[i].Flipflag = FALSE;
								cookieinfo[i].stay = FALSE;
								cookieinfo[i].staytime = STAYTIME;
								cookieinfo[i].deletestaytime = 0;
								MV1SetEmiColorScale(cookie[i], NORMALCOLOR) ;
							}

							resetwaittime = 0;
							resetcnt = 0;
							maintimer = timer();				// �b����i�߂�
							stageflg = 1;
							DrawBillboard3D(VGet(charainfo[0].pos.x,charainfo[0].pos.y,charainfo[0].pos.z),0.5f,0.5f,1200.0f,0.0f,Graph[0],TRUE);
							SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0);
							SetGlobalAmbientLight(BLACKCOLOR);
							Mixer();
						}
					}else{
						maintimer = timer();
					}

					/*              //
					// �X�^�[�g��� // 
					//              */
					if(maintimer > 90){
						if(maintimer == 93 && gamesubtimer == 1){
							PlaySoundMem( soundh[4] , DX_PLAYTYPE_BACK ) ;
						}
						DrawGraph(0,0,Graph[9],TRUE);	
//						SetFontSize(64);
//						DrawString(420,290,"START!",GetColor(255, 100, 100));
					}


					/* ---------------------------------------------------- //
					//                       �I������                       //
					// ---------------------------------------------------- */
					if(maintimer == -1){													// �ړ�����܂ł̎���()
						if(sceentime == 0){
							 PlaySoundMem( soundh[15] , DX_PLAYTYPE_BACK ) ;
						}
						DrawGraph(0,0,Graph[12],TRUE);
						sceentime++;
						if(sceentime == 60 * 2){
							StopSoundMem(soundh[3]);
							gamemode = eSceneOver;										//	���U���g���
							sceentime = 0;												// �V�[���҂����Ԃ̏�����
						}
					}else if(maintimer <= 90){
						if(stageflg != 1){
							DrawRectGraph(90  ,130,(charainfo[0].getcookie % 10) * 57,0,57,103,Graph[5],TRUE,FALSE);
							DrawRectGraph(1125,130,(charainfo[1].getcookie % 10) * 57,0,57,103,Graph[6],TRUE,FALSE);
						}else{																// ��ʈȍ~��B��
							// ??? �\��
 							DrawGraph(80  ,130,Graph[7],TRUE);
							DrawGraph(1105,130,Graph[7],TRUE);
						}
						// P1P2�摜
						DrawGraph(0,0,Graph[4],TRUE);
						if(maintimer >= 10){
							DrawRectGraph(581,25,(maintimer / 10) * 70,0,57,103,Graph[8],TRUE,FALSE);
							DrawRectGraph(638,25,(maintimer % 10) * 70,0,57,103,Graph[8],TRUE,FALSE);
						}else{
							DrawRectGraph(619,25,(maintimer % 10) * 70,0,57,103,Graph[8],TRUE,FALSE);
						}
					}

					// ���Z�b�g�̂Ƃ��摜��\��
					if(resetcnt > RESETTIME-30){
						if(gamesubtimer%6 != 0){
							DrawGraph(0,0,Graph[10],TRUE);	
						}
//						DrawString(410 + ((resetcnt-RESETTIME-20) * 12),290,"Reset",GetColor(255, 100, 100));
					}
				}
				ScreenFlip() ;
				break ;

			/********************************************************************************************************************************/
			/*																																*/
			/*														���U���g���															*/
			/*																																*/
			/********************************************************************************************************************************/
			case eSceneOver :		// ���ʏ���(���U���g�A�j���[�V����)
				// �F
				SetGlobalAmbientLight(RESULTCOLOR);
				MV1SetEmiColorScale( charainfo[0].chara, CHARACOLOR) ;
				MV1SetEmiColorScale( charainfo[1].chara, NORMALCOLOR) ;

				if(charainfo[0].getcookie == charainfo[1].getcookie ){
					if(charainfo[0].getcookie%2 == 0){
						charainfo[1].getcookie++ ;
					}else{
						charainfo[0].getcookie++ ;
					}
				} 

				// ���Z�b�g
				key = GetJoypadInputState(DX_INPUT_KEY_PAD1) ;
				key2 = GetJoypadInputState(DX_INPUT_PAD2) ;

				if( resultsetflg == FALSE ){
//debugs
//					charainfo[0].getcookie = 1;
//					charainfo[1].getcookie = 1;
//
					waittimer = 0;
					if(0 == CheckSoundMem(soundh[17])){
					    PlaySoundMem( soundh[17] , DX_PLAYTYPE_BACK ) ;
					}
					// ���C�g�̕�����ݒ�
					SetLightDirection( VGet( 6.0f, -100.f, 5.0f ) );

					// �ǉ����C�g
					LightHandle = CreatePointLightHandle(
						VGet( -900.0f,1000.0f,1000.0f),
						2000.0f,
						0.0f,
						0.002f,
						0.0f);
					// �e�[�u���̈ʒu
					tablepos    = VGet(600.0f,-11000.0f,51.0f) ;
					rangepos    = VGet(600.0f,-270.0f,6000.0f) ;

					// �J�����|�W�V����
					cpos5 = VGet( 750.0f, -140.0f, -380.0f ) ;
					ctgt5 = VGet( 750.0f, -170.0f, 50.0f ) ;
					cpos4 = VGet( 180.0f, -140.0f, -380.0f ) ;
					ctgt4 = VGet( 180.0f, -170.0f, 50.0f ) ;
					cpos = VGet( 480.0f, 20.0f, -570.0f ) ;
					ctgt = VGet( 480.0f, -150.0f, 50.0f ) ;
					// �J�����ݒ�
					SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet( 0.0f,0.0f, 0.1f)) ;

					// �L�����ʒu���Œ�
					charainfo[0].direction = DOWNRIGHT ;
					charainfo[1].direction = DOWNLEFT ;
					charainfo[0].pos = VGet(323.2f, -60.0f , 14.4f) ;
					charainfo[1].pos = VGet(632.0f, -60.0f , 14.4f) ;
					cookieinfo[0].cookiepos = VGet( 280.0f , -390.0f , 14.4f ) ; 
					cookieinfo[1].cookiepos = VGet( 669.0f , -390.0f , 14.4f ) ;
					MV1SetPosition(cookie[0] , VGet( cookieinfo[0].cookiepos.x , cookieinfo[0].cookiepos.y , cookieinfo[0].cookiepos.z ) ) ;
					MV1SetPosition(cookie[1] , VGet( cookieinfo[1].cookiepos.x , cookieinfo[1].cookiepos.y , cookieinfo[1].cookiepos.z ) ) ;
					// �}��������
					if( charainfo[0].getcookie > charainfo[1].getcookie ){					
						MV1SetPosition(charainfo[6].model1,charainfo[1].pos);
						// �������ꍇ���̃}�[�N�ɂȂ�
						cookieinfo[4].cookienum = 2 ;
						cookieinfo[5].cookienum = 5 ;
						if(charainfo[1].chara != 0){
//							charainfo[6].pos.y += 150.0f;	
						}
					}else if( charainfo[0].getcookie < charainfo[1].getcookie ){
						MV1SetPosition(charainfo[6].model1,charainfo[0].pos);
						// �������ꍇ���̃}�[�N�ɂȂ�
						cookieinfo[4].cookienum = 4 ;
						cookieinfo[5].cookienum = 3 ;
						if(charainfo[0].chara != 0){
//							charainfo[6].pos.y += 150.0f;	
						}
					}else{
						MV1SetPosition(charainfo[6].model1,charainfo[0].pos);
						MV1SetPosition(charainfo[7].model1,charainfo[0].pos);
						cookieinfo[4].cookienum = 4 ;
						cookieinfo[5].cookienum = 5 ;
						if(charainfo[0].chara != 0){
//							charainfo[7].pos.y += 150.0f;	
						}
						if(charainfo[1].chara != 0){
//							charainfo[6].pos.y += 150.0f;	
						}
					}

					// �N�b�L�[�w�ʂɐ}����\��t��
					for( int i = 0 ; i < 2 ; i++ ) {
						// �N�b�L�[�摜	
						switch( i ) {
							case 1 :
								MV1SetPosition(cookie_pic[cookieinfo[i].cookienum] , VGet( cookieinfo[0].cookiepos.x , cookieinfo[0].cookiepos.y - 20.0f , cookieinfo[0].cookiepos.z ) ) ;
								MV1SetScale(cookie_pic[cookieinfo[i].cookienum],VGet(0.42f,0.49f,0.42f));				// �N�b�L�[�̔w�ʃ��f�� ��
								break ;
							case 2:
								MV1SetPosition(cookie_pic[cookieinfo[i].cookienum] , VGet( cookieinfo[1].cookiepos.x , cookieinfo[1].cookiepos.y - 20.0f , cookieinfo[1].cookiepos.z ) ) ;
								MV1SetScale(cookie_pic[cookieinfo[i].cookienum],VGet(0.42f,0.49f,0.42f));				// �N�b�L�[�̔w�ʃ��f�� ��
								break ;
						}
					}

					for(int P = 0 ; P < MAX_PLAYER ; P++){
						if(charainfo[P].chara != 0){
								charainfo[P].pos.y -= 150.0f;	
						}else{
								charainfo[P].pos.y += 30.0f;	
						}
					}

					objectinfo[THUNDER].playtime = 0.0f ;
					// �e�L�����ɂ��I�t�Z�b�g
					for( int  P = 0 ; P < MAX_PLAYER ; P++ )
					{
						cookieinfo[P].playtime = 0.0f;//	�N�b�L�[���Ђ�����Ԃ�
						cookieinfo[P].Flipflag = 0;
						charainfo[P].sunder		= TRUE ;
						stageflg = TRUE ;
						switch( P ){
							// �v���C���[1
							case 0 :
								// �L�����N�^�[�̈ʒu�Ɖ�]
								MV1SetScale(charainfo[0].model1,VGet(1.8f, 1.8f, 1.8f));			// chara1
								MV1SetRotationXYZ(charainfo[0].model1,VGet( 0.0f , charainfo[0].direction * 0.450f ,  0.0f )) ;
//								MV1SetPosition(charainfo[0].model1 , VGet( charainfo[0].pos.x - 25.0f , charainfo[0].pos.y, charainfo[0].pos.z - 30.0f ) );
								break ;
							// �v���C���[�Q
							case 1 :
								// �L�����N�^�[�̈ʒu�Ɖ�]
								MV1SetScale(charainfo[1].model1,VGet(1.8f, 1.8f, 1.8f));
								MV1SetRotationXYZ(charainfo[1].model1,VGet( 0.0f , charainfo[1].direction * 0.585f ,  0.0f )) ;
//								MV1SetPosition(charainfo[1].model1 , VGet( charainfo[1].pos.x + 25.0f , charainfo[1].pos.y, charainfo[1].pos.z - 30.0f ) );
								break ;
							}
					}
					MV1SetRotationXYZ(charainfo[0].model1,VGet( 0.0f , DOWN * 0.785f , 0.0f )) ;
					MV1SetRotationXYZ(charainfo[1].model1,VGet( 0.0f , DOWN * 0.785f , 0.0f )) ;
					MV1SetPosition(charainfo[0].model1 , VGet( charainfo[0].pos.x - 25.0f , charainfo[0].pos.y, charainfo[0].pos.z - 30.0f ) );
					MV1SetPosition(charainfo[1].model1 , VGet( charainfo[1].pos.x + 25.0f , charainfo[1].pos.y, charainfo[1].pos.z - 30.0f ) );
					MV1SetRotationXYZ(cookie[0],VGet( 0.0f , 0.5f ,  0.0f )) ;
					MV1SetRotationXYZ(range ,VGet( 0.0f , 1.5f ,  0.0f )) ;
					MV1SetScale( range ,VGet(0.5f,0.5f,0.5f));				// �d�q�����W
					MV1SetPosition(table,tablepos);
					MV1SetPosition(range,rangepos);
					// ���̈ʒu����
					MV1SetRotationXYZ(thunder,VGet(0.0f,1.57f*1,0.0f));
					MV1SetRotationXYZ(thunder2,VGet(0.0f,1.57f*1,0.0f));
					MV1SetScale(thunder,VGet(0.5f,0.1f,0.5f));
					MV1SetScale(thunder2,VGet(0.5f,0.1f,0.5f));
					MV1SetEmiColorScale(thunder,THUNDERMODELCOLOR);
					MV1SetEmiColorScale(thunder2,THUNDERMODELCOLOR);
					resultsetflg = TRUE;
				}
				ClearDrawScreen() ;		

				Animset();
				PlayerFly();		//�@�v���C���[�̕��V�A�j���[�V����

				MV1SetScale(charainfo[6].model1,VGet(2.0f,2.0f,2.0f));
				MV1SetScale(charainfo[7].model1,VGet(2.0f,2.0f,2.0f));
				if(charainfo[0].getcookie > charainfo[1].getcookie){
					if(objectinfo[THUNDER].playtime >= objectinfo[THUNDER].anim_totaltime){
						if(charainfo[6].playtime < charainfo[6].anim_totaltime){
							charainfo[6].playtime += 0.5f;
						}
						else
						{
							charainfo[6].playtime = 0.0f;
						}
						MV1SetEmiColorScale(charainfo[6].model1,THUNDERCOLOR);
						MV1DrawModel(charainfo[0].model1) ;
						MV1DrawModel(charainfo[6].model1) ;
					}else{
						if(charainfo[1].chara != 0){
							MV1SetPosition(charainfo[6].model1,VGet(charainfo[1].pos.x + 60.0f,charainfo[1].pos.y + 215.0f,charainfo[1].pos.z ));
						}else{
							MV1SetPosition(charainfo[6].model1,VGet(charainfo[1].pos.x + 60.0f,charainfo[1].pos.y + 40.0f,charainfo[1].pos.z));
						}
						MV1DrawModel(charainfo[0].model1) ;
						MV1DrawModel(charainfo[1].model1) ;
					}
				}else if(charainfo[0].getcookie < charainfo[1].getcookie){
					if(objectinfo[THUNDER].playtime >= objectinfo[THUNDER].anim_totaltime){
						if(charainfo[6].playtime < charainfo[6].anim_totaltime){
							charainfo[6].playtime += 0.5f;
						}
						else
						{
							charainfo[6].playtime = 0.0f;
						}
						MV1SetEmiColorScale(charainfo[6].model1,THUNDERCOLOR);
						MV1DrawModel(charainfo[1].model1) ;
						MV1DrawModel(charainfo[6].model1) ;
					}else{
						if(charainfo[0].chara != 0){
							MV1SetPosition(charainfo[6].model1,VGet(charainfo[0].pos.x - 60.0f,charainfo[0].pos.y + 215.0f,charainfo[0].pos.z));
						}else{
							MV1SetPosition(charainfo[6].model1,VGet(charainfo[0].pos.x - 60.0f,charainfo[0].pos.y + 40.0f,charainfo[0].pos.z));
						}
						MV1DrawModel(charainfo[0].model1) ;
						MV1DrawModel(charainfo[1].model1) ;
					}
				}
				MV1DrawModel(cookie[0])	;
				MV1DrawModel(cookie[1])	;
				MV1DrawModel(table) ;
				MV1DrawModel(Sfloor[0]) ;
				MV1DrawModel(range) ;

				MV1SetAttachAnimTime(thunder, objectinfo[THUNDER].attachidx, objectinfo[THUNDER].playtime) ;
				MV1SetAttachAnimTime(thunder2, objectinfo[THUNDER + 1].attachidx, objectinfo[THUNDER].playtime) ;

				if(charainfo[0].bdownF == FALSE && charainfo[1].bdownF == FALSE){
					MV1SetRotationXYZ(charainfo[0].model1,VGet( 0.0f , DOWN * 0.785f , 0.0f )) ;
					MV1SetRotationXYZ(charainfo[1].model1,VGet( 0.0f , DOWN * 0.785f , 0.0f )) ;
					MV1SetRotationXYZ(charainfo[6].model1,VGet( 0.0f , DOWN * 0.785f , 0.0f )) ;
					MV1SetRotationXYZ(charainfo[7].model1,VGet( 0.0f , DOWN * 0.785f , 0.0f )) ;
				}

				// �^�C�}�[
				if(waittimer == (MAXTIME- 90)){
					charainfo[0].bdownF		= TRUE ;
					charainfo[1].bdownF		= TRUE ;
				}
				if(waittimer > MAXTIME){
					if(charainfo[0].bdownF == FALSE && charainfo[1].bdownF == FALSE){
						for(int i = 0; i < MAX_COOKIE; i++){
							if(cookieinfo[i].playtime < cookieinfo[i].anim_totaltime){
									cookieinfo[i].playtime += 0.9f;//	�N�b�L�[���Ђ�����Ԃ�
							}
							if(cookieinfo[i].playtime >= 40.0f){
								MV1SetPosition(cookie_pic[cookieinfo[4].cookienum] , VGet( cookieinfo[0].cookiepos.x , cookieinfo[0].cookiepos.y + 40.0f , cookieinfo[0].cookiepos.z ) ) ;
								MV1SetScale(cookie_pic[cookieinfo[4].cookienum],VGet(0.42f,0.49f,0.42f));				// �N�b�L�[�̔w�ʃ��f�� ��
								MV1SetPosition(cookie_pic[cookieinfo[5].cookienum] , VGet( cookieinfo[1].cookiepos.x , cookieinfo[1].cookiepos.y + 40.0f , cookieinfo[1].cookiepos.z ) ) ;
								MV1SetScale(cookie_pic[cookieinfo[5].cookienum],VGet(0.42f,0.49f,0.42f));				// �N�b�L�[�̔w�ʃ��f�� ��
								MV1DrawModel(cookie_pic[cookieinfo[4].cookienum]) ;				// �N�b�L�[�}���\��
								MV1DrawModel(cookie_pic[cookieinfo[5].cookienum]) ;				// �N�b�L�[�}���\��					
							}
						}
					}
				}

				// ���ʔ��\
//				DrawString(50,20,"P1",GetColor(0,20,255));
//				DrawString(1090,20,"P2",GetColor(255,60,0));
				DrawGraph(0,0,Graph[4],TRUE);

				if( waittimer > (MAXTIME + 30) && cookieinfo[1].playtime >= cookieinfo[1].anim_totaltime){
					StopSoundMem(soundh[17]);
					if(0 == CheckSoundMem(soundh[21])){
					    PlaySoundMem( soundh[21] , DX_PLAYTYPE_LOOP ) ;
					}
					// �X�R�A�\��
					DrawRectGraph(90  ,130,(charainfo[0].getcookie % 10) * 57,0,57,103,Graph[5],TRUE,FALSE);
					DrawRectGraph(1125,130,(charainfo[1].getcookie % 10) * 57,0,57,103,Graph[6],TRUE,FALSE);

					// �X�R�A�������̎��A����ł������ŏ��������܂鏈���i��X�ǉ��j
					if( charainfo[0].getcookie > charainfo[1].getcookie ) {
						DrawGraph(0,0,Graph[13],TRUE);
						// �������[�V����
						if(objectinfo[THUNDER].playtime == 0.0f){
							switch(charainfo[0].chara){
								case 0:
									MV1DetachAnim(charainfo[0].model1, charainfo[0].attachidx) ;
									charainfo[0].attachidx = MV1AttachAnim(charainfo[0].model1, 2, Pwin) ;
									charainfo[0].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[0].model1, charainfo[0].attachidx) ;
									charainfo[0].rootflm = MV1SearchFrame(charainfo[0].model1,"root") ;
									MV1SetFrameUserLocalMatrix(charainfo[0].model1, charainfo[0].rootflm,MGetIdent()) ;
									charainfo[0].playtime = 0.0f ;
									break;
								case 1:
									MV1DetachAnim(charainfo[0].model1, charainfo[0].attachidx) ;
									charainfo[0].attachidx = MV1AttachAnim(charainfo[0].model1, 2, P2win) ;
									charainfo[0].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[0].model1, charainfo[0].attachidx) ;
									charainfo[0].rootflm = MV1SearchFrame(charainfo[0].model1,"root") ;
									MV1SetFrameUserLocalMatrix(charainfo[0].model1, charainfo[0].rootflm,MGetIdent()) ;
									charainfo[0].playtime = 0.0f ;
									break;
								case 2:
									MV1DetachAnim(charainfo[0].model1, charainfo[0].attachidx) ;
									charainfo[0].attachidx = MV1AttachAnim(charainfo[0].model1, 1, P3win) ;
									charainfo[0].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[0].model1, charainfo[0].attachidx) ;
									charainfo[0].rootflm = MV1SearchFrame(charainfo[0].model1,"root") ;
									MV1SetFrameUserLocalMatrix(charainfo[0].model1, charainfo[0].rootflm,MGetIdent()) ;
									charainfo[0].playtime = 0.0f ;
									break;
							}
						}

						// �������ق��ɗ��𗎂Ƃč�������
						if(objectinfo[THUNDER].playtime < objectinfo[THUNDER].anim_totaltime) {
							if(0 == CheckSoundMem(soundh[10])){
								PlaySoundMem( soundh[10] , DX_PLAYTYPE_BACK ) ;
							}
							// ��
							MV1SetPosition(thunder,VGet(charainfo[1].pos.x - 25.0f,charainfo[1].pos.y - 30.0f , charainfo[1].pos.z - 30.0f));
							objectinfo[THUNDER].playtime += 0.4f;
							MV1SetEmiColorScale(charainfo[1].model1,THUNDERCOLOR);
							MV1DrawModel(thunder);
						}else{
/*							if(cpos.x > cpos4.x){
								cpos.x -= 0.2f;
								cpos.z += 0.2f;
								ctgt.x -= 0.2f;
							}else{
								cpos.x = cpos4.x;
								ctgt.x = ctgt4.x;
							}
*/						}
					}
					else if( charainfo[0].getcookie < charainfo[1].getcookie ){
						DrawGraph(0,0,Graph[14],TRUE);
						// �������[�V����
						if(objectinfo[THUNDER].playtime == 0.0f){
							switch(charainfo[1].chara){
								case 0:
									MV1DetachAnim(charainfo[1].model1, charainfo[1].attachidx) ;
									charainfo[1].attachidx = MV1AttachAnim(charainfo[1].model1, 2, Pwin) ;
									charainfo[1].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[1].model1, charainfo[1].attachidx) ;
									charainfo[1].rootflm = MV1SearchFrame(charainfo[1].model1,"root") ;
									MV1SetFrameUserLocalMatrix(charainfo[1].model1, charainfo[1].rootflm,MGetIdent()) ;
									charainfo[1].playtime = 0.0f ;
									break;
								case 1:
									MV1DetachAnim(charainfo[1].model1, charainfo[1].attachidx) ;
									charainfo[1].attachidx = MV1AttachAnim(charainfo[1].model1, 2, P2win) ;
									charainfo[1].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[1].model1, charainfo[1].attachidx) ;
									charainfo[1].rootflm = MV1SearchFrame(charainfo[1].model1,"root") ;
									MV1SetFrameUserLocalMatrix(charainfo[1].model1, charainfo[1].rootflm,MGetIdent()) ;
									charainfo[1].playtime = 0.0f ;
									break;
								case 2:
									MV1DetachAnim(charainfo[1].model1, charainfo[1].attachidx) ;
									charainfo[1].attachidx = MV1AttachAnim(charainfo[1].model1, 1, P3win) ;
									charainfo[1].anim_totaltime = MV1GetAttachAnimTotalTime(charainfo[1].model1, charainfo[1].attachidx) ;
									charainfo[1].rootflm = MV1SearchFrame(charainfo[1].model1,"root") ;
									MV1SetFrameUserLocalMatrix(charainfo[1].model1, charainfo[1].rootflm,MGetIdent()) ;
									charainfo[1].playtime = 0.0f ;
									break;
							}
						}
						// �������ق��ɗ��𗎂Ƃ�
						if(objectinfo[THUNDER].playtime < objectinfo[THUNDER].anim_totaltime) {
							if(0 == CheckSoundMem(soundh[10])){
								PlaySoundMem( soundh[10] , DX_PLAYTYPE_BACK ) ;
							}
							MV1SetPosition(thunder,VGet(charainfo[0].pos.x - 25.0f,charainfo[0].pos.y - 30.0f , charainfo[0].pos.z - 30.0f));
							// ��
							objectinfo[THUNDER].playtime += 0.4f;
							MV1SetEmiColorScale(charainfo[0].model1,THUNDERCOLOR);
							MV1DrawModel(thunder);
						}else{
/*							if(cpos.x < cpos5.x){
								cpos.x += 8.0f;
								ctgt.x -= 8.0f;
							}else{
								cpos.x = cpos5.x;
//								ctgt.x = ctgt5.x;
//								cpos = cpos5;
							}							
*/						}
					}else{
						DrawString(480,50,"Draw",GetColor(255, 255, 0));
						if(objectinfo[THUNDER].playtime < objectinfo[THUNDER].anim_totaltime) {
							// ��
							if(0 == CheckSoundMem(soundh[10])){
								PlaySoundMem( soundh[10] , DX_PLAYTYPE_BACK ) ;
							}

							// ������thunder2�������
							MV1SetPosition(thunder,VGet(charainfo[0].pos.x - 25.0f,charainfo[0].pos.y - 30.0f , charainfo[0].pos.z - 30.0f));
							MV1SetPosition(thunder2,VGet(charainfo[1].pos.x - 25.0f,charainfo[1].pos.y - 30.0f , charainfo[1].pos.z - 30.0f));
							objectinfo[THUNDER].playtime += 0.4f;
							MV1SetEmiColorScale(charainfo[0].model1,THUNDERCOLOR);
							MV1SetEmiColorScale(charainfo[1].model1,THUNDERCOLOR);
							MV1DrawModel(thunder);
							MV1DrawModel(thunder2);
						}
					}
				}else{
					waittimer++;
				}
				MV1SetAttachAnimTime(charainfo[6].model1, charainfo[6].attachidx, charainfo[6].playtime) ;
				MV1SetAttachAnimTime(charainfo[7].model1, charainfo[7].attachidx, charainfo[7].playtime) ;
				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet( 0.0f,0.0f, 0.1f)) ;
				if(key == 3840 || key2 == 3840){									// ResetButton;
					ClearDrawScreen();
					DrawString(700,600,"Loading...",RGB(255,255,255),TRUE);
					ScreenFlip();
					resetcnt = 0;
					for(char i = 0; i < MAX_SOUND; i++){
						StopSoundMem(soundh[i]);
					}
					for(char i = 0; i < MAX_COOKIE; i++){
						cookieinfo[i].playtime = 0.0f;
						cookieinfo[i].Flipflag = FALSE;
					}
					FlipCnt();
					// come
					SetGlobalAmbientLight(BLACKCOLOR);
					MV1SetEmiColorScale( charainfo[0].chara, NORMALCOLOR) ;
					MV1SetEmiColorScale( charainfo[1].chara, NORMALCOLOR) ;
					cpos3 = VGet(550.0f,-80.0f,-380.0f) ;
					ctgt3 = VGet(550.0f,-100.0f,50.0f) ;
					cpos2 = VGet(440.0f,100.0f,-320.0f) ;
					ctgt2 = VGet(440.0f,-150.0f,50.0f) ;
					cpos = VGet(440.0f,500.0f,-10020.0f) ;
					ctgt = VGet(440.0f,-150.0f,50.0f) ;
					//�X�e�[�W�̃|�W�V����
					pancakepos  = VGet(440.0f,-555.0f,690.0f) ;
					pancake2pos = VGet(2500.0f,-675.0f,600.0f) ;
					platepos    = VGet(90.0f,-1000.0f,900.0f) ;
					tablepos    = VGet(600.0f,-10050.0f,5200.0f) ;
					rangepos = VGet(600.0f,50.0f,900.0f);	// �����W
					// ���C�g�̕�����ݒ�
					SetLightDirection( VGet( 0.5f, -0.5f, 0.5f ) );
					DeleteLightHandle(LightHandle);	
					gamemode = eSceneBlank2;
				}
				ScreenFlip();
				break ;

			case eSceneEnd :														// �I������
				break;
		}
	}
	DxLib_End() ;
	return 0 ;
}

