#pragma once
#include "wx/wx.h"
#include "wx/stc/stc.h"

#include "tree_data.h"

class custom_text : public wxStyledTextCtrl
{
public:
	custom_text(wxWindow* parent, const wxString& file_path, tree_data* tree_data);
	wxString get_path();
	tree_data* get_tree();
	void set_path(const wxString& new_path);
private:
	wxString path;
	tree_data* tree_connection;
};