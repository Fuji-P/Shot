/*
* サイト名	：プログラミング入門サイト ～bituse～
* リンク	：https://bituse.info/
*/

enum SCOREDATA {
	HIGH_SCORE,
	CURRENT_SCORE,
	GRAZE_SCORE,
	LIFE_SCORE,
	POWER_SCORE
};

class SCORE {
private:

	int	g_board[4];		//グラフィックハンドル
	int	g_number[10];	//グラフィックハンドル
	int	high_score;
	int	score;
	int	graze;
	int	life;
	int	power;

private:
	void Draw();

public:
	SCORE();
	void All();
	void SetScore(
		SCOREDATA	data,
		int			val
	);
	int GetScore(
		SCOREDATA	data
	);
};