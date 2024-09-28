#pragma once
#include "wx/wx.h"
#include "wx/treectrl.h"
class tree_data: public wxTreeItemData
{
public:
	tree_data(const wxString& name);
	wxString get_path();
	bool is_opened();
	void set_open(bool value);
	void set_path(const wxString& new_path);
private:
	wxString path;
	bool opened{ false };
};
