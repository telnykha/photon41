object AboutBox: TAboutBox
  Left = 396
  Top = 328
  BorderStyle = bsDialog
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 136
  ClientWidth = 298
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 281
    Height = 89
    BevelInner = bvRaised
    BevelOuter = bvLowered
    ParentColor = True
    TabOrder = 0
    object ProductName: TLabel
      Left = 91
      Top = 16
      Width = 91
      Height = 13
      Caption = #1057#1095#1077#1090#1095#1080#1082' '#1086#1073#1098#1077#1082#1090#1086#1074
      IsControl = True
    end
    object Label1: TLabel
      Left = 24
      Top = 64
      Width = 230
      Height = 13
      Caption = 'Copyright (c) 2015-2017 Adaptive Neurosystems '
    end
    object Label2: TLabel
      Left = 24
      Top = 40
      Width = 43
      Height = 13
      Caption = #1042#1077#1088#1089#1080#1103': '
    end
    object Version: TLabel
      Left = 72
      Top = 40
      Width = 35
      Height = 13
      Caption = 'Version'
    end
  end
  object OKButton: TButton
    Left = 111
    Top = 103
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
end
