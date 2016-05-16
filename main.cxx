#include "frame.hxx"

class Alarma : public wxApp
{
	public:
		virtual bool OnInit() override {
			wxImage::AddHandler(new wxICOHandler);
			new AlarmaFrame ();
			return true;
		}
};

wxDECLARE_APP (Alarma);
wxIMPLEMENT_APP (Alarma);
