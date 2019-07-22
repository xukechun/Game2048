#pragma once
#include "Graph.h"         
#include "Window.h"
#include "Simple_window.h"
#include <string>
#include <cstring>


//Draw our game grid
class Rect_with_text : public Shape
{
	string lab;
	Font fnt;
	int fnt_sz;
	int w;
	int h;
public:
	Rect_with_text() : fnt(fl_font()), fnt_sz(fl_size()) { }
	Rect_with_text(Point xy, int ww, int hh, const int s);
	void reset(Point xy, int ww, int hh, const int s) { add(xy); w = ww; h = hh; lab = to_string(s); }
	void reset(Point xy, int ww, int hh, const string& s) { add(xy); w = ww; h = hh; lab = s; }

	void draw_lines() const;

	int height() const { return h; }
	int width() const { return w; }

	void set_num(const int s) { /*if (s == 0) lab = " ";*/ lab = to_string(s); }
	string label() const { return lab; }
	int num() const;
	void set_font(Font f) { fnt = f; }
	Font font() const { return Font(fnt); }
	void set_font_size(int s) { fnt_sz = s; }
	int font_size() const { return fnt_sz; }

	~Rect_with_text() {}
};
