/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

class ITEM {
private:

	static	int		gh[2];		//グラフィックハンドル
	static	int		ghs[2];		//グラフィックハンドル
			int		type;		//どっちのアイテムかを示す変数
			int		count;		//カウント
			double	x;			//座標
			double	y;			//座標
			double	prev_y;
			double	rad;		//回転角度
			bool	fall_flag;	//アイテムが落下し始めるフラグ
			bool	flag;		//出現中かどうかのフラグ

private:
	void Move();
	void Draw();

public:
	ITEM();
	void All();
	void SetFlag(double x, double y, int type);
	void Delete();
	void GetPosition(double* x, double* y);
	int  GetType();
	bool GetFlag();
};
