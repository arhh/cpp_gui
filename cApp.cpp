#include "cApp.h"

// preprocessor directive to create a special main() function.
// internals do not matter for wxWidgets development
wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {

}

bool cApp::OnInit() {
    // instantiate the main window and show it on screen.
    m_frame_1 = new cMain();
    m_frame_1->Show();

    return true;
}
