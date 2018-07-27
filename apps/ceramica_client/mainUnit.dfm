object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Form3'
  ClientHeight = 321
  ClientWidth = 260
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 41
    Width = 260
    Height = 111
    Align = alTop
    Caption = #1048#1079#1084#1077#1088#1077#1085#1085#1099#1077' '#1079#1085#1072#1095#1077#1085#1080#1103
    TabOrder = 0
    object Label1: TLabel
      Left = 5
      Top = 23
      Width = 55
      Height = 13
      Caption = #1044#1080#1072#1084#1077#1090#1088':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 5
      Top = 39
      Width = 105
      Height = 13
      Caption = #1041#1086#1083#1100#1096#1072#1103' '#1087#1086#1083#1091#1086#1089#1100':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 5
      Top = 57
      Width = 92
      Height = 13
      Caption = #1052#1072#1083#1072#1103' '#1087#1086#1083#1091#1086#1089#1100':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 5
      Top = 74
      Width = 83
      Height = 13
      Caption = #1059#1075#1086#1083' '#1085#1072#1082#1083#1086#1085#1072':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 132
      Top = 17
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
      Top = 34
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
      Top = 52
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
      Top = 69
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
      Top = 90
      Width = 115
      Height = 13
      Caption = #1062#1077#1085#1090#1088' '#1084#1072#1089#1089' ('#1084#1084':'#1084#1084')'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label10: TLabel
      Left = 132
      Top = 89
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
    Left = 0
    Top = 0
    Width = 260
    Height = 41
    Align = alTop
    Caption = #1057#1077#1088#1074#1077#1088
    TabOrder = 1
    object Edit1: TEdit
      Left = 2
      Top = 15
      Width = 256
      Height = 24
      Align = alClient
      TabOrder = 0
      Text = 'Edit1'
      ExplicitHeight = 21
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 177
    Width = 260
    Height = 144
    Align = alClient
    Lines.Strings = (
      'Memo1')
    TabOrder = 2
  end
  object Panel1: TPanel
    Left = 0
    Top = 152
    Width = 260
    Height = 25
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    object CheckBox1: TCheckBox
      Left = 5
      Top = 4
      Width = 182
      Height = 17
      Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103' '#1082' '#1089#1077#1088#1074#1077#1088#1091
      TabOrder = 0
      OnClick = CheckBox1Click
    end
  end
  object IdTCPClient1: TIdTCPClient
    OnDisconnected = IdTCPClient1Disconnected
    OnConnected = IdTCPClient1Connected
    ConnectTimeout = 5000
    IPVersion = Id_IPv4
    Port = 0
    ReadTimeout = -1
    Left = 136
    Top = 193
  end
  object IdAntiFreeze1: TIdAntiFreeze
    Left = 184
    Top = 192
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 96
    Top = 192
  end
end
