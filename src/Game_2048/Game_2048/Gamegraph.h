#pragma once
#ifndef GAMEGRAPH_GUARD
#define GAMEGRAPH_GUARD 1

#include <string>
#include <memory>
#include "Graph.h" 
#include "GUI.h"
#include "Simple_window.h"       
#include "GUI.h"
#include "FL/forms.H"
#include "Rect_with_text.h"
#include "global.h"
#include <FL/Fl_Clock.h>
#include <FL/Fl_JPEG_Image.H>

namespace Gamegraph_lib {


	class Game_window : public Simple_window               
	{
		Fl_Box backbox;  //background box 
		Fl_JPEG_Image backg;   //background
		Point xy;
		int w;
		int h;
		string title;
		Menu game_menu;
		Button begin_button;
		Button save_button;
		Button load_button;
		Out_box max_grade; //show the max grade
		Out_box show_state; //show your state now
		Fl_Clock *clock;
	public:
		Game_window(Point xy, int w, int h, const string&s);
		~Game_window() { }

		static bool CreateNum();  //Create number at setting probability, which is different in different levels.
		int state();  //Judge the state now.
		void gui(int state);  //Gui with different state.
		int maxgrade(); //Get te max grade now.
		void setcolor(); //Different num colors differently.
		void putstate(); //Output the state now.

		//Callbacks
		void begin_pressed();
		void up_pressed();
		void down_pressed();
		void left_pressed();
		void right_pressed();
		void restart_pressed();
		void save_pressed();
		void load_pressed();

		static void cb_begin(Address, Address);
		static void cb_up(Address, Address);
		static void cb_down(Address, Address);
		static void cb_left(Address, Address);
		static void cb_right(Address, Address);
		static void cb_restart(Address, Address);
		static void cb_save(Address, Address);
		static void cb_load(Address, Address);
	};

	//-------------------------------------------------------------------------
    //Derive from Game_window, but several realization and rules are different.
	class Game_medium :public Game_window   
	{
		Fl_Box backbox;
		Fl_JPEG_Image backg;
		Point xy;
		int w;
		int h;
		string title;
		Menu game_menu;
		Button begin_button;
		Button save_button;
		Button load_button;
		Out_box max_grade;
		Out_box show_state;
		Fl_Widget* clock;
	public:
		Game_medium(Point xy, int w, int h, const string&s);

		~Game_medium() { }

		static bool CreateNum();
		void putstate();
		int state();
		int maxgrade();
		void setcolor();

		void begin_pressed();
		void up_pressed();
		void down_pressed();
		void left_pressed();
		void right_pressed();
		void restart_pressed();
		void save_pressed();
		void load_pressed();

		static void cb_begin(Address, Address);
		static void cb_up(Address, Address);
		static void cb_down(Address, Address);
		static void cb_left(Address, Address);
		static void cb_right(Address, Address);
		static void cb_restart(Address, Address);
		static void cb_save(Address, Address);
		static void cb_load(Address, Address);
	}; 

	//-------------------------------------------------------------------------
	//Derive from Game_window, but several realization and rules are different.
	class Game_hard :public Game_window
	{
		Fl_Box backbox;
		Fl_JPEG_Image backg;
		Point xy;
		int w;
		int h;
		string title;
		Menu game_menu;
		Button begin_button;
		Button save_button;
		Button load_button;
		Out_box max_grade;
		Out_box show_state;
		Fl_Widget* clock;
	public:
		Game_hard(Point xy, int w, int h, const string&s);
		~Game_hard() { }

		static bool CreateNum();
		int state();
		void putstate();
		int maxgrade();
		void setcolor();

		void begin_pressed();
		void up_pressed();
		void down_pressed();
		void left_pressed();
		void right_pressed();
		void restart_pressed();
		void save_pressed();
		void load_pressed();

		static void cb_begin(Address, Address);
		static void cb_up(Address, Address);
		static void cb_down(Address, Address);
		static void cb_left(Address, Address);
		static void cb_right(Address, Address);
		static void cb_restart(Address, Address);
		static void cb_save(Address, Address);
		static void cb_load(Address, Address);
	};

	//-------------------------------------------------------------------------
	//GUI linking to all game_windows
	class Applicant_window : public Window
	{
		Fl_Box backbox;
		Fl_JPEG_Image backg;
		Menu application_menu;
		Button quit_button;
		Button menu_button;
		Text welcome;

	public:
		Applicant_window(Point xy, int w, int h, const string& title);
		~Applicant_window() { }

		void menu_pressed() { menu_button.hide(); application_menu.show(); }
		void explain_pressed();
		static void game1_pressed();
		static void game2_pressed();
		static void game3_pressed();
		void quit();

		static void cb_explain(Address, Address);
		static void cb_game1(Address, Address);
		static void cb_game2(Address, Address);
		static void cb_game3(Address, Address);
		static void cb_menu(Address, Address);
		static void cb_quit(Address, Address);

	};

}
#endif