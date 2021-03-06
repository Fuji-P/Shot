/*
* サイト名	：プログラミング入門サイト 〜bituse〜
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "control.h"

//キー取得用配列
char key[256];

//ゲームが開始してから何ループしたのか
int g_count;

int main() {}

// プログラムは WinMain から始まります
int WINAPI WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow
)
{
	ChangeWindowMode(TRUE);

	if( DxLib_Init() == -1 ) {	// ＤＸライブラリ初期化処理
		return -1 ;				// エラーが起きたら直ちに終了
	}

//	CONTROL *control = new CONTROL;
	//CONTROLクラスの参照
	CONTROL& control = CONTROL::GetInstance();

	while(ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && GetHitKeyStateAll(key)==0){
//		control->All();
		control.All();
	}

	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;					// ソフトの終了 
}