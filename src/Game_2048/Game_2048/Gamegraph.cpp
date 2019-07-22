#include "Gamegraph.h"
#include "GuiWindow.h"
#include <iostream>
#include <ctime>
#include "global.h"
#include "Window.h"
#include <fstream>
#include <FL/Fl_JPEG_Image.H>

using namespace std;

namespace Gamegraph_lib {

int ROW = 4;
int COL = 4;
int flag = 0;  //never win a game.

Rect_with_text gamebase[4][4];
Rect_with_text gamemedium[6][6];
Rect_with_text gamehard[8][8];

Game_window::Game_window(Point xy, int w, int h, const string&s) :
	Simple_window(xy, w, h, s),
	game_menu(Point(0, 0), 100, 20, Menu::vertical, "Menu"),
	begin_button(Point(0, 0), 100, 20, "Begin &B", cb_begin),
	max_grade(Point(200, 0), 80, 20, "Max grade:"),
	show_state(Point(380, 0), 120, 20, "State now:"),
	backbox(0, 20, 600, 400),
	backg("2048b.jpg"),
	save_button(Point(10, 260), 28, 28, "save", cb_save),
	load_button(Point(60, 260), 30, 30, "load", cb_load)
{
	backbox.image(backg);
	add(backbox);
	for (int i = 0; i < 4; i++) {		// i is the horizontal coordinate
		for (int j = 0; j < 4; j++) {	// j is the vertical coordinate
			gamebase[i][j].reset(Point(x_max() / 2 - 100 + 50 * j, y_max() / 2 - 100 + 50 * i), 50, 50, 0);
			gamebase[i][j].set_font_size(14);
			gamebase[i][j].set_fill_color(FL_WHITE);
			attach(gamebase[i][j]);
		}
	}
	clock = fl_add_clock(FL_ANALOG_CLOCK, 0, 140, 100, 100, "Clock");
	//clock->draw();
	add(clock);
	attach(save_button);
	attach(load_button);
	game_menu.attach(new Button(Point(0, 0), 0, 0, " ↑ &W", cb_up));
	game_menu.attach(new Button(Point(0, 0), 0, 0, " ↓ &S", cb_down));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "← &A", cb_left));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "→ &D", cb_right));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Restart &R", cb_restart));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Save &E", cb_save));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Load &L", cb_load));
	attach(game_menu);
	attach(begin_button);
	game_menu.hide();
	attach(show_state);
	show_state.put("Init!");
	attach(max_grade);
	max_grade.put("no grade");
}

void Game_window::putstate()  //show state in the out box
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

void Game_window::setcolor()   //different numbers has different colors
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

int Game_window::maxgrade()  //find the max grade
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
 
	// Two-thirds of the probability generates two, and one-third generates four.
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
	flag = 0;
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
				// The last is empty
				if (gamebase[crow - 1][col].num() == 0)
				{
					gamebase[crow - 1][col].set_num(gamebase[crow][col].num());
					gamebase[crow][col].set_num(0);
				}
				else
				{
					//merge
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
	putstate();  //show the state and max grade
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
	flag = 0;
	for (int i = 0; i < ROW; i++) {		// i is the horizontal coordinate
		for (int j = 0; j < COL; j++) {	// j is the vertical coordinate
			gamebase[i][j].reset(Point(x_max() / 2 - 100 + 50 * j, y_max() / 2 - 100 + 50 * i), 50, 50, 0);
			attach(gamebase[i][j]);
		}
	}
	CreateNum();  // Selecting randomly two lattices to generate numbers 
	CreateNum();
	setcolor();
	show_state.put("Restart!");
	max_grade.put("no grade");
	this->redraw();
}

void Game_window::cb_save(Address, Address pw)
{
	reference_to<Game_window>(pw).save_pressed();
}

