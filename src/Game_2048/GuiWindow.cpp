/*Author: Kechun Xu*/
/*Created on 2019.6.2*/
#include "GuiWindow.h"


GuiWindow::GuiWindow(Point xy1, Point xy2, int w, int h, const string& title, const string &s) :
	Simple_window(xy1, w, h, title),
	t(xy2, s),
	continue_button(Point(x_max() / 2 - 80, 80), 70, 20, "Continue &C", cb_continue),
	quit_button(Point(x_max() - 155, 80), 70, 20, "Quit &Q", cb_quit)
{
	t.set_font_size(16);
	attach(t);
	attach(quit_button);
	attach(continue_button);
}

void GuiWindow::cb_quit(Address, Address pw)    // "the usual"
{
	reference_to<GuiWindow>(pw).quit();
}

void GuiWindow::cb_continue(Address, Address pw)
{
	reference_to<GuiWindow>(pw).continue_();
}

void GuiWindow::quit()
{
	hide();        // curious FLTK idiom for delete window
}

void GuiWindow::continue_()
{
	hide();
}
