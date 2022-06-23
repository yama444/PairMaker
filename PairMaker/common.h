
/* _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	FILE	: Common.h
	NAME	: TeamA

+ ------ Explanation of file --------------------------------------------------------------------------
       
	�S�Ẵt�@�C���ŋ��ʂ̃w�b�_�[�t�@�C��

+ _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/ */

/* -----------------------------------------------------------------------------------------
|
|       DEFINE�錾
|
+ --------------------------------------------------------------------------------------- */

// FOV
#define FOV 1.0f

// �R���W�������f���̍ő�}�e���A����
#define STAGE_COLLISION_MODEL_MATERIAL_MAX_NUM		(32)

// �L�����N�^�[�̃f�[�^�t�@�C�����i�[����Ă���t�H���_
#define CHARADATA_DIR					"..\\Data\\Character\\"

// �L�����N�^�[�A�j���[�V������FPS
#define CHARA_ANIM_FPS					(30)

// �A�j���[�V�����C�x���g�̃T�E���h�t�@�C���p�X�Ŏg�p�ł���ő啶����
#define ANIM_EVENT_SOUNDPATH_MAX_LENGTH			(64)

// �A�j���[�V�����C�x���g�̍ő吔
#define ANIM_EVENT_MAX_NUM						(64)

// �A�j���[�V�����̃^�C���𐮐��^�ɕϊ�����ۂ̃X�P�[��
#define ANIM_TIME_INT_SCALE						(10000.0f)

// �A�j���[�V�����ōĐ�������ʉ��̃t�@�C�����i�[����Ă���t�H���_
#define ANIM_SE_FILE_DIRECTORY_PATH				"SE\\"
//
//#define SOUND_DIRECTORY_PATH					"..\\Data\\Sound\\"
#define SOUND_DIRECTORY_PATH		"..\\Data\\Sound\\"
// �L�����T�C�Y
#define PC_WIDTH 120.0f
#define PC_HEIGHT 180.0f
#define MAX_PLAYER 2

#define PLAYER_HITOFFX -109.0f
#define PLAYER_HITOFFZ 832.0f 

#define	C3OFFX 0.0f
#define	C3OFFZ 0.0f

#define COOKIE_SIZE 120.5f
#define COOKIE_HITOFFY 300.0f
#define DEBUGC 5

#define MAX_FLY_HEIGHT 0.22f

#define ATTACKWIDTH 90

#define EFFECT_SLASH_WIDTH_MAX 15
#define EFFECT_SLASH_WIDTH_MIN 1
#define EFFECT_SLASH_WIDTH_FRAME 3
#define EFFECT_SLASH_WIDTH_SIZE 200
#define EFFECT_SLASH_HEIGHT_SIZE 200

#define EFFECT_SLASH_RADIAN 315

#define CHARA_ENUM_DEFAULT_SIZE		500.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
#define CHARA_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔

#define CHARA_HIT_HEIGHT			700.0f		// �����蔻��J�v�Z���̍���

#define walkspeed					5.0f
#define upperspeed					2.0f

#define BACKMULTI					12

#define MAX_COOKIE					6
#define MAX_SOUND					40

#define MAX_FLIPS                   4
#define MAX_LOOP                    100

// �N�b�L�[���Ђ�����Ԃ�܂ł̕ێ�����
#define STAYTIME                    40
#define CookieY						-430.0f

#define RESETTIME					100

#define MAX_BOWL 5

// objectinfo �萔
#define RANGE    0
#define BOWL    15	// ~20
#define THUNDER 25 //25 26
#define EFFSTAR  30// ~24

#define MAX_WALL 1

// �Q�ʈڍs
#define SCEENWAIT 45			
//#define SCEENWAIT 89			
//#define SCEENWAIT 1			

#define P1COLOR GetColorF( 0.2f, 0.4f, 1.0f, 1.0f )
#define P2COLOR GetColorF( 1.0f, 0.4f, 0.2f, 1.0f )
#define NORMALCOLOR GetColorF( 1.0f, 1.0f, 1.0f, 1.0f )
#define THUNDERCOLOR GetColorF( 0.0f, 0.0f, 0.0f, 1.0f )
#define THUNDERMODELCOLOR GetColorF(1.0f,1.0f,0.5,1.0f)
#define METALCOLOR GetColorF( 0.7f, 0.4f, 0.4f, 1.0f )
#define BURNCOLOR  GetColorF( 0.13f, 0.01f, 0.01f, 1.0f )
#define BLACKCOLOR  GetColorF( 0.0f, 0.0f, 0.0f, 1.0f )
#define REDCOLOR  GetColorF( 1.0f, 0.3f, 0.3f, 1.0f )
#define BLUECOLOR  GetColorF( 0.3f, 0.3f, 1.0f, 1.0f )

#define Selectpos_1 VGet(76.935f* 7,-210.1111f,80.785f)
#define Selectpos_2 VGet(76.935f* 7,-250.1111f,80.785f)
#define Selectpos1_1 VGet(36.935f* 7,-320.1111f,80.785f)
#define Selectpos1_2 VGet(36.935f* 7,-360.1111f,80.785f)
#define Selectpos2_1 VGet(119.932f* 7,-320.1111f,80.785f)
#define Selectpos2_2 VGet(119.932f* 7,-360.1111f,80.785f)

#define DOWNCOOLTIME 30

/*Result*/
#define MAXTIME						300
#define BROWNCOLOR GetColorF( 0.0f , 0.50f , 0.86f , 0.18f )
#define RESULTCOLOR GetColorF( 0.3f , 0.01f , 0.01f , 0.0f )
#define CHARACOLOR GetColorF( 0.5f , 0.5f , 0.5f , 0.5f )

#define P1POSX 98.0f
#define P1POSZ 353.0f
#define P2POSX 798.0f
#define P2POSZ P1POSZ

#define MAXLEFT  -52.0f
#define MAXRIGHT 977.0f
#define MAXUP    986.0f
#define MAXDOWN  -50.0f

/* -----------------------------------------------------------------------------------------
|
|       ���ʃw�b�_�[
|
+ --------------------------------------------------------------------------------------- */
#include <DxLib.h>

#include "math.h"
#include <ctime>        // time
#include <cstdlib>      // srand,rand	

/* -----------------------------------------------------------------------------------------
|
|       �^�錾
|
+ --------------------------------------------------------------------------------------- */
// --- �V�[���̖��O
enum SceneName
{
	eSceneBlank = -1 ,
	eSceneBlank2,
	eSceneTitleInit,
	eSceneTitle ,
	eSceneInit,
	eSceneCharasel,
	eScenePlayInit,
	eScenePlay ,
	eSceneOver ,
	eSceneEnd,
} ;

// --- �L�����̕���
enum Direction
{
	DOWNRIGHT = 1,
	DOWN,     //2
	DOWNLEFT, //3
	LEFT,     //4   2
	UPLEFT,   //5
	UP,       //6
	UPRIGHT,  //7
	RIGHT     //8
};


// --- �L�����̏��
enum CharaMode
{
	STAND,
	RUN,
	JUMPIN,
	JUMPLOOP,
	JUMPOUT,
	FALL,
	ATTACK,
	DAMAGE,
} ;

/* -----------------------------------------------------------------------------------------
|
|       �\���̐錾
|
+ --------------------------------------------------------------------------------------- */
// �L�����N�^�[�̓����蔻��̏��
typedef struct _SCharaHitInfo
{
	// �����蔻��̕�
	float                 Width;

	// �����蔻��̍���
	float                 Height;

	// �����蔻��̒��S���W
	VECTOR                CenterPosition;
} SCharaHitInfo;

// �L�������\����
typedef struct _CharaInfo{
	int				model1 ;			// �L�����̃��f�����i�[
	int				chara ;
	int				mode ;				// �L�����̏��
	int				attachidx ;			// �L�����̌��݂̃A�j���[�V�������i�[�i�A�^�b�`�j
	float			anim_totaltime ;	// �A�j���̃g�[�^���A�j��
	float			playtime ;			// �A�j���Đ�����
	int				rootflm ;			// �A�j���̃��[�g
	VECTOR			pos ;				// �L�����̍��W x,y,z
	VECTOR			move ;				// �L�����̈ړ��� x,y,z
	int				direction ;			// �L�����̌���
	SCharaHitInfo	charahitinfo ;		// �L�����q�b�g�`�F�b�N�p���
	int				Selcookie[3];		// �I��ł���N�b�L�[��I��			
	int				getcookie;			// �N�b�L�[�̎擾��
	VECTOR          upper;
	BOOL            stay;				// �N�b�L�[��I��
	float           bdown;				// �Ђ�����Ԃ�{�^���������A�j��
	BOOL			bdownF;				// ��̃t���O
	BOOL			sunder;				// ���𗎂Ƃ�
} SCharaInfo ;

//	�N�b�L�[���\����
typedef struct _CookieInfo{
	int				cookienum;			//	�N�b�L�[�̔ԍ�	
	int				cookieplacenum;		//	�N�b�L�[�̏ꏊ�ԍ�
	VECTOR			cookiepos;
	int				attachidx ;			// �L�����̌��݂̃A�j���[�V�������i�[�i�A�^�b�`�j
	float			anim_totaltime ;	// �A�j���̃g�[�^���A�j��
	float			playtime ;			// �A�j���Đ�����
	int				rootflm ;			// �A�j���̃��[�g
	char			Flipflag ;			// �N�b�L�[��]�̃t���O
	char			stay;				// �N�b�L�[��\�ɕԂ����̃t���O
	char			staytime;			// �N�b�L�[�̗�����\���������鎞��
	char			deletestaytime;		// �N�b�L�[�̗�����\���������鎞��
	BOOL			fliped;				// �I�΂ꂽ�t���O
	char			sunder;				// ���𗎂Ƃ�
	BOOL            effect;				// �G�t�F�N�g���sflag
} SCookieInfo ;

typedef struct _ObjectInfo{
	VECTOR			pos;
	int				attachidx ;			// �L�����̌��݂̃A�j���[�V�������i�[�i�A�^�b�`�j
	float			anim_totaltime ;	// �A�j���̃g�[�^���A�j��
	float			playtime ;			// �A�j���Đ�����
	int				rootflm ;			// �A�j���̃��[�g
} SObjectInfo ;



/* -----------------------------------------------------------------------------------------
|
|       �v���g�^�C�v�錾
|
+ --------------------------------------------------------------------------------------- */
int InitSet( void );
int charainit();
void Mixer( void ) ;
int charactorMove( void );
int charactorMove2( void );
int cookieflip( void );
int flip( void );
int cookiechecker( void );
void Animset();
void PlayerFly();
void upper();
int timer(void);
void playerhitcheck();
int FlipCnt();
int ChangeScreen();
int SelCharaInclude();
void EffectAct();
/* -----------------------------------------------------------------------------------------
|
|       �O���Q�Ɛ錾
|
+ --------------------------------------------------------------------------------------- */
extern	SCharaInfo charainfo[10];							//
extern  SCookieInfo cookieinfo[MAX_COOKIE];					//
extern  SObjectInfo objectinfo[40];							//
extern  int cookie_pic[20];
extern 	int anim_natural, cookie_flip, Cookie_flip_Star, Cookie_flip_Heart, Cookie_flip_Square, 
	Pmove, Pstay, Pwin, P2move, P2stay, P2win, P3move, P3stay, P3win, rangeanim, bowlanim,
	heatM,
	crosshair[2],
	thunderdown;		//
extern  int	Graph[40];										// �摜
extern 	int		   key ;								    // �擾�L�[�̊i�[
extern 	int		   key2 ;								    // �擾�L�[�̊i�[
extern  BOOL       roolflipF[2];								
extern 	int plate, table, pancake, pancake2, egg, Sfloor[1], cookie[MAX_COOKIE], thunder, thunder2, range, milk, bowl[MAX_BOWL], lack, reizo;		//	�X�e�[�W���f��
extern  int soundh[MAX_SOUND];
extern  int getcookiecnt;
extern  int gamemaintimer;
extern  int gamesubtimer;
extern  int characterselect[7];
extern int  efstar[MAX_COOKIE];
extern VECTOR Stg2cookie[MAX_COOKIE]; //  �Q�ʗp�N�b�L�[
extern char resetwaittime;

extern float cookieColl[MAX_COOKIE][2];


