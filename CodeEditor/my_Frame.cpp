#include "my_Frame.h"

my_Frame::my_Frame(const wxString& title, const wxPoint& point, const wxSize& size)
	:wxFrame(nullptr, wxID_ANY, title, point, size)
{
	window_manager = new wxAuiManager(this);
	main_bar = new custom_status_bar(this);
	SetStatusBar(main_bar);
	
	main_bar->Bind(wxEVT_FONTPICKER_CHANGED, &my_Frame::set_font_for_ui, this);

	top_menu = new wxMenuBar();
	create_menu();

	open_folder = new wxToggleButton(this, wxID_ANY, "File", wxDefaultPosition, wxSize(100,100), wxBU_NOTEXT | wxBORDER_NONE);
	open_folder->SetBackgroundColour(wxColour("White"));
	open_folder->SetBitmap(wxArtProvider::GetBitmapBundle(wxART_FOLDER, wxART_BUTTON, wxSize(48,48)));
	open_folder->SetBitmapPressed(wxArtProvider::GetBitmapBundle(wxART_FOLDER_OPEN, wxART_OTHER ,wxSize(48,48)));
	open_folder->Bind(wxEVT_TOGGLEBUTTON, &my_Frame::toggle_tree, this);

	settings = new wxButton(this, wxID_ANY, "Settings", wxDefaultPosition, wxSize(100,100), wxBORDER_NONE);

	text_tabs = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_CLOSE_ON_ALL_TABS);
	text_tabs->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &my_Frame::close_tab, this);
	text_tabs->Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED, &my_Frame::set_status, this);
	text_tabs->Bind(wxEVT_STC_UPDATEUI, &my_Frame::update_status, this);

	folder_shower = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_SINGLE | wxTR_NO_LINES | wxTR_MULTIPLE);
	wxImageList* tree_list = new wxImageList(16,16,false,2);
	tree_list->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_MENU));
	tree_list->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_BUTTON));
	folder_shower->AssignImageList(tree_list);

	folder_shower->Bind(wxEVT_TREE_SEL_CHANGED, &my_Frame::load_file, this);

	window_manager->AddPane(open_folder, wxAuiPaneInfo().Left().Position(0).Row(0).Fixed().CaptionVisible(false).MaxSize(100, 100));
	window_manager->AddPane(settings, wxAuiPaneInfo().Left().Position(1).Fixed().CaptionVisible(false).MaxSize(100, 100));
	window_manager->AddPane(folder_shower, wxAuiPaneInfo().Row(1).Caption(_("Folder")).BestSize(wxSize(300, 500)));
	window_manager->AddPane(text_tabs, wxAuiPaneInfo().Center().CaptionVisible(false).BestSize(wxSize(1000, 500)));
	window_manager->Update();
}

void my_Frame::create_menu() {
	wxMenu* file_menu = new wxMenu();
	file_menu->Append(wxID_FILE, "New File");
	file_menu->Append(wxID_OPEN, "New Window");
	file_menu->AppendSeparator();
	file_menu->Append(wxID_FILE1, "Open File");
	file_menu->Append(wxID_FILE2, "Open Folder");
	file_menu->AppendSeparator();
	file_menu->Append(wxID_SAVE, "&Save");
	file_menu->Append(wxID_SAVEAS, "Save &As");
	file_menu->Append(wxID_FILE3, "Save All");
	file_menu->AppendSeparator();
	file_menu->Append(wxID_FILE4, "Close Folder");
	file_menu->Append(wxID_CLOSE, "Close Tab");
	file_menu->Append(wxID_CLOSE_ALL, "Close Window");
	file_menu->AppendSeparator();
	file_menu->Append(wxID_EXIT, "Exit");

	wxMenu* edit_menu = new wxMenu();
	edit_menu->Append(wxID_CUT);
	edit_menu->Append(wxID_COPY);
	edit_menu->Append(wxID_PASTE);
	edit_menu->Append(wxID_DELETE);
	edit_menu->AppendSeparator();
	edit_menu->Append(wxID_UNDO);
	edit_menu->Append(wxID_REDO);
	edit_menu->AppendSeparator();
	edit_menu->Append(wxID_SELECTALL);

	wxMenu* view_menu = new wxMenu();
	view_menu->AppendCheckItem(wxID_FILE5, "File Explorer");
	view_menu->AppendCheckItem(wxID_FILE6, "Status Bar");

	top_menu->Append(file_menu, "&File");
	top_menu->Append(edit_menu, "Edit");
	top_menu->Append(view_menu, "View");
	SetMenuBar(top_menu);

	top_menu->Bind(wxEVT_MENU, &my_Frame::new_file, this, wxID_FILE, wxID_FILE);
	top_menu->Bind(wxEVT_MENU, &my_Frame::new_window, this, wxID_OPEN, wxID_OPEN);
	top_menu->Bind(wxEVT_MENU, &my_Frame::file_open, this, wxID_FILE1, wxID_FILE1);
	top_menu->Bind(wxEVT_MENU, &my_Frame::folder_open, this, wxID_FILE2, wxID_FILE2);
	top_menu->Bind(wxEVT_MENU, &my_Frame::file_save, this, wxID_SAVE, wxID_SAVE);
	top_menu->Bind(wxEVT_MENU, &my_Frame::save_file_as, this, wxID_SAVEAS, wxID_SAVEAS);
	top_menu->Bind(wxEVT_MENU, &my_Frame::exit, this, wxID_EXIT, wxID_EXIT);
}

