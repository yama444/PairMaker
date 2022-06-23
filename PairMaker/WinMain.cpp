
#include <windows.h>
#include "Common.h"		// --- 全ファイルでの共通ヘッダー
#include <time.h>

int WINAPI WinMain(HINSTANCE hI,HINSTANCE hP,LPSTR lpC,int nC){

	// -------------------------------------------------------------------------------------------- //
	//                                             変数宣言                                         //
	// -------------------------------------------------------------------------------------------- //
	// 全体的なゲームの管理
	int gamemode = eSceneBlank ;
	// ステージ管理
	int stageflg = 0;
	//  追加ライトハンドル
	int LightHandle;
	// タイマー
	int maintimer;
	//	クッキーが外れたときのひっくり返しフラグ
	BOOL offF[3] = {FALSE, FALSE, FALSE}; 				
	// キャラ吹き飛ばしのカウンター
	static char upperNum = 0;						
	// キャラ選択番号
	char charasel[2] = {0,0};
	//  クッキー回転
	float Trote = 0.12f;
	//  クッキー回転フラグ
	int  TroteC = 0;
	//  クッキー回転フラグ
	BOOL  TroteF = FALSE;
	// キャラ選択で連続入力させないように
	BOOL first[2] = {FALSE, FALSE};						
	// フルスク管理
	BOOL fullscreen = 1;								
	//  シャドウマップハンドル
	int ShadowMapHandle ;
	//  シーン切り替え時間
	char sceentime = 0;
	// クッキーデリートタイム
	char delettime = 0;										
	//  パンケーキアニメーション時間
	float pancakeA = 0.0f;
	// パンケーキアニメ切り替えフラグ
	BOOL  pancakeAF = FALSE;			
	//  クッキー移動角度(2面)
	int   circleAngle;
	//  reset
	int resetcnt = 0;
	//  ?
	int fl[2] = {0,0};
	// charasel時のローテーション
	float chararote[2] = {0,0};
	// charasel時のローテーション
	float chararote1[2] = {0,0};
	// charasel時のローテーション
	float chararote2[2] = {0,0};
	char titleF = FALSE;
	long titlecnt = 0;

	// 点滅遅らせ
	int delay = 0;
	int delay2 = 20;
	int cnt = 0 ;
	int cnt2 = 0 ;
	BOOL flipdraw[2] = {FALSE,FALSE};
	// 選択カーソルの移動
	BOOL charactersetcheck[2] = {FALSE,FALSE};
	// キーが押されるまで選択カーソルがでない
	BOOL selectdrawflg[2]= {FALSE,FALSE};
	// 始めるかのチェック
	BOOL okflg[2] = {FALSE,FALSE};
	BOOL plyblin[2] = {FALSE,FALSE};
	BOOL seleweight[2] ={FALSE,FALSE};

	int waittimer = 0 ;
	int cookiestaytime = 0 ;
	BOOL resultsetflg = FALSE;

	//ステージのポジション
	VECTOR pancakepos  = VGet(440.0f,-555.0f,690.0f) ;
	VECTOR pancake2pos = VGet(2500.0f,-675.0f,600.0f) ;
	VECTOR platepos    = VGet(90.0f,-1000.0f,900.0f) ;
	VECTOR tablepos    = VGet(600.0f,-10050.0f,5200.0f) ;
	VECTOR eggpos	   = VGet(-800.0f,-805.0f,1800.0f) ;
	VECTOR milkpos	   = VGet(-690.0f,-1205.0f,4400.0f) ;
	VECTOR bowlpos[MAX_BOWL];
	VECTOR Sfloorpos[MAX_WALL];
	Sfloorpos[0]   = VGet(440.0f,-475.0f,5000.0f) ;
	VECTOR rangepos = VGet(600.0f,50.0f,900.0f);	// レンジ

	// ------------------------------------------------------------------------ // 
	//							ウィンドウ設定									//
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

	// DXライブラリの初期化
	if(DxLib_Init() == -1) return -1 ;

	// ------------------------------------------------------------------------- // 
	//						カメラポジションセット			                     //
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
				//							フォント読み込み					             //
				// ------------------------------------------------------------------------- // 
				SetFontThickness(7); //0-9 
				SetFontSize(64);
				ChangeFont("Wide Latin");

				// サウンドデータタイプ
				SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);

				// Loading
				ClearDrawScreen();
				DrawString(700,600,"Loading...",RGB(255,255,255),TRUE);
				ScreenFlip();

				// シャドウマップハンドルの作成
				ShadowMapHandle = MakeShadowMap( 1024, 1024 ) ;

				// 描画する奥行き方向の範囲を設定
				SetCameraNearFar( 1.000f, 20000.000f );

				// ライトの方向を設定
				SetLightDirection( VGet( 0.6f, -0.5f, 0.5f ) );

				// シャドウマップが想定するライトの方向もセット
				SetShadowMapLightDirection( ShadowMapHandle, VGet( 0.5f, -0.5f, 0.5f ) ) ;

				// シャドウマップに描画する範囲を設定
				SetShadowMapDrawArea( ShadowMapHandle, VGet( -1000.0f, -1.0f, -1000.0f ), VGet( 1000.0f, 1000.0f, 1000.0f )) ;
				
				// 初期セット
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
				//タイトル処理
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
				//						クッキーポジションセット		                     //
				// ------------------------------------------------------------------------- // 
				// クッキーのポジション
				// 丸
				cookieinfo[0].cookiepos  = VGet(100.0f, CookieY - 000.0f, 275.0f);		// 左下
				cookieinfo[1].cookiepos  = VGet(450.0f, CookieY + 000.0f, 921.0f);		// 上
				cookieinfo[2].cookiepos  = VGet(800.0f, CookieY - 000.0f, 275.0f);		// 右下

				// 星
				cookieinfo[3].cookiepos  = VGet(450.0f, CookieY - 000.0f, 275.0f);		// 真ん中	
				cookieinfo[4].cookiepos  = VGet(650.0f, CookieY - 000.0f, 598.0f);		// 中右
				cookieinfo[5].cookiepos  = VGet(250.0f, CookieY - 000.0f, 598.0f);		// 中左

				// ゲームのタイマー設定
				gamemaintimer = 93;
