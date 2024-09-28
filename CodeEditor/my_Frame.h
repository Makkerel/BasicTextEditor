#pragma once
#include "wx/wx.h"
#include "wx/tglbtn.h"
#include "wx/treectrl.h"
#include "wx/dir.h"
#include "wx/aui/framemanager.h"
#include "wx/aui/auibook.h"
#include "wx/artprov.h"
#include "wx/imaglist.h"
#include "wx/utils.h"
#include "wx/stdpaths.h"

#include "custom_text.h"
#include "custom_status_bar.h"
#include "dir_traverser.h"
#include "tree_data.h"

class my_Frame : public wxFrame
{
public:
	my_Frame(const wxString& title, const wxPoint& point, const wxSize& size);
private:
	wxToggleButton* open_folder{ nullptr };
	wxButton* settings{ nullptr };
	wxMenuBar* top_menu{ nullptr };
	wxAuiNotebook* text_tabs{ nullptr };
	wxTreeCtrl* folder_shower{ nullptr };
	custom_status_bar* main_bar;
	wxAuiManager* window_manager{ nullptr };
private:
	void create_menu();
	
	//Text Load and Save Functions
	void close_tab(wxAuiNotebookEvent& event);
	void load_file(wxTreeEvent& event);

	//Button Functions
	void toggle_tree(wxCommandEvent& event);

	//All Menu Related Functions
	void new_file(wxCommandEvent& event);
	void new_window(wxCommandEvent& event);
	void file_open(wxCommandEvent& event);
	void folder_open(wxCommandEvent& event);
	void file_save(wxCommandEvent& event);
	void save_file_as(wxCommandEvent& event);
	void exit(wxCommandEvent& event);

	//Changes Numbers on Status Bar
	void update_status(wxStyledTextEvent& event);
	void set_status(wxAuiNotebookEvent& event);

	//Font Functions
	void set_font_for_ui(wxFontPickerEvent& event);
};