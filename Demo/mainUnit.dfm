object mainForm: TmainForm
  Left = 0
  Top = 0
  Caption = 'Photon 4.1 demo '
  ClientHeight = 490
  ClientWidth = 709
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 471
    Width = 709
    Height = 19
    Panels = <
      item
        Width = 300
      end
      item
        Alignment = taCenter
        Width = 100
      end
      item
        Alignment = taCenter
        Width = 150
      end
      item
        Alignment = taCenter
        Width = 150
      end
      item
        Alignment = taCenter
        Width = 100
      end>
  end
  object PhImage1: TPhImage
    Left = 0
    Top = 0
    Width = 709
    Height = 414
    BorderStyle = bsFSingle
    Align = alClient
    ParentColor = False
    PopupMenu = PopupMenu1
    AfterOpen = PhImage1AfterOpen
    OnScaleChange = PhImage1ScaleChange
    OnChange = PhImage1Change
    OnToolChange = PhImage1ToolChange
  end
  object Panel1: TPanel
    Left = 0
    Top = 414
    Width = 709
    Height = 57
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 2
    Visible = False
    object SpeedButton4: TSpeedButton
      Left = 192
      Top = 0
      Width = 64
      Height = 57
      Align = alLeft
      Caption = 'Next'
      Flat = True
      Glyph.Data = {
        B6020000424DB602000000000000760000002800000030000000180000000100
        0400000000004002000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFCCFFFCCFFFFFFFFFFFFFFFFFFF77FFF77FFFFFFFFFFFFFFFCCCFFC
        CCFFFFFFFFFFFFFFFFFF777FF777FFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFF
        FFFF7777F7777FFFFFFFFFFFFFCCCCCCCCCCFFFFFFFFFFFFFFFF7777777777FF
        FFFFFFFFFFCCCCCCCCCCCFFFFFFFFFFFFFFF77777777777FFFFFFFFFFFCCCCCC
        CCCCFFFFFFFFFFFFFFFF7777777777FFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFF
        FFFF7777F7777FFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFFFFFFFF777FF777FFFF
        FFFFFFFFFFCCFFFCCFFFFFFFFFFFFFFFFFFF77FFF77FFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
      Layout = blGlyphTop
      NumGlyphs = 2
      ExplicitLeft = 216
      ExplicitTop = 6
    end
    object SpeedButton5: TSpeedButton
      Left = 256
      Top = 0
      Width = 64
      Height = 57
      Align = alLeft
      Caption = 'Finish'
      Flat = True
      Glyph.Data = {
        B6020000424DB602000000000000760000002800000030000000180000000100
        0400000000004002000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCCFF
        FCCCFFFFFFFFFFFFFFFF77FFF777FFFFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFF
        FFFF777FF777FFFFFFFFFFFFFFFFCCCCFCCCFFFFFFFFFFFFFFFF7777F777FFFF
        FFFFFFFFFFFFCCCCCCCCFFFFFFFFFFFFFFFF77777777FFFFFFFFFFFFFFFFCCCC
        CCCCFFFFFFFFFFFFFFFF77777777FFFFFFFFFFFFFFFFCCCCFCCCFFFFFFFFFFFF
        FFFF7777F777FFFFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFFFFFF777FF777FFFF
        FFFFFFFFFFFFCCFFFCCCFFFFFFFFFFFFFFFF77FFF777FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
      Layout = blGlyphTop
      NumGlyphs = 2
      ExplicitLeft = 296
      ExplicitTop = -6
    end
    object SpeedButton9: TSpeedButton
      Left = 128
      Top = 0
      Width = 64
      Height = 57
      Align = alLeft
      AllowAllUp = True
      Caption = 'Play'
      Flat = True
      Glyph.Data = {
        F6040000424DF604000000000000760000002800000060000000180000000100
        0400000000008004000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCFFFF
        FFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFFFFFFFFFFFFFFCFFFFFFFFFFFFFFFFFFF
        FFFCCCCFCCCCFFFFFFFFFFFFFFFCCFFFFFFFFFFFFFFFFFFFFFFFF77FFFFFFFFF
        FFFFFFFFFFFFCCFFFFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCCFF
        FFFFFFFFFFFFFFFFFFFFF777FFFFFFFFFFFFFFFFFFFFCCCFFFFFFFFFFFFFFFFF
        FFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCFFFFFFFFFFFFFFFFFFFFFF7777FFFFFFF
        FFFFFFFFFFFFCCCCFFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCC
        FFFFFFFFFFFFFFFFFFFFF77777FFFFFFFFFFFFFFFFFFCCCCCFFFFFFFFFFFFFFF
        FFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCCCFFFFFFFFFFFFFFFFFFFF777777FFFFF
        FFFFFFFFFFFFCCCCCCFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCC
        CFFFFFFFFFFFFFFFFFFFF777777FFFFFFFFFFFFFFFFFCCCCCCFFFFFFFFFFFFFF
        FFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCCFFFFFFFFFFFFFFFFFFFFF77777FFFFFF
        FFFFFFFFFFFFCCCCCFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCF
        FFFFFFFFFFFFFFFFFFFFF7777FFFFFFFFFFFFFFFFFFFCCCCFFFFFFFFFFFFFFFF
        FFFCCCCFCCCCFFFFFFFFFFFFFFFCCCFFFFFFFFFFFFFFFFFFFFFFF777FFFFFFFF
        FFFFFFFFFFFFCCCFFFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCFFF
        FFFFFFFFFFFFFFFFFFFFF77FFFFFFFFFFFFFFFFFFFFFCCFFFFFFFFFFFFFFFFFF
        FFFCCCCFCCCCFFFFFFFFFFFFFFFCFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFF
        FFFFFFFFFFFFCFFFFFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
      Layout = blGlyphTop
      NumGlyphs = 4
      ExplicitLeft = 144
      ExplicitTop = 6
    end
    object SpeedButton3: TSpeedButton
      Left = 64
      Top = 0
      Width = 64
      Height = 57
      Align = alLeft
      Caption = 'Prev '
      Flat = True
      Glyph.Data = {
        B6020000424DB602000000000000760000002800000030000000180000000100
        0400000000004002000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFCCFFFCCFFFFFFFFFFFFFFFFFFF77FFF77FFFFFFFFFFFFFFCCCF
        FCCCFFFFFFFFFFFFFFFFFF777FF777FFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFF
        FFFFF7777F7777FFFFFFFFFFFFCCCCCCCCCCFFFFFFFFFFFFFFFF7777777777FF
        FFFFFFFFFCCCCCCCCCCCFFFFFFFFFFFFFFF77777777777FFFFFFFFFFFFCCCCCC
        CCCCFFFFFFFFFFFFFFFF7777777777FFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFF
        FFFFF7777F7777FFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFFFFFFFF777FF777FF
        FFFFFFFFFFFFFCCFFFCCFFFFFFFFFFFFFFFFFFF77FFF77FFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
      Layout = blGlyphTop
      NumGlyphs = 2
      ExplicitLeft = 80
      ExplicitTop = 6
    end
    object SpeedButton2: TSpeedButton
      Left = 0
      Top = 0
      Width = 64
      Height = 57
      Align = alLeft
      Caption = 'Start'
      Flat = True
      Glyph.Data = {
        B6020000424DB602000000000000760000002800000030000000180000000100
        0400000000004002000000000000000000001000000000000000000000000000
        8000008000000080800080000000800080008080000080808000C0C0C0000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCCCF
        FFCCFFFFFFFFFFFFFFFF777FFF77FFFFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFF
        FFFF777FF777FFFFFFFFFFFFFFFFCCCFCCCCFFFFFFFFFFFFFFFF777F7777FFFF
        FFFFFFFFFFFFCCCCCCCCFFFFFFFFFFFFFFFF77777777FFFFFFFFFFFFFFFFCCCC
        CCCCFFFFFFFFFFFFFFFF77777777FFFFFFFFFFFFFFFFCCCFCCCCFFFFFFFFFFFF
        FFFF777F7777FFFFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFFFFFF777FF777FFFF
        FFFFFFFFFFFFCCCFFFCCFFFFFFFFFFFFFFFF777FFF77FFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
        FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
      Layout = blGlyphTop
      NumGlyphs = 2
      ExplicitTop = 6
    end
  end
  object ActionList1: TActionList
    Left = 24
    Top = 16
    object fileOpenAction: TAction
      Category = 'File'
      Caption = 'Open image(s)...'
      OnExecute = fileOpenActionExecute
    end
    object fileSaveAction: TAction
      Category = 'File'
      Caption = 'Save As...'
      OnExecute = fileSaveActionExecute
      OnUpdate = fileSaveActionUpdate
    end
    object fileCloseAction: TAction
      Category = 'File'
      Caption = 'Close media'
      OnExecute = fileCloseActionExecute
      OnUpdate = fileCloseActionUpdate
    end
    object fileExitAction: TFileExit
      Category = 'File'
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 43
    end
    object editCopyAction: TAction
      Category = 'Edit'
      Caption = 'Copy'
      OnExecute = editCopyActionExecute
      OnUpdate = editCopyActionUpdate
    end
    object editPasteAction: TAction
      Category = 'Edit'
      Caption = 'Paste'
      OnExecute = editPasteActionExecute
      OnUpdate = editPasteActionUpdate
    end
    object toolPaneAction: TAction
      Category = 'Tools'
      Caption = 'Pane Tool'
      OnExecute = toolPaneActionExecute
      OnUpdate = toolPaneActionUpdate
    end
    object toolZoomToRectAction: TAction
      Category = 'Tools'
      Caption = 'Zoom To Rect Tool'
      OnExecute = toolZoomToRectActionExecute
      OnUpdate = toolZoomToRectActionUpdate
    end
    object toolSelectRectAction: TAction
      Category = 'Tools'
      Caption = 'Select Rect Tool'
      OnExecute = toolSelectRectActionExecute
      OnUpdate = toolSelectRectActionUpdate
    end
    object toolLenzAction: TAction
      Category = 'Tools'
      Caption = 'Lenz Tool'
      OnExecute = toolLenzActionExecute
      OnUpdate = toolLenzActionUpdate
    end
    object viewZoomInAction: TAction
      Category = 'View'
      Caption = 'Zoom In'
      OnExecute = viewZoomInActionExecute
      OnUpdate = viewZoomInActionUpdate
    end
    object viewZoomOutAction: TAction
      Category = 'View'
      Caption = 'Zoom Out '
      OnExecute = viewZoomOutActionExecute
      OnUpdate = viewZoomOutActionUpdate
    end
    object viewZoomToAction: TAction
      Category = 'View'
      Caption = 'Zoom To...'
      OnExecute = viewZoomToActionExecute
      OnUpdate = viewZoomToActionUpdate
    end
    object viewBestFitAction: TAction
      Category = 'View'
      Caption = 'Best Fit'
      OnExecute = viewBestFitActionExecute
      OnUpdate = viewBestFitActionUpdate
    end
    object viewActualSizeAction: TAction
      Category = 'View'
      Caption = 'Actual Size'
      OnExecute = viewActualSizeActionExecute
      OnUpdate = viewActualSizeActionUpdate
    end
    object viewFitWidthAction: TAction
      Category = 'View'
      Caption = 'Fit To Width'
      OnExecute = viewFitWidthActionExecute
      OnUpdate = viewFitWidthActionUpdate
    end
    object viewFitHeightAction: TAction
      Category = 'View'
      Caption = 'Fit Height'
      OnExecute = viewFitHeightActionExecute
      OnUpdate = viewFitHeightActionUpdate
    end
    object viewMoveCenterAction: TAction
      Category = 'View'
      Caption = 'Move To Center'
      OnExecute = viewMoveCenterActionExecute
      OnUpdate = viewMoveCenterActionUpdate
    end
    object viewMoveLeftTopAction: TAction
      Category = 'View'
      Caption = 'Move Left Top'
      OnExecute = viewMoveLeftTopActionExecute
      OnUpdate = viewMoveLeftTopActionUpdate
    end
    object viewMoveRightBottomAction: TAction
      Category = 'View'
      Caption = 'Move Right Bottom'
      OnExecute = viewMoveRightBottomActionExecute
      OnUpdate = viewMoveRightBottomActionUpdate
    end
    object viewMoveToAction: TAction
      Category = 'View'
      Caption = 'Move To...'
      OnExecute = viewMoveToActionExecute
      OnUpdate = viewMoveToActionUpdate
    end
    object viewMoveByAction: TAction
      Category = 'View'
      Caption = 'Move By...'
      OnExecute = viewMoveByActionExecute
      OnUpdate = viewMoveByActionUpdate
    end
    object editClearSelectionAction: TAction
      Category = 'Edit'
      Caption = 'Clear Selection'
      OnExecute = editClearSelectionActionExecute
      OnUpdate = editClearSelectionActionUpdate
    end
  end
  object MainMenu1: TMainMenu
    Left = 24
    Top = 64
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Action = fileOpenAction
      end
      object SaveAs1: TMenuItem
        Action = fileSaveAction
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Closemedia1: TMenuItem
        Action = fileCloseAction
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Action = fileExitAction
      end
    end
    object Edit1: TMenuItem
      Caption = '&Edit'
      object Copy1: TMenuItem
        Action = editCopyAction
      end
      object Paste1: TMenuItem
        Action = editPasteAction
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object ClearSelection1: TMenuItem
        Action = editClearSelectionAction
      end
    end
    object Mode1: TMenuItem
      Caption = 'Mode'
      object PaneTool1: TMenuItem
        Action = toolPaneAction
      end
      object ZoomToRectTool1: TMenuItem
        Action = toolZoomToRectAction
      end
      object toolSelectRectAction1: TMenuItem
        Action = toolSelectRectAction
      end
      object LenzTool1: TMenuItem
        Action = toolLenzAction
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object ZoomIn1: TMenuItem
        Action = viewZoomInAction
      end
      object ZoomOut1: TMenuItem
        Action = viewZoomOutAction
      end
      object ZoomTo1: TMenuItem
        Action = viewZoomToAction
      end
      object BestFit1: TMenuItem
        Action = viewBestFitAction
      end
      object ActualSize1: TMenuItem
        Action = viewActualSizeAction
      end
      object FitToWidth1: TMenuItem
        Action = viewFitWidthAction
      end
      object FitHeight1: TMenuItem
        Action = viewFitHeightAction
      end
      object N6: TMenuItem
        Caption = '-'
      end
      object MoveToCenter1: TMenuItem
        Action = viewMoveCenterAction
      end
      object MoveLeftTop1: TMenuItem
        Action = viewMoveLeftTopAction
      end
      object MoveRightBottom1: TMenuItem
        Action = viewMoveRightBottomAction
      end
      object MoveTo1: TMenuItem
        Action = viewMoveToAction
      end
      object MoveBy1: TMenuItem
        Action = viewMoveByAction
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'Jpeg images|*.jpg|BMP images|*.bmp|PPM images|*.ppm|TGA images|*' +
      '.tga|GIF images|*.gif|AWP images|*.awp|PNG images|*.png|TIFF ima' +
      'ges|*.tif'
    Left = 24
    Top = 120
  end
  object SaveDialog1: TSaveDialog
    FileName = 'default.jpg'
    Filter = 
      'Jpeg images|*.jpg|Awp imges|*.awp|PNG images|*.png|TIFF images |' +
      '*.tif'
    Left = 24
    Top = 176
  end
  object PopupMenu1: TPopupMenu
    Left = 24
    Top = 240
    object Openmedia1: TMenuItem
      Action = fileOpenAction
    end
    object SaveAs2: TMenuItem
      Action = fileSaveAction
    end
    object N4: TMenuItem
      Caption = '-'
    end
    object Closemedia2: TMenuItem
      Action = fileCloseAction
    end
    object N5: TMenuItem
      Caption = '-'
    end
    object BestFit2: TMenuItem
      Action = viewBestFitAction
    end
    object ActualSize2: TMenuItem
      Action = viewActualSizeAction
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Copy2: TMenuItem
      Action = editCopyAction
    end
    object Paste2: TMenuItem
      Action = editPasteAction
    end
  end
  object PhPaneTool1: TPhPaneTool
    PhImage = PhImage1
    Left = 256
    Top = 40
  end
  object PhLenzTool1: TPhLenzTool
    PhImage = PhImage1
    Left = 256
    Top = 168
  end
  object PhZoomToRectTool1: TPhZoomToRectTool
    PhImage = PhImage1
    Left = 256
    Top = 104
  end
  object PhSelRectTool1: TPhSelRectTool
    PhImage = PhImage1
    Left = 256
    Top = 232
  end
end
