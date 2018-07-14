object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #1050#1077#1088#1072#1084#1080#1082#1072' '
  ClientHeight = 442
  ClientWidth = 647
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 423
    Width = 647
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Text = #1056#1045#1046#1048#1052': '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1072
        Width = 150
      end
      item
        Alignment = taCenter
        Text = #1050#1072#1076#1088' 999999 '#1080#1079' 1000000'
        Width = 150
      end
      item
        Text = #1048#1089#1090#1086#1095#1085#1080#1082' '#1076#1072#1085#1085#1099#1093': '
        Width = 200
      end
      item
        Text = #1057#1090#1072#1090#1091#1089':'
        Width = 50
      end>
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 647
    Height = 423
    Align = alClient
    TabOrder = 1
    object Panel3: TPanel
      Left = 1
      Top = 343
      Width = 645
      Height = 79
      Align = alBottom
      TabOrder = 0
      object SpeedButton4: TSpeedButton
        Left = 249
        Top = 1
        Width = 84
        Height = 77
        Action = viewNextAction
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
        ExplicitLeft = 205
        ExplicitTop = 6
      end
      object SpeedButton1: TSpeedButton
        Left = 333
        Top = 1
        Width = 84
        Height = 77
        Action = viewLastAction
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
        ExplicitLeft = 252
        ExplicitTop = 0
        ExplicitHeight = 72
      end
      object SpeedButton3: TSpeedButton
        Left = 85
        Top = 1
        Width = 84
        Height = 77
        Action = viewPrevAction
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
        ExplicitLeft = 84
        ExplicitTop = 0
        ExplicitHeight = 72
      end
      object SpeedButton2: TSpeedButton
        Left = 1
        Top = 1
        Width = 84
        Height = 77
        Action = viewFirstAction
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
        ExplicitLeft = 9
        ExplicitTop = 2
      end
      object SpeedButton9: TSpeedButton
        Left = 169
        Top = 1
        Width = 80
        Height = 77
        Action = viewPlayAction
        Align = alLeft
        AllowAllUp = True
        GroupIndex = 1
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
      end
    end
    object PhImage1: TPhImage
      Left = 1
      Top = 1
      Width = 407
      Height = 342
      ThumbWidht = 128
      ThumbHeight = 128
      SlideShowInterval = 500
      Align = alClient
      ParentColor = False
      OnMouseMove = PhImage1MouseMove
      AfterOpen = PhImage1AfterOpen
      OnFrameData = PhImage1FrameData
    end
    object Panel1: TPanel
      Left = 408
      Top = 1
      Width = 238
      Height = 342
      Align = alRight
      TabOrder = 2
      object GroupBox1: TGroupBox
        Left = 1
        Top = 1
        Width = 236
        Height = 160
        Align = alTop
        Caption = #1048#1079#1084#1077#1088#1077#1085#1085#1099#1077' '#1079#1085#1072#1095#1077#1085#1080#1103
        TabOrder = 0
        object Label1: TLabel
          Left = 5
          Top = 37
          Width = 67
          Height = 13
          Caption = #1044#1080#1072#1084#1077#1090#1088' ('#1084#1084')'
        end
        object Label2: TLabel
          Left = 5
          Top = 61
          Width = 111
          Height = 13
          Caption = #1041#1086#1083#1100#1096#1072#1103' '#1087#1086#1083#1091#1086#1089#1100' ('#1084#1084')'
        end
        object Label3: TLabel
          Left = 5
          Top = 87
          Width = 99
          Height = 13
          Caption = #1052#1072#1083#1072#1103' '#1087#1086#1083#1091#1086#1089#1100' ('#1084#1084')'
        end
        object Label4: TLabel
          Left = 5
          Top = 113
          Width = 104
          Height = 13
          Caption = #1059#1075#1086#1083' '#1085#1072#1082#1083#1086#1085#1072' ('#1075#1088#1072#1076')'
        end
        object Label5: TLabel
          Left = 132
          Top = 31
          Width = 55
          Height = 19
          Caption = '000.00'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clRed
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label6: TLabel
          Left = 132
          Top = 56
          Width = 55
          Height = 19
          Caption = '000.00'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clBlue
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label7: TLabel
          Left = 132
          Top = 82
          Width = 55
          Height = 19
          Caption = '000.00'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clBlue
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label8: TLabel
          Left = 132
          Top = 108
          Width = 55
          Height = 19
          Caption = '000.00'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clBlue
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
        object Label9: TLabel
          Left = 5
          Top = 138
          Width = 96
          Height = 13
          Caption = #1062#1077#1085#1090#1088' '#1084#1072#1089#1089' ('#1084#1084':'#1084#1084')'
        end
        object Label10: TLabel
          Left = 132
          Top = 137
          Width = 92
          Height = 14
          Caption = '000.00:000.00'
          Font.Charset = RUSSIAN_CHARSET
          Font.Color = clBlue
          Font.Height = -12
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
      object GroupBox2: TGroupBox
        Left = 1
        Top = 161
        Width = 236
        Height = 180
        Align = alClient
        Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1072#1083#1075#1086#1088#1080#1090#1084#1072
        TabOrder = 1
        object Label11: TLabel
          Left = 8
          Top = 24
          Width = 68
          Height = 13
          Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072': '
        end
        object Label12: TLabel
          Left = 8
          Top = 40
          Width = 77
          Height = 13
          Caption = #1044#1083#1080#1085#1072' ('#1087#1080#1082#1089') ='
        end
        object Label13: TLabel
          Left = 91
          Top = 40
          Width = 40
          Height = 13
          Caption = '0000.00'
        end
        object Label14: TLabel
          Left = 208
          Top = 40
          Width = 16
          Height = 13
          Caption = 'mm'
        end
        object Edit1: TEdit
          Left = 137
          Top = 37
          Width = 56
          Height = 21
          TabOrder = 0
          Text = '10'
        end
      end
    end
  end
  object ActionList1: TActionList
    Left = 56
    Top = 16
    object fileExitAction: TAction
      Category = 'File'
      Caption = #1042#1099#1093#1086#1076
      OnExecute = fileExitActionExecute
    end
    object modeExperimentAction: TAction
      Category = 'Mode'
      Caption = #1069#1082#1089#1087#1077#1088#1080#1084#1077#1085#1090
      GroupIndex = 1
      OnExecute = modeExperimentActionExecute
      OnUpdate = modeExperimentActionUpdate
    end
    object modeAutoAnalysisAction: TAction
      Category = 'Mode'
      Caption = #1053#1072#1073#1083#1102#1076#1077#1085#1080#1077
      GroupIndex = 1
      OnExecute = modeAutoAnalysisActionExecute
      OnUpdate = modeAutoAnalysisActionUpdate
    end
    object modeHandAction: TAction
      Category = 'Mode'
      Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072
      GroupIndex = 1
      OnExecute = modeHandActionExecute
      OnUpdate = modeHandActionUpdate
    end
    object viewSourceImageAction: TAction
      Category = 'view'
      Caption = #1048#1089#1093#1086#1076#1085#1086#1077' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077
      GroupIndex = -1
      OnExecute = viewSourceImageActionExecute
    end
    object viewAnalysisAreaAction: TAction
      Category = 'view'
      Caption = #1054#1073#1083#1072#1089#1090#1100' '#1072#1085#1072#1083#1080#1079#1072' '#1076#1072#1085#1085#1099#1093' '
      OnExecute = viewAnalysisAreaActionExecute
      OnUpdate = viewAnalysisAreaActionUpdate
    end
    object viewObjectContourAction: TAction
      Category = 'view'
      Caption = #1050#1086#1085#1090#1091#1088' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
      OnExecute = viewObjectContourActionExecute
      OnUpdate = viewObjectContourActionUpdate
    end
    object viewCenterAction: TAction
      Category = 'view'
      Caption = #1062#1077#1085#1090#1088' '#1084#1072#1089#1089' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
      OnExecute = viewCenterActionExecute
      OnUpdate = viewCenterActionUpdate
    end
    object viewAxisAction: TAction
      Category = 'view'
      Caption = #1053#1072#1081#1076#1077#1085#1085#1099#1077' '#1087#1086#1083#1091#1086#1089#1080'  '#1101#1083#1083#1080#1087#1089#1072
      OnExecute = viewAxisActionExecute
      OnUpdate = viewAxisActionUpdate
    end
    object viewEllipseAction: TAction
      Category = 'view'
      Caption = #1040#1087#1087#1088#1086#1082#1089#1080#1084#1080#1088#1091#1102#1097#1080#1081' '#1101#1083#1083#1080#1087#1089
      OnExecute = viewEllipseActionExecute
      OnUpdate = viewEllipseActionUpdate
    end
    object fileOpenImagesAction: TAction
      Category = 'File'
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1103'...'
      OnExecute = fileOpenImagesActionExecute
    end
    object fileOpenVideoAction: TAction
      Category = 'File'
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1074#1080#1076#1077#1086#1092#1072#1081#1083'... '
      OnExecute = fileOpenVideoActionExecute
    end
    object fileConnectToCameraAction: TAction
      Category = 'File'
      Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103' '#1082' '#1082#1072#1084#1077#1088#1077'... '
      OnExecute = fileConnectToCameraActionExecute
    end
    object fileCloseAction: TAction
      Category = 'File'
      Caption = #1047#1072#1082#1088#1099#1090#1100' '#1080#1089#1090#1086#1095#1085#1080#1082
      OnExecute = fileCloseActionExecute
    end
    object viewFirstAction: TAction
      Category = 'view'
      Caption = #1042' '#1085#1072#1095#1072#1083#1086
      OnExecute = viewFirstActionExecute
      OnUpdate = viewFirstActionUpdate
    end
    object viewPrevAction: TAction
      Category = 'view'
      Caption = #1055#1088#1077#1076#1091#1076#1091#1097'.'
      OnExecute = viewPrevActionExecute
      OnUpdate = viewPrevActionUpdate
    end
    object viewNextAction: TAction
      Category = 'view'
      Caption = #1057#1083#1077#1076#1091#1102#1097'.'
      OnExecute = viewNextActionExecute
      OnUpdate = viewNextActionUpdate
    end
    object viewLastAction: TAction
      Category = 'view'
      Caption = #1042' '#1082#1086#1085#1077#1094
      OnExecute = viewLastActionExecute
      OnUpdate = viewLastActionUpdate
    end
    object viewPlayAction: TAction
      Category = 'view'
      Caption = #1042#1086#1089#1087#1088#1086#1080#1079#1074#1077#1089#1090#1080
      OnExecute = viewPlayActionExecute
      OnUpdate = viewPlayActionUpdate
    end
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 16
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083#1099
      object N15: TMenuItem
        Action = fileOpenImagesAction
      end
      object N16: TMenuItem
        Action = fileOpenVideoAction
      end
      object N17: TMenuItem
        Action = fileConnectToCameraAction
      end
      object N18: TMenuItem
        Caption = '-'
      end
      object N19: TMenuItem
        Action = fileCloseAction
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object N2: TMenuItem
        Action = fileExitAction
      end
    end
    object N8: TMenuItem
      Caption = #1055#1088#1086#1089#1084#1086#1090#1088
      object N9: TMenuItem
        Action = viewSourceImageAction
      end
      object N10: TMenuItem
        Action = viewAnalysisAreaAction
      end
      object N11: TMenuItem
        Action = viewObjectContourAction
      end
      object N12: TMenuItem
        Action = viewCenterAction
      end
      object N13: TMenuItem
        Action = viewAxisAction
      end
      object N14: TMenuItem
        Action = viewEllipseAction
      end
    end
    object N4: TMenuItem
      Caption = #1056#1077#1078#1080#1084
      object N7: TMenuItem
        Action = modeHandAction
      end
      object N6: TMenuItem
        Action = modeAutoAnalysisAction
      end
      object N5: TMenuItem
        Action = modeExperimentAction
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofFileMustExist, ofEnableSizing]
    Left = 88
    Top = 16
  end
  object PhRulerTool1: TPhRulerTool
    PhImage = PhImage1
    Left = 16
    Top = 80
  end
  object PhPaneTool1: TPhPaneTool
    PhImage = PhImage1
    Left = 56
    Top = 80
  end
end
