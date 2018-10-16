object TuningForm: TTuningForm
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1084#1086#1076#1091#1083#1103
  ClientHeight = 284
  ClientWidth = 250
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    AlignWithMargins = True
    Left = 3
    Top = 10
    Width = 244
    Height = 103
    Margins.Top = 10
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 16
      Width = 153
      Height = 13
      Caption = #1063#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1076#1077#1090#1077#1082#1090#1086#1088#1072
    end
    object Label2: TLabel
      Left = 16
      Top = 72
      Width = 84
      Height = 13
      Caption = #1052#1072#1089#1096#1090#1072#1073' '#1085#1086#1084#1077#1088#1072
      Enabled = False
    end
    object TrackBar1: TTrackBar
      Left = 13
      Top = 36
      Width = 168
      Height = 24
      Max = 100
      Position = 50
      ShowSelRange = False
      TabOrder = 0
      ThumbLength = 15
      TickMarks = tmBoth
      TickStyle = tsNone
      OnChange = TrackBar1Change
    end
    object Edit1: TEdit
      Left = 187
      Top = 36
      Width = 38
      Height = 21
      Alignment = taCenter
      Enabled = False
      TabOrder = 1
      Text = '50'
    end
    object CSpinEdit1: TCSpinEdit
      Left = 187
      Top = 69
      Width = 38
      Height = 22
      Enabled = False
      TabOrder = 2
    end
  end
  object CheckBox1: TCheckBox
    Left = 16
    Top = 4
    Width = 185
    Height = 17
    Caption = #1056#1072#1089#1087#1086#1079#1085#1072#1074#1072#1085#1080#1077' '#1085#1086#1084#1077#1088#1086#1074' '#1074#1072#1075#1086#1085#1086#1074
    Checked = True
    State = cbChecked
    TabOrder = 1
    OnClick = CheckBox1Click
  end
  object GroupBox2: TGroupBox
    AlignWithMargins = True
    Left = 3
    Top = 126
    Width = 244
    Height = 150
    Margins.Top = 10
    Align = alTop
    TabOrder = 2
    object Label3: TLabel
      Left = 19
      Top = 16
      Width = 153
      Height = 13
      Caption = #1063#1091#1074#1089#1090#1074#1080#1090#1077#1083#1100#1085#1086#1089#1090#1100' '#1076#1077#1090#1077#1082#1090#1086#1088#1072
    end
    object Label4: TLabel
      Left = 19
      Top = 128
      Width = 159
      Height = 13
      Caption = #1052#1086#1076#1077#1083#1100' '#1084#1080#1096#1077#1085#1080' '#1085#1077' '#1089#1091#1097#1077#1089#1090#1074#1091#1077#1090
      Color = clBackground
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object Edit2: TEdit
      Left = 187
      Top = 36
      Width = 38
      Height = 21
      Alignment = taCenter
      Enabled = False
      TabOrder = 0
      Text = '50'
    end
    object TrackBar2: TTrackBar
      Left = 16
      Top = 36
      Width = 168
      Height = 24
      Max = 100
      Position = 50
      ShowSelRange = False
      TabOrder = 1
      ThumbLength = 15
      TickMarks = tmBoth
      TickStyle = tsNone
      OnChange = TrackBar2Change
    end
    object Button1: TButton
      Left = 19
      Top = 66
      Width = 162
      Height = 25
      Caption = #1057#1086#1079#1076#1072#1090#1100' '#1084#1086#1076#1077#1083#1100
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 19
      Top = 97
      Width = 162
      Height = 25
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1084#1086#1076#1077#1083#1100
      TabOrder = 3
      OnClick = Button2Click
    end
  end
  object CheckBox2: TCheckBox
    Left = 8
    Top = 117
    Width = 105
    Height = 17
    Caption = #1057#1095#1077#1090#1095#1080#1082' '#1074#1072#1075#1086#1085#1086#1074
    Checked = True
    State = cbChecked
    TabOrder = 3
    OnClick = CheckBox2Click
  end
  object ApplicationEvents1: TApplicationEvents
    OnIdle = ApplicationEvents1Idle
    Left = 203
    Top = 238
  end
end
