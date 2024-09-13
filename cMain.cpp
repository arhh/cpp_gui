#include "cMain.h"

// one of many ways to bind events to handlers
wxBEGIN_EVENT_TABLE(cMain, wxFrame)
// PART 1 EXERCISE
//    EVT_BUTTON(10001, cMain::OnButtonClicked)
wxEND_EVENT_TABLE()

// call the base class's constructor with null parent, random id, title, position, and width-height
cMain::cMain() : wxFrame(nullptr, wxID_ANY, "cMain Frame", wxPoint(30, 30), wxSize(800, 600)) {
    // PART 1 EXERCISE
    // m_btn1 = new wxButton(this, 10001, "Click Me", wxPoint(10, 10), wxSize(150, 50));
    // m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
    // m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));

    // PART 2 EXERCISE
    // We are initialising an array of pointers to wxButton objects
    // Just like myVar = new int[5] ...initialises an array of five integers. 
    buttonsArray = new wxButton*[nFieldHeight * nFieldWidth];
    wxGridSizer* gridSizerPtr = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

    // the grid of mines is the same size as buttons array
    nMineFields = new int[nFieldHeight * nFieldWidth];

    // part 3 exercise
    // adjust our font on squares to make clearer
    // Same as: wxFont *buttonFont = new wxFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
    // except above will allocate memory on heap instead of stack so need to call "delete" for the above statement.
    wxFont buttonFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

    for (int i = 0; i < nFieldWidth; i++)
    {
        for (int j = 0; j < nFieldHeight; j++) {
            buttonsArray[j * nFieldWidth + i] = new wxButton(this, 10000 + (j * nFieldWidth + i));
            (*buttonsArray[j * nFieldWidth + i]).SetFont(buttonFont);
            gridSizerPtr->Add(buttonsArray[j * nFieldWidth + i], 1, wxEXPAND | wxALL);
        
            // Bind event handler to the button we just added
            buttonsArray[j * nFieldWidth + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
            nMineFields[j * nFieldWidth + i] = 0;
        }
    }

    this->SetSizer(gridSizerPtr);
    this->Layout();
    
}

cMain::~cMain() {}

void cMain::OnButtonClicked(wxCommandEvent &evt) {
    // PART 1 EXERCISE
    // m_list1->AppendString(m_txt1->GetValue());

    // PART 2 EXERCISE
    int x = (evt.GetId() - 10000) % nFieldWidth;
    int y = (evt.GetId() - 10000) / nFieldWidth;

    // Place mines across board only when it is the first click by user
    if (bFirstClick) {
        int remainingMines = 30;

        // Randomly scatter mines (denoted by -1) across board but not on button just clicked
        while (remainingMines) {
            int randomX = rand() % nFieldWidth;
            int randomY = rand() % nFieldHeight;

            if (nMineFields[randomY * nFieldWidth + randomX] == 0 &&
                                            randomX != x && randomY != y) {
                
                nMineFields[randomY * nFieldWidth + randomX] = -1;
                remainingMines--;
            }
        }

        bFirstClick = false;
    }

    // Disable the button just clicked so user cannot click again.
    buttonsArray[y * nFieldWidth + x]->Enable(false);

    if (nMineFields[y * nFieldWidth + x] == -1) {
        wxMessageBox("Game Over!");

        // Reset game by setting next click to be first, removing all mines and labels
        bFirstClick = true;
        for (int x = 0; x < nFieldWidth; x++) {
            for (int y = 0; y < nFieldHeight; y++) {
                nMineFields[y * nFieldWidth + x] = 0;
                buttonsArray[y * nFieldWidth + x]->SetLabel("");
                buttonsArray[y * nFieldWidth + x]->Enable(true);
            }
        }
    } else {
        // If user didn't click mine, check for mine around eight neighbours and keep a count of them.
        int neighbourMineCount = 0;
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight) {

                    if (nMineFields[(y + j) * nFieldWidth + (x + i)] == -1) {
                        neighbourMineCount++;
                    }
                }
            }
        }

        if (neighbourMineCount > 0) {
            buttonsArray[y * nFieldWidth + x]->SetLabel(std::to_string(neighbourMineCount));
        }
    }

    // tell c++ not to bubble-up the event since we fully handled it here.
    evt.Skip();
}