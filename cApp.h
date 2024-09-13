#pragma once

#include <wx/wxprec.h>
#include "cMain.h"

// Added in wxWidgets tutorial for compilers not using precompiled headers
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

/* 
 * Class representing the base app on which a gui frame is drawn.
 *
 * Public derived base class means all public members of base are public to callers of this class.
 * and all protected members are protected to callers of this class.
 */
class cApp : public wxApp {
    public:
        cApp();
        ~cApp();
        // public overrideable method that has to be overridden by this class
        // from the base class
        virtual bool OnInit();

    private:
        // private instance attribute representing app's main frame
        cMain* m_frame_1 = NULL;
};