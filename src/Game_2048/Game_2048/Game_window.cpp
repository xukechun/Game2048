#include "Game_window.h"
#include "Simple_window.h"
#include "GuiWindow.h"
#include <iostream>
#include <ctime>
#include "global.h"

int ROW = 4;
int COL = 4;

void Game_window::putstate()
{
	switch (state())
	{
	case 1: show_state.put("Game Over!");
	case 2: show_state.put("Game Win!");
	case 3: show_state.put("Game Continue!");
	default:
		break;
	}
}

void Game_window::setcolor()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			switch (gamebase[i][j].num())
			{
			case 0: gamebase[i][j].set_fill_color(FL_WHITE); break;
			case 2: gamebase[i][j].set_fill_color(FL_YELLOW); break;
			case 4: gamebase[i][j].set_fill_color(FL_DARK_YELLOW); break;
			case 8: gamebase[i][j].set_fill_color(FL_CYAN); break;
			case 16: gamebase[i][j].set_fill_color(FL_DARK_CYAN); break;
			case 32: gamebase[i][j].set_fill_color(FL_GREEN); break;
			case 64: gamebase[i][j].set_fill_color(FL_DARK_GREEN); break;
			case 128: gamebase[i][j].set_fill_color(FL_RED); break;
			case 256: gamebase[i][j].set_fill_color(FL_DARK_RED); break;
			case 512: gamebase[i][j].set_fill_color(FL_BLUE); break;
			case 1024: gamebase[i][j].set_fill_color(FL_DARK_CYAN); break;
			case 2048: gamebase[i][j].set_fill_color(FL_MAGENTA); break;
			}
		}
	}
}
/*
			red = FL_RED,
			blue = FL_BLUE,
			green = FL_GREEN,
			yellow = FL_YELLOW,
			white = FL_WHITE,
			black = FL_BLACK,
			magenta = FL_MAGENTA,
			cyan = FL_CYAN,
			dark_red = FL_DARK_RED,
			dark_green = FL_DARK_GREEN,
			dark_yellow = FL_DARK_YELLOW,
			dark_blue = FL_DARK_BLUE,
			dark_magenta = FL_DARK_MAGENTA,
			dark_cyan = FL_DARK_CYAN
*/

int Game_window::maxgrade()
{
	int max = gamebase[0][0].num();
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (max < gamebase[i][j].num())
			{
				max = gamebase[i][j].num();
			}
		}
	}
	return max;
}

bool Game_window::CreateNum()
{
	int x = -1;
	int y = -1;
	int times = 0;
	int maxTimes = ROW * COL;
	//三分之二的概率生成2，三分之一的概率生成4
	int whitch = rand() % 3;
	srand((unsigned int)time(0));
	do
	{
		x = rand() % ROW;
		y = rand() % COL;
		++times;
	} while (gamebase[x][y].num() != 0 && times <= maxTimes);

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
		gamebase[x][y].set_num(num);
	}
	return true;
}

void Game_window::cb_begin(Address, Address pw)
{
	reference_to<Game_window>(pw).begin_pressed();
}

void Game_window::begin_pressed()
{
	begin_button.hide();
	CreateNum();
	CreateNum();
	setcolor();
	show_state.put("Begin!");
	game_menu.show();
}

void Game_window::cb_up(Address, Address pw)
{
	reference_to<Game_window>(pw).up_pressed();
}

