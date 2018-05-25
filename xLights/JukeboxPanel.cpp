//(*InternalHeaders(JukeboxPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/button.h>

#include "JukeboxPanel.h"
#include "sequencer/MainSequencer.h"
#include "xLightsApp.h"
#include "xLightsMain.h"
#include "LinkJukeboxButtonDialog.h"

ButtonControl::ButtonControl(int i)
{
    _element = "";
    _layer = -1;
    _time = -1;
    _number = i;
    _description = "";
    _tooltip = "";
    _type = LOOKUPTYPE::LTDISABLED;
}

ButtonControl::ButtonControl(int i, std::string description, std::string tooltip)
{
    _element = "";
    _tooltip = tooltip;
    _layer = -1;
    _time = -1;
    _number = i;
    _description = description;
    _type = LOOKUPTYPE::LTDESCRIPTION;
}

ButtonControl::ButtonControl(int i, std::string element, int layer, int time, std::string tooltip)
{
    _element = element;
    _layer = layer;
    _time = time;
    _number = i;
    _description = "";
    _tooltip = tooltip;
    _type = LOOKUPTYPE::LTMLT;
}

ButtonControl::ButtonControl(wxXmlNode* n)
{
    _element = "";
    _layer = -1;
    _time = -1;
    _number = -1;
    _description = "";
    _tooltip = "";
    _type = LOOKUPTYPE::LTDISABLED;

    if (n->GetName() == "Button")
    {
        _element = n->GetAttribute("Element", "").ToStdString();
        _layer = wxAtoi(n->GetAttribute("Layer", "-1"));
        _time = wxAtoi(n->GetAttribute("Time", "-1"));
        _number = wxAtoi(n->GetAttribute("Number", "-1"));
        _description = n->GetAttribute("Description", "").ToStdString();
        _tooltip = n->GetAttribute("Tooltip", "").ToStdString();
        _type = n->GetAttribute("Type", "") == "DESCRIPTION" ? LOOKUPTYPE::LTDESCRIPTION : LOOKUPTYPE::LTMLT;
    }
}

wxXmlNode* ButtonControl::Save()
{
    auto res = new wxXmlNode(wxXML_ELEMENT_NODE, "Button");
    res->AddAttribute("Type", _type == LOOKUPTYPE::LTDESCRIPTION ? "DESCRIPTION" : "MLT");
    res->AddAttribute("Description", _description);
    res->AddAttribute("Tooltip", _tooltip);
    res->AddAttribute("Element", _element);
    res->AddAttribute("Layer", wxString::Format("%d", _layer));
    res->AddAttribute("Time", wxString::Format("%d", _time));
    res->AddAttribute("Number", wxString::Format("%d", _number));
    return res;
}

void ButtonControl::SelectEffect(MainSequencer* sequencer)
{
    if (sequencer != nullptr)
    {
        if (_type == LOOKUPTYPE::LTDESCRIPTION)
        {
            sequencer->SelectEffectUsingDescription(_description);
        }
        else if (_type == LOOKUPTYPE::LTMLT)
        {
            sequencer->SelectEffectUsingElementLayerTime(_element, _layer - 1, _time);
        }
    }
}

//(*IdInit(JukeboxPanel)
//*)

BEGIN_EVENT_TABLE(JukeboxPanel,wxPanel)
	//(*EventTable(JukeboxPanel)
	//*)
END_EVENT_TABLE()

JukeboxPanel::JukeboxPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(JukeboxPanel)
	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	GridSizer1 = new wxGridSizer(0, 5, 0, 0);
	SetSizer(GridSizer1);
	GridSizer1->Fit(this);
	GridSizer1->SetSizeHints(this);

	Connect(wxEVT_SIZE,(wxObjectEventFunction)&JukeboxPanel::OnResize);
	//*)

    GridSizer1->SetCols(5);
    for (int i = 0; i < JUKEBOXBUTTONS; i++)
    {
        wxButton* button = new wxButton(this, wxID_ANY, wxString::Format("%d", i + 1), wxDefaultPosition, wxSize(BUTTONWIDTH, BUTTONHEIGHT),
            0, wxDefaultValidator, _T("ID_BITMAPBUTTON_JB") + wxString::Format("%d", i + 1));
        button->SetMinSize(wxSize(BUTTONWIDTH, BUTTONHEIGHT));
        button->SetMaxSize(wxSize(BUTTONWIDTH, BUTTONHEIGHT));
        GridSizer1->Add(button, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, i);
        Connect(button->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, (wxObjectEventFunction)&JukeboxPanel::OnButtonClick);
        Connect(button->GetId(), wxEVT_CONTEXT_MENU, (wxObjectEventFunction)&JukeboxPanel::OnButtonRClick);
        if (i == 0)
            _defaultColour = button->GetBackgroundColour();
    }

    // This is used by xSchedule
    SetLabel("XLIGHTS_JUKEBOX");

    wxSizeEvent evt;
    OnResize(evt);

    GridSizer1->Fit(this);
    GridSizer1->SetSizeHints(this);

    ValidateWindow();
}

JukeboxPanel::~JukeboxPanel()
{
	//(*Destroy(JukeboxPanel)
	//*)

    for (auto it = _buttons.begin(); it != _buttons.end(); ++it)
    {
        SetButtonTooltip(it->second->_number, "");
        delete it->second;
    }
}

wxXmlNode* JukeboxPanel::Save()
{
    auto res = new wxXmlNode(wxXML_ELEMENT_NODE, "Jukebox");
    for (auto it = _buttons.begin(); it != _buttons.end(); ++it)
    {
        res->AddChild((*it).second->Save());
    }

    return res;
}

void JukeboxPanel::SetButtonTooltip(int b, std::string tooltip)
{
    wxWindow* button = FindWindowByLabel(wxString::Format("%d", b), this);
    if (button != nullptr)
    {
        if (tooltip == "")
        {
            button->UnsetToolTip();
        }
        else
        {
            button->SetToolTip(tooltip);
        }
    }
}

void JukeboxPanel::Load(wxXmlNode* node)
{
    for (auto it = _buttons.begin(); it != _buttons.end(); ++it)
    {
        SetButtonTooltip(it->second->_number, "");
        delete it->second;
    }
    _buttons.clear();

    if (node->GetName() == "Jukebox")
    {
        for (wxXmlNode* n = node->GetChildren(); n != nullptr; n = n->GetNext())
        {
            ButtonControl* b = new ButtonControl(n);
            _buttons[b->_number] = b;
            SetButtonTooltip(b->_number, b->_tooltip);
        }
    }
    ValidateWindow();
}

void JukeboxPanel::PlayItem(int item)
{
    if (_buttons.find(item) != _buttons.end())
    {
        _buttons[item]->SelectEffect(xLightsApp::GetFrame()->GetMainSequencer());
    }
    else
    {
        xLightsApp::GetFrame()->GetMainSequencer()->UnselectAllEffects();
        xLightsApp::GetFrame()->GetMainSequencer()->SetPlayStatus(PLAY_TYPE_STOPPED);
        xLightsApp::GetFrame()->UnselectEffect();

        // turn all the lights off in case we are outputting to lights
        xLightsApp::GetFrame()->GetOutputManager()->AllOff();
    }
}

void JukeboxPanel::OnResize(wxSizeEvent& event)
{
    wxSize wsz = event.GetSize();
    if (wsz.GetWidth() <= 10) {
        return;
    }

    if (wsz.GetWidth() < 10) return;

    double cols = wsz.GetWidth() * JUKEBOXBUTTONS;
    cols /= std::max(wsz.GetHeight(), 1);
    cols = std::sqrt(cols);
    int i = std::round(cols);

    GridSizer1->SetCols(i);
    GridSizer1->SetDimension(0, 0, wsz.GetWidth(), wsz.GetHeight());
    GridSizer1->RecalcSizes();
}

void JukeboxPanel::OnButtonClick(wxCommandEvent& event)
{
    int button = wxAtoi(((wxButton*)event.GetEventObject())->GetLabel());
    PlayItem(button);
}

void JukeboxPanel::OnButtonRClick(wxContextMenuEvent& event)
{
    int button = wxAtoi(((wxButton*)event.GetEventObject())->GetLabel());

    ButtonControl* control = nullptr;
    if (_buttons.find(button) != _buttons.end())
    {
        control = _buttons[button];
    }

    LinkJukeboxButtonDialog dlg(this, button, control, xLightsApp::GetFrame()->GetMainSequencer());

    if (dlg.ShowModal() == wxID_OK)
    {
        if (control != nullptr)
        {
            SetButtonTooltip(control->_number, "");
            delete control;
            _buttons.erase(button);
        }

        if (dlg.RadioButton_ED->GetValue())
        {
            control = new ButtonControl(button, dlg.Choice_Description->GetStringSelection().ToStdString(), dlg.TextCtrl_Tooltip->GetValue().ToStdString());
        }
        else
        {
            control = new ButtonControl(button, dlg.Choice_Model->GetStringSelection().ToStdString(), wxAtoi(dlg.Choice_Layer->GetStringSelection()), wxAtoi(dlg.Choice_Time->GetStringSelection()), dlg.TextCtrl_Tooltip->GetValue().ToStdString());
        }
        _buttons[button] = control;
        SetButtonTooltip(control->_number, control->_tooltip);
        xLightsApp::GetFrame()->GetMainSequencer()->SetChanged();
        ValidateWindow();
    }
}

void JukeboxPanel::ValidateWindow()
{
    auto children = GetChildren();

    for (auto it = children.begin(); it != children.end(); ++it)
    {
        int b = wxAtoi((*it)->GetLabel());

        if (b > 0)
        {
            if (_buttons.find(b) != _buttons.end())
            {
                // button has a control
                (*it)->SetBackgroundColour(_defaultColour);
            }
            else
            {
                (*it)->SetBackgroundColour(wxColour(255, 108, 108));
            }
        }
    }
}

wxString JukeboxPanel::GetTooltips()
{
    wxString res = "|";
    for (int i = 0; i < JUKEBOXBUTTONS; i++)
    {
            if (_buttons.find(i+1) != _buttons.end())
            {
        res += _buttons[i+1]->GetTooltip() + "|";
            }
            else
            {
                res += "|";
            }
    }

    return res;
}

wxString JukeboxPanel::GetEffectPresent() const
{
    wxString res = "|";
    for (int i = 0; i < JUKEBOXBUTTONS; i++)
    {
            if (_buttons.find(i+1) != _buttons.end())
            {
        res += "TRUE|";
            }
            else
            {
                res += "|";
            }
    }

    return res;
}
