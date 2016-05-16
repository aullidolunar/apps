#include "frame.hxx"

AlarmaHelper::AlarmaHelper (wxTopLevelWindow* _f, wxPanel* _p, const wxIcon& i) :
	wxTaskBarIcon (), m_pFrameParent(_f), m_appIcon(i)
{
	// blink
	blink_state = false; // hay un evento de parpadeo
	blink_motion = false; // cambio de icono
#ifdef __WXMSW__
	wxIcon _icon(wxT("blink_icon"), wxBITMAP_TYPE_ICO_RESOURCE);
#else
	wxIcon _icon(wxT(BLINK_ICO));
#endif
	m_blinkIcon = _icon;
	m_pBlinkTimer = new wxTimer (this, TIMER_BLINK_ID);
	
	// taskbar
	SetIcon (i, _f->GetTitle());
	// mediactrl
	m_pMediaCtrl = new wxMediaCtrl (_p, MEDIA_ID);
	// binders
	Bind (wxEVT_TIMER, &AlarmaHelper::on_start_blink_timer, this);
	Bind (wxEVT_TASKBAR_LEFT_DOWN, &AlarmaHelper::on_tray_clicked, this);
	m_pMediaCtrl->Bind (wxEVT_MEDIA_LOADED, &AlarmaHelper::on_loaded, this);
}

void AlarmaHelper::on_start_blink_timer (wxTimerEvent& WXUNUSED(event)) {
	wxIcon use_icon;
	if (blink_motion) {
		use_icon = m_blinkIcon;
		blink_motion = false;
	} else {
		use_icon = m_appIcon;
		blink_motion = true;
	}
	SetIcon (use_icon);
}

void AlarmaHelper::Blinkit () {
	blink_state = true;
	m_pBlinkTimer->Start (800);
}

void AlarmaHelper::on_tray_clicked (wxTaskBarIconEvent& WXUNUSED(event)) {
	// probamos el evento blink
	if (blink_state) {
		blink_state = false;
		m_pBlinkTimer->Stop();
		SetIcon (m_appIcon, m_pFrameParent->GetTitle());
		return;
	}
	
	// 
	bool state = m_pFrameParent->IsShown();
	if (!state) { // show
		m_pFrameParent->Iconize (false);
		m_pFrameParent->Show ();
		m_pFrameParent->Raise ();
	} else { // hide
		m_pFrameParent->Iconize (true);
		m_pFrameParent->Show (false);
	}
}

void AlarmaHelper::on_loaded (wxMediaEvent& WXUNUSED(event)) {
	m_pMediaCtrl->Play();
}

void AlarmaHelper::Soundit () {
	m_pMediaCtrl->Load (wxT(ALARM_SOUND));
}

void AlarmaHelper::Notifyit (const wxString& _msg, int m) {
#ifdef __WXMSW__
	ShowBalloon (m_pFrameParent->GetTitle(), _msg, m, wxICON_INFORMATION);
#else
	wxNotificationMessage nmsg(m_pFrameParent->GetTitle(), _msg, m_pFrameParent, wxICON_INFORMATION);
	nmsg.Show (m/1000);
#endif 
}

AlarmaHelper::~AlarmaHelper () {
	if (m_pBlinkTimer->IsRunning ()) m_pBlinkTimer->Stop();
}

AlarmaFrame::AlarmaFrame () : 
	wxFrame(NULL, wxID_ANY, wxT(PACKAGE_STRING))
{
	wxPanel *panel = new wxPanel (this);
	wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);
	
	// timer
	m_pTimer = new wxTimer (this, TIMER_ALARM_ID);
	s = 0;
	m = 0;
	max = 0;
	
	// ruta del icono
#ifdef __WXMSW__
	wxIcon main_icon(wxT("aaaaa_icon"), wxBITMAP_TYPE_ICO_RESOURCE);
#else
	wxIcon main_icon(wxT(PACKAGE_ICON_ICO));
