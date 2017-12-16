//---------------------------------------------------------------------------

#ifndef mainUnitH
#define mainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "FImage41.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Buttons.hpp>
#include "PhMediaSource.h"
#include "PhImageTool.h"
#include "PhPaneTool.h"
#include "PhLenzTool.h"
#include "PhZoomToRectTool.h"
#include "PhSelectRectTool.h"
#include <Vcl.Samples.Gauges.hpp>
//---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TPhImage *PhImage1;
	TPanel *Panel1;
	TActionList *ActionList1;
	TAction *fileOpenAction;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Open1;
	TAction *fileSaveAction;
	TMenuItem *SaveAs1;
	TMenuItem *N2;
	TAction *fileCloseAction;
	TMenuItem *Closemedia1;
	TMenuItem *N3;
	TFileExit *fileExitAction;
	TMenuItem *Exit1;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TAction *editCopyAction;
	TAction *editPasteAction;
	TMenuItem *Edit1;
	TMenuItem *Copy1;
	TMenuItem *Paste1;
	TPopupMenu *PopupMenu1;
	TMenuItem *Openmedia1;
	TMenuItem *SaveAs2;
	TMenuItem *N4;
	TMenuItem *Closemedia2;
	TMenuItem *N5;
	TMenuItem *Copy2;
	TMenuItem *Paste2;
	TAction *toolPaneAction;
	TAction *toolZoomToRectAction;
	TAction *toolSelectRectAction;
	TAction *toolLenzAction;
	TMenuItem *Mode1;
	TMenuItem *PaneTool1;
	TMenuItem *ZoomToRectTool1;
	TMenuItem *toolSelectRectAction1;
	TMenuItem *LenzTool1;
	TAction *viewZoomInAction;
	TAction *viewZoomOutAction;
	TAction *viewZoomToAction;
	TAction *viewBestFitAction;
	TAction *viewActualSizeAction;
	TAction *viewFitWidthAction;
	TAction *viewFitHeightAction;
	TAction *viewMoveCenterAction;
	TAction *viewMoveLeftTopAction;
	TAction *viewMoveRightBottomAction;
	TAction *viewMoveToAction;
	TAction *viewMoveByAction;
	TMenuItem *View1;
	TMenuItem *ZoomIn1;
	TMenuItem *ZoomOut1;
	TMenuItem *ZoomTo1;
	TMenuItem *BestFit1;
	TMenuItem *ActualSize1;
	TMenuItem *FitToWidth1;
	TMenuItem *FitHeight1;
	TMenuItem *N6;
	TMenuItem *MoveToCenter1;
	TMenuItem *MoveLeftTop1;
	TMenuItem *MoveRightBottom1;
	TMenuItem *MoveTo1;
	TMenuItem *MoveBy1;
	TMenuItem *N1;
	TMenuItem *BestFit2;
	TMenuItem *ActualSize2;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton9;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton2;
	TAction *editClearSelectionAction;
	TMenuItem *N7;
	TMenuItem *ClearSelection1;
	TPhPaneTool *PhPaneTool1;
	TPhLenzTool *PhLenzTool1;
	TPhZoomToRectTool *PhZoomToRectTool1;
	TPhSelRectTool *PhSelRectTool1;
	TAction *navFirstAction;
	TAction *navLastAction;
	TAction *navPrevAction;
	TAction *navNextAction;
	TAction *navPlayAction;
	TSpeedButton *SpeedButton1;
	TAction *viewMosaicAction;
	TMenuItem *viewMosaicAction1;
	TMenuItem *N8;
	TMenuItem *Mosaic1;
	TMenuItem *N9;
	TPanel *Panel2;
	TTrackBar *TrackBar1;
	TPanel *Panel3;
	TAction *editSelectAllAction;
	TAction *editInvertSelectionAction;
	TMenuItem *SelectAll1;
	TMenuItem *InvertSelection1;
	TAction *imgCopyAction;
	TAction *imgMoveAction;
	TAction *imgDeleteAction;
	TAction *imgRotateAction;
	TAction *imgResizeAction;
	TAction *imgGrayScaleAction;
	TAction *imgInvertAction;
	TAction *imgConvertAction;
	TAction *imgCropAction;
	TMenuItem *Image1;
	TMenuItem *CopyImages1;
	TMenuItem *MoveImages1;
	TMenuItem *DeleteImages1;
	TMenuItem *ConvertImages1;
	TMenuItem *N10;
	TMenuItem *ResizeImages1;
	TMenuItem *RotateImages1;
	TMenuItem *GrayscaleImages1;
	TMenuItem *InvertImages1;
	TMenuItem *CropImage1;
	TAction *fileNewInstanceAction;
	TMenuItem *N11;
	TMenuItem *NewInstance1;
	TGroupBox *GroupBox1;
	TButton *Button1;
	TGauge *Gauge1;
	void __fastcall fileOpenActionExecute(TObject *Sender);
	void __fastcall fileSaveActionExecute(TObject *Sender);
	void __fastcall fileSaveActionUpdate(TObject *Sender);
	void __fastcall fileCloseActionExecute(TObject *Sender);
	void __fastcall fileCloseActionUpdate(TObject *Sender);
	void __fastcall PhImage1AfterOpen(TObject *Sender);
	void __fastcall editCopyActionExecute(TObject *Sender);
	void __fastcall editCopyActionUpdate(TObject *Sender);
	void __fastcall editPasteActionExecute(TObject *Sender);
	void __fastcall editPasteActionUpdate(TObject *Sender);
	void __fastcall PhImage1Change(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall toolPaneActionExecute(TObject *Sender);
	void __fastcall toolPaneActionUpdate(TObject *Sender);
	void __fastcall toolZoomToRectActionExecute(TObject *Sender);
	void __fastcall toolZoomToRectActionUpdate(TObject *Sender);
	void __fastcall toolSelectRectActionExecute(TObject *Sender);
	void __fastcall toolSelectRectActionUpdate(TObject *Sender);
	void __fastcall toolLenzActionExecute(TObject *Sender);
	void __fastcall toolLenzActionUpdate(TObject *Sender);
	void __fastcall viewZoomInActionExecute(TObject *Sender);
	void __fastcall viewZoomInActionUpdate(TObject *Sender);
	void __fastcall viewZoomOutActionExecute(TObject *Sender);
	void __fastcall viewZoomOutActionUpdate(TObject *Sender);
	void __fastcall viewZoomToActionExecute(TObject *Sender);
	void __fastcall viewZoomToActionUpdate(TObject *Sender);
	void __fastcall viewBestFitActionExecute(TObject *Sender);
	void __fastcall viewBestFitActionUpdate(TObject *Sender);
	void __fastcall viewActualSizeActionExecute(TObject *Sender);
	void __fastcall viewActualSizeActionUpdate(TObject *Sender);
	void __fastcall viewFitWidthActionExecute(TObject *Sender);
	void __fastcall viewFitWidthActionUpdate(TObject *Sender);
	void __fastcall viewFitHeightActionExecute(TObject *Sender);
	void __fastcall viewFitHeightActionUpdate(TObject *Sender);
	void __fastcall viewMoveCenterActionExecute(TObject *Sender);
	void __fastcall viewMoveCenterActionUpdate(TObject *Sender);
	void __fastcall viewMoveLeftTopActionExecute(TObject *Sender);
	void __fastcall viewMoveLeftTopActionUpdate(TObject *Sender);
	void __fastcall viewMoveRightBottomActionExecute(TObject *Sender);
	void __fastcall viewMoveRightBottomActionUpdate(TObject *Sender);
	void __fastcall viewMoveToActionExecute(TObject *Sender);
	void __fastcall viewMoveToActionUpdate(TObject *Sender);
	void __fastcall viewMoveByActionExecute(TObject *Sender);
	void __fastcall viewMoveByActionUpdate(TObject *Sender);
	void __fastcall PhImage1ScaleChange(TObject *Sender);
	void __fastcall PhImage1ToolChange(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall editClearSelectionActionExecute(TObject *Sender);
	void __fastcall editClearSelectionActionUpdate(TObject *Sender);
	void __fastcall navFirstActionExecute(TObject *Sender);
	void __fastcall navFirstActionUpdate(TObject *Sender);
	void __fastcall navLastActionExecute(TObject *Sender);
	void __fastcall navLastActionUpdate(TObject *Sender);
	void __fastcall navPrevActionExecute(TObject *Sender);
	void __fastcall navPrevActionUpdate(TObject *Sender);
	void __fastcall navNextActionExecute(TObject *Sender);
	void __fastcall navNextActionUpdate(TObject *Sender);
	void __fastcall navPlayActionExecute(TObject *Sender);
	void __fastcall navPlayActionUpdate(TObject *Sender);
	void __fastcall viewMosaicActionExecute(TObject *Sender);
	void __fastcall viewMosaicActionUpdate(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall editSelectAllActionExecute(TObject *Sender);
	void __fastcall editSelectAllActionUpdate(TObject *Sender);
	void __fastcall editInvertSelectionActionExecute(TObject *Sender);
	void __fastcall editInvertSelectionActionUpdate(TObject *Sender);
	void __fastcall imgCopyActionExecute(TObject *Sender);
	void __fastcall imgCopyActionUpdate(TObject *Sender);
	void __fastcall imgMoveActionExecute(TObject *Sender);
	void __fastcall imgMoveActionUpdate(TObject *Sender);
	void __fastcall imgRotateActionExecute(TObject *Sender);
	void __fastcall imgRotateActionUpdate(TObject *Sender);
	void __fastcall imgResizeActionExecute(TObject *Sender);
	void __fastcall imgResizeActionUpdate(TObject *Sender);
	void __fastcall imgGrayScaleActionExecute(TObject *Sender);
	void __fastcall imgGrayScaleActionUpdate(TObject *Sender);
	void __fastcall imgInvertActionExecute(TObject *Sender);
	void __fastcall imgInvertActionUpdate(TObject *Sender);
	void __fastcall imgConvertActionExecute(TObject *Sender);
	void __fastcall imgConvertActionUpdate(TObject *Sender);
	void __fastcall imgCropActionExecute(TObject *Sender);
	void __fastcall imgCropActionUpdate(TObject *Sender);
	void __fastcall imgDeleteActionExecute(TObject *Sender);
	void __fastcall imgDeleteActionUpdate(TObject *Sender);
	void __fastcall Panel1Click(TObject *Sender);
	void __fastcall fileNewInstanceActionExecute(TObject *Sender);
	void __fastcall PhImage1Progress(TObject *Sender, UnicodeString &strMessage, int Progress);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall PhImage1Start(TObject *Sender);
	void __fastcall PhImage1Finish(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TmainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
