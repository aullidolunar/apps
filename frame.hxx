#ifndef FRAME_HXX_INC
#define FRAME_HXX_INC

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __WXMSW__
#define _WIN32_IE 0x0600
#endif

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
#include <wx/taskbar.h>
#include <wx/sharedptr.h>
#ifndef __WXMSW__
#include <wx/notifmsg.h>
#endif
#include <wx/msgdlg.h>
#include <wx/mediactrl.h>

enum {
	__INITIDS__ = 200,
	TIMER_ALARM_ID,
	TIMER_BLINK_ID,
	MEDIA_ID
};

const int ALARM_MAX = 120;

class AlarmaHelper : public wxTaskBarIcon
{
private:
	wxTopLevelWindow *m_pFrameParent;
	wxMediaCtrl *m_pMediaCtrl;
	bool blink_motion;
	bool blink_state;
	wxTimer *m_pBlinkTimer;
	wxIcon m_blinkIcon;
	wxIcon m_appIcon;
public:
	AlarmaHelper (wxTopLevelWindow*, wxPanel*, const wxIcon&);
	void Soundit();
	void Notifyit(const wxString&, int);
	void Blinkit ();
	virtual ~AlarmaHelper ();
protected:
	void on_tray_clicked (wxTaskBarIconEvent&);
	void on_loaded (wxMediaEvent&);
	void on_start_blink_timer (wxTimerEvent&);
};

class AlarmaFrame : public wxFrame
{
private:
	wxStaticText *m_TimeText;
	wxSpinCtrl *m_SpinCtrl;
	wxCheckBox *m_checkNotify;
	wxCheckBox *m_checkSound;
	wxCheckBox *m_checkBlink;
	wxCheckBox *m_checkReset;
	wxPanel *m_boxedPanel;
	wxButton *m_buttonPlay;
	wxTimer *m_pTimer;
	int s;
	int m;
	int max;
	wxSharedPtr<AlarmaHelper> m_pHelper;
public:
	AlarmaFrame();
	virtual ~AlarmaFrame();
protected:
	void on_play_clicked (wxCommandEvent&);
	void on_timer_tick (wxTimerEvent&);
	void on_close (wxCloseEvent&);
	void on_iconized (wxIconizeEvent&);
};


#endif
