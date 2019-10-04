#pragma once
#include "wx/wx.h"

class DragColoursBitmapButton : public wxBitmapButton
{
    public:
        DragColoursBitmapButton (wxWindow *parent, wxWindowID id, const wxBitmap &bitmap, const wxPoint &pos=wxDefaultPosition,
                                const wxSize &size=wxDefaultSize, long style=wxBU_AUTODRAW, const wxValidator &validator=wxDefaultValidator,
                                const wxString &name=wxButtonNameStr);
        virtual void DoSetSizeHints( int minW, int minH,
                                int maxW, int maxH,
                                int incW, int incH );
        virtual ~DragColoursBitmapButton();
        void OnMouseLeftDown (wxMouseEvent& event);
        void SetBitmap(const wxBitmap &bmp);
        void SetColour(const std::string& colour);
        std::string GetColour() const { return _c; }

    protected:
    private:
        wxString (*GetStringFunction)();
        std::string _c;
};
