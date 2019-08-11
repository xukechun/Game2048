/*Author: Kechun Xu*/
/*Created on 2019.6.2*/
#include <iostream>
#include "Gamegraph.h"
#include <FL/Fl_JPEG_Image.H>

using namespace Graph_lib;
using namespace Gamegraph_lib;
using namespace std;


bool isPauseTime;
int useTime = 0;

void callback(void*)
{
	useTime++;
	//cout << "time:" << useTime << endl;
	if (useTime > 10000)//·ÅÖÃÒç³ö
	{
		useTime = 0;
	}
	if (isPauseTime) useTime--;
	Fl::repeat_timeout(1.0, callback);
}

int main()
{
	try {
		Gamegraph_lib::Applicant_window win(Point(500, 250), 600, 400, "2048 based on FLTK");
		Fl::add_timeout(1.0, callback);
		return gui_main();
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}
}
