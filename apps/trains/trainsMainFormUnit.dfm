object mainForm: TmainForm
  Left = 0
  Top = 0
  Caption = #1054#1073#1085#1072#1088#1091#1078#1077#1085#1080#1077' '#1080' '#1088#1072#1089#1087#1086#1079#1085#1072#1074#1072#1085#1080#1077' '#1085#1086#1084#1077#1088#1086#1074' '#1074#1072#1075#1086#1085#1086#1074'. '
  ClientHeight = 542
  ClientWidth = 764
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 523
    Width = 764
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Text = #1056#1077#1078#1080#1084':'
        Width = 150
      end
      item
        Alignment = taCenter
        Text = #1050#1072#1076#1088' 999999 '#1080#1079' 1000000'
        Width = 150
      end
      item
        Alignment = taCenter
        Text = #1048#1089#1090#1086#1095#1085#1080#1082' '#1076#1072#1085#1085#1099#1093': '
        Width = 200
      end
      item
        Text = #1048#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077':'
        Width = 150
      end>
    ExplicitWidth = 737
  end
  object Panel1: TPanel
    Left = 0
    Top = 448
    Width = 764
    Height = 75
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 1
    ExplicitWidth = 737
    object SpeedButton2: TSpeedButton
      Left = 1
      Top = 1
      Width = 64
      Height = 73
      Action = FirstFrameAction
      Align = alLeft
      Caption = #1074' '#1085#1072#1095#1072#1083#1086
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
      ExplicitLeft = 2
      ExplicitTop = 3
      ExplicitHeight = 48
    end
    object SpeedButton3: TSpeedButton
      Left = 65
      Top = 1
      Width = 64
      Height = 73
      Action = PrevFrameAction
      Align = alLeft
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
      ExplicitLeft = 66
      ExplicitTop = 3
      ExplicitHeight = 48
    end
    object SpeedButton9: TSpeedButton
      Left = 129
      Top = 1
      Width = 64
      Height = 73
      Action = PlayAction
      Align = alLeft
      AllowAllUp = True
      Caption = #1074#1086#1089#1087#1088'.'
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
      ExplicitLeft = 130
      ExplicitTop = 3
      ExplicitHeight = 48
    end
    object SpeedButton4: TSpeedButton
      Left = 193
      Top = 1
      Width = 64
      Height = 73
      Action = NextFrameAction
      Align = alLeft
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
      ExplicitLeft = 194
      ExplicitTop = 3
      ExplicitHeight = 48
    end
    object SpeedButton5: TSpeedButton
      Left = 257
      Top = 1
      Width = 64
      Height = 73
      Action = LastFrameAction
      Align = alLeft
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
      ExplicitLeft = 258
      ExplicitTop = 3
      ExplicitHeight = 48
    end
    object GroupBox1: TGroupBox
      Left = 346
      Top = 1
      Width = 160
      Height = 73
      Align = alLeft
      TabOrder = 0
      ExplicitLeft = 321
      object Label2: TLabel
        Left = 59
        Top = 28
        Width = 88
        Height = 42
        Caption = '0000'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -35
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label4: TLabel
        Left = 12
        Top = 3
        Width = 132
        Height = 25
        Caption = '000.00 '#1082#1084'/'#1095
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -21
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Panel2: TPanel
        Left = 12
        Top = 35
        Width = 41
        Height = 33
        BevelOuter = bvLowered
        Color = clRed
        ParentBackground = False
        TabOrder = 0
      end
    end
    object GroupBox2: TGroupBox
      Left = 506
      Top = 1
      Width = 248
      Height = 73
      Align = alLeft
      TabOrder = 1
      ExplicitLeft = 481
      object Label3: TLabel
        Left = 6
        Top = 28
        Width = 232
        Height = 42
        Caption = '########'
        Color = clHighlight
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGray
        Font.Height = -35
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentColor = False
        ParentFont = False
      end
    end
    object ProgressBar1: TProgressBar
      AlignWithMargins = True
      Left = 324
      Top = 6
      Width = 19
      Height = 63
      Margins.Top = 5
      Margins.Bottom = 5
      Align = alLeft
      DoubleBuffered = False
      Orientation = pbVertical
      ParentDoubleBuffered = False
      Step = 1
      TabOrder = 2
    end
  end
  object FImage1: TPhImage
    Left = 0
    Top = 0
    Width = 764
    Height = 424
    ThumbWidht = 128
    ThumbHeight = 128
    SlideShowInterval = 500
    Align = alClient
    ParentColor = False
    OnFrameData = FImage1FrameData
    ExplicitWidth = 737
  end
  object PhTrackBar1: TPhTrackBar
    Left = 0
    Top = 424
    Width = 764
    Height = 24
    Align = alBottom
    Max = 0
    ShowSelRange = False
    TabOrder = 3
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = PhTrackBar1Change
    OnKeyUp = PhTrackBar1KeyUp
    OnMouseUp = PhTrackBar1MouseUp
    ExplicitWidth = 737
  end
  object ActionList1: TActionList
    Left = 56
    Top = 24
    object CloseAction: TAction
      Category = 'Files'
      Caption = #1042#1099#1093#1086#1076
      OnExecute = CloseActionExecute
    end
    object ModePaneAction: TAction
      Caption = #1056#1077#1078#1080#1084' '#1087#1088#1086#1089#1084#1086#1090#1088#1072
      OnExecute = ModePaneActionExecute
      OnUpdate = ModePaneActionUpdate
    end
    object ModeSelRectAction: TAction
      Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1090#1100' '#1079#1086#1085#1099
      OnExecute = ModeSelRectActionExecute
      OnUpdate = ModeSelRectActionUpdate
    end
    object ActualSizeAction: TAction
      Category = 'View'
      Caption = #1048#1089#1093#1086#1076#1085#1099#1081' '#1088#1072#1079#1084#1077#1088
      OnExecute = ActualSizeActionExecute
      OnUpdate = ActualSizeActionUpdate
    end
    object BestFitAction: TAction
      Category = 'View'
      Caption = #1042#1087#1080#1089#1072#1090#1100' '#1074' '#1086#1082#1085#1086
      OnExecute = BestFitActionExecute
      OnUpdate = BestFitActionUpdate
    end
    object AboutAction: TAction
      Category = 'Help'
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
    end
    object OpenVideoAction: TAction
      Category = 'Files'
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1074#1080#1076#1077#1086#1092#1072#1081#1083'...'
      OnExecute = OpenVideoActionExecute
    end
    object SaveImageAction: TAction
      Category = 'Files'
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077'...'
      Visible = False
    end
    object CloseVideoAction: TAction
      Category = 'Files'
      Caption = #1047#1072#1082#1088#1099#1090#1100' '#1074#1080#1076#1077#1086#1080#1089#1090#1086#1095#1085#1080#1082
      OnExecute = CloseVideoActionExecute
      OnUpdate = CloseVideoActionUpdate
    end
    object PlayAction: TAction
      Category = 'Video'
      Caption = #1042#1086#1089#1087#1088#1086#1080#1079#1074#1077#1089#1090#1080
      OnExecute = PlayActionExecute
      OnUpdate = PlayActionUpdate
    end
    object FirstFrameAction: TAction
      Category = 'Video'
      Caption = 'FirstFrameAction'
      OnExecute = FirstFrameActionExecute
      OnUpdate = FirstFrameActionUpdate
    end
    object PrevFrameAction: TAction
      Category = 'Video'
      Caption = #1087#1088#1077#1076#1099#1076#1091#1097'.'
      OnExecute = PrevFrameActionExecute
      OnUpdate = PrevFrameActionUpdate
    end
    object NextFrameAction: TAction
      Category = 'Video'
      Caption = #1089#1083#1077#1076#1091#1102#1097'.'
      OnExecute = NextFrameActionExecute
      OnUpdate = NextFrameActionUpdate
    end
    object LastFrameAction: TAction
      Category = 'Video'
      Caption = #1074' '#1082#1086#1085#1077#1094
      OnExecute = LastFrameActionExecute
      OnUpdate = LastFrameActionUpdate
    end
    object OptionsAction: TAction
      Category = 'Tools'
      Caption = #1055#1077#1088#1077#1093#1086#1076' '#1085#1072' '#1082#1072#1076#1088'...'
    end
    object logOpenAction: TAction
      Hint = #1047#1072#1075#1088#1091#1079#1080#1090#1100' log '#1092#1072#1081#1083
    end
    object logSaveAction: TAction
      Hint = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1083#1086#1075' '#1092#1072#1081#1083
    end
    object logClearAction: TAction
      Hint = #1054#1095#1080#1089#1090#1080#1090#1100' '#1083#1086#1075' '#1092#1072#1081#1083
    end
    object logInsertAction: TAction
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1085#1086#1074#1086#1077' '#1089#1086#1073#1099#1090#1080#1077' '#1074' '#1083#1086#1075' '#1092#1072#1081#1083
    end
    object logDeleteAction: TAction
      Hint = #1059#1076#1072#1083#1080#1090#1100' '#1089#1086#1073#1099#1090#1080#1077' '#1080#1079' '#1083#1086#1075' '#1092#1072#1081#1083#1072
    end
    object GotoFrameAction: TAction
      Category = 'Video'
      Caption = #1055#1077#1088#1077#1081#1090#1080' '#1085#1072' '#1082#1072#1076#1088'...'
      OnExecute = GotoFrameActionExecute
      OnUpdate = GotoFrameActionUpdate
    end
    object modeAnalysisAction: TAction
      Category = 'Mode'
      Caption = #1053#1072#1073#1083#1102#1076#1077#1085#1080#1077
      GroupIndex = 4
      OnExecute = modeAnalysisActionExecute
      OnUpdate = modeAnalysisActionUpdate
    end
    object modeTuningAction: TAction
      Category = 'Mode'
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
      Checked = True
      GroupIndex = 4
      OnExecute = modeTuningActionExecute
      OnUpdate = modeTuningActionUpdate
    end
    object viewZonesAction: TAction
      Category = 'View'
      Caption = #1047#1086#1085#1099' '#1085#1072#1073#1083#1102#1076#1077#1085#1080#1103
      Checked = True
      OnExecute = viewZonesActionExecute
    end
    object viewDetectRectAction: TAction
      Category = 'View'
      Caption = #1042#1099#1074#1086#1076' '#1076#1077#1090#1077#1082#1090#1086#1088#1072
      Checked = True
      OnExecute = viewDetectRectActionExecute
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 88
    Top = 24
    object N1: TMenuItem
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077'...'
      Visible = False
    end
    object N4: TMenuItem
      Caption = '-'
    end
    object N5: TMenuItem
      Action = ModePaneAction
    end
    object N6: TMenuItem
      Action = ModeSelRectAction
    end
    object N7: TMenuItem
      Caption = '-'
    end
    object N8: TMenuItem
      Action = ActualSizeAction
    end
    object N9: TMenuItem
      Action = BestFitAction
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object N10: TMenuItem
      Action = AboutAction
    end
    object N3: TMenuItem
      Action = CloseAction
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Jpeg images|*.jpeg;*.jpg|AWP images|*.awp'
    Left = 120
    Top = 24
  end
  object MainMenu1: TMainMenu
    Left = 152
    Top = 24
    object N11: TMenuItem
      Caption = #1060#1072#1081#1083#1099
      object N14: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077'...'
        Visible = False
      end
      object N17: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100' '#1089#1083#1072#1081#1076'-'#1096#1086#1091'...'
        Visible = False
      end
      object N18: TMenuItem
        Action = OpenVideoAction
      end
      object USB1: TMenuItem
        Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103' '#1082' USB '#1082#1072#1084#1077#1088#1077'...'
        Visible = False
      end
      object IP1: TMenuItem
        Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103' '#1082' IP '#1082#1072#1084#1077#1088#1077'...'
        Visible = False
      end
      object N22: TMenuItem
        Caption = '-'
      end
      object N21: TMenuItem
        Action = CloseVideoAction
      end
      object N19: TMenuItem
        Caption = '-'
      end
      object N20: TMenuItem
        Action = SaveImageAction
      end
      object N13: TMenuItem
        Caption = '-'
      end
      object N12: TMenuItem
        Action = CloseAction
      end
    end
    object N36: TMenuItem
      Caption = #1055#1088#1086#1089#1084#1086#1090#1088
      object N37: TMenuItem
        Action = viewZonesAction
      end
      object N38: TMenuItem
        Action = viewDetectRectAction
      end
    end
    object N25: TMenuItem
      Caption = #1042#1080#1076#1077#1086
      object FirstFrameAction1: TMenuItem
        Action = FirstFrameAction
      end
      object N26: TMenuItem
        Action = PrevFrameAction
      end
      object N27: TMenuItem
        Action = NextFrameAction
      end
      object N28: TMenuItem
        Action = LastFrameAction
      end
      object N29: TMenuItem
        Caption = '-'
      end
      object N30: TMenuItem
        Action = PlayAction
      end
      object N31: TMenuItem
        Caption = '-'
      end
      object N32: TMenuItem
        Action = GotoFrameAction
      end
    end
    object N33: TMenuItem
      Caption = #1056#1077#1078#1080#1084
      object N34: TMenuItem
        Action = modeTuningAction
      end
      object N35: TMenuItem
        Action = modeAnalysisAction
      end
    end
    object N15: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      object N16: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
        OnClick = N16Click
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 184
    Top = 24
  end
  object PhPaneTool1: TPhPaneTool
    PhImage = FImage1
    Left = 224
    Top = 24
  end
end