void my_Frame::new_file(wxCommandEvent& event) {
	tree_data* new_file = new tree_data("new");
	new_file->set_open(true);
	custom_text* untitled = new custom_text(text_tabs, "new", new_file);
	text_tabs->AddPage(untitled, "Untitled", true);
	folder_shower->AppendItem(folder_shower->GetRootItem(), "Untitled", 1, -1, new_file);
}

void my_Frame::new_window(wxCommandEvent& event) {
	wxExecute(wxStandardPaths::Get().GetExecutablePath(), wxEXEC_ASYNC, nullptr);
}

void my_Frame::file_open(wxCommandEvent& event) {
	wxFileDialog* OpenDialog = new wxFileDialog(this, _("Choose a text file to open"), wxEmptyString, wxEmptyString, "", wxFD_OPEN, wxDefaultPosition);

	if (OpenDialog->ShowModal() == wxID_OK) {
		wxString path = OpenDialog->GetPath();
		custom_text* current_tab = new custom_text(text_tabs, path, nullptr);
		text_tabs->AddPage(current_tab, OpenDialog->GetFilename());
		current_tab->LoadFile(path);
	}

	OpenDialog->Destroy();
}

void my_Frame::folder_open(wxCommandEvent& event) {
	wxDirDialog* dir_pick = new wxDirDialog(this, "Pick a Folder", "", wxDD_DEFAULT_STYLE | wxDD_SHOW_HIDDEN);

	if (dir_pick->ShowModal() == wxID_OK) {
		folder_shower->DeleteAllItems();
		wxString path = dir_pick->GetPath();
		wxDir dir(path);
		wxString name = dir.GetName();
		name = (name.find_last_of("/\\") == std::string::npos) ? name : name.substr(name.find_last_of("/\\") + 1);

		folder_shower->AddRoot(name, 0, -1);
		dir_traverser file_trav(folder_shower, dir.GetName());
		dir.Traverse(file_trav, "", wxDIR_DEFAULT);
		folder_shower->ExpandAll();
	}

	dir_pick->Destroy();
}

void my_Frame::file_save(wxCommandEvent& event) {
	custom_text* current_tab = static_cast<custom_text*>(text_tabs->GetCurrentPage());
	if (current_tab->get_path() == "new") {
		save_file_as(event);
		return;
	}
	current_tab->SaveFile(current_tab->get_path());
}

void my_Frame::save_file_as(wxCommandEvent& event) {
	wxFileDialog* save_dialog = new wxFileDialog(this, "Save File As", wxEmptyString, wxEmptyString, wxEmptyString, wxFD_SAVE | wxFD_OVERWRITE_PROMPT, wxDefaultPosition);

	if (save_dialog->ShowModal() == wxID_OK) {
		custom_text* current_tab = static_cast<custom_text*>(text_tabs->GetCurrentPage());
		if (current_tab->get_path() == "new") {
			current_tab->set_path(save_dialog->GetPath());
			current_tab->get_tree()->set_path(save_dialog->GetPath());
			wxTreeItemId tree = current_tab->get_tree()->GetId();
			folder_shower->SetItemText(tree, save_dialog->GetFilename());
		}
		current_tab->SaveFile(save_dialog->GetPath());
	}

	save_dialog->Destroy();
}

void my_Frame::exit(wxCommandEvent& event) {
	Close(true);
}

void my_Frame::load_file(wxTreeEvent& event) {
	wxTreeItemId file = event.GetItem();
	if (folder_shower->HasChildren(file)) {
		event.Veto();
		return;
	}

	tree_data* data = static_cast<tree_data*>(folder_shower->GetItemData(file));
	if (data->is_opened()) {
		folder_shower->UnselectItem(file);
		return;
	}

	custom_text* new_tab = new custom_text(text_tabs, data->get_path(), data);
	if (!new_tab->LoadFile(data->get_path())) {
		new_tab->Destroy();
		return;
	}
	data->set_open(true);
	text_tabs->AddPage(new_tab, folder_shower->GetItemText(file), true);
	folder_shower->UnselectItem(file);
}

void my_Frame::close_tab(wxAuiNotebookEvent& event) {
	custom_text* close_tab = static_cast<custom_text*>(text_tabs->GetPage(event.GetSelection()));
	if (close_tab->get_path() == "new") {
		save_file_as(event);
		close_tab->get_tree()->set_open(false);
		return;
	}
	close_tab->SaveFile(close_tab->get_path());
	if (close_tab->get_tree()) {
		close_tab->get_tree()->set_open(false);
	}
}

void my_Frame::toggle_tree(wxCommandEvent& event) {
	if (open_folder->GetValue()) {
		open_folder->SetBackgroundColour(wxColour("Black"));
		window_manager->GetPane(folder_shower).Hide();
		window_manager->Update();
	}
	else {
		open_folder->SetBackgroundColour(wxColour("White"));
		window_manager->GetPane(folder_shower).Show();
		window_manager->Update();
	}
}

void my_Frame::update_status(wxStyledTextEvent& event) {
	custom_text* update_tab = static_cast<custom_text*>(text_tabs->GetCurrentPage());
	main_bar->update_text_info(update_tab->GetCurrentLine(), update_tab->GetColumn(update_tab->GetCurrentPos()), update_tab->GetTextLength());
	event.Skip();
}

void my_Frame::set_status(wxAuiNotebookEvent& event) {
	custom_text* update_tab = static_cast<custom_text*>(text_tabs->GetCurrentPage());
	main_bar->update_text_info(0, 0, update_tab->GetTextLength());
	event.Skip();
}

void my_Frame::set_font_for_ui(wxFontPickerEvent& event) {
	SetFont(event.GetFont());
	folder_shower->SetFont(event.GetFont());
	text_tabs->SetFont(event.GetFont());
	main_bar->change_fonts(event.GetFont());
}