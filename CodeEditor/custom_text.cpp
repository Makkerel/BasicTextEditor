#include "custom_text.h"

custom_text::custom_text(wxWindow* parent, const wxString& file_path, tree_data* tree_data)
	: wxStyledTextCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(0, 0)), path(file_path), tree_connection(tree_data)
{}

wxString custom_text::get_path() {
	return path;
}

tree_data* custom_text::get_tree() {
	return tree_connection;
}

void custom_text::set_path(const wxString& new_path) {
	path = new_path;
}