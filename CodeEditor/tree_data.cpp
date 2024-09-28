#include "tree_data.h"

tree_data::tree_data(const wxString& name)
	: wxTreeItemData()
{
	path = name;
}

wxString tree_data::get_path() {
	return path;
}

bool tree_data::is_opened()
{
	return opened;
}

void tree_data::set_open(bool value) {
	opened = value;
}

void tree_data::set_path(const wxString& new_path) {
	path = new_path;
}