#include "dir_traverser.h"

dir_traverser::dir_traverser(wxTreeCtrl* main_folder_shower, const wxString& root)
	: folder_shower(main_folder_shower) 
{
	folder_stack.push_back(std::make_pair(root, folder_shower->GetRootItem()));
}

wxDirTraverseResult dir_traverser::OnFile(const wxString& file) {
	size_t last_slash = file.find_last_of("/\\");
	wxString directory = file.substr(0, last_slash);
	wxString name = file.substr(last_slash + 1);

	for (const auto& pair : folder_stack) {
		if (pair.first == directory) {
			tree_data* file_name = new tree_data(file);
			folder_shower->AppendItem(pair.second, name, 1, -1, file_name);
			return wxDIR_CONTINUE;
		}
	}
	folder_shower->AppendItem(folder_stack.back().second, name);
	return wxDIR_CONTINUE;
}

wxDirTraverseResult dir_traverser::OnDir(const wxString& folder) {
	size_t last_slash = folder.find_last_of("/\\");
	wxString directory = folder.substr(0, last_slash);
	wxString name = folder.substr(last_slash + 1);

	for (const auto& pair : folder_stack) {
		if (pair.first == directory) {
			tree_data* folder_name = new tree_data(folder);
			folder_stack.push_back(std::make_pair(folder, folder_shower->AppendItem(pair.second, name, 0, -1, folder_name)));
			return wxDIR_CONTINUE;
		}
	}
	folder_stack.push_back(std::make_pair(folder, folder_shower->AppendItem(folder_stack.back().second, name)));
	return wxDIR_CONTINUE;
}	