void Game_window::up_pressed()
{
	for (int row = 1; row < ROW; ++row)
	{
		for (int crow = row; crow >= 1; --crow)
		{
			for (int col = 0; col < COL; ++col)
			{
				//上一个格子为空
				if (gamebase[crow - 1][col].num() == 0)
				{
					gamebase[crow - 1][col].set_num(gamebase[crow][col].num());
					gamebase[crow][col].set_num(0);
				}
				else
				{
					//合并
					if (gamebase[crow - 1][col].num() == gamebase[crow][col].num())
					{
						gamebase[crow - 1][col].set_num(gamebase[crow - 1][col].num() * 2);
						gamebase[crow][col].set_num(0);
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
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << " " << gamebase[i][j].num() << " ";
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

void Game_window::cb_down(Address, Address pw)
{
	reference_to<Game_window>(pw).down_pressed();
}

void Game_window::down_pressed()
{
	for (int row = ROW - 2; row >= 0; --row)
	{
		for (int crow = row; crow < ROW - 1; ++crow)
		{
			for (int col = 0; col < COL; ++col)
			{
				//上一个格子为空
				if (gamebase[crow + 1][col].num() == 0)
				{
					gamebase[crow + 1][col].set_num(gamebase[crow][col].num());
					gamebase[crow][col].set_num(0);
				}
				else
				{
					//合并
					if (gamebase[crow + 1][col].num() == gamebase[crow][col].num())
					{
						gamebase[crow + 1][col].set_num(gamebase[crow + 1][col].num() * 2);
						gamebase[crow][col].set_num(0);
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
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << " " << gamebase[i][j].num() << " ";
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

void Game_window::cb_left(Address, Address pw)
{
	reference_to<Game_window>(pw).left_pressed();
}

void Game_window::left_pressed()
{
	for (int col = 1; col < COL; ++col)
	{
		for (int ccol = col; ccol >= 1; --ccol)
		{
			for (int row = 0; row < ROW; ++row)
			{
				//上一个格子为空
				if (gamebase[row][ccol - 1].num() == 0)
				{
					gamebase[row][ccol - 1].set_num(gamebase[row][ccol].num());
					gamebase[row][ccol].set_num(0);
				}
				else
				{
					//合并
					if (gamebase[row][ccol - 1].num() == gamebase[row][ccol].num())
					{
						gamebase[row][ccol - 1].set_num(gamebase[row][ccol - 1].num() * 2);
						gamebase[row][ccol].set_num(0);
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
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << " " << gamebase[i][j].num() << " ";
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

void Game_window::cb_right(Address, Address pw)
{
	reference_to<Game_window>(pw).right_pressed();
}

void Game_window::right_pressed()
{
	for (int col = COL - 2; col >= 0; --col)
	{
		for (int ccol = col; ccol <= COL - 2; ++ccol)
		{
			for (int row = 0; row < ROW; ++row)
			{
				//上一个格子为空
				if (gamebase[row][ccol + 1].num() == 0)
				{
					gamebase[row][ccol + 1].set_num(gamebase[row][ccol].num());
					gamebase[row][ccol].set_num(0);
				}
				else
				{
					//合并
					if (gamebase[row][ccol + 1].num() == gamebase[row][ccol].num())
					{
						gamebase[row][ccol + 1].set_num(gamebase[row][ccol + 1].num() * 2);
						gamebase[row][ccol].set_num(0);
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
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			cout << " " << gamebase[i][j].num() << " ";
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

void Game_window::cb_restart(Address, Address pw)
{
	reference_to<Game_window>(pw).restart_pressed();
}

void Game_window::restart_pressed()
{
	for (int i = 0; i < ROW; i++) {		// i is the horizontal coordinate
		for (int j = 0; j < COL; j++) {	// j is the vertical coordinate
			gamebase[i][j].reset(Point(x_max() / 2 - 100 + 50 * j, y_max() / 2 - 100 + 50 * i), 50, 50, 0);
			setcolor();
			attach(gamebase[i][j]);
		}
	}
	CreateNum();
	CreateNum();
	show_state.put("Restart!");
	max_grade.put("no grade");
	this->redraw();
}

int Game_window::state()
{
	//赢得游戏

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (gamebase[i][j].num() == 2048)
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
			if (gamebase[i][j].num() == 0 || (gamebase[i][j].num() == gamebase[i][j + 1].num()))
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
			if (gamebase[i][j].num() == 0 || (gamebase[i][j].num() == gamebase[i + 1][j].num()))
			{
				return GAME_CONTINUE;
				break;
			}
		}
	}
	//不符合上述两种状况，游戏结束
	return GAME_OVER;
}

void Game_window::gui(int state)
{
	if (state == GAME_OVER)
	{
		show_state.put("Game Over!");
		GuiWindow win(Point(650, 350), Point(90, 50), 350, 150, "2048", "Fail to get 2048!  You lost!");
		win.wait_for_button();
	}
	if (state == GAME_WIN)
	{
		show_state.put("Game Win!");
		GuiWindow win(Point(350, 250), Point(110, 50), 350, 150, "2048", "Got 2048!  You win!");
		win.wait_for_button();
	}
	if (state == GAME_CONTINUE)
	{
		show_state.put("Game Continue!");
	}
}
