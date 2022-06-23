
/* _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	FILE	: Common.h
	NAME	: TeamA

+ ------ Explanation of file --------------------------------------------------------------------------
       
	全てのファイルで共通のヘッダーファイル

+ _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/ */

/* -----------------------------------------------------------------------------------------
|
|       DEFINE宣言
|
+ --------------------------------------------------------------------------------------- */

// FOV
#define FOV 1.0f

// コリジョンモデルの最大マテリアル数
#define STAGE_COLLISION_MODEL_MATERIAL_MAX_NUM		(32)

// キャラクターのデータファイルが格納されているフォルダ
#define CHARADATA_DIR					"..\\Data\\Character\\"

// キャラクターアニメーションのFPS
#define CHARA_ANIM_FPS					(30)

// アニメーションイベントのサウンドファイルパスで使用できる最大文字数
#define ANIM_EVENT_SOUNDPATH_MAX_LENGTH			(64)

// アニメーションイベントの最大数
#define ANIM_EVENT_MAX_NUM						(64)

// アニメーションのタイムを整数型に変換する際のスケール
#define ANIM_TIME_INT_SCALE						(10000.0f)

// アニメーションで再生する効果音のファイルが格納されているフォルダ
#define ANIM_SE_FILE_DIRECTORY_PATH				"SE\\"
//
//#define SOUND_DIRECTORY_PATH					"..\\Data\\Sound\\"
#define SOUND_DIRECTORY_PATH		"..\\Data\\Sound\\"
// キャラサイズ
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

#define CHARA_ENUM_DEFAULT_SIZE		500.0f		// 周囲のポリゴン検出に使用する球の初期サイズ
#define CHARA_MAX_HITCOLL			2048		// 処理するコリジョンポリゴンの最大数

#define CHARA_HIT_HEIGHT			700.0f		// 当たり判定カプセルの高さ

#define walkspeed					5.0f
#define upperspeed					2.0f

#define BACKMULTI					12

#define MAX_COOKIE					6
#define MAX_SOUND					40

#define MAX_FLIPS                   4
#define MAX_LOOP                    100

// クッキーがひっくり返るまでの保持時間
#define STAYTIME                    40
#define CookieY						-430.0f

#define RESETTIME					100

#define MAX_BOWL 5

// objectinfo 定数
#define RANGE    0
#define BOWL    15	// ~20
#define THUNDER 25 //25 26
#define EFFSTAR  30// ~24

#define MAX_WALL 1

// ２面移行
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
|       共通ヘッダー
|
+ --------------------------------------------------------------------------------------- */
#include <DxLib.h>

#include "math.h"
#include <ctime>        // time
#include <cstdlib>      // srand,rand	

/* -----------------------------------------------------------------------------------------
|
|       型宣言
|
+ --------------------------------------------------------------------------------------- */
// --- シーンの名前
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

// --- キャラの方向
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


// --- キャラの状態
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
|       構造体宣言
|
+ --------------------------------------------------------------------------------------- */
// キャラクターの当たり判定の情報
typedef struct _SCharaHitInfo
{
	// 当たり判定の幅
	float                 Width;

	// 当たり判定の高さ
	float                 Height;

	// 当たり判定の中心座標
	VECTOR                CenterPosition;
} SCharaHitInfo;

// キャラ情報構造体
typedef struct _CharaInfo{
	int				model1 ;			// キャラのモデルを格納
	int				chara ;
	int				mode ;				// キャラの状態
	int				attachidx ;			// キャラの現在のアニメーションを格納（アタッチ）
	float			anim_totaltime ;	// アニメのトータルアニメ
	float			playtime ;			// アニメ再生時間
	int				rootflm ;			// アニメのルート
	VECTOR			pos ;				// キャラの座標 x,y,z
	VECTOR			move ;				// キャラの移動量 x,y,z
	int				direction ;			// キャラの向き
	SCharaHitInfo	charahitinfo ;		// キャラヒットチェック用情報
	int				Selcookie[3];		// 選んでいるクッキーを選択			
	int				getcookie;			// クッキーの取得数
	VECTOR          upper;
	BOOL            stay;				// クッキーを選択中
	float           bdown;				// ひっくり返るボタン押したアニメ
	BOOL			bdownF;				// 上のフラグ
	BOOL			sunder;				// 雷を落とす
} SCharaInfo ;

//	クッキー情報構造体
typedef struct _CookieInfo{
	int				cookienum;			//	クッキーの番号	
	int				cookieplacenum;		//	クッキーの場所番号
	VECTOR			cookiepos;
	int				attachidx ;			// キャラの現在のアニメーションを格納（アタッチ）
	float			anim_totaltime ;	// アニメのトータルアニメ
	float			playtime ;			// アニメ再生時間
	int				rootflm ;			// アニメのルート
	char			Flipflag ;			// クッキー回転のフラグ
	char			stay;				// クッキーを表に返すかのフラグ
	char			staytime;			// クッキーの裏側を表示し続ける時間
	char			deletestaytime;		// クッキーの裏側を表示し続ける時間
	BOOL			fliped;				// 選ばれたフラグ
	char			sunder;				// 雷を落とす
	BOOL            effect;				// エフェクト実行flag
} SCookieInfo ;

typedef struct _ObjectInfo{
	VECTOR			pos;
	int				attachidx ;			// キャラの現在のアニメーションを格納（アタッチ）
	float			anim_totaltime ;	// アニメのトータルアニメ
	float			playtime ;			// アニメ再生時間
	int				rootflm ;			// アニメのルート
} SObjectInfo ;



/* -----------------------------------------------------------------------------------------
|
|       プロトタイプ宣言
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
|       外部参照宣言
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
extern  int	Graph[40];										// 画像
extern 	int		   key ;								    // 取得キーの格納
extern 	int		   key2 ;								    // 取得キーの格納
extern  BOOL       roolflipF[2];								
extern 	int plate, table, pancake, pancake2, egg, Sfloor[1], cookie[MAX_COOKIE], thunder, thunder2, range, milk, bowl[MAX_BOWL], lack, reizo;		//	ステージモデル
extern  int soundh[MAX_SOUND];
extern  int getcookiecnt;
extern  int gamemaintimer;
extern  int gamesubtimer;
extern  int characterselect[7];
extern int  efstar[MAX_COOKIE];
extern VECTOR Stg2cookie[MAX_COOKIE]; //  ２面用クッキー
extern char resetwaittime;

extern float cookieColl[MAX_COOKIE][2];


