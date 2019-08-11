/*Author: Kechun Xu*/
/*Created on 2019.6.2*/
#include "GameGrid.h"

//const int row[3] = { 4, 8, 16 };
//const int col[3] = { 4, 8, 16 };

//上下左右
extern const int ROW = 4;
extern const int COL = 4;
extern const int UP = 1;
extern const int DOWN = 2;
extern const int LEFT = 3;
extern const int RIGHT = 4;

//游戏所处的状态
extern const int GAME_OVER = 1;
extern const int GAME_WIN = 2;
extern const int GAME_CONTINUE = 3;

extern enum GameNum
{
	Game_2 = 2,
	Game_4 = 4,
	Game_8 = 8,
	Game_16 = 16,
	Game_32 = 32,
	Game_64 = 64,
	Game_128 = 128,
	Game_256 = 256,
	Game_512 = 512,
	Game_1024 = 1024,
	Game_2048 = 2048,
};

Game_Grid::Game_Grid(int w, int h, int type)
{
	w = 50;
	h = 50;
	switch (type)
	{
	case 1:
		Simple_window wingame(Point(100, 100), 600, 400, "2048");
		for (int i = 0; i < 4; i++) {		// i is the horizontal coordinate
			for (int j = 0; j < 4; j++) {	// j is the vertical coordinate
				game[i][j].reset(Point(200 + w * i, 200 + h * j), w, h, 0);
				CreateNum();
				wingame.attach(game[i][j]);
			}
		}
		wingame.wait_for_button();
	}
}

bool Game_Grid::CreateNum()
{
	int x = -1;
	int y = -1;
	int times = 0;
	int maxTimes = ROW * COL;
	//三分之二的概率生成2，三分之一的概率生成4
	int whitch = rand() % 3;
	do
	{
		x = rand() % ROW;
		y = rand() % COL;
		++times;
	} while (game[x][y].num() != 0 && times <= maxTimes);

	//说明格子已经满了
	if (times >= maxTimes)
	{
		return false;
	}
	else
	{
		GameNum num;
		if (whitch == 0)
		{
			num = Game_4;
		}
		else if (whitch)
		{
			num = Game_2;
		}
		game[x][y].set_num(num);
	}
	return true;
}

/*
int Game_Grid::handle(int event)
{
	switch (event)
	{
	case FL_KEYDOWN:
		switch (Fl::event_key())
		{
		case FL_Up:
			up_cb(); break;
		case FL_Down:
			down_cb(); break;
		case FL_Left:
			left_cb(); break;
		case FL_Right:
			right_cb(); break;
		}
	}
	return 0;
}
*/
void Game_Grid::up_cb()
{
	for (int row = 1; row < ROW; ++row)
	{
		for (int crow = row; crow >= 1; --crow)
		{
			for (int col = 0; col < COL; ++col)
			{
				//上一个格子为空
				if (game[crow - 1][col].num() == 0)
				{
					game[crow - 1][col].set_num(game[crow][col].num());
					game[crow][col].set_num(0);
				}
				else
				{
					//合并
					if (game[crow - 1][col].num() == game[crow][col].num())
					{
						game[crow - 1][col].set_num(game[crow - 1][col].num() * 2);
						game[crow][col].set_num(0);
					}

				}
			}
		}
	}
}

void Game_Grid::down_cb()
{
	for (int row = ROW - 2; row >= 0; --row)
	{
		for (int crow = row; crow < ROW - 1; ++crow)
		{
			for (int col = 0; col < COL; ++col)
			{
				//上一个格子为空
				if (game[crow + 1][col].num() == 0)
				{
					game[crow + 1][col].set_num(game[crow][col].num());
					game[crow][col].set_num(0);
				}
				else
				{
					//合并
					if (game[crow + 1][col].num() == game[crow][col].num())
					{
						game[crow + 1][col].set_num(game[crow + 1][col].num() * 2);
						game[crow][col].set_num(0);
					}
				}
			}
		}
	}
}

void Game_Grid::left_cb()
{
	for (int col = 1; col < COL; ++col)
	{
		for (int ccol = col; ccol >= 1; --ccol)
		{
			for (int row = 0; row < ROW; ++row)
			{
				//上一个格子为空
				if (game[row][ccol - 1].num() == 0)
				{
					game[row][ccol - 1].set_num(game[row][ccol].num());
					game[row][ccol].set_num(0);
				}
				else
				{
					//合并
					if (game[row][ccol - 1].num() == game[row][ccol].num())
					{
						game[row][ccol - 1].set_num(game[row][ccol - 1].num() * 2);
						game[row][ccol].set_num(0);
					}
				}
			}
		}
	}
}

void Game_Grid::right_cb()
{
	for (int col = COL - 2; col >= 0; --col)
	{
		for (int ccol = col; ccol <= COL - 2; ++ccol)
		{
			for (int row = 0; row < ROW; ++row)
			{
				//上一个格子为空
				if (game[row][ccol + 1].num() == 0)
				{
					game[row][ccol + 1].set_num(game[row][ccol].num());
					game[row][ccol].set_num(0);
				}
				else
				{
					//合并
					if (game[row][ccol + 1].num() == game[row][ccol].num())
					{
						game[row][ccol + 1].set_num(game[row][ccol + 1].num() * 2);
						game[row][ccol].set_num(0);
					}

				}
			}
		}
	}
}

int Game_Grid::state()
{
	//赢得游戏
	
for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (game[i][j].num() == 2048)
			{
				return GAME_WIN;
				break;
			}
		}
	}

	//横向检查
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL - 1; ++j)
		{
			if (game[i][j].num() != 0 || (game[i][j].num() == game[i][j + 1].num()))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
	//纵向检查
	for (int j = 0; j < COL; ++j)
	{
		for (int i = 0; i < ROW - 1; ++i)
		{
			if (game[i][j].num() != 0 || (game[i][j].num() == game[i + 1][j].num()))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}

	//不符合上述两种状况，游戏结束
	return GAME_OVER;
}

void Game_Grid::gui(int state)
{
	switch (state)
	{
	case GAME_OVER: 
	    
	case GAME_WIN: 

	case GAME_CONTINUE: 
		CreateNum();
	}
}