#endif
	SetIcon (main_icon);
	m_pHelper = new AlarmaHelper (this, panel, main_icon);

	// row 1
	wxStaticBoxSizer *bsz1 = new wxStaticBoxSizer(wxVERTICAL, panel, wxT("Tiempo transcurrido"));
	m_TimeText = new wxStaticText (bsz1->GetStaticBox(), wxID_ANY, wxT("00:00"));
	// row 2
	wxStaticBoxSizer *bsz2 = new wxStaticBoxSizer(wxVERTICAL, panel, wxT("Configuración"));
	m_boxedPanel = new wxPanel(bsz2->GetStaticBox(), wxID_ANY);
	wxFlexGridSizer *fgsz = new wxFlexGridSizer (2, 10, 10);
	fgsz->AddGrowableCol (1);
	wxStaticText *_l1 = new wxStaticText (m_boxedPanel, wxID_ANY, wxT("Ajuste de tiempo:"));
	m_SpinCtrl = new wxSpinCtrl (m_boxedPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, ALARM_MAX, 1);
	m_checkNotify = new wxCheckBox (m_boxedPanel, wxID_ANY, wxT("Deshabilitar notificaciones"));
	m_checkSound = new wxCheckBox (m_boxedPanel, wxID_ANY, wxT("Deshabilitar sonido"));
	m_checkBlink = new wxCheckBox (m_boxedPanel, wxID_ANY, wxT("Deshabilitar parpadeo"));
	m_checkReset = new wxCheckBox (m_boxedPanel, wxID_ANY, wxT("Reiniciar segundero manualmente"));
	// row 3
	wxStaticBoxSizer *bsz3 = new wxStaticBoxSizer(wxVERTICAL, panel, wxT("Algo para recordar"));
	wxTextCtrl *edit = new wxTextCtrl (bsz3->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_BESTWRAP);
	// separator
	wxStaticLine *sep = new wxStaticLine (panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	// button
	m_buttonPlay = new wxButton (panel, wxID_ANY, wxT("Reproducir"));
	
	// binders
	m_buttonPlay->Bind (wxEVT_BUTTON, &AlarmaFrame::on_play_clicked, this);
	Bind (wxEVT_TIMER, &AlarmaFrame::on_timer_tick, this);
	Bind (wxEVT_ICONIZE, &AlarmaFrame::on_iconized, this);
	Bind (wxEVT_CLOSE_WINDOW, &AlarmaFrame::on_close, this);
	
	// layout
	
	// row1
	bsz1->Add (m_TimeText, 1, wxEXPAND|wxALL, 10);
	topsizer->Add (bsz1, 0, wxEXPAND|wxALL, 10);
	// row2
	fgsz->Add (_l1, 0, wxALIGN_CENTER_VERTICAL);
	fgsz->Add (m_SpinCtrl, 0, wxALIGN_RIGHT|wxALL);
	fgsz->Add (m_checkNotify);
	fgsz->AddStretchSpacer ();
	fgsz->Add (m_checkSound);
	fgsz->AddStretchSpacer ();
	fgsz->Add (m_checkBlink);
	fgsz->AddStretchSpacer ();
	fgsz->Add (m_checkReset);
	m_boxedPanel->SetSizer (fgsz);
	bsz2->Add (m_boxedPanel, 1, wxALL|wxEXPAND, 10);
	topsizer->Add (bsz2, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 10);
	// row3
	bsz3->Add (edit, 1, wxEXPAND|wxALL, 10);
	topsizer->Add (bsz3, 1, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 10);
	// sep
	topsizer->Add (sep, 0, wxEXPAND | wxALL);
	// button
	topsizer->Add (m_buttonPlay, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 10 );
	
	panel->SetSizer (topsizer);
	topsizer->Fit (this);
	topsizer->SetSizeHints (this);
	Layout();
	Centre ();
	Show ();
}

void AlarmaFrame::on_play_clicked (wxCommandEvent& WXUNUSED(event)) {
	bool state = m_pTimer->IsRunning();
	if (state) { // is running, so stop it
		m_pTimer->Stop();
		state = false;
	} else { // start it
		max = m_SpinCtrl->GetValue ();
		if (!m_checkReset->GetValue ()) s = 0;
		m_pTimer->Start(1000);
		state = true;
	}
	m_buttonPlay->SetLabel (state ? wxT("Detener") : wxT("Reproducir"));
	m_boxedPanel->Enable (!state);
	if (!m_checkNotify->GetValue()) m_pHelper->Notifyit(state ? wxT("La alarma ha iniciado") : wxT("La alarma ha terminado"), 3000); 
}

void AlarmaFrame::on_close (wxCloseEvent& event) {
	if (event.CanVeto() && m_pTimer->IsRunning ()) {
		if (wxMessageBox (wxT("La alarma aún sigue corriendo, ¿deseas salir de cualquier modo?"), wxT("Atención"), wxICON_QUESTION|wxYES_NO, this) != wxYES ) {
            event.Veto();
            return;
        } else {
			m_pTimer->Stop ();
		}
	}
	event.Skip ();
}

void AlarmaFrame::on_iconized (wxIconizeEvent& WXUNUSED(event)) {
	Hide ();
}

void AlarmaFrame::on_timer_tick (wxTimerEvent& WXUNUSED(event)) {
	s++;
	if (s == 60) {
		s = 0;
		m++;
	}
	if (m == max) {
		m = 0;
		if (!m_checkBlink->GetValue()) m_pHelper->Blinkit(); 
		if (!m_checkSound->GetValue()) m_pHelper->Soundit(); 
		if (!m_checkNotify->GetValue()) m_pHelper->Notifyit(wxT("La alarma ha terminado"), 3000); 
		m_pTimer->Stop();
		m_buttonPlay->SetLabel (wxT("Reproducir"));
		m_boxedPanel->Enable(true);
	}
	m_TimeText->SetLabel (wxString::Format (wxT("%02i:%02i"), m, s));
}

AlarmaFrame::~AlarmaFrame () {}