/**/
//gamemaintimer = 65;
//gamemaintimer = 1;
//gamemaintimer = 2;
/**/				gamesubtimer = 0;
				// ステージ管理
				stageflg = 0;
				// タイマー
				maintimer = 90;
				//	クッキーが外れたときのひっくり返しフラグ
				offF[0] = FALSE; 				
				offF[1] = FALSE; 				
				offF[2] = FALSE; 				
				// キャラ吹き飛ばしのカウンター
				upperNum = 0;						
				// キャラ選択番号
				charasel[0] = 0;
				charasel[1] = 0;
				//  クッキー回転
				Trote = 0.12f;
				//  クッキー回転フラグ
				TroteC = 0;
				//  クッキー回転フラグ
				TroteF = FALSE;
				// キャラ選択で連続入力させないように
				first[0] = FALSE;
				first[1] = FALSE;
				// フルスク管理
				fullscreen = 1;								
				//  シーン切り替え時間
				sceentime = 0;
				// クッキーデリートタイム
				delettime = 0;										
				//  パンケーキアニメーション時間
				pancakeA = 0.0f;
				// パンケーキアニメ切り替えフラグ
				pancakeAF = FALSE;
				key = 0;
				key2 = 0;
				platepos = VGet(90.0f,-1000.0f,900.0f) ;
				// stage1camセット
				cpos3 = VGet(550.0f,-80.0f,-380.0f) ;
				ctgt3 = VGet(550.0f,-100.0f,50.0f) ;
				cpos2 = VGet(440.0f,100.0f,-320.0f) ;
				ctgt2 = VGet(440.0f,-150.0f,50.0f) ;
				cpos = VGet(440.0f,500.0f,-10020.0f) ;
				ctgt = VGet(440.0f,-150.0f,50.0f) ;
				// タイマーの初期セット
				maintimer = 9999;
				getcookiecnt = 0;
				//	クッキーが外れたときのひっくり返すフラグ
				offF[0] = FALSE; 
				offF[1] = FALSE; 
				offF[2] = FALSE; 
				//ステージのポジション
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
						// 選択カーソルの移動
					charactersetcheck[P] = FALSE;
						// キーが押されるまで選択カーソルがでない
					selectdrawflg[P] = FALSE;
						// 始めるかのチェック
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
			//	 	 	 	 	 	 	 	 キャラ選択画面 	 	 	 	 	 	  //
			// ---------------------------------------------------------------------- */
			case eSceneCharasel:
				// カメラ設定
				SetCameraPositionAndTargetAndUpVec(cpos3,ctgt3,VGet(0.0f,0.0f,1.0f)) ;
				while(1){		
					// 無限ループ
					key = GetJoypadInputState(DX_INPUT_KEY_PAD1);				// 1P 
				//	key = GetJoypadInputState(DX_INPUT_PAD1) ;
					key2 = GetJoypadInputState(DX_INPUT_PAD2);					// 2P

					if((key & PAD_INPUT_LEFT || key & PAD_INPUT_RIGHT) && (first[0] == FALSE && first[1] == FALSE)){
						PlaySoundMem( soundh[14] , DX_PLAYTYPE_BACK ) ;
					}
					if((key2 & PAD_INPUT_LEFT || key2 & PAD_INPUT_RIGHT) && (first[0] == FALSE && first[1] == FALSE)){
						PlaySoundMem( soundh[14] , DX_PLAYTYPE_BACK ) ;
					}
					
					if(key & PAD_INPUT_LEFT && first[0] == FALSE && seleweight[0] != TRUE ){				// 1P左入力時
						charasel[0]++;
 						if(charasel[0] == 3){
							charasel[0] = 0;
						}
						first[0] = TRUE;
					}else if(key & PAD_INPUT_LEFT && first[0] == FALSE && seleweight[0] != FALSE){			// ゲームを始めるか入力
						if(selectdrawflg[0] != FALSE && okflg[0] != TRUE){
							charactersetcheck[0]++;
							if(charactersetcheck[0] == 2){
								charactersetcheck[0] = 0;
							}
							first[0] = TRUE;
						}
						selectdrawflg[0] = 1;
					}
					if(key & PAD_INPUT_RIGHT && first[0] == FALSE && seleweight[0] != TRUE){				// 1P右入力時
						charasel[0]--;
						if(charasel[0] == -1){
							charasel[0] = 2;
						}
						first[0] = TRUE;
					}else if(key & PAD_INPUT_RIGHT && first[0] == FALSE && seleweight[0] != FALSE){			// ゲームを始めるか入力
						if(selectdrawflg[0] != FALSE && okflg[0] != TRUE){
							charactersetcheck[0]--;
							if(charactersetcheck[0] == -1){
								charactersetcheck[0] = 1;
							}
							first[0] = TRUE;
						}
						selectdrawflg[0] = 1;
					}
					if(key & PAD_INPUT_B && first[0] == FALSE){		//○
						if(	seleweight[1] == TRUE && charasel[1] == charasel[0] ){		// 相手と同じキャラだったら選べない
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

					if(key2 & PAD_INPUT_LEFT && first[1] == FALSE && seleweight[1] != TRUE){				// 2P左入力時
						charasel[1]++;
 						if(charasel[1] == 3){
							charasel[1] = 0;
						}
						first[1] = TRUE;
					}else if(key2 & PAD_INPUT_LEFT && first[1] == FALSE && seleweight[1] != FALSE){			// ゲームを始めるか入力
						if(selectdrawflg[1] != FALSE && okflg[1] != TRUE){
							charactersetcheck[1]++;
							if(charactersetcheck[1] == 2){
								charactersetcheck[1] = 0;
							}
							first[1] = TRUE;
						}
						selectdrawflg[1] = 1;
					}

					if(key2 & PAD_INPUT_RIGHT && first[1] == FALSE && seleweight[1] != TRUE){			// 2P右入力時
						charasel[1]--;
						if(charasel[1] == -1){
							charasel[1] = 2;
						}
						first[1] = TRUE;
					}else if(key2 & PAD_INPUT_RIGHT && first[1] == FALSE && seleweight[1] != FALSE){	// ゲームを始めるか入力
						if(selectdrawflg[1] != FALSE && okflg[1] != TRUE){
							charactersetcheck[1]--;
							if(charactersetcheck[1] == -1){
								charactersetcheck[1] = 1;
							}
							first[1] = TRUE;
						}
						selectdrawflg[1] = 1;
					}
					if(key2 & PAD_INPUT_B && first[1] == FALSE){		//○
						if(	seleweight[0] == TRUE && charasel[0] == charasel[1] ){		// 相手と同じキャラだったら選べない
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


					charainfo[0].chara = charasel[0];									// 1P決定キャラ代入
					charainfo[1].chara = charasel[1];									// 2P決定キャラ代入

					// ゲーム画面に移行
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
						(charactersetcheck[0] == TRUE || charactersetcheck[1] == TRUE)){		// リセット
						for(int i = 0; i < 2 ; i++){
								charasel[i] = 0;
								fl[i] = 0;
							// charasel時のローテーション
							chararote[i] = 0;
							// charasel時のローテーション
							chararote1[i] = 0;
							// charasel時のローテーション
							chararote2[i] = 0;
							// キャラクター選択flag
							seleweight[i] = FALSE;
							// 1P　2Pの点滅flag
							plyblin[i] = FALSE;
							// 点滅遅らせ
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
						// スケール設定
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
							MV1SetScale(Sfloor[0],VGet(23.0f,12.0f,20.0f));								//	壁
						}else{
							MV1SetScale(Sfloor[0],VGet(23.0f,13.0f,20.0f));								//	壁
						}
						MV1SetScale(cookie[1],VGet(1.0f,1.8f,1.0f));									//	1Pクッキー
						MV1SetScale(cookie[2],VGet(1.0f,1.8f,1.0f));									//	2Pクッキー

						//  アニメーションの値を加算
						for(char P = 0; P < MAX_PLAYER; P++){
							if(charainfo[charasel[P] + 2].playtime <= charainfo[charasel[P] + 2].anim_totaltime){
								charainfo[charasel[P] + 2].playtime += 0.8f;
							}else{
								charainfo[charasel[P] + 2].playtime = 0.0f;
							}
						}
						// アニメーションのアタッチ
						MV1SetAttachAnimTime(charainfo[charasel[0] + 2].model1, charainfo[charasel[0] + 2].attachidx, charainfo[charasel[0] + 2].playtime) ;
						MV1SetAttachAnimTime(charainfo[charasel[1] + 2].model1, charainfo[charasel[1] + 2].attachidx, charainfo[charasel[1] + 2].playtime) ;

						// キャラクターの選択中ローテーション
						for(char P = MAX_PLAYER; P < MAX_PLAYER + 3; P++){							
							if(charasel[0] + 2 == P){
								switch(P) {
									case 2:
										MV1SetPosition(cookie[1],Selectpos_1);
										chararote1[0] = 0.0f;
										chararote2[0] = 0.0f;
										chararote[0] += 0.01f;
										MV1SetRotationXYZ(charainfo[2].model1,VGet(0.0f,1.5f + chararote[0],0.0f)) ;			//	せんくうキャラクターの移動回転 & クッキーの移動
										break;
									case 3:
										MV1SetPosition(cookie[1],Selectpos1_1);
										chararote[0] = 0.0f;
										chararote2[0] = 0.0f;
										chararote1[0] += 0.01f;
										MV1SetRotationXYZ(charainfo[3].model1,VGet(0.0f,1.2f + chararote1[0],0.0f)) ;			//	イチゴキャラクターの移動回転 & クッキーの移動
										break;
									case 4:
										MV1SetPosition(cookie[1],Selectpos2_1);
										chararote[0] = 0.0f;
										chararote1[0] = 0.0f;
										chararote2[0] += 0.01f;
										MV1SetRotationXYZ(charainfo[4].model1,VGet(0.0f,1.9f + chararote2[0],0.0f)) ;			//	コックキャラクターの移動回転 & クッキーの移動
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
										MV1SetRotationXYZ(charainfo[2].model1,VGet(0.0f,1.5f + chararote[1],0.0f)) ;			//	キャラクターの移動回転
										break;
									case 3:
										MV1SetPosition(cookie[2],Selectpos1_2);
										chararote[1] = 0.0f;
										chararote1[1] += 0.01f;
										chararote2[1] = 0.0f;
										MV1SetRotationXYZ(charainfo[3].model1,VGet(0.0f,1.2f + chararote1[1],0.0f)) ;			//	キャラクターの移動回転
										break;
									case 4:
										MV1SetPosition(cookie[2],Selectpos2_2);
										chararote[1] = 0.0f;
										chararote1[1] = 0.0f;
										chararote2[1] += 0.01f;
										MV1SetRotationXYZ(charainfo[4].model1,VGet(0.0f,1.9f + chararote2[1],0.0f)) ;			//	キャラクターの移動回転
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
										MV1SetRotationXYZ(charainfo[2].model1,VGet(0.0f,1.5f + chararote[0],0.0f)) ;			//	キャラクターの移動回転
										break;
									case 3:
										chararote1[0] = 0.0f;
										chararote1[1] = 0.0f;
										MV1SetRotationXYZ(charainfo[3].model1,VGet(0.0f,1.2f + chararote1[0],0.0f)) ;			//	キャラクターの移動回転
										break;
									case 4:
										chararote2[0] = 0.0f;
										chararote2[1] = 0.0f;
										MV1SetRotationXYZ(charainfo[4].model1,VGet(0.0f,1.9f + chararote2[0],0.0f)) ;			//	キャラクターの移動回転
										break;
								}
							}
						}

						MV1SetRotationXYZ(cookie[1],VGet(0.4f,0.0f,0.0f)) ;			//	キャラクターの移動回転
						MV1SetRotationXYZ(cookie[2],VGet(0.4f,0.0f,0.0f)) ;			//	キャラクターの移動回転
						for(int i = 0;i < MAX_WALL; i++){
							MV1SetRotationXYZ(Sfloor[i],VGet(0.0f,1.57f*2,0.0f)) ;											//	壁の回転
						}
						MV1SetPosition(charainfo[2].model1, VGet(76.935f* 7,90.111f,80.785f ) );
						MV1SetPosition(charainfo[3].model1,	VGet(37.935f* 7,-190.1111f,80.785f ) );
						MV1SetPosition(charainfo[4].model1, VGet(119.935f* 7,-210.1111f,80.785f ));
						MV1SetPosition(Sfloor[0],VGet(119.935f* 7,2210.1111f,5000.785f ));

						ClearDrawScreen() ;
						for(char i = 0; i < 1;i++){
							MV1DrawModel(Sfloor[i]) ;
						}
						MV1DrawModel(charainfo[2].model1) ;				// せんくうもどき
						MV1DrawModel(charainfo[3].model1) ;				// イチゴ
						MV1DrawModel(charainfo[4].model1) ;				// コック

						if(cnt == 599){
							cnt = 0;
						}else{
							cnt++ ;
						}
						// 1P 2Pの選択中点滅
						if(cnt%15 == 0){
							for(char i = 0; i  < MAX_PLAYER; i++){
								if( flipdraw[i] == TRUE){
									flipdraw[i] = FALSE;
								}else{
									flipdraw[i] = TRUE;
								}
							}
						}									

						// 同じキャラを選択していた場合の処理
						switch(charasel[0]){							// select文字
							case 0:										// せんくう上表示
								if(charasel[0] == 0 && charasel[1] == 0)
								{
									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(470,20,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(470,20,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(620,20,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(620,20,"P2",GetColor(255,60,0));
									}

								}else{
									if(plyblin[0] != TRUE){				// 1P単体
										if(flipdraw[0] == FALSE){
											DrawString(540,20,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(540,20,"P1",GetColor(0,20,255));		
									}
								}
								break;
							case 1:										// イチゴ上表示
								if(charasel[0] == 1 && charasel[1] == 1)
								{

									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(100,200,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(100,200,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(250,200,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
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
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(180,200,"P1",GetColor(0,20,255));
									}
								}
								break;
							case 2:										// コック上表示
								if(charasel[0] == 2 && charasel[1] == 2)
								{
									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(890,200,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(890,200,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(1040,200,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
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
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(965,200,"P1",GetColor(0,20,255));
									}
								}
								break;
						}
						switch(charasel[1]){							// 2P
							case 0:										// せんくう上表示
								if(charasel[0] == 0 && charasel[1] == 0)
								{
									if(plyblin[0] != TRUE){
										if(flipdraw[0] == FALSE){
											DrawString(470,20,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(470,20,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){
										if(flipdraw[1] == FALSE){
											DrawString(620,20,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
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
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(540,20,"P2",GetColor(255,60,0));
									}
								}
								break;
							case 1:										// イチゴ上表示
								if(charasel[0] == 1 && charasel[1] == 1)
								{
									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(100,200,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(100,200,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(250,200,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(250,200,"P2",GetColor(255,60,0));
									}

									if(plyblin[1] != TRUE){
										if(flipdraw[1] == FALSE){
											DrawString(250,200,"P2",GetColor(255,60,0));		
										}
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
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
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(180,200,"P2",GetColor(255,60,0));		
									}
								}
								break;
							case 2:										// コック上表示
								if(charasel[0] == 2 && charasel[1] == 2)
								{
									if(plyblin[0] != TRUE){				// 1P
										if(flipdraw[0] == FALSE){
											DrawString(890,200,"P1",GetColor(0,20,255));		
										}
										if(seleweight[0] != FALSE){						//　決定ボタン押下後
											plyblin[0] = TRUE;
										}
									}else{
										DrawString(890,200,"P1",GetColor(0,20,255));		
									}

									if(plyblin[1] != TRUE){				// 2P
										if(flipdraw[1] == FALSE){
											DrawString(1040,200,"P2",GetColor(255,60,0));
										}
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
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
										if(seleweight[1] != FALSE){						//　決定ボタン押下後
											plyblin[1] = TRUE;
										}
									}else{
										DrawString(965,200,"P2",GetColor(255,60,0));		
									}
								}
								break;
						}

						// Coment
						if(seleweight[0] == TRUE && seleweight[1] == TRUE ){						// ゲーム前の最終チェック
//						if(seleweight[0] == TRUE){						// ゲーム前の最終チェック
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
				メイン処理
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


				// カメラ移動
				if(stageflg == 1){	// ぬるぬるカメラのほう	
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
			
				// 移動値の初期化
				charainfo[0].move.x = 0.0f;
				charainfo[0].move.y = 0.0f;
				charainfo[0].move.z = 0.0f;
				charainfo[1].move.x = 0.0f;
				charainfo[1].move.y = 0.0f;
				charainfo[1].move.z = 0.0f;

/*
				// 一枚でも表であれば進んでいるというフラグ
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

				// リセットReset
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
								if(charactorMove() == -1){								// リセット処理
//									gamemode = eSceneTitleInit;
								}
							}
							if(charainfo[1].upper.x == 0.0f || charainfo[1].upper.z == 0.0f){
								if(charactorMove2() == -1){								// リセット処理
//									gamemode = eSceneTitleInit;
								}
							}
						}
					}
					cookieflip();													// クッキーのフリップ処理
				}
				switch(cookiechecker()){														//  クッキーの正誤判定
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

				// キー操作				
				if(charainfo[0].mode == STAND || charainfo[0].mode == RUN){
					Animset();														// アニメーション処理
					// Player1s
					if(offF[0] == TRUE){
						if(cookieinfo[charainfo[0].Selcookie[1]].stay == 0 && cookieinfo[charainfo[0].Selcookie[1]].playtime >= cookieinfo[charainfo[0].Selcookie[1]].anim_totaltime){ // ひっくり返し終わったか
							PlaySoundMem( soundh[9] , DX_PLAYTYPE_BACK ) ;
							cookieinfo[charainfo[0].Selcookie[1]].stay = 1;
							cookieinfo[charainfo[0].Selcookie[0]].Flipflag = 0;
							cookieinfo[charainfo[0].Selcookie[1]].Flipflag = 0;
							charainfo[0].stay = TRUE;
						}
						if(cookieinfo[charainfo[0].Selcookie[1]].stay == 1){
							if(cookieinfo[charainfo[0].Selcookie[1]].staytime <= 0){
								// クッキーが同時に戻る
								if(cookieinfo[charainfo[0].Selcookie[1]].playtime >= 0.0f){
									cookieinfo[charainfo[0].Selcookie[0]].playtime -= 2.5f ;
									cookieinfo[charainfo[0].Selcookie[1]].playtime -= 2.5f ;
								}
								else if(cookieinfo[charainfo[0].Selcookie[0]].playtime <= 0.0f && cookieinfo[charainfo[0].Selcookie[1]].playtime <= 0.0f){							// プレイタイムが0.0f
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
								cookieinfo[charainfo[0].Selcookie[1]].staytime-- ;													// 待ち時間のカウントダウン
							}																				// 待ち時間を終えたら動きを戻す
						}
					}

					 // Player2
					if(offF[1] == TRUE){
						if(cookieinfo[charainfo[1].Selcookie[1]].stay == 0 && cookieinfo[charainfo[1].Selcookie[1]].playtime >= cookieinfo[charainfo[1].Selcookie[1]].anim_totaltime){ // ひっくり返し終わったか
							PlaySoundMem( soundh[9] , DX_PLAYTYPE_BACK ) ;
							cookieinfo[charainfo[1].Selcookie[1]].stay = 1;
							cookieinfo[charainfo[1].Selcookie[0]].Flipflag = 0;
							cookieinfo[charainfo[1].Selcookie[1]].Flipflag = 0;
							charainfo[1].stay = TRUE;
						}
						if(cookieinfo[charainfo[1].Selcookie[1]].stay == 1){
							if(cookieinfo[charainfo[1].Selcookie[1]].staytime <= 0){
								// クッキーが同時に戻る
								if(cookieinfo[charainfo[1].Selcookie[1]].playtime >= 0.0f){
									cookieinfo[charainfo[1].Selcookie[0]].playtime -= 2.5f ;
									cookieinfo[charainfo[1].Selcookie[1]].playtime -= 2.5f ;
								}
								else if(cookieinfo[charainfo[1].Selcookie[0]].playtime < 0.0f && cookieinfo[charainfo[1].Selcookie[1]].playtime < 0.0f){							// プレイタイムが0.0f
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
								cookieinfo[charainfo[1].Selcookie[1]].staytime-- ;							// 待ち時間のカウントダウン
							}																				// 待ち時間を終えたら動きを戻す
						}
					}

					PlayerFly();		//　プレイヤーの浮遊アニメーション
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

				// カメラ設定
				SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet(0.0f,0.0f,1.0f)) ;

				// シャドウマップへの描画の準備
				ShadowMap_DrawSetup( ShadowMapHandle ) ;

				// シャドウマップへキャラクターモデルの描画
				MV1DrawModel( charainfo[0].model1 ) ;

				// シャドウマップへキャラクターモデルの描画
				MV1DrawModel( charainfo[1].model1 ) ;
				MV1DrawModel( egg ) ;

				// シャドウマップへの描画を終了
				ShadowMap_DrawEnd() ;

				// 描画に使用するシャドウマップを設定
				SetUseShadowMap( 0, ShadowMapHandle ) ;

				// スケール設定//
				// プレイヤー1
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

				// プレイヤー2
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
						MV1SetScale(cookie_pic[i],VGet(0.42f,0.49f,0.42f));				// クッキーの背面モデル kaminari
					}else{
						MV1SetScale(cookie_pic[i],VGet(0.29f,0.39f,0.29f));				// クッキーの背面モデル     normal
					}
				}

				MV1SetScale(crosshair[0],VGet(0.2f,1.0f,0.2f));					// 皿
				MV1SetScale(crosshair[1],VGet(0.2f,1.0f,0.2f));					// 皿
				MV1SetScale(plate,VGet(3.5f,2.5f,3.5f));						// 皿
				MV1SetScale(table,VGet(1.0f,1.2f,1.6f));						// テーブル
//				MV1SetScale(pancake,VGet(0.64f,0.58f,0.50f));					// パンケーキ
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

				// スケール
				MV1SetScale(pancake,VGet(0.64f + pancakeA,0.58f,0.50f + pancakeA));					// パンケーキ
//				MV1SetScale(pancake2,VGet(0.55f,0.55f,0.55f));										// パンケーキ
				MV1SetScale(egg,VGet(0.58f,0.58f,0.58f));											//卵
				MV1SetScale(milk,VGet(1.9f,1.7f,1.9f));												//bowlanim
				for(char i = 0; i < MAX_BOWL; i++){
					MV1SetScale(bowl[i],VGet(1.6f,1.6f,1.6f));												//bowlanim
				}
				if(stageflg == 0){
					MV1SetScale(Sfloor[0],VGet(23.0f,10.0f,20.0f));								//	壁
				}else{
					MV1SetScale(Sfloor[0],VGet(23.0f,13.0f,20.0f));								//	壁
					MV1SetScale(reizo,VGet(23.0f,13.0f,20.0f));									//	冷蔵庫
				}


				// XYZRotation
				if(charainfo[0].bdownF == FALSE){
					MV1SetRotationXYZ(charainfo[0].model1,VGet(0.0f,0.785f * charainfo[0].direction,0.0f)) ;			//	キャラクターの移動回転
				}
				if(charainfo[1].bdownF == FALSE){
					MV1SetRotationXYZ(charainfo[1].model1,VGet(0.0f,0.785f * charainfo[1].direction,0.0f)) ;			//	キャラクターの移動回転
				}
				MV1SetRotationXYZ(crosshair[0],VGet(1.57f * 4,0.0f,0.0f)) ;												//	パンケーキモデルの回転
				MV1SetRotationXYZ(crosshair[1],VGet(1.57f * 4,0.0f,0.0f)) ;												//	パンケーキモデルの回転
				MV1SetRotationXYZ(egg,VGet(0.0f,1.57f * 1.1f,0.0f)) ;												//	パンケーキモデルの回転
				MV1SetRotationXYZ(pancake,VGet(3.0f,0.0f,0.0f)) ;													//	パンケーキモデルの回転
				MV1SetRotationXYZ(pancake2,VGet(0.0f,0.0f,0.0f)) ;													//	パンケーキモデルの回転
				MV1SetRotationXYZ(milk,VGet(0.0f,2.45f,0.0f)) ;												//	牛乳パックモデルの回転
				for(int i = 0;i < MAX_WALL; i++){
					MV1SetRotationXYZ(Sfloor[i],VGet(0.0f,1.57f*2,0.0f)) ;											//	パンケーキモデルの回転
				}

				//Position
				// モデルの移動(配置)
				MV1SetPosition(charainfo[0].model1,charainfo[0].pos);
				MV1SetPosition(charainfo[1].model1,charainfo[1].pos);

				// 地面(配置)＆描画
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

				if(stageflg != 1){							// 1面
					for( int i = 0 ; i < MAX_COOKIE ; i++ ){
						MV1SetPosition(cookie[i],cookieinfo[i].cookiepos);
						MV1SetPosition(cookie_pic[cookieinfo[i].cookienum],VGet(cookieinfo[i].cookiepos.x, cookieinfo[i].cookiepos.y + 40.0f, cookieinfo[i].cookiepos.z - 15.0f));
						MV1SetRotationXYZ(cookie[i],VGet(0.0f,0.0f,0.0f));
					}
				}
				else{										// 2面
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
					// モデルの描画
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

				}else// 2面
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
					MV1SetScale( range ,VGet(1.0f,1.0f,1.0f));				// 電子レンジ
					MV1SetRotationXYZ(range,VGet(0.0f,1.6f,0.0f)) ;				// レンジの回転
					MV1SetRotationXYZ(lack,VGet(0.0f,1.6f,0.0f)) ;				// レンジの回転
					MV1SetPosition(plate,platepos);
					MV1SetPosition(range,rangepos);
					MV1SetPosition(lack,rangepos);


					// クッキーがふわふわ動くアニメーション
					for(int i = 0; i < MAX_COOKIE; i++){
						if(TroteF == TRUE){
							cookieinfo[i].cookiepos.y -= Trote;
						}else{
							cookieinfo[i].cookiepos.y += Trote;
						}
						Stg2cookie[i].x = (cos( (circleAngle)/2 * 3.141f / 180 ) * 25.7f) + cookieinfo[i].cookiepos.x ;
						Stg2cookie[i].z = (sin( (circleAngle)/2 * 3.141f / 180 ) * 25.7f) + cookieinfo[i].cookiepos.z ;		//	2.0を基準にすると楕円　	
					}
					circleAngle += 10;
					if(circleAngle > 720){
						circleAngle = 0;
					}
					TroteC++;
					if(TroteC == 60){											// ループ数カウント
						if(TroteF == TRUE){
							TroteF = FALSE;
						}
						else if(TroteF == FALSE){
							TroteF = TRUE;
						}
						TroteC = 0;
					}

					// モデルの描画
					MV1DrawModel(plate) ;
					MV1DrawModel(range) ;
					MV1DrawModel(lack);
					MV1DrawModel(Sfloor[0]) ;
					MV1DrawModel(reizo) ;
				}

				// 描画に使用するシャドウマップの設定を解除
				SetUseShadowMap( 0, -1 ) ;

				/*  ------------------------------------------------ //
				//                      落雷の処理                   //
				// ------------------------------------------------- */
				for(int P = 0; P < MAX_PLAYER; P++ ){
					if( charainfo[P].sunder == TRUE ){
						if(objectinfo[THUNDER].playtime < objectinfo[THUNDER].anim_totaltime){
							objectinfo[THUNDER].playtime += 0.17f;
							// 移動の制限
							charainfo[P].move.x = 0.0f;
							charainfo[P].move.y = 0.0f;
							charainfo[P].move.z = 0.0f;

							// 雷モデルの調節
							MV1SetPosition(thunder,VGet(charainfo[P].pos.x + 30.0f,-220.0f,charainfo[P].pos.z - 60.0f));
							MV1SetScale(thunder,VGet(0.5f,0.1f,0.5f));
							MV1SetEmiColorScale(thunder,THUNDERMODELCOLOR);
							MV1SetRotationXYZ(thunder,VGet(0.0f,1.57f*1,0.0f)); 												//	パンケーキモデルの回転
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
					if(cookieinfo[i].fliped != TRUE)	MV1DrawModel(cookie[i])	;		// クッキー表示

					if((cookieinfo[i].Flipflag == 1 || cookieinfo[i].staytime != 0) &&
						cookieinfo[i].playtime > 40.0f &&
						cookieinfo[i].fliped != TRUE){
						MV1SetRotationXYZ(cookie_pic[cookieinfo[i].cookienum],VGet(0.0f,1.57f*2,1.57f*0));
						MV1DrawModel(cookie_pic[cookieinfo[i].cookienum]) ;				// クッキー図柄表示
					}
				}
				MV1DrawModel(crosshair[0]) ;
				MV1DrawModel(crosshair[1]) ;


				// キャラクターの移動処理 //
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
				//                            時間ごとのイベント処理                              //
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
					//			ステージチェンジ予告		  //
					// -------------------------------------- */
					if(maintimer > SCEENWAIT && maintimer < (SCEENWAIT + 5) ){
						 DrawGraph(0,0,Graph[11],TRUE);
					}

					/* -------------------------------------- //
					//			ステージ移動処理			 //
					// -------------------------------------- */
					if(maintimer == SCEENWAIT && stageflg != 1){
						getcookiecnt = 0;
						if(0 == CheckSoundMem(soundh[19])){
							PlaySoundMem( soundh[19] , DX_PLAYTYPE_BACK ) ;
						}

						/* --------------------------- //
						//           初期処理          //
						// --------------------------- */
						charainfo[0].pos.y += 5.0f;
						charainfo[1].pos.y += 5.0f;
						if(0 == ChangeScreen()){
							DrawBillboard3D(VGet(343.2f, -120.0f, 10.4f),0.5f,0.5f,1200.0f,0.0f,Graph[0],TRUE);
						}else{
							/* ---------------- //
							// ２面メインカメラ // 
							// ---------------- */
							cpos = VGet(440.0f,500.0f,-10020.0f) ;
							ctgt = VGet(440.0f,-150.0f,50.0f) ;
							/* //
							// サンダーが有効だった場合処理を終わらせる  //
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
							maintimer = timer();				// 秒数を進める
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
					// スタート画面 // 
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
					//                       終了処理                       //
					// ---------------------------------------------------- */
					if(maintimer == -1){													// 移動するまでの時間()
						if(sceentime == 0){
							 PlaySoundMem( soundh[15] , DX_PLAYTYPE_BACK ) ;
						}
						DrawGraph(0,0,Graph[12],TRUE);
						sceentime++;
						if(sceentime == 60 * 2){
							StopSoundMem(soundh[3]);
							gamemode = eSceneOver;										//	リザルト画面
							sceentime = 0;												// シーン待ち時間の初期化
						}
					}else if(maintimer <= 90){
						if(stageflg != 1){
							DrawRectGraph(90  ,130,(charainfo[0].getcookie % 10) * 57,0,57,103,Graph[5],TRUE,FALSE);
							DrawRectGraph(1125,130,(charainfo[1].getcookie % 10) * 57,0,57,103,Graph[6],TRUE,FALSE);
						}else{																// 二面以降後隠す
							// ??? 表示
 							DrawGraph(80  ,130,Graph[7],TRUE);
							DrawGraph(1105,130,Graph[7],TRUE);
						}
						// P1P2画像
						DrawGraph(0,0,Graph[4],TRUE);
						if(maintimer >= 10){
							DrawRectGraph(581,25,(maintimer / 10) * 70,0,57,103,Graph[8],TRUE,FALSE);
							DrawRectGraph(638,25,(maintimer % 10) * 70,0,57,103,Graph[8],TRUE,FALSE);
						}else{
							DrawRectGraph(619,25,(maintimer % 10) * 70,0,57,103,Graph[8],TRUE,FALSE);
						}
					}

					// リセットのとき画像を表示
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
			/*														リザルト画面															*/
			/*																																*/
			/********************************************************************************************************************************/
			case eSceneOver :		// 結果処理(リザルトアニメーション)
				// 色
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

				// リセット
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
					// ライトの方向を設定
					SetLightDirection( VGet( 6.0f, -100.f, 5.0f ) );

					// 追加ライト
					LightHandle = CreatePointLightHandle(
						VGet( -900.0f,1000.0f,1000.0f),
						2000.0f,
						0.0f,
						0.002f,
						0.0f);
					// テーブルの位置
					tablepos    = VGet(600.0f,-11000.0f,51.0f) ;
					rangepos    = VGet(600.0f,-270.0f,6000.0f) ;

					// カメラポジション
					cpos5 = VGet( 750.0f, -140.0f, -380.0f ) ;
					ctgt5 = VGet( 750.0f, -170.0f, 50.0f ) ;
					cpos4 = VGet( 180.0f, -140.0f, -380.0f ) ;
					ctgt4 = VGet( 180.0f, -170.0f, 50.0f ) ;
					cpos = VGet( 480.0f, 20.0f, -570.0f ) ;
					ctgt = VGet( 480.0f, -150.0f, 50.0f ) ;
					// カメラ設定
					SetCameraPositionAndTargetAndUpVec(cpos,ctgt,VGet( 0.0f,0.0f, 0.1f)) ;

					// キャラ位置を固定
					charainfo[0].direction = DOWNRIGHT ;
					charainfo[1].direction = DOWNLEFT ;
					charainfo[0].pos = VGet(323.2f, -60.0f , 14.4f) ;
					charainfo[1].pos = VGet(632.0f, -60.0f , 14.4f) ;
					cookieinfo[0].cookiepos = VGet( 280.0f , -390.0f , 14.4f ) ; 
					cookieinfo[1].cookiepos = VGet( 669.0f , -390.0f , 14.4f ) ;
					MV1SetPosition(cookie[0] , VGet( cookieinfo[0].cookiepos.x , cookieinfo[0].cookiepos.y , cookieinfo[0].cookiepos.z ) ) ;
					MV1SetPosition(cookie[1] , VGet( cookieinfo[1].cookiepos.x , cookieinfo[1].cookiepos.y , cookieinfo[1].cookiepos.z ) ) ;
					// 図柄初期化
					if( charainfo[0].getcookie > charainfo[1].getcookie ){					
						MV1SetPosition(charainfo[6].model1,charainfo[1].pos);
						// 負けた場合雷のマークになる
						cookieinfo[4].cookienum = 2 ;
						cookieinfo[5].cookienum = 5 ;
						if(charainfo[1].chara != 0){
//							charainfo[6].pos.y += 150.0f;	
						}
					}else if( charainfo[0].getcookie < charainfo[1].getcookie ){
						MV1SetPosition(charainfo[6].model1,charainfo[0].pos);
						// 負けた場合雷のマークになる
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

					// クッキー背面に図柄を貼り付け
					for( int i = 0 ; i < 2 ; i++ ) {
						// クッキー画像	
						switch( i ) {
							case 1 :
								MV1SetPosition(cookie_pic[cookieinfo[i].cookienum] , VGet( cookieinfo[0].cookiepos.x , cookieinfo[0].cookiepos.y - 20.0f , cookieinfo[0].cookiepos.z ) ) ;
								MV1SetScale(cookie_pic[cookieinfo[i].cookienum],VGet(0.42f,0.49f,0.42f));				// クッキーの背面モデル 雷
								break ;
							case 2:
								MV1SetPosition(cookie_pic[cookieinfo[i].cookienum] , VGet( cookieinfo[1].cookiepos.x , cookieinfo[1].cookiepos.y - 20.0f , cookieinfo[1].cookiepos.z ) ) ;
								MV1SetScale(cookie_pic[cookieinfo[i].cookienum],VGet(0.42f,0.49f,0.42f));				// クッキーの背面モデル 雷
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
					// 各キャラによるオフセット
					for( int  P = 0 ; P < MAX_PLAYER ; P++ )
					{
						cookieinfo[P].playtime = 0.0f;//	クッキーをひっくり返す
						cookieinfo[P].Flipflag = 0;
						charainfo[P].sunder		= TRUE ;
						stageflg = TRUE ;
						switch( P ){
							// プレイヤー1
							case 0 :
								// キャラクターの位置と回転
								MV1SetScale(charainfo[0].model1,VGet(1.8f, 1.8f, 1.8f));			// chara1
								MV1SetRotationXYZ(charainfo[0].model1,VGet( 0.0f , charainfo[0].direction * 0.450f ,  0.0f )) ;
//								MV1SetPosition(charainfo[0].model1 , VGet( charainfo[0].pos.x - 25.0f , charainfo[0].pos.y, charainfo[0].pos.z - 30.0f ) );
								break ;
							// プレイヤー２
							case 1 :
								// キャラクターの位置と回転
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
					MV1SetScale( range ,VGet(0.5f,0.5f,0.5f));				// 電子レンジ
					MV1SetPosition(table,tablepos);
					MV1SetPosition(range,rangepos);
					// 雷の位置調整
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
				PlayerFly();		//　プレイヤーの浮遊アニメーション

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

				// タイマー
				if(waittimer == (MAXTIME- 90)){
					charainfo[0].bdownF		= TRUE ;
					charainfo[1].bdownF		= TRUE ;
				}
				if(waittimer > MAXTIME){
					if(charainfo[0].bdownF == FALSE && charainfo[1].bdownF == FALSE){
						for(int i = 0; i < MAX_COOKIE; i++){
							if(cookieinfo[i].playtime < cookieinfo[i].anim_totaltime){
									cookieinfo[i].playtime += 0.9f;//	クッキーをひっくり返す
							}
							if(cookieinfo[i].playtime >= 40.0f){
								MV1SetPosition(cookie_pic[cookieinfo[4].cookienum] , VGet( cookieinfo[0].cookiepos.x , cookieinfo[0].cookiepos.y + 40.0f , cookieinfo[0].cookiepos.z ) ) ;
								MV1SetScale(cookie_pic[cookieinfo[4].cookienum],VGet(0.42f,0.49f,0.42f));				// クッキーの背面モデル 雷
								MV1SetPosition(cookie_pic[cookieinfo[5].cookienum] , VGet( cookieinfo[1].cookiepos.x , cookieinfo[1].cookiepos.y + 40.0f , cookieinfo[1].cookiepos.z ) ) ;
								MV1SetScale(cookie_pic[cookieinfo[5].cookienum],VGet(0.42f,0.49f,0.42f));				// クッキーの背面モデル 雷
								MV1DrawModel(cookie_pic[cookieinfo[4].cookienum]) ;				// クッキー図柄表示
								MV1DrawModel(cookie_pic[cookieinfo[5].cookienum]) ;				// クッキー図柄表示					
							}
						}
					}
				}

				// 結果発表
//				DrawString(50,20,"P1",GetColor(0,20,255));
//				DrawString(1090,20,"P2",GetColor(255,60,0));
				DrawGraph(0,0,Graph[4],TRUE);

				if( waittimer > (MAXTIME + 30) && cookieinfo[1].playtime >= cookieinfo[1].anim_totaltime){
					StopSoundMem(soundh[17]);
					if(0 == CheckSoundMem(soundh[21])){
					    PlaySoundMem( soundh[21] , DX_PLAYTYPE_LOOP ) ;
					}
					// スコア表示
					DrawRectGraph(90  ,130,(charainfo[0].getcookie % 10) * 57,0,57,103,Graph[5],TRUE,FALSE);
					DrawRectGraph(1125,130,(charainfo[1].getcookie % 10) * 57,0,57,103,Graph[6],TRUE,FALSE);

					// スコアが同じの時、雷を打った数で勝利が決まる処理（後々追加）
					if( charainfo[0].getcookie > charainfo[1].getcookie ) {
						DrawGraph(0,0,Graph[13],TRUE);
						// 勝ちモーション
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

						// 負けたほうに雷を落とて黒くする
						if(objectinfo[THUNDER].playtime < objectinfo[THUNDER].anim_totaltime) {
							if(0 == CheckSoundMem(soundh[10])){
								PlaySoundMem( soundh[10] , DX_PLAYTYPE_BACK ) ;
							}
							// 雷
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
						// 勝ちモーション
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
						// 負けたほうに雷を落とす
						if(objectinfo[THUNDER].playtime < objectinfo[THUNDER].anim_totaltime) {
							if(0 == CheckSoundMem(soundh[10])){
								PlaySoundMem( soundh[10] , DX_PLAYTYPE_BACK ) ;
							}
							MV1SetPosition(thunder,VGet(charainfo[0].pos.x - 25.0f,charainfo[0].pos.y - 30.0f , charainfo[0].pos.z - 30.0f));
							// 雷
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
							// 雷
							if(0 == CheckSoundMem(soundh[10])){
								PlaySoundMem( soundh[10] , DX_PLAYTYPE_BACK ) ;
							}

							// ここにthunder2をいれて
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
					//ステージのポジション
					pancakepos  = VGet(440.0f,-555.0f,690.0f) ;
					pancake2pos = VGet(2500.0f,-675.0f,600.0f) ;
					platepos    = VGet(90.0f,-1000.0f,900.0f) ;
					tablepos    = VGet(600.0f,-10050.0f,5200.0f) ;
					rangepos = VGet(600.0f,50.0f,900.0f);	// レンジ
					// ライトの方向を設定
					SetLightDirection( VGet( 0.5f, -0.5f, 0.5f ) );
					DeleteLightHandle(LightHandle);	
					gamemode = eSceneBlank2;
				}
				ScreenFlip();
				break ;

			case eSceneEnd :														// 終了処理
				break;
		}
	}
	DxLib_End() ;
	return 0 ;
}