void Game_window::save_pressed()
{
	save_button.hide();
	ofstream saveFile;
	saveFile.open("mygrade.txt", ios::out|ios::trunc);
	int count = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			saveFile << " " << gamebase[i][j].num() << " ";
			count++;
			if (count % 4 == 0)
			{
				saveFile << endl;
			}
		}
	}
	saveFile << endl;
	saveFile.close();
	save_button.show();
}

void Game_window::cb_load(Address, Address pw)
{
	reference_to<Game_window>(pw).load_pressed();
}

void Game_window::load_pressed()
{
	load_button.hide();
	ifstream loadFile;
	int num[16];
	loadFile.open("mygrade.txt");
	for (int i = 0; i < 16; i++)
	{
		loadFile >> num[i];
		cout << num[i] << " ";
	}
	int k = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			gamebase[i][j].set_num(num[k]);
			k++;
		}
	}
	setcolor();
	this->redraw();
	load_button.show();
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
	if (state == GAME_WIN && flag == 0)
	{
		flag = 1;
		show_state.put("Game Win!");
		GuiWindow win(Point(350, 250), Point(110, 50), 350, 150, "2048", "Got 2048!  You win!");
		win.wait_for_button();
	}
	if (state == GAME_CONTINUE)
	{
		show_state.put("Game Continue!");
	}
}


//-------------------------------------------------------------------------

Game_medium::Game_medium(Point xy, int w, int h, const string&s) :
	Game_window(xy, w, h, s),
	game_menu(Point(0, 0), 100, 20, Menu::vertical, "Menu"),
	begin_button(Point(0, 0), 100, 20, "Begin &B", cb_begin),
	max_grade(Point(200, 0), 80, 20, "Max grade:"),
	show_state(Point(380, 0), 120, 20, "State now:"),
	backbox(0, 20, 600, 400),
	backg("2048b.jpg"),
	save_button(Point(10, 260), 28, 28, "save", cb_save),
	load_button(Point(60, 260), 30, 30, "load", cb_load)
{
	backbox.image(backg);
	add(backbox);
	attach(save_button);
	attach(load_button);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			gamemedium[i][j].reset(Point(x_max() / 2 - 150 + 50 * j, y_max() / 2 - 150 + 50 * i), 50, 50, 0);
			gamemedium[i][j].set_font_size(14);
			gamemedium[i][j].set_fill_color(FL_WHITE);
			//CreateNum();
			attach(gamemedium[i][j]);
		}
	}
	clock = fl_add_clock(FL_ANALOG_CLOCK, 0, 140, 100, 100, "Clock");
	clock->draw();
	add(clock);
	game_menu.attach(new Button(Point(0, 0), 0, 0, " ↑ &W", cb_up));
	game_menu.attach(new Button(Point(0, 0), 0, 0, " ↓ &S", cb_down));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "← &A", cb_left));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "→ &D", cb_right));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Restart &R", cb_restart));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Save &E", cb_save));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Load &L", cb_load));
	attach(game_menu);
	attach(begin_button);
	game_menu.hide();
	attach(show_state);
	show_state.put("Init!");
	attach(max_grade);
	max_grade.put("no grade");
}

void Game_medium::putstate()
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
	flag = 0;
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
			if (count % 6 == 0)
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
			if (count % 6 == 0)
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
			if (count % 6 == 0)
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
			if (count % 6 == 0)
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
	flag = 0;
	for (int i = 0; i < 6; i++) {		// i is the horizontal coordinate
		for (int j = 0; j < 6; j++) {	// j is the vertical coordinate
			gamemedium[i][j].reset(Point(x_max() / 2 - 100 + 50 * j, y_max() / 2 - 100 + 50 * i), 50, 50, 0);
			attach(gamemedium[i][j]);
		}
	}
	CreateNum();
	CreateNum();
	setcolor();
	show_state.put("Restart!");
	max_grade.put("no grade");
	this->redraw();
}

void Game_medium::cb_save(Address, Address pw)
{
	reference_to<Game_medium>(pw).save_pressed();
}

