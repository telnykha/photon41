object NewEventDlg: TNewEventDlg
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = #1053#1086#1074#1086#1077' '#1089#1086#1073#1099#1090#1080#1077
  ClientHeight = 87
  ClientWidth = 384
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 281
    Height = 73
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 83
    Height = 13
    Caption = #1042#1088#1077#1084#1103' '#1089#1086#1073#1099#1090#1080#1103': '
  end
  object Label2: TLabel
    Left = 115
    Top = 19
    Width = 5
    Height = 19
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 16
    Top = 52
    Width = 86
    Height = 13
    Caption = #1063#1080#1089#1083#1086' '#1086#1073#1098#1077#1082#1090#1086#1074':'
  end
  object OKBtn: TButton
    Left = 300
    Top = 8
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 300
    Top = 38
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object SpinEdit1: TSpinEdit
    Left = 112
    Top = 43
    Width = 65
    Height = 22
    MaxValue = 5
    MinValue = -5
    TabOrder = 2
    Value = 0
  end
end
