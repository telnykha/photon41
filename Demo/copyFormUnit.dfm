object copyForm: TcopyForm
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Copy/Move Image(s)'
  ClientHeight = 381
  ClientWidth = 297
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 7
    Width = 281
    Height = 234
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 44
    Height = 13
    Caption = 'To Path: '
  end
  object Label2: TLabel
    Left = 16
    Top = 195
    Width = 25
    Height = 13
    Caption = 'Drive'
  end
  object OKBtn: TButton
    Left = 64
    Top = 348
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 145
    Top = 348
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
    Height = 150
    TabOrder = 3
    OnChange = DirectoryListBox1Change
  end
  object DriveComboBox1: TDriveComboBox
    Left = 16
    Top = 213
    Width = 265
    Height = 19
    DirList = DirectoryListBox1
    TabOrder = 4
  end
  object RadioGroup1: TRadioGroup
    Left = 8
    Top = 247
    Width = 281
    Height = 95
    Caption = 'After Operatioin Action'
    ItemIndex = 0
    Items.Strings = (
      'Open images in Windows Explorer '
      'Open images with this Photon'
      'Open images with new Photon')
    TabOrder = 5
  end
end
