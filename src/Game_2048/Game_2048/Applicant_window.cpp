#include "Applicant_window.h"


Applicant_window::Applicant_window(Point xy, int w, int h, const string& title)
	:Window(xy, w, h, title),
	application_menu(Point(x_max() / 2 - 75, 150), 150, 50, Menu::vertical, "Menu"),
	menu_button(Point(x_max() / 2 - 75, y_max() / 2 - 60), 150, 50, "application menu &A", cb_menu),
	quit_button(Point(x_max() - 70, 0), 70, 20, "Quit &Q", cb_quit),
	welcome(Point(x_max() / 2 - 75, 90), "Welcome to 2048!")
	//background(Point(0, 0), "2048.jpg")
{
	//Image background(Point(500, 300), "2048.jpg");	
	//background.set_mask(Point(500, 300), 600, 400);
	//attach(background);
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

//------------------------------------------------------------------------------

void Applicant_window::cb_menu(Address, Address pw)
{
	reference_to<Applicant_window>(pw).menu_pressed();
}

void Applicant_window::cb_quit(Address, Address pw)    // "the usual"
{
	reference_to<Applicant_window>(pw).quit();
}

//------------------------------------------------------------------------------

void Applicant_window::quit()
{
	hide();        // curious FLTK idiom for delete window
}

//------------------------------------------------------------------------------

void Applicant_window::cb_explain(Address, Address pw)     // "the usual"
{
	reference_to<Applicant_window>(pw).explain_pressed();
}

//------------------------------------------------------------------------------

void Applicant_window::explain_pressed()
{
	Simple_window winhelp(Point(500, 250), 600, 400, "About 2048");
	//Rectangle r(Point(100, 50), 200, 300);
	//winhelp.attach(r);
	winhelp.wait_for_button();
}

//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

void Applicant_window::game1_pressed()     // "the usual"
{
	int w = 50, h = 50;
	Game_window wingame(Point(500, 250), 600, 400, "2048");
	wingame.wait_for_button();
}

void Applicant_window::game2_pressed()     // "the usual"
{
	int w = 50, h = 50;
	Game_medium wingame(Point(500, 250), 600, 400, "2048");
	wingame.wait_for_button();
}

void Applicant_window::game3_pressed()     // "the usual"
{
	int w = 50, h = 50;
	Game_hard wingame(Point(400, 150), 700, 500, "2048");
	//use_time.put(to_string(useTime));
	wingame.wait_for_button();
	//ShowBox* m_pTimeShowBox;//时间显示器
	//m_pTimeShowBox = ShowBox::getInstance();
	//m_pTimeShowBox->resize(0, 20, 50, timeShowBoxHeight);
	//m_pTimeShowBox->showGrade(0);
	//wingame.add(m_pTimeShowBox);
	//wingame.begin();//往窗体里面添加对象
	//wingame.wait_for_button();
}
