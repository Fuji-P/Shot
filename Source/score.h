/*
* �T�C�g��	�F�v���O���~���O����T�C�g �`bituse�`
* �����N	�Fhttps://bituse.info/
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

	int	g_board[4];		//�O���t�B�b�N�n���h��
	int	g_number[10];	//�O���t�B�b�N�n���h��
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