#pragma once

#include <wx/wxprec.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

/* 
 * Class representing the main frame of the app.
 */
class cMain : public wxFrame {
    public:
        cMain();
        ~cMain();

        // PART 2 EXERCISE
        // wxButton* m_btn1 = nullptr;
        // wxTextCtrl* m_txt1 = nullptr;
        // wxListBox* m_list1 = nullptr;

        int nFieldWidth = 10;
        int nFieldHeight = 10;

        // This is a 1D array. It will have 100 items (see .cpp definition code)
        // representing a 2D grid.
        // We are creating a pointer to an array of pointers to wxButton objects
        wxButton** buttonsArray;

        // list of cells with a mine in it
        int *nMineFields = nullptr;

        // whether the user's click is their first click.
        // simply prevents scenario where the first click by user is a mine and ends game.
        bool bFirstClick = true;

        void OnButtonClicked(wxCommandEvent &evt);

        // must be here to enable event handlers
        wxDECLARE_EVENT_TABLE();

};