void Game_medium::save_pressed()
{
	save_button.hide();
	ofstream saveFile;
	saveFile.open("mygrade_2.txt", ios::out | ios::trunc);
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			saveFile << " " << gamemedium[i][j].num() << " ";
			count++;
			if (count % 6 == 0)
			{
				saveFile << endl;
			}
		}
	}
	saveFile << endl;
	saveFile.close();
	save_button.show();
}

void Game_medium::cb_load(Address, Address pw)
{
	reference_to<Game_medium>(pw).load_pressed();
}

void Game_medium::load_pressed()
{
	load_button.hide();
	ifstream loadFile;
	int num[36];
	loadFile.open("mygrade_2.txt");
	for (int i = 0; i < 36; i++)
	{
		loadFile >> num[i];
		cout << num[i] << " ";
	}
	int k = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			gamemedium[i][j].set_num(num[k]);
			k++;
		}
	}
	setcolor();
	this->redraw();
	load_button.show();
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

//---------------------------------------------------------------------

Game_hard::Game_hard(Point xy, int w, int h, const string&s) :
	Game_window(xy, w, h, s),
	game_menu(Point(0, 0), 100, 20, Menu::vertical, "Menu"),
	begin_button(Point(0, 0), 100, 20, "Begin &B", cb_begin),
	max_grade(Point(200, 0), 80, 20, "Max grade:"),
	show_state(Point(380, 0), 120, 20, "State now:"),
	backbox(0, 20, 700, 500),
	backg("2048b.jpg"),
	save_button(Point(10, 260), 28, 28, "save", cb_save),
	load_button(Point(60, 260), 30, 30, "load", cb_load)
{
	backbox.image(backg);
	add(backbox);
	attach(save_button);
	attach(load_button);
	for (int i = 0; i < 8; i++) {		// i is the horizontal coordinate
		for (int j = 0; j < 8; j++) {	// j is the vertical coordinate
			gamehard[i][j].reset(Point(x_max() / 2 - 200 + 50 * j, y_max() / 2 - 200 + 50 * i), 50, 50, 0);
			gamehard[i][j].set_font_size(14);
			gamehard[i][j].set_fill_color(FL_WHITE);
			attach(gamehard[i][j]);
		}
	}
	clock = fl_add_clock(FL_ANALOG_CLOCK, 0, 140, 100, 100, "Clock");
	clock->draw();
	add(clock);
	game_menu.attach(new Button(Point(0, 0), 0, 0, " ↑ &W", cb_up));
	game_menu.attach(new Button(Point(0, 0), 0, 0, " ↓ &S", cb_down));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "← &A", cb_left));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "→ &D", cb_right));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Restart &R", cb_restart));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Save &E", cb_save));
	game_menu.attach(new Button(Point(0, 0), 0, 0, "Load &L", cb_load));
	attach(game_menu);
	attach(begin_button);
	game_menu.hide();
	attach(show_state);
	show_state.put("Init!");
	attach(max_grade);
	max_grade.put("no grade");
}

void Game_hard::putstate()
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
	flag = 0;
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
			if (count % 8 == 0)
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
			if (count % 8 == 0)
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
			if (count % 8 == 0)
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
			if (count % 8 == 0)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
	cout << state() << endl;
	gui(state());
}

void Game_hard::cb_save(Address, Address pw)
{
	reference_to<Game_hard>(pw).save_pressed();
}

void Game_hard::save_pressed()
{
	save_button.hide();
	ofstream saveFile;
	saveFile.open("mygrade_3.txt", ios::out | ios::trunc);
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			saveFile << " " << gamehard[i][j].num() << " ";
			count++;
			if (count % 8 == 0)
			{
				saveFile << endl;
			}
		}
	}
	saveFile << endl;
	saveFile.close();
	save_button.show();
}

