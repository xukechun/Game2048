/*Author: Kechun Xu*/
/*Created on 2019.6.2*/
#pragma once
#include "Graph.h"         
#include "GUI.h"
#include "Simple_window.h"
#include "Point.h"


//GUI when fail or win
class GuiWindow : public Simple_window
{
	int w;  //window's width
	int h; //window's height
	Text t;
	Button quit_button;
	Button continue_button;
public:
	GuiWindow(Point xy1, Point xy2, int w, int h, const string& title, const string &s);  // window top left corner in xy1, text top left corner in xy2
	~GuiWindow() {}
	void continue_();
	void quit();
	static void cb_continue(Address, Address);  //continue game
	static void cb_quit(Address, Address);  //quit gui
};
