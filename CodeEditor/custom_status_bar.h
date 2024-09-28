#pragma once
#include "wx/wx.h"
#include "wx/fontpicker.h"

class custom_status_bar : public wxStatusBar
{
public:
	custom_status_bar(wxWindow* parent);
	void update_text_info(int line, int column, int chars);
	void update_all(int line_end, int line, int column, int chars);
	void change_fonts(const wxFont& font);

private:
	wxBoxSizer* bar_sizer;
	wxFontPickerCtrl* font_picker;
	wxStaticText* end_of_line;
	wxStaticText* encoding;
	wxStaticText* line_count;
	wxStaticText* column_count;
	wxStaticText* char_count;
};

