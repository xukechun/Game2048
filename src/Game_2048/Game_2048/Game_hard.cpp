#include "Game_hard.h"
#include "Game_medium.h"
#include <iostream>
#include <ctime>
#include "global.h"

void Game_hard::setcolor()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			switch (gamehard[i][j].num())
			{
			case 0: gamehard[i][j].set_fill_color(FL_WHITE); break;
			case 2: gamehard[i][j].set_fill_color(FL_YELLOW); break;
			case 4: gamehard[i][j].set_fill_color(FL_DARK_YELLOW); break;
			case 8: gamehard[i][j].set_fill_color(FL_CYAN); break;
			case 16: gamehard[i][j].set_fill_color(FL_DARK_CYAN); break;
			case 32: gamehard[i][j].set_fill_color(FL_GREEN); break;
			case 64: gamehard[i][j].set_fill_color(FL_DARK_GREEN); break;
			case 128: gamehard[i][j].set_fill_color(FL_RED); break;
			case 256: gamehard[i][j].set_fill_color(FL_DARK_RED); break;
			case 512: gamehard[i][j].set_fill_color(FL_BLUE); break;
			case 1024: gamehard[i][j].set_fill_color(FL_DARK_CYAN); break;
			case 2048: gamehard[i][j].set_fill_color(FL_MAGENTA); break;
			}
		}
	}
}

int Game_hard::maxgrade()
{
	int max = gamehard[0][0].num();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (max < gamehard[i][j].num())
			{
				max = gamehard[i][j].num();
			}
		}
	}
	return max;
}

bool Game_hard::CreateNum()
{
	int x = -1;
	int y = -1;
	int times = 0;
	int maxTimes = 8 * 8;
	//三分之二的概率生成2，三分之一的概率生成4
	int whitch = rand() % 3;
	srand((unsigned int)time(0));
	do
	{
		x = rand() % 8;
		y = rand() % 8;
		++times;
	} while (gamehard[x][y].num() != 0 && times <= maxTimes);

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
		gamehard[x][y].set_num(num);
	}
	return true;
}

void Game_hard::cb_begin(Address, Address pw)
{
	reference_to<Game_hard>(pw).begin_pressed();
}

void Game_hard::begin_pressed()
{
	begin_button.hide();
	CreateNum();
	CreateNum();
	setcolor();
	show_state.put("Begin!");
	game_menu.show();
}

void Game_hard::cb_up(Address, Address pw)
{
	reference_to<Game_hard>(pw).up_pressed();
}

void Game_hard::up_pressed()
{
	for (int row = 1; row < 8; ++row)
	{
		for (int crow = row; crow >= 1; --crow)
		{
			for (int col = 0; col < 8; ++col)
			{
				//上一个格子为空
				if (gamehard[crow - 1][col].num() == 0)
				{
					gamehard[crow - 1][col].set_num(gamehard[crow][col].num());
					gamehard[crow][col].set_num(0);
				}
				else
				{
					//合并
					if (gamehard[crow - 1][col].num() == gamehard[crow][col].num())
					{
						gamehard[crow - 1][col].set_num(gamehard[crow - 1][col].num() * 2);
						gamehard[crow][col].set_num(0);
					}

				}
			}
		}
	}
	CreateNum();
	setcolor();
	this->redraw();
	putstate();
	max_grade.put(to_string(maxgrade()));
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << " " << gamehard[i][j].num() << " ";
			count++;
			if (count % 4 == 0)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
	cout << state() << endl;

	gui(state());
}

void Game_hard::cb_down(Address, Address pw)
{
	reference_to<Game_hard>(pw).down_pressed();
}

void Game_hard::down_pressed()
{
	for (int row = 8 - 2; row >= 0; --row)
	{
		for (int crow = row; crow < 8 - 1; ++crow)
		{
			for (int col = 0; col < 8; ++col)
			{
				//上一个格子为空
				if (gamehard[crow + 1][col].num() == 0)
				{
					gamehard[crow + 1][col].set_num(gamehard[crow][col].num());
					gamehard[crow][col].set_num(0);
				}
				else
				{
					//合并
					if (gamehard[crow + 1][col].num() == gamehard[crow][col].num())
					{
						gamehard[crow + 1][col].set_num(gamehard[crow + 1][col].num() * 2);
						gamehard[crow][col].set_num(0);
					}
				}
			}
		}
	}
	CreateNum();
	setcolor();
	this->redraw();
	putstate();
	max_grade.put(to_string(maxgrade()));
	cout << state() << endl;
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << " " << gamehard[i][j].num() << " ";
			count++;
			if (count % 4 == 0)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
	gui(state());
}

void Game_hard::cb_left(Address, Address pw)
{
	reference_to<Game_hard>(pw).left_pressed();
}

void Game_hard::left_pressed()
{
	for (int col = 1; col < 8; ++col)
	{
		for (int ccol = col; ccol >= 1; --ccol)
		{
			for (int row = 0; row < 8; ++row)
			{
				//上一个格子为空
				if (gamehard[row][ccol - 1].num() == 0)
				{
					gamehard[row][ccol - 1].set_num(gamehard[row][ccol].num());
					gamehard[row][ccol].set_num(0);
				}
				else
				{
					//合并
					if (gamehard[row][ccol - 1].num() == gamehard[row][ccol].num())
					{
						gamehard[row][ccol - 1].set_num(gamehard[row][ccol - 1].num() * 2);
						gamehard[row][ccol].set_num(0);
					}
				}
			}
		}
	}
	CreateNum();
	setcolor();
	this->redraw();
	putstate();
	max_grade.put(to_string(maxgrade()));
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << " " << gamehard[i][j].num() << " ";
			count++;
			if (count % 4 == 0)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
	cout << state() << endl;
	gui(state());
}

void Game_hard::cb_right(Address, Address pw)
{
	reference_to<Game_hard>(pw).right_pressed();
}

void Game_hard::right_pressed()
{
	for (int col = 8 - 2; col >= 0; --col)
	{
		for (int ccol = col; ccol <= 8 - 2; ++ccol)
		{
			for (int row = 0; row < 8; ++row)
			{
				//上一个格子为空
				if (gamehard[row][ccol + 1].num() == 0)
				{
					gamehard[row][ccol + 1].set_num(gamehard[row][ccol].num());
					gamehard[row][ccol].set_num(0);
				}
				else
				{
					//合并
					if (gamehard[row][ccol + 1].num() == gamehard[row][ccol].num())
					{
						gamehard[row][ccol + 1].set_num(gamehard[row][ccol + 1].num() * 2);
						gamehard[row][ccol].set_num(0);
					}

				}
			}
		}
	}
	CreateNum();
	setcolor();
	this->redraw();
	putstate();
	max_grade.put(to_string(maxgrade()));
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << " " << gamehard[i][j].num() << " ";
			count++;
			if (count % 4 == 0)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
	cout << state() << endl;
	gui(state());
}

void Game_hard::cb_restart(Address, Address pw)
{
	reference_to<Game_hard>(pw).restart_pressed();
}

void Game_hard::restart_pressed()
{
	for (int i = 0; i < 8; i++) {		// i is the horizontal coordinate
		for (int j = 0; j < 8; j++) {	// j is the vertical coordinate
			gamehard[i][j].reset(Point(x_max() / 2 - 100 + 50 * j, y_max() / 2 - 100 + 50 * i), 50, 50, 0);
			setcolor();
			attach(gamehard[i][j]);
		}
	}
	CreateNum();
	CreateNum();
	show_state.put("Restart!");
	max_grade.put("no grade");
	this->redraw();
}

int Game_hard::state()
{
	//赢得游戏

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (gamehard[i][j].num() == 2048)
			{
				return GAME_WIN;
				break;
			}
		}
	}
	//横向检查
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8 - 1; ++j)
		{
			if (gamehard[i][j].num() == 0 || (gamehard[i][j].num() == gamehard[i][j + 1].num()))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
	//纵向检查
	for (int j = 0; j < 8; ++j)
	{
		for (int i = 0; i < 8 - 1; ++i)
		{
			if (gamehard[i][j].num() == 0 || (gamehard[i][j].num() == gamehard[i + 1][j].num()))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
	//不符合上述两种状况，游戏结束
	return GAME_OVER;
}
