#include "my_App.h"
#include "my_Frame.h"
bool my_App::OnInit() {
	my_Frame* main_window = new my_Frame("Pluton", wxPoint(1,1), wxSize(2000, 1000));
	main_window->Maximize();
	main_window->Show();
	return true;
}