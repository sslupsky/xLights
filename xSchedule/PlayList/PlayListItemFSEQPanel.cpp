#include "PlayListItemFSEQPanel.h"
#include "PlayListItemFSEQ.h"
#include "PlayListDialog.h"
#include "../xScheduleMain.h"
#include "../ScheduleManager.h"

//(*InternalHeaders(PlayListItemFSEQPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PlayListItemFSEQPanel)
const long PlayListItemFSEQPanel::ID_STATICTEXT1 = wxNewId();
const long PlayListItemFSEQPanel::ID_FILEPICKERCTRL1 = wxNewId();
const long PlayListItemFSEQPanel::ID_STATICTEXT5 = wxNewId();
const long PlayListItemFSEQPanel::ID_CHOICE1 = wxNewId();
const long PlayListItemFSEQPanel::ID_CHECKBOX3 = wxNewId();
const long PlayListItemFSEQPanel::ID_STATICTEXT6 = wxNewId();
const long PlayListItemFSEQPanel::ID_SPINCTRL2 = wxNewId();
const long PlayListItemFSEQPanel::ID_STATICTEXT7 = wxNewId();
const long PlayListItemFSEQPanel::ID_SPINCTRL3 = wxNewId();
const long PlayListItemFSEQPanel::ID_CHECKBOX1 = wxNewId();
const long PlayListItemFSEQPanel::ID_STATICTEXT2 = wxNewId();
const long PlayListItemFSEQPanel::ID_FILEPICKERCTRL2 = wxNewId();
const long PlayListItemFSEQPanel::ID_CHECKBOX4 = wxNewId();
const long PlayListItemFSEQPanel::ID_CHECKBOX2 = wxNewId();
const long PlayListItemFSEQPanel::ID_SLIDER1 = wxNewId();
const long PlayListItemFSEQPanel::ID_STATICTEXT4 = wxNewId();
const long PlayListItemFSEQPanel::ID_SPINCTRL1 = wxNewId();
const long PlayListItemFSEQPanel::ID_STATICTEXT3 = wxNewId();
const long PlayListItemFSEQPanel::ID_TEXTCTRL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PlayListItemFSEQPanel,wxPanel)
	//(*EventTable(PlayListItemFSEQPanel)
	//*)
END_EVENT_TABLE()

class FSEQFilePickerCtrl : public wxFilePickerCtrl
{
public:
    FSEQFilePickerCtrl(wxWindow *parent,
        wxWindowID id,
        const wxString& path = wxEmptyString,
        const wxString& message = wxFileSelectorPromptStr,
        const wxString& wildcard = wxFileSelectorDefaultWildcardStr,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxFLP_DEFAULT_STYLE,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxFilePickerCtrlNameStr) :
        wxFilePickerCtrl(parent, id, path, message, FSEQFILES, pos, size, style, validator, name)
    {}
    virtual ~FSEQFilePickerCtrl() {}
};

class AudioFilePickerCtrl : public wxFilePickerCtrl
{
#define AUDIOFILES "Audio files|*.mp3;*.ogg;*.m4p;*.mp4;*.avi;*.wma;*.au;*.wav;*.m4a;*.mid;*.mkv;*.mov;*.mpg;*.asf;*.flv;*.mpeg|All Files|*.*"

public:
    AudioFilePickerCtrl(wxWindow *parent,
        wxWindowID id,
        const wxString& path = wxEmptyString,
        const wxString& message = wxFileSelectorPromptStr,
        const wxString& wildcard = wxFileSelectorDefaultWildcardStr,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxFLP_DEFAULT_STYLE,
        const wxValidator& validator = wxDefaultValidator,
        const wxString& name = wxFilePickerCtrlNameStr) :
        wxFilePickerCtrl(parent, id, path, message, AUDIOFILES, pos, size, style, validator, name)
    {}
    virtual ~AudioFilePickerCtrl() {}
};

PlayListItemFSEQPanel::PlayListItemFSEQPanel(wxWindow* parent, PlayListItemFSEQ* fseq, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    _fseq = fseq;

	//(*Initialize(PlayListItemFSEQPanel)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(1);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("FSEQ File:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FilePickerCtrl_FSEQFile = new FSEQFilePickerCtrl(this, ID_FILEPICKERCTRL1, wxEmptyString, _("FSEQ File"), _T("*.fseq"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	FlexGridSizer1->Add(FilePickerCtrl_FSEQFile, 1, wxALL|wxEXPAND, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Blend Mode:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer1->Add(StaticText5, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Choice_BlendMode = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	FlexGridSizer1->Add(Choice_BlendMode, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBox_LimitChannels = new wxCheckBox(this, ID_CHECKBOX3, _("Limit Channels"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	CheckBox_LimitChannels->SetValue(false);
	FlexGridSizer1->Add(CheckBox_LimitChannels, 1, wxALL|wxEXPAND, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Start Channel"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer1->Add(StaticText6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_StartChannel = new wxSpinCtrl(this, ID_SPINCTRL2, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 100, 1, _T("ID_SPINCTRL2"));
	SpinCtrl_StartChannel->SetValue(_T("1"));
	FlexGridSizer1->Add(SpinCtrl_StartChannel, 1, wxALL|wxEXPAND, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Channels"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer1->Add(StaticText7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_Channels = new wxSpinCtrl(this, ID_SPINCTRL3, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL3"));
	SpinCtrl_Channels->SetValue(_T("0"));
	FlexGridSizer1->Add(SpinCtrl_Channels, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBox_OverrideAudio = new wxCheckBox(this, ID_CHECKBOX1, _("Override Audio"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox_OverrideAudio->SetValue(false);
	FlexGridSizer1->Add(CheckBox_OverrideAudio, 1, wxALL|wxEXPAND, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Audio File:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	FilePickerCtrl_AudioFile = new AudioFilePickerCtrl(this, ID_FILEPICKERCTRL2, wxEmptyString, _("Audio File"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL2"));
	FlexGridSizer1->Add(FilePickerCtrl_AudioFile, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBox_FastStartAudio = new wxCheckBox(this, ID_CHECKBOX4, _("Fast start audio"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	CheckBox_FastStartAudio->SetValue(false);
	FlexGridSizer1->Add(CheckBox_FastStartAudio, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBox_OverrideVolume = new wxCheckBox(this, ID_CHECKBOX2, _("Override Volume"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBox_OverrideVolume->SetValue(false);
	FlexGridSizer1->Add(CheckBox_OverrideVolume, 1, wxALL|wxEXPAND, 5);
	FlexGridSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Slider1 = new wxSlider(this, ID_SLIDER1, 100, 0, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
	FlexGridSizer1->Add(Slider1, 1, wxALL|wxEXPAND, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Priority:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	SpinCtrl_Priority = new wxSpinCtrl(this, ID_SPINCTRL1, _T("5"), wxDefaultPosition, wxDefaultSize, 0, 1, 10, 5, _T("ID_SPINCTRL1"));
	SpinCtrl_Priority->SetValue(_T("5"));
	FlexGridSizer1->Add(SpinCtrl_Priority, 1, wxALL|wxEXPAND, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Delay:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl_Delay = new wxTextCtrl(this, ID_TEXTCTRL1, _("0.000"), wxDefaultPosition, wxDefaultSize, wxTE_RIGHT, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(TextCtrl_Delay, 1, wxALL|wxEXPAND, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_FILEPICKERCTRL1,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&PlayListItemFSEQPanel::OnFilePickerCtrl1FileChanged);
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PlayListItemFSEQPanel::OnCheckBox_LimitChannelsClick);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PlayListItemFSEQPanel::OnCheckBox_OverrideAudioClick);
	Connect(ID_FILEPICKERCTRL2,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&PlayListItemFSEQPanel::OnFilePickerCtrl2FileChanged);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PlayListItemFSEQPanel::OnCheckBox_OverrideVolumeClick);
	//*)

    auto bms = FSEQFile::GetBlendModes();
    for (auto it = bms.begin(); it != bms.end(); ++it)
    {
        Choice_BlendMode->AppendString(*it);
    }

    FilePickerCtrl_FSEQFile->SetFileName(wxFileName(fseq->GetFSEQFileName()));
    FilePickerCtrl_AudioFile->SetFileName(wxFileName(fseq->GetAudioFile()));
    CheckBox_OverrideAudio->SetValue(fseq->GetOverrideAudio());
    TextCtrl_Delay->SetValue(wxString::Format(wxT("%.3f"), (float)fseq->GetDelay() / 1000.0));
    Choice_BlendMode->SetSelection(fseq->GetBlendMode());
    SpinCtrl_Priority->SetValue(fseq->GetPriority());
    CheckBox_FastStartAudio->SetValue(fseq->GetFastStartAudio());

    if (fseq->GetVolume() != -1)
    {
        CheckBox_OverrideVolume->SetValue(true);
        Slider1->SetValue(fseq->GetVolume());
    }
    else
    {
        CheckBox_OverrideVolume->SetValue(false);
    }

    long channels = xScheduleFrame::GetScheduleManager()->GetTotalChannels();
    SpinCtrl_StartChannel->SetRange(1, channels);
    SpinCtrl_Channels->SetRange(1, channels);

    SpinCtrl_StartChannel->SetValue(fseq->GetStartChannel());
    int chs = fseq->GetChannels();
    if (chs == 0)
    {
        CheckBox_LimitChannels->SetValue(false);
    }
    else
    {
        CheckBox_LimitChannels->SetValue(true);
        SpinCtrl_Channels->SetValue(fseq->GetChannels());
    }

    if (!CheckBox_OverrideAudio->GetValue())
    {
        std::string f = FSEQFile::GrabAudioFilename(FilePickerCtrl_FSEQFile->GetFileName().GetFullPath().ToStdString());
        FilePickerCtrl_AudioFile->SetFileName(wxFileName(f));
        FilePickerCtrl_AudioFile->SetToolTip(f);
    }

    ValidateWindow();
}

PlayListItemFSEQPanel::~PlayListItemFSEQPanel()
{
	//(*Destroy(PlayListItemFSEQPanel)
	//*)
    _fseq->SetFSEQFileName(FilePickerCtrl_FSEQFile->GetFileName().GetFullPath().ToStdString());
    _fseq->SetAudioFile(FilePickerCtrl_AudioFile->GetFileName().GetFullPath().ToStdString());
    _fseq->SetOverrideAudio(CheckBox_OverrideAudio->GetValue());
    _fseq->SetDelay(wxAtof(TextCtrl_Delay->GetValue()) * 1000);
    _fseq->SetBlendMode(Choice_BlendMode->GetSelection());
    _fseq->SetPriority(SpinCtrl_Priority->GetValue());
    _fseq->SetFastStartAudio(CheckBox_FastStartAudio->GetValue());

    if (CheckBox_OverrideVolume->GetValue())
    {
        _fseq->SetVolume(Slider1->GetValue());
    }
    else
    {
        _fseq->SetVolume(-1);
    }
    if (CheckBox_LimitChannels->GetValue())
    {
        _fseq->SetStartChannel(SpinCtrl_StartChannel->GetValue());
        _fseq->SetChannels(SpinCtrl_Channels->GetValue());
    }
    else
    {
        _fseq->SetStartChannel(1);
        _fseq->SetChannels(0);
    }
}

void PlayListItemFSEQPanel::OnTextCtrl_DelayText(wxCommandEvent& event)
{
}

void PlayListItemFSEQPanel::OnFilePickerCtrl1FileChanged(wxFileDirPickerEvent& event)
{
    _fseq->SetFSEQFileName(FilePickerCtrl_FSEQFile->GetFileName().GetFullPath().ToStdString());
    ((PlayListDialog*)GetParent()->GetParent()->GetParent()->GetParent())->UpdateTree();

    if (!CheckBox_OverrideAudio->GetValue())
    {
        std::string f = FSEQFile::GrabAudioFilename(FilePickerCtrl_FSEQFile->GetFileName().GetFullPath().ToStdString());
        FilePickerCtrl_AudioFile->SetFileName(wxFileName(f));
        FilePickerCtrl_AudioFile->SetToolTip(f);
    }
}

void PlayListItemFSEQPanel::OnFilePickerCtrl2FileChanged(wxFileDirPickerEvent& event)
{
}

void PlayListItemFSEQPanel::OnCheckBox_OverrideAudioClick(wxCommandEvent& event)
{
    if (!CheckBox_OverrideAudio->GetValue())
    {
        std::string f = FSEQFile::GrabAudioFilename(FilePickerCtrl_FSEQFile->GetFileName().GetFullPath().ToStdString());
        FilePickerCtrl_AudioFile->SetFileName(wxFileName(f));
        FilePickerCtrl_AudioFile->SetToolTip(f);
    }

    ValidateWindow();
}

void PlayListItemFSEQPanel::ValidateWindow()
{
    if (CheckBox_OverrideAudio->GetValue())
    {
        FilePickerCtrl_AudioFile->Enable(true);
    }
    else
    {
        FilePickerCtrl_AudioFile->Enable(false);
    }

    if (CheckBox_OverrideVolume->GetValue())
    {
        Slider1->Enable();
    }
    else
    {
        Slider1->Enable(false);
    }

    if (CheckBox_LimitChannels->GetValue())
    {
        SpinCtrl_StartChannel->Enable();
        SpinCtrl_Channels->Enable();
    }
    else
    {
        SpinCtrl_StartChannel->Enable(false);
        SpinCtrl_Channels->Enable(false);
    }
}

void PlayListItemFSEQPanel::OnCheckBox_OverrideVolumeClick(wxCommandEvent& event)
{
    ValidateWindow();
}

void PlayListItemFSEQPanel::OnCheckBox_LimitChannelsClick(wxCommandEvent& event)
{
    ValidateWindow();
}
