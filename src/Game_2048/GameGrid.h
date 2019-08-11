/*Author: Kechun Xu*/
/*Created on 2019.6.2*/
#pragma once
#include <iostream>
#include <sstream>

#include <memory>
#include <vector>
#include <cassert>
#include "FL/Fl_Button.H"
#include "FL/Fl_Shared_Image.H"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Menu_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Timer.H>
#include "Window.h"
#include "Graph.h" 
#include <FL/Fl_Button.H>
#include <string>
#include "Point.h"
#include "Simple_window.h"
#include "Rect_with_text.h"
#include <string>

class Game_Grid
{
	int w;
	int h;
	int type;
	Point xy;
	static Rect_with_text game[4][4];
public:
	Game_Grid(int w, int h, int type);
	~Game_Grid() {}
	static bool CreateNum();
	int handle(int event);
	void up_cb();
    void down_cb();
	void left_cb();
	void right_cb();
	int state();
	void gui(int state);
};


