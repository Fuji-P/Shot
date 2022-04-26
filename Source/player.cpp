/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

#include "pch.h"
#include "player.h"

PLAYER::PLAYER()
{
	//画像読み込み
	
//	if(-1==LoadDivGraph("charall.png",12,3,4,29,40,gh)){
	if(-1 == LoadDivGraph("shot_chara.png", 12, 3, 4, 29, 40, gh)) {
		MSG("エラー発生");
	}

	width=29;
	height=40;

	//移動係数
	move=1.0f;

	//横方向と縦方向のカウント数。
	xcount=0,ycount=0;

	//添字用変数
	ix=0,iy=0,result=0;

	//初期位置
	x=180;
	y=400;

	//生きているかどうか
	life=true;

	//弾初期化
	memset(shot, 0, sizeof(shot));

	//弾画像読み込み
	int temp = LoadGraph("shot.png");
	int w, h;
	GetGraphSize(temp, &w, &h);

	//フラグを全部falseにしとく
	//グラフィックハンドルと画像のサイズを代入しとく
	for (int i = 0; i < PSHOT_NUM; ++i) {
		shot[i].flag = false;
		shot[i].gh = temp;
		shot[i].width = w;
		shot[i].height = h;
	}

	count = 0;

}
void PLAYER::Move()
{
	
		if(key[KEY_INPUT_LEFT] == 1 || key[KEY_INPUT_RIGHT] == 1) {
			
			if(key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
				//移動係数を０．７１に設定
				move = 0.71f;
			} else {
				//斜めじゃなければ１．０に設定
				move = 1.0f;
			}
		} else if(key[KEY_INPUT_UP] == 1 || key[KEY_INPUT_DOWN] == 1) {
			move = 1.0f;
		}

		//左
		if (key[KEY_INPUT_LSHIFT] == 1) {
			move = move / 2.0f;
		}

		//左
		if(key[KEY_INPUT_LEFT] == 1) {
			x -= (int)PLAYER_SPEED * move;
		}
		//右
		if(key[KEY_INPUT_RIGHT] == 1) {
			x += (int)PLAYER_SPEED * move;
		}
		//上
		if(key[KEY_INPUT_UP] == 1) {
			y -= (int)PLAYER_SPEED * move;
		}
		//下
		if(key[KEY_INPUT_DOWN] == 1) {
			y += (int)PLAYER_SPEED * move;
		}

		//キャラの移動制御
		if (x > 400 - MARGIN) {
			x = 400 - MARGIN;
		} else if (x < MARGIN) {
			x = MARGIN;
		}

		if (y > 480 - height / 2 - MARGIN) {
			y = 480 - height / 2 - MARGIN;
		} else if (y < height / 2 + MARGIN) {
			y = height / 2 + MARGIN;
		}

		//左キーが押されてて、かつxcountが０以上なら０にしてから１引く。
		//それ以外は１引く
		if(key[KEY_INPUT_LEFT] == 1) {
			if(xcount > 0) xcount = 0;
			--xcount;
		}
		//右キーが押されてて、かつxcountが０以下なら０にしてから１足す。
		//それ以外は１引く
		if(key[KEY_INPUT_RIGHT] == 1) {
			if(xcount < 0) xcount = 0;
			++xcount;
		}
		//上キーが押されてて、かつycountが０以上なら０にしてから１引く。
		//それ以外は１引く
		if(key[KEY_INPUT_UP] == 1) {
			if(ycount > 0) ycount = 0;
			--ycount;
		}
		//下キーが押されてて、かつycountが０以下なら０にしてから１足す。
		//それ以外は１足す
		if(key[KEY_INPUT_DOWN] == 1) {
			if(ycount < 0) ycount = 0;
			++ycount;
		}

		//カウント数から添字を求める。
		ix = abs(xcount) % 30 / 10;
		iy = abs(ycount) % 30 / 10;

		//xカウントがプラスなら右向きなので2行目の先頭添字番号を足す。
		if(xcount > 0) {
			ix += 3;
			result = ix;
		} else if(xcount < 0) {
			//マイナスなら左向きなので、4行目の先頭添字番号を足す。
			ix += 9;
			result = ix;
		}

		//yカウントがプラスなら下向きなので、3行目の先頭添字番号を足す。
		if(ycount > 0) {
			iy += 6;
			result = iy;
		} else if(ycount<0) {
			//１行目の先頭添字番号は０なので何もする必要なし。(分かりやすくするために書いときました)
			iy += 0;
			result = iy;
		}

		//斜め移動の場合は横顔を優先
		if(move == 0.71f) result = ix;

		//押されてなければカウントをゼロにする。
		if(key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_RIGHT] != 1) {
			xcount=0;
		}
		if(key[KEY_INPUT_UP] !=1 && key[KEY_INPUT_DOWN] != 1) {
			ycount=0;
		}

}

void PLAYER::Shot()
{
	//キーが押されててかつ、6ループに一回発射
//	if (key[KEY_INPUT_Z] == 1 && count % 6 == 0) {
	if (key[KEY_INPUT_Z] == 1 && count % 12 == 0) {
	for (int i = 0; i < PSHOT_NUM; ++i) {
			if (shot[i].flag == false) {
				shot[i].flag = true;
				shot[i].x = x;
				shot[i].y = y;
				break;
			}
		}
	}

	//弾を移動させる処理
	for (int i = 0; i < PSHOT_NUM; ++i) {
		//発射してる弾だけ
		if (shot[i].flag) {
			shot[i].y -= PSHOT_SPEED;

			//画面の外にはみ出したらフラグを戻す
			if (shot[i].y < -10) {
				shot[i].flag = false;
			}
		}
	}
}


void PLAYER::Draw()
{
	//弾描画
	for (int i = 0; i < PSHOT_NUM; ++i) {
		if (shot[i].flag) {
			DrawGraph(shot[i].x - shot[i].width / 2,
						shot[i].y - shot[i].height / 2,
						shot[i].gh, TRUE);
		}
	}

	//生きてれば描画
	if(life) {
		//描画
		DrawGraph(x - width / 2, y - height / 2, gh[result], TRUE);
	}
}


void PLAYER::All()
{
	Move();
	Shot();
	Draw();

	++count;
}