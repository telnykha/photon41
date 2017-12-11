object convertForm: TconvertForm
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Convert images'
  ClientHeight = 131
  ClientWidth = 187
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 169
    Height = 89
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 93
    Height = 13
    Caption = 'Output File Format '
  end
  object OKBtn: TButton
    Left = 12
    Top = 103
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 93
    Top = 103
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object ComboBox1: TComboBox
    Left = 16
    Top = 38
    Width = 145
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 2
    Text = 'jpeg'
    Items.Strings = (
      'jpeg'
      'png'
      'tiff'
      'tga'
      'bmp '
      'ppm'
      'awp')
  end
  object CheckBox1: TCheckBox
    Left = 16
    Top = 71
    Width = 97
    Height = 17
    Caption = 'Keep source files'
    TabOrder = 3
  end
end