void Game_hard::cb_load(Address, Address pw)
{
	reference_to<Game_hard>(pw).load_pressed();
}

void Game_hard::load_pressed()
{
	load_button.hide();
	ifstream loadFile;
	int num[64];
	loadFile.open("mygrade_3.txt");
	for (int i = 0; i < 64; i++)
	{
		loadFile >> num[i];
		cout << num[i] << " ";
	}
	int k = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			gamehard[i][j].set_num(num[k]);
			k++;
		}
	}
	setcolor();
	this->redraw();
	load_button.show();
}

void Game_hard::cb_restart(Address, Address pw)
{
	reference_to<Game_hard>(pw).restart_pressed();
}

void Game_hard::restart_pressed()
{
	flag = 0;
	for (int i = 0; i < 8; i++) {		// i is the horizontal coordinate
		for (int j = 0; j < 8; j++) {	// j is the vertical coordinate
			gamehard[i][j].reset(Point(x_max() / 2 - 100 + 50 * j, y_max() / 2 - 100 + 50 * i), 50, 50, 0);
			attach(gamehard[i][j]);
		}
	}
	CreateNum();
	CreateNum();
	setcolor();
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

//---------------------------------------------------------------------

 Applicant_window::Applicant_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	application_menu(Point(x_max() / 2 - 75, 130), 150, 50, Menu::vertical, "Menu"),
	menu_button(Point(x_max() / 2 - 75, y_max() / 2 - 60), 150, 50, "application menu &A", cb_menu),
	quit_button(Point(x_max() - 70, 0), 70, 20, "Quit &Q", cb_quit),
	welcome(Point(x_max() / 2 - 75, 90), "Welcome to 2048!"),
	 backbox(0, 0, 600, 400),
	 backg("2048i.jpg")
{
	backbox.image(backg);
    add(backbox);
	welcome.font_size();
	welcome.set_font(FL_TIMES_ITALIC);
	attach(welcome);
	attach(quit_button);
	application_menu.attach(new Button(Point(0, 0), 0, 0, "GAME_base &B", cb_game1));
	application_menu.attach(new Button(Point(0, 0), 0, 0, "GAME_mediun &M", cb_game2));
	application_menu.attach(new Button(Point(0, 0), 0, 0, "GAME_hard &H", cb_game3));
	application_menu.attach(new Button(Point(0, 0), 0, 0, "About 2048 &E", cb_explain));
	attach(application_menu);
	application_menu.hide();
	attach(menu_button);
}

void Applicant_window::cb_menu(Address, Address pw)
{
	reference_to<Applicant_window>(pw).menu_pressed();
}

void Applicant_window::cb_quit(Address, Address pw)    // "the usual"
{
	reference_to<Applicant_window>(pw).quit();
}

void Applicant_window::quit()
{
	hide();        // curious FLTK idiom for delete window
}

void Applicant_window::cb_explain(Address, Address pw)     // "the usual"
{
	reference_to<Applicant_window>(pw).explain_pressed();
}

void Applicant_window::explain_pressed()
{
	Simple_window winexplain(Point(500, 250), 600, 400, "About 2048");
	Fl_Box background(0,0,600,400);
	Fl_JPEG_Image backg("2048d.jpg");
	background.image(backg);
	winexplain.add(background);
	Text t1(Point(30,80),"Welcome! There are three levels in our game. Please enter the corresponding");
	Text t11(Point(30, 110), "level according to the menu. ");
	Text t2(Point(30, 150), "It is suggested to use Caps-lock and use the shortcuts to play the game. ");
	Text t3(Point(30, 190), "The game wins to 2048. After getting 2048, you can still press Continue to play. ");
	Text t4(Point(30, 230), "If you want to interupt the game, you can Save to record grade. Press the Load");
	Text t44(Point(30, 260), "to read what you save before.");
	Text t5(Point(30, 290), "For each window, you can press N to come back!");
	t1.set_font_size(16);
	t11.set_font_size(16);
	t2.set_font_size(16);
	t3.set_font_size(16);
	t4.set_font_size(16);
	t44.set_font_size(16);
	t5.set_font_size(16);
	winexplain.attach(t1);
	winexplain.attach(t11);
	winexplain.attach(t2);
	winexplain.attach(t3);
	winexplain.attach(t4);
	winexplain.attach(t44);
	winexplain.attach(t5);
	Fl_Box quit(560, 0, 25, 25);
	Fl_JPEG_Image quitimage("quit.jpg");
	quit.image(quitimage);
	winexplain.add(quit);
	winexplain.wait_for_button();
}

void Applicant_window::cb_game1(Address, Address pw)      // "the usual"
{
	reference_to<Applicant_window>(pw).game1_pressed();
}

void Applicant_window::cb_game2(Address, Address pw)      // "the usual"
{
	reference_to<Applicant_window>(pw).game2_pressed();
}

void Applicant_window::cb_game3(Address, Address pw)      // "the usual"
{
	reference_to<Applicant_window>(pw).game3_pressed();
}

void Applicant_window::game1_pressed()     // "the usual"
{
	int w = 50, h = 50;
	Game_window wingame(Point(500, 250), 600, 400, "2048");
	Fl_Box quit(560, 0, 25, 25);
	Fl_JPEG_Image quitimage("quit.jpg");
	quit.image(quitimage);
	wingame.add(quit);
	Fl_Box save(10, 260, 28, 28);
	Fl_JPEG_Image saveimage("save.jpg");
	save.image(saveimage);
	wingame.add(save);
	Fl_Box load(60, 260, 30, 30);
	Fl_JPEG_Image loadimage("read.jpg");
	load.image(loadimage);
	wingame.add(load);
	/*
	Fl_Box up(10, 0, 20, 20);
	Fl_JPEG_Image upimage("up.jpg");
	up.image(upimage);
	wingame.add(up);
	Fl_Box down(0, 20, 20, 20);
	Fl_JPEG_Image downimage("down.jpg");
	up.image(downimage);
	wingame.add(down);
	Fl_Box left(0, 40, 20, 20);
	Fl_JPEG_Image leftimage("left.jpg");
	left.image(leftimage);
	wingame.add(left);
	Fl_Box right(0, 60, 20, 20);
	Fl_JPEG_Image rightimage("right.jpg");
	right.image(rightimage);
	wingame.add(right);
	*/
	wingame.wait_for_button();
}

void Applicant_window::game2_pressed()     // "the usual"
{
	int w = 50, h = 50;
	Game_medium wingame(Point(500, 250), 600, 400, "2048");
	Fl_Box quit(560, 0, 25, 25);
	Fl_JPEG_Image quitimage("quit.jpg");
	quit.image(quitimage);
	wingame.add(quit);
	Fl_Box save(10, 260, 28, 28);
	Fl_JPEG_Image saveimage("save.jpg");
	save.image(saveimage);
	wingame.add(save);
	Fl_Box load(60, 260, 30, 30);
	Fl_JPEG_Image loadimage("read.jpg");
	load.image(loadimage);
	wingame.add(load);
	wingame.wait_for_button();
}

void Applicant_window::game3_pressed()     // "the usual"
{
	int w = 50, h = 50;
	Game_hard wingame(Point(400, 150), 700, 500, "2048");
	Fl_Box quit(660, 0, 25, 25);
	Fl_JPEG_Image quitimage("quit.jpg");
	quit.image(quitimage);
	wingame.add(quit);
	Fl_Box save(10, 260, 28, 28);
	Fl_JPEG_Image saveimage("save.jpg");
	save.image(saveimage);
	wingame.add(save);
	Fl_Box load(60, 260, 30, 30);
	Fl_JPEG_Image loadimage("read.jpg");
	load.image(loadimage);
	wingame.add(load);
	wingame.wait_for_button();

}

}