object copyForm: TcopyForm
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Copy/Move Image(s)'
  ClientHeight = 374
  ClientWidth = 297
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
    Height = 241
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 44
    Height = 13
    Caption = 'To Path: '
  end
  object OKBtn: TButton
    Left = 64
    Top = 342
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 145
    Top = 342
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 72
    Top = 16
    Width = 209
    Height = 21
    ReadOnly = True
    TabOrder = 2
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 16
    Top = 43
    Width = 265
    Height = 198
    TabOrder = 3
  end
  object CheckBox1: TCheckBox
    Left = 8
    Top = 256
    Width = 281
    Height = 17
    Caption = 'Open in Explorer '
    TabOrder = 4
  end
  object CheckBox2: TCheckBox
    Left = 8
    Top = 280
    Width = 281
    Height = 17
    Caption = 'Open with Photon '
    TabOrder = 5
  end
  object CheckBox3: TCheckBox
    Left = 8
    Top = 304
    Width = 281
    Height = 17
    Caption = 'Open with new instance of Photon'
    TabOrder = 6
  end
end
