object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 396
  ClientWidth = 600
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PhImage1: TPhImage
    Left = 0
    Top = 0
    Width = 421
    Height = 377
    BorderStyle = bsFSingle
    Align = alClient
    ParentColor = False
    OnMouseUp = PhImage1MouseUp
    AfterOpen = PhImage1AfterOpen
    OnScaleChange = PhImage1ScaleChange
    OnChange = PhImage1Change
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 377
    Width = 600
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
        Width = 100
      end
      item
        Alignment = taCenter
        Width = 100
      end
      item
        Alignment = taCenter
        Width = 100
      end>
  end
  object Panel1: TPanel
    Left = 421
    Top = 0
    Width = 179
    Height = 377
    Align = alRight
    TabOrder = 2
    object PhImage2: TPhImage
      Left = 1
      Top = 1
      Width = 177
      Height = 100
      BorderStyle = bsFSingle
      Align = alTop
      ParentColor = False
    end
    object Panel2: TPanel
      Left = 1
      Top = 101
      Width = 177
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      Caption = 'RESULT'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 142
      Width = 177
      Height = 107
      Align = alTop
      Caption = 'OCR Tesseract'
      TabOrder = 2
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 249
      Width = 177
      Height = 127
      Align = alClient
      Caption = 'Search Engine'
      TabOrder = 3
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
        OnClick = Exit1Click
      end
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
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
        Action = toolLenzAction
      end
      object LenzTool1: TMenuItem
        Action = toolSelectRectAction
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object ZoomIn1: TMenuItem
        Action = viewActualSizeAction
      end
      object ZoomOut1: TMenuItem
        Action = viewBestFitAction
      end
      object ZoomTo1: TMenuItem
        Action = viewZoomInAction
      end
      object BestFit1: TMenuItem
        Action = viewZoomOutAction
      end
      object FitToWidth1: TMenuItem
        Action = viewFitWidthAction
      end
      object FitHeight1: TMenuItem
        Action = viewFitHeightAction
      end
    end
  end
  object ActionList1: TActionList
    Left = 24
    Top = 16
    object fileOpenAction: TAction
      Category = 'File'
      Caption = 'Open media...'
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
    object editClearSelectionAction: TAction
      Category = 'Edit'
      Caption = 'Clear Selection'
      OnExecute = editClearSelectionActionExecute
      OnUpdate = editClearSelectionActionUpdate
    end
  end
  object SaveDialog1: TSaveDialog
    FileName = 'default.jpg'
    Filter = 
      'Jpeg images|*.jpg|Awp imges|*.awp|PNG images|*.png|TIFF images |' +
      '*.tif'
    Left = 24
    Top = 176
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'Jpeg images|*.jpg|BMP images|*.bmp|PPM images|*.ppm|TGA images|*' +
      '.tga|GIF images|*.gif|AWP images|*.awp|PNG images|*.png|TIFF ima' +
      'ges|*.tif'
    Left = 24
    Top = 120
  end
  object PhSelRectTool1: TPhSelRectTool
    PhImage = PhImage1
    Left = 360
    Top = 16
  end
  object PhPaneTool1: TPhPaneTool
    PhImage = PhImage1
    Left = 360
    Top = 72
  end
  object PhZoomToRectTool1: TPhZoomToRectTool
    PhImage = PhImage1
    Left = 360
    Top = 128
  end
  object PhLenzTool1: TPhLenzTool
    PhImage = PhImage1
    Left = 360
    Top = 184
  end
end
