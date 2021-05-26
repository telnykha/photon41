//---------------------------------------------------------------------------

#ifndef PalettemainH
#define PalettemainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "PhPalette.h"
#include "FImage41.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm9 : public TForm
{
__published:	// IDE-managed Components
	TPhPalette *PhPalette1;
	TPhImage *PhImage1;
	TSplitter *Splitter1;
	TPhPalette *PhPalette2;
	TPhPalette *PhPalette3;
private:	// User declarations
public:		// User declarations
	__fastcall TForm9(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm9 *Form9;
//---------------------------------------------------------------------------
#endif
