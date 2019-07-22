#pragma once
#include "Game_window.h"
#include "global.h"

//Rect_with_text gamemedium[6][6];

class Game_medium :public Game_window
{
	Point xy;
	int w;
	int h;
	string title;
	Menu game_menu;
	Button begin_button;
	Out_box max_grade;
	Out_box show_state;
	Fl_Widget* clock;
public:
	static Rect_with_text gamemedium[6][6];
	Game_medium(Point xy, int w, int h, const string&s) :
		Game_window(xy, w, h, s),
		game_menu(Point(0, 0), 100, 20, Menu::vertical, "Menu"),
		begin_button(Point(0, 0), 100, 20, "Begin &B", cb_begin),
		max_grade(Point(200, 0), 80, 20, "Max grade:"),
		show_state(Point(380, 0), 120, 20, "State now:")
	{
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				gamemedium[i][j].reset(Point(x_max() / 2 - 150 + 50 * j, y_max() / 2 - 150 + 50 * i), 50, 50, 0);
				gamemedium[i][j].set_font_size(14);
				gamemedium[i][j].set_fill_color(FL_WHITE);
				//CreateNum();
				attach(gamemedium[i][j]);
			}
		}
		clock = fl_add_clock(FL_ANALOG_CLOCK, 0, 100, 100, 100, "Clock");
		clock->draw();
		add(clock);
		game_menu.attach(new Button(Point(0, 0), 0, 0, "Up &W", cb_up));
		game_menu.attach(new Button(Point(0, 0), 0, 0, "Down &S", cb_down));
		game_menu.attach(new Button(Point(0, 0), 0, 0, "Left &A", cb_left));
		game_menu.attach(new Button(Point(0, 0), 0, 0, "Right &D", cb_right));
		game_menu.attach(new Button(Point(0, 0), 0, 0, "Restart &R", cb_restart));
		attach(game_menu);
		attach(begin_button);
		game_menu.hide();
		attach(show_state);
		show_state.put("Init!");
		attach(max_grade);
		max_grade.put("no grade");
	}

	~Game_medium() { }

	static bool CreateNum();
	int state();
	int maxgrade();
	void setcolor();

	void begin_pressed();
	void up_pressed();
	void down_pressed();
	void left_pressed();
	void right_pressed();
	void restart_pressed();

	static void cb_begin(Address, Address);
	static void cb_up(Address, Address);
	static void cb_down(Address, Address);
	static void cb_left(Address, Address);
	static void cb_right(Address, Address);
	static void cb_restart(Address, Address);
};

