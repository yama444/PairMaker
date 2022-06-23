#include <windows.h>
#include "common.h"

int InitSet( void ){
	// ------------------------------------------------------------------------- // 
	//							�T�E���h�̓ǂݍ���			                     //
	// ------------------------------------------------------------------------- // 
	
	// test.wav�̃������ւ̓ǂݍ��݃T�E���h�n���h����SHandle�ɕۑ����܂�
    soundh[0] = LoadSoundMem( "..\\Data\\Sound\\BGM\\SUNNY_CLOUDY.mp3" ) ;		// �^�C�g��BGM
    soundh[1] = LoadSoundMem( "..\\Data\\Sound\\SE\\touch.mp3" ) ;				// �^�C�g������
	soundh[2] = LoadSoundMem( "..\\Data\\Sound\\BGM\\������g�[��.mp3" ) ;		// �I��
	soundh[3] = LoadSoundMem( "..\\Data\\Sound\\BGM\\�X�L�b�v�E�X�L�b�v.mp3" ) ;// MainBGM
	soundh[4] = LoadSoundMem( "..\\Data\\Sound\\SE\\timeup.mp3" ) ; ;			// �J�n��
	soundh[5] = LoadSoundMem( "..\\Data\\Sound\\SE\\collision.mp3" ) ;			// �Ԃ������Ƃ��̉�
	soundh[6] = LoadSoundMem( "..\\Data\\Sound\\SE\\touch.mp3" ) ;				//  �O�p�{�^���������Ƃ�
//	soundh[7] = LoadSoundMem( "..\\Data\\Sound\\SE\\" ) ;						// �N�b�L�[���Ђ�����Ԃ�����
	soundh[8] = LoadSoundMem( "..\\Data\\Sound\\SE\\flip.mp3" ) ;				// ��������
	soundh[9] = LoadSoundMem( "..\\Data\\Sound\\SE\\miss.mp3" ) ;				// �O������
	soundh[10] = LoadSoundMem( "..\\Data\\Sound\\SE\\��.mp3" ) ;				// ��
	soundh[11] = LoadSoundMem( "..\\Data\\Sound\\SE\\collision.mp3" ) ;			// ���Z�b�g�̉�
	soundh[12] = LoadSoundMem( "..\\Data\\Sound\\SE\\�����v.mp3" ) ;			// �X�e�[�W�؂�ւ��O���m�点
	soundh[13] = LoadSoundMem( "..\\Data\\Sound\\SE\\push.mp3" ) ;				// sel���艹
	soundh[14] = LoadSoundMem( "..\\Data\\Sound\\SE\\move.mp3" ) ;				// sel�ړ���
	soundh[15] = LoadSoundMem( "..\\Data\\Sound\\SE\\timeup.mp3" ) ;				// �I��
	soundh[16] = LoadSoundMem( "..\\Data\\Sound\\SE\\���ʔ��\.mp3" ) ;			// ���U���g��(����)
	soundh[17] = LoadSoundMem( "..\\Data\\Sound\\SE\\dramroll.mp3" ) ;			// �h�������[��
//	soundh[18] = LoadSoundMem( "..\\Data\\Sound\\BGM\\Flowering_Road.mp3" ) ;	// ���ʔ��\��BGM
	soundh[19] = LoadSoundMem( "..\\Data\\Sound\\SE\\flying.mp3" ) ;			// �X�e�[�W�؂�ւ���
	soundh[20] = LoadSoundMem( "..\\Data\\Sound\\SE\\cancel.mp3" ) ;			// �L�����Z����
	soundh[21] = LoadSoundMem( "..\\Data\\Sound\\BGM\\���N�`���L.mp3" ) ;		// ���U���gBGM
	soundh[22] = LoadSoundMem( "..\\Data\\Sound\\SE\\clock.mp3" ) ;			// �}������
    // �ǂ݂��񂾉����m�[�}���Đ����܂�(�wPlaySoundMem�x�֐��g�p)
//    PlaySoundMem( soundh[0] , DX_PLAYTYPE_BACK ) ;
//    PlaySoundMem( soundh[0] , DX_PLAYTYPE_LOOP ) ;
//				StopSoundMem(soundh[0]);
//ChangeVolumeSoundMem( 255 * 80 / 100, SHandle ) ; // 0 ~ max255 	
//ChangeVolumeSoundMem( 170,soundh[3]);

	// ------------------------------------------------------------------------ // 
	//							�摜�ǂݍ���									//
	// ------------------------------------------------------------------------ //
	characterselect[0] = LoadGraph("..\\Stage\\selectcheck.png");
	characterselect[1] = LoadGraph("..\\Stage\\biscuitw.png");
	characterselect[2] = LoadGraph("..\\Stage\\biscuitw2.png");
	characterselect[3] = LoadGraph("..\\Stage\\biscuitw3.png");
	characterselect[4] = LoadGraph("..\\Stage\\biscuitw4.png");
	characterselect[5] = LoadGraph("..\\Stage\\biscuityesno.png");


	// ------------------------------------------------------------------------- // 
	//							�A�j���[�V�����̓ǂݍ���	                     //
	// ------------------------------------------------------------------------- // 
	cookie_flip = MV1LoadModel("..\\Player\\cookie_flip.mv1") ;
	if(cookie_flip == -1) return -1 ;
	Cookie_flip_Square = MV1LoadModel("..\\Player\\Square_Cookieflip.mv1") ;
	if(Cookie_flip_Star == -1) return -1;

	Pmove = MV1LoadModel("..\\Player\\Pmove.mv1") ;
	if(Pmove == -1) return -1;
	Pstay = MV1LoadModel("..\\Player\\Pstay.mv1") ;
	if(Pstay == -1) return -1;
	Pwin =  MV1LoadModel("..\\Player\\Pwin.mv1");
	if(Pwin == -1) return -1;

	P2move = MV1LoadModel("..\\Player\\P2move.mv1") ;
	if(P2move == -1) return -1;
	P2stay = MV1LoadModel("..\\Player\\P2stay.mv1") ;
	if(P2stay == -1) return -1;
	P2win =  MV1LoadModel("..\\Player\\P2win.mv1");
	if(P2win == -1) return -1;

	P3move = MV1LoadModel("..\\Player\\P3move.mv1") ;
	if(P3move == -1) return -1;
	P3stay = MV1LoadModel("..\\Player\\P3stay.mv1") ;
	if(P3stay == -1) return -1;
	P3win =  MV1LoadModel("..\\Player\\P3win.mv1");
	if(P3win == -1) return -1;

	heatM = MV1LoadModel("..\\Player\\charalose_anim.mv1");
	if(heatM == -1) return -1;

	thunderdown = MV1LoadModel("..\\Player\\thunderdown.mv1");
	if(thunderdown == -1) return -1;
	rangeanim = MV1LoadModel("..\\Player\\rangeanim.mv1") ;
	if(rangeanim == -1) return -1;
	bowlanim = MV1LoadModel("..\\Stage\\Hoipper_bowl_model.mv1");
	if(bowlanim == -1) return -1;


	// ------------------------------------------------------------------------- // 
	//							�X�e�[�W���̓ǂݍ���		                     //
	// ------------------------------------------------------------------------- // 
	for(char i = 0; i < MAX_COOKIE; i++){
		if(i == 0){
			efstar[0] = MV1LoadModel("..\\Stage\\efsstar.mv1");
			if(efstar[0] == -1) return -1;
		}else{
			efstar[i] = MV1DuplicateModel(efstar[0]);
		}
		objectinfo[EFFSTAR + i].attachidx = MV1AttachAnim(efstar[i], 0, efstar[i]);
		objectinfo[EFFSTAR + i].anim_totaltime = 15.0f;
		objectinfo[EFFSTAR + i].rootflm = MV1SearchFrame(efstar[i],"root") ;
		MV1SetFrameUserLocalMatrix(efstar[i], objectinfo[EFFSTAR + i].rootflm,MGetIdent()) ;
		objectinfo[EFFSTAR + i].playtime = 0.0f ;
	}

	crosshair[0] = MV1LoadModel("..\\Player\\crosshair.mv1") ;			//�@�M�̓ǂݍ���
	if(crosshair[0] == -1) return -1 ;
	crosshair[1] = MV1DuplicateModel(crosshair[0]);

	plate = MV1LoadModel("..\\Stage\\plate.mv1") ;			//�@�M�̓ǂݍ���
	if(plate == -1) return -1 ;
	
	pancake = MV1LoadModel("..\\Stage\\pancake.mv1") ;		//�@�p���P�[�L�̓ǂݍ���
	if(pancake == -1) return -1 ;
	pancake2 = MV1DuplicateModel(pancake) ;		//�@�p���P�[�L�̓ǂݍ���
	if(pancake2 == -1) return -1 ;

	table = MV1LoadModel("..\\Stage\\table.mv1") ;			//	�e�[�u���ǂݍ���
	if(table == -1) return -1 ;

	Sfloor[0] = MV1LoadModel("..\\Stage\\floor.mv1") ;			//	�e�[�u���ǂݍ���
	if(Sfloor[0] == -1) return -1 ;
	
	egg   = MV1LoadModel("..\\Stage\\egg.mv1") ;			//	�e�[�u���ǂݍ���
	if(egg == -1) return -1 ;

	thunder = MV1LoadModel("..\\Stage\\thundermodel.mv1");
	if(thunder == -1) return -1;
	thunder2 = MV1DuplicateModel(thunder);

	range = MV1LoadModel("..\\Stage\\range.mv1") ;			//	�����W�ǂݍ���
	if(range == -1) return -1 ;

	milk = MV1LoadModel("..\\Stage\\Milk_carton.mv1");
	if(milk == -1) return -1 ;

	lack = MV1LoadModel("..\\Stage\\lacks.mv1");
	if(lack == -1) return -1;

	reizo = MV1LoadModel("..\\Stage\\reizo.mv1");
	if(reizo == -1) return -1;
	
	for(char i = 0; i < MAX_BOWL; i++){
		if(i == 0){
			bowl[i] = MV1LoadModel("..\\Stage\\Hoipper_bowl_model.mv1");
			if(bowl[0] == -1) return -1;
		}else if(i == 1){
			bowl[i] = MV1LoadModel("..\\Stage\\Hoipper_bowl_model3.mv1");
		}else if(i == 2){
			bowl[i] = MV1LoadModel("..\\Stage\\Hoipper_bowl_model2.mv1");
		}else{
			bowl[i] = MV1DuplicateModel(bowl[0]);
		}
	}

	for(char i = 0; i < MAX_BOWL; i++){
		objectinfo[BOWL + i].attachidx = MV1AttachAnim(bowl[i],0,bowlanim) ;
		objectinfo[BOWL + i].anim_totaltime = MV1GetAttachAnimTotalTime(bowl[i],objectinfo[BOWL + i].attachidx) ;
		objectinfo[BOWL + i].rootflm = MV1SearchFrame(bowl[i],"root") ;
		MV1SetFrameUserLocalMatrix(bowl[i],objectinfo[BOWL + i].rootflm,MGetIdent()) ;
		objectinfo[BOWL + i].playtime = 0.0f ;	
	}

	for(int i = 0; i < MAX_COOKIE ; i++){
		if( MAX_COOKIE/2 > i){
			cookie[i] = MV1LoadModel("..\\Stage\\cookie.mv1") ;				//	�e�[�u���ǂݍ���
			cookieinfo[i].attachidx = MV1AttachAnim(cookie[i],0,cookie_flip) ;
		}else{
			cookie[i] = MV1LoadModel("..\\Stage\\Square_Cookie.mv1") ;		//	�e�[�u���ǂݍ���
			cookieinfo[i].attachidx = MV1AttachAnim(cookie[i], 0, Cookie_flip_Square) ;
		}
		if(cookie[i] == -1) return -1 ;
		cookieinfo[i].anim_totaltime = MV1GetAttachAnimTotalTime(cookie[i],cookieinfo[i].attachidx) ;
		cookieinfo[i].rootflm = MV1SearchFrame(cookie[i],"root") ;
		MV1SetFrameUserLocalMatrix(cookie[i],cookieinfo[i].rootflm,MGetIdent()) ;
	}

	objectinfo[0].attachidx = MV1AttachAnim(range,0,rangeanim) ;
	objectinfo[0].anim_totaltime = MV1GetAttachAnimTotalTime(range,objectinfo[0].attachidx) ;
	objectinfo[0].rootflm = MV1SearchFrame(range,"root") ;
	MV1SetFrameUserLocalMatrix(range,objectinfo[0].rootflm,MGetIdent()) ;
	objectinfo[0].playtime = 0.0f ;	

	// ------------------------------------------------------------------------ // 
	//						�T���_�[�摜�ǂݍ���								//
	// ------------------------------------------------------------------------ //
	objectinfo[THUNDER].attachidx = MV1AttachAnim(thunder, 0, thunderdown) ;
	objectinfo[THUNDER].anim_totaltime = MV1GetAttachAnimTotalTime(thunder,objectinfo[THUNDER].attachidx) ;
	objectinfo[THUNDER].rootflm = MV1SearchFrame(thunder,"root") ;
	objectinfo[THUNDER].playtime = 0.0f ;	

	objectinfo[THUNDER + 1].attachidx = MV1AttachAnim(thunder2, 0, thunderdown) ;
	MV1SetFrameUserLocalMatrix(thunder,objectinfo[THUNDER].rootflm,MGetIdent()) ;
	objectinfo[THUNDER + 1].rootflm = MV1SearchFrame(thunder,"root") ;
	MV1SetFrameUserLocalMatrix(thunder,objectinfo[THUNDER + 1].rootflm,MGetIdent()) ;

	// ------------------------------------------------------------------------ // 
	//						�N�b�L�[�摜�ǂݍ���								//
	// ------------------------------------------------------------------------ //
	cookie_pic[0] = MV1LoadModel("..\\Stage\\Clover.mv1");
	cookie_pic[1] = MV1LoadModel("..\\Stage\\Clover.mv1");
	cookie_pic[2] = MV1LoadModel("..\\Stage\\Star.mv1");
	cookie_pic[3] = MV1LoadModel("..\\Stage\\Star.mv1");
	cookie_pic[4] = MV1LoadModel("..\\Stage\\Thunder.mv1");
	cookie_pic[5] = MV1LoadModel("..\\Stage\\Thunder.mv1");
	for(int i = 0; i < MAX_COOKIE; i++){
		if(cookie_pic[i] == -1) return -1; 
	}

	// ------------------------------------------------------------------------ // 
	//							�摜�ǂݍ���									//
	// ------------------------------------------------------------------------ //
	Graph[0] = LoadGraph("..\\Stage\\a.png");
	objectinfo[0].pos = VGet(440.0f,-675.0f,1700.0f) ;
	Graph[1] = LoadGraph("..\\Stage\\select.png");
	Graph[2] = LoadGraph("..\\Stage\\title.png");
	Graph[3] = LoadGraph("..\\Stage\\titlebutton.png");
	Graph[4] = LoadGraph("..\\Stage\\P1P2.png");
	Graph[5] = LoadGraph("..\\Stage\\numB.png");
	Graph[6] = LoadGraph("..\\Stage\\numR.png");
	Graph[7] = LoadGraph("..\\Stage\\mistery.png");
	Graph[8] = LoadGraph("..\\Stage\\timer.png");
	Graph[9] = LoadGraph("..\\Stage\\start.png");
	Graph[10] = LoadGraph("..\\Stage\\change.png");
	Graph[11] = LoadGraph("..\\Stage\\stagechange.png");	// �X�e�[�W�ύX
	Graph[12] = LoadGraph("..\\Stage\\finish.png");	//  finish
	Graph[13] = LoadGraph("..\\Stage\\1PWIN.png");	// winP1
	Graph[14] = LoadGraph("..\\Stage\\2PWIN.png");	// winP2
	return 0;
}