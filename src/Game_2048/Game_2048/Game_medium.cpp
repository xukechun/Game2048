#include "Game_medium.h"
#include <iostream>
#include <ctime>
#include "global.h"


void Game_medium::setcolor()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			switch (gamemedium[i][j].num())
			{
			case 0: gamemedium[i][j].set_fill_color(FL_WHITE); break;
			case 2: gamemedium[i][j].set_fill_color(FL_YELLOW); break;
			case 4: gamemedium[i][j].set_fill_color(FL_DARK_YELLOW); break;
			case 8: gamemedium[i][j].set_fill_color(FL_CYAN); break;
			case 16: gamemedium[i][j].set_fill_color(FL_DARK_CYAN); break;
			case 32: gamemedium[i][j].set_fill_color(FL_GREEN); break;
			case 64: gamemedium[i][j].set_fill_color(FL_DARK_GREEN); break;
			case 128: gamemedium[i][j].set_fill_color(FL_RED); break;
			case 256: gamemedium[i][j].set_fill_color(FL_DARK_RED); break;
			case 512: gamemedium[i][j].set_fill_color(FL_BLUE); break;
			case 1024: gamemedium[i][j].set_fill_color(FL_DARK_CYAN); break;
			case 2048: gamemedium[i][j].set_fill_color(FL_MAGENTA); break;
			}
		}
	}
}

int Game_medium::maxgrade()
{
	int max = gamemedium[0][0].num();
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (max < gamemedium[i][j].num())
			{
				max = gamemedium[i][j].num();
			}
		}
	}
	return max;
}

bool Game_medium::CreateNum()
{
	int x = -1;
	int y = -1;
	int times = 0;
	int maxTimes = 6 * 6;
	//三分之二的概率生成2，三分之一的概率生成4
	int whitch = rand() % 3;
	srand((unsigned int)time(0));
	do
	{
		x = rand() % 6;
		y = rand() % 6;
		++times;
	} while (gamemedium[x][y].num() != 0 && times <= maxTimes);

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
		gamemedium[x][y].set_num(num);
	}
	return true;
}

void Game_medium::cb_begin(Address, Address pw)
{
	reference_to<Game_medium>(pw).begin_pressed();
}

void Game_medium::begin_pressed()
{
	begin_button.hide();
	CreateNum();
	CreateNum();
	setcolor();
	show_state.put("Begin!");
	game_menu.show();
}

void Game_medium::cb_up(Address, Address pw)
{
	reference_to<Game_medium>(pw).up_pressed();
}

void Game_medium::up_pressed()
{
	for (int row = 1; row < 6; ++row)
	{
		for (int crow = row; crow >= 1; --crow)
		{
			for (int col = 0; col < 6; ++col)
			{
				//上一个格子为空
				if (gamemedium[crow - 1][col].num() == 0)
				{
					gamemedium[crow - 1][col].set_num(gamemedium[crow][col].num());
					gamemedium[crow][col].set_num(0);
				}
				else
				{
					//合并
					if (gamemedium[crow - 1][col].num() == gamemedium[crow][col].num())
					{
						gamemedium[crow - 1][col].set_num(gamemedium[crow - 1][col].num() * 2);
						gamemedium[crow][col].set_num(0);
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
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << " " << gamemedium[i][j].num() << " ";
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

void Game_medium::cb_down(Address, Address pw)
{
	reference_to<Game_medium>(pw).down_pressed();
}

void Game_medium::down_pressed()
{
	for (int row = 6 - 2; row >= 0; --row)
	{
		for (int crow = row; crow < 6 - 1; ++crow)
		{
			for (int col = 0; col < 6; ++col)
			{
				//上一个格子为空
				if (gamemedium[crow + 1][col].num() == 0)
				{
					gamemedium[crow + 1][col].set_num(gamemedium[crow][col].num());
					gamemedium[crow][col].set_num(0);
				}
				else
				{
					//合并
					if (gamemedium[crow + 1][col].num() == gamemedium[crow][col].num())
					{
						gamemedium[crow + 1][col].set_num(gamemedium[crow + 1][col].num() * 2);
						gamemedium[crow][col].set_num(0);
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
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << " " << gamemedium[i][j].num() << " ";
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

void Game_medium::cb_left(Address, Address pw)
{
	reference_to<Game_medium>(pw).left_pressed();
}

void Game_medium::left_pressed()
{
	for (int col = 1; col < 6; ++col)
	{
		for (int ccol = col; ccol >= 1; --ccol)
		{
			for (int row = 0; row < 6; ++row)
			{
				//上一个格子为空
				if (gamemedium[row][ccol - 1].num() == 0)
				{
					gamemedium[row][ccol - 1].set_num(gamemedium[row][ccol].num());
					gamemedium[row][ccol].set_num(0);
				}
				else
				{
					//合并
					if (gamemedium[row][ccol - 1].num() == gamemedium[row][ccol].num())
					{
						gamemedium[row][ccol - 1].set_num(gamemedium[row][ccol - 1].num() * 2);
						gamemedium[row][ccol].set_num(0);
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
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << " " << gamemedium[i][j].num() << " ";
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

void Game_medium::cb_right(Address, Address pw)
{
	reference_to<Game_medium>(pw).right_pressed();
}

void Game_medium::right_pressed()
{
	for (int col = 6 - 2; col >= 0; --col)
	{
		for (int ccol = col; ccol <= 6 - 2; ++ccol)
		{
			for (int row = 0; row < 6; ++row)
			{
				//上一个格子为空
				if (gamemedium[row][ccol + 1].num() == 0)
				{
					gamemedium[row][ccol + 1].set_num(gamemedium[row][ccol].num());
					gamemedium[row][ccol].set_num(0);
				}
				else
				{
					//合并
					if (gamemedium[row][ccol + 1].num() == gamemedium[row][ccol].num())
					{
						gamemedium[row][ccol + 1].set_num(gamemedium[row][ccol + 1].num() * 2);
						gamemedium[row][ccol].set_num(0);
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
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			cout << " " << gamemedium[i][j].num() << " ";
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

void Game_medium::cb_restart(Address, Address pw)
{
	reference_to<Game_medium>(pw).restart_pressed();
}

void Game_medium::restart_pressed()
{
	for (int i = 0; i < 6; i++) {		// i is the horizontal coordinate
		for (int j = 0; j < 6; j++) {	// j is the vertical coordinate
			gamemedium[i][j].reset(Point(x_max() / 2 - 100 + 50 * j, y_max() / 2 - 100 + 50 * i), 50, 50, 0);
			setcolor();
			attach(gamemedium[i][j]);
		}
	}
	CreateNum();
	CreateNum();
	show_state.put("Restart!");
	max_grade.put("no grade");
	this->redraw();
}

int Game_medium::state()
{
	//赢得游戏

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			if (gamemedium[i][j].num() == 2048)
			{
				return GAME_WIN;
				break;
			}
		}
	}
	//横向检查
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6 - 1; ++j)
		{
			if (gamemedium[i][j].num() == 0 || (gamemedium[i][j].num() == gamemedium[i][j + 1].num()))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
	//纵向检查
	for (int j = 0; j < 6; ++j)
	{
		for (int i = 0; i < 6 - 1; ++i)
		{
			if (gamemedium[i][j].num() == 0 || (gamemedium[i][j].num() == gamemedium[i + 1][j].num()))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
	//不符合上述两种状况，游戏结束
	return GAME_OVER;
}
