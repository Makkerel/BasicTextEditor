#include "custom_status_bar.h"

custom_status_bar::custom_status_bar(wxWindow* parent)
	: wxStatusBar(parent, wxID_ANY)
{
	SetFieldsCount(1);
	end_of_line = new wxStaticText(this, wxID_ANY, "CRLF");
	encoding = new wxStaticText(this, wxID_ANY, "UTF-8");
	line_count = new wxStaticText(this, wxID_ANY, "Line: 0");
	column_count = new wxStaticText(this, wxID_ANY, "Column: 0");
	char_count = new wxStaticText(this, wxID_ANY, "Characters: 0");

	font_picker = new wxFontPickerCtrl(this, wxID_ANY, wxNullFont, wxDefaultPosition, wxDefaultSize);

	bar_sizer = new wxBoxSizer(wxHORIZONTAL);
	bar_sizer->Add(end_of_line, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 2));
	bar_sizer->Add(encoding, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 2));
	bar_sizer->Add(1, 1, wxSizerFlags(1).Expand());
	bar_sizer->Add(font_picker, wxSizerFlags().Center().Border(wxLEFT | wxRIGHT, 2));
	bar_sizer->Add(line_count, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 10));
	bar_sizer->Add(column_count, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 10));
	bar_sizer->Add(char_count, wxSizerFlags(0).Center().Border(wxLEFT | wxRIGHT, 10));
	bar_sizer->Add(10, 1, wxSizerFlags(0).Center());
	SetSizer(bar_sizer);
}

void custom_status_bar::update_text_info(int line, int column, int chars) {
	line_count->SetLabel(wxString::Format("Line: %d", line));
	column_count->SetLabel(wxString::Format("Column: %d", column));
	char_count->SetLabel(wxString::Format("Characters: %d", chars));
	bar_sizer->Layout();
}

void custom_status_bar::change_fonts(const wxFont& font) {
	end_of_line->SetFont(font);
	encoding->SetFont(font);
	line_count->SetFont(font);
	column_count->SetFont(font);
	char_count->SetFont(font);
	Layout();
}