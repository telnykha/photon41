object VideoControlDlg: TVideoControlDlg
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1074#1080#1076#1077#1086
  ClientHeight = 267
  ClientWidth = 292
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 19
    Width = 46
    Height = 13
    Caption = #1071#1088#1082#1086#1089#1090#1100':'
  end
  object Label2: TLabel
    Left = 8
    Top = 47
    Width = 57
    Height = 13
    Caption = #1050#1086#1085#1089#1090#1088#1072#1089#1090':'
  end
  object Label5: TLabel
    Left = 8
    Top = 77
    Width = 34
    Height = 13
    Caption = #1043#1072#1084#1084#1072':'
  end
  object Label7: TLabel
    Left = 8
    Top = 107
    Width = 28
    Height = 13
    Caption = #1043#1077#1081#1085':'
  end
  object Label8: TLabel
    Left = 8
    Top = 132
    Width = 59
    Height = 13
    Caption = #1069#1082#1089#1087#1086#1079#1080#1094#1080#1103
  end
  object Label9: TLabel
    Left = 18
    Top = 154
    Width = 34
    Height = 13
    Caption = #1043#1088#1091#1073#1086':'
  end
  object Label10: TLabel
    Left = 18
    Top = 182
    Width = 34
    Height = 13
    Caption = #1058#1086#1095#1085#1086':'
  end
  object Label3: TLabel
    Left = 18
    Top = 219
    Width = 46
    Height = 13
    Caption = #1071#1088#1082#1086#1089#1090#1100':'
  end
  object TrackBar1: TTrackBar
    Left = 73
    Top = 12
    Width = 150
    Height = 24
    Max = 255
    Position = 128
    ShowSelRange = False
    TabOrder = 0
    ThumbLength = 15
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = TrackBar1Change
  end
  object TrackBar2: TTrackBar
    Left = 73
    Top = 41
    Width = 150
    Height = 24
    Max = 512
    Position = 256
    ShowSelRange = False
    TabOrder = 1
    ThumbLength = 15
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = TrackBar2Change
  end
  object TrackBar5: TTrackBar
    Left = 73
    Top = 74
    Width = 150
    Height = 24
    Max = 217
    Min = 45
    Position = 128
    ShowSelRange = False
    TabOrder = 2
    ThumbLength = 15
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = TrackBar5Change
  end
  object TrackBar7: TTrackBar
    Left = 73
    Top = 105
    Width = 150
    Height = 24
    Max = 6
    ShowSelRange = False
    TabOrder = 3
    ThumbLength = 15
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = TrackBar7Change
  end
  object TrackBar8: TTrackBar
    Left = 73
    Top = 147
    Width = 150
    Height = 24
    Max = 333152
    Min = 11
    Frequency = 10000
    Position = 128
    ShowSelRange = False
    TabOrder = 4
    ThumbLength = 15
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = TrackBar8Change
  end
  object TrackBar9: TTrackBar
    Left = 73
    Top = 179
    Width = 150
    Height = 23
    Max = 200
    ShowSelRange = False
    TabOrder = 5
    ThumbLength = 15
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = TrackBar8Change
  end
  object Edit1: TEdit
    Left = 229
    Top = 11
    Width = 54
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 6
    Text = '128'
  end
  object Edit2: TEdit
    Left = 229
    Top = 38
    Width = 54
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 7
    Text = '128'
  end
  object Edit5: TEdit
    Left = 229
    Top = 68
    Width = 54
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 8
    Text = '128'
  end
  object Edit7: TEdit
    Left = 229
    Top = 98
    Width = 54
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 9
    Text = '128'
  end
  object Edit8: TEdit
    Left = 229
    Top = 146
    Width = 54
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 10
    Text = '128'
  end
  object CheckBox1: TCheckBox
    Left = 18
    Top = 242
    Width = 97
    Height = 17
    Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1095#1077#1089#1082#1080
    TabOrder = 11
    OnClick = CheckBox1Click
  end
  object TrackBar3: TTrackBar
    Left = 73
    Top = 212
    Width = 150
    Height = 24
    Max = 128
    Frequency = 10000
    Position = 64
    ShowSelRange = False
    TabOrder = 12
    ThumbLength = 15
    TickMarks = tmBoth
    TickStyle = tsNone
    OnChange = TrackBar3Change
  end
  object Edit3: TEdit
    Left = 229
    Top = 211
    Width = 54
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 13
    Text = '128'
  end
end
