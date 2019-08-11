/*Author: Kechun Xu*/
/*Created on 2019.6.2*/
#include "Rect_with_text.h"

Rect_with_text::Rect_with_text(Point xy, int ww, int hh, const int s) : w(ww), h(hh), lab(to_string(s)), fnt(fl_font()), fnt_sz(fl_size())
{
	add(xy);
	if (h <= 0 || w <= 0) error("Bad rectangle: non-positive side");
}

void Rect_with_text::draw_lines() const
{
	if (fill_color().visibility()) {    // fill
		fl_color(fill_color().as_int());
		fl_rectf(point(0).x, point(0).y, w, h);
	}

	if (color().visibility()) {    // lines on top of fill
		fl_color(color().as_int());
		fl_rect(point(0).x, point(0).y, w, h);
	}
	int ofnt = fl_font();
	int osz = fl_size();
	fl_font(fnt.as_int(), fnt_sz);
	fl_draw(lab.c_str(), point(0).x + w / 3, point(0).y + 2 * h / 3);
	fl_font(ofnt, osz);
}

int Rect_with_text::num() const
{
	if (lab == " ")
	{
		return 0;
	}
	else
	{
		return stoi(lab, 0, 10);
	}
}
