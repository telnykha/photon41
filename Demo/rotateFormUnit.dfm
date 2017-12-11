object rotateForm: TrotateForm
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Rotate image(s)'
  ClientHeight = 265
  ClientWidth = 201
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 185
    Height = 161
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 8
    Top = 176
    Width = 74
    Height = 13
    Caption = 'Rotation angle:'
  end
  object Label2: TLabel
    Left = 154
    Top = 195
    Width = 35
    Height = 13
    Caption = 'Degree'
  end
  object OKBtn: TButton
    Left = 21
    Top = 232
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 102
    Top = 232
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object RadioGroup1: TRadioGroup
    Left = 13
    Top = 8
    Width = 172
    Height = 153
    Caption = 'Flip Image(s)'
    ItemIndex = 4
    Items.Strings = (
      'Flip To Left'
      'Flip To Right'
      'Mirror Horizontal'
      'Mirror Vertical '
      'Rotate ange')
    TabOrder = 2
  end
  object SpinEdit1: TSpinEdit
    Left = 8
    Top = 192
    Width = 140
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 3
    Value = 0
  end
end
