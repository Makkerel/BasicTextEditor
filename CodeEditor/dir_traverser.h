#pragma once
#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/treectrl.h"
#include <vector>
#include <utility>
#include <string>

#include "tree_data.h"


class dir_traverser : public wxDirTraverser
{
public:
	dir_traverser(wxTreeCtrl* main_folder_shower, const wxString& root);

	virtual wxDirTraverseResult OnFile(const wxString& file);
	virtual wxDirTraverseResult OnDir(const wxString& folder);

private:
	wxTreeCtrl* folder_shower;
	std::vector<std::pair<wxString,wxTreeItemId>> folder_stack;
};

