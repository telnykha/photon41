object resizeForm: TresizeForm
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Dialog'
  ClientHeight = 182
  ClientWidth = 209
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 193
    Height = 137
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 34
    Height = 13
    Caption = 'Resize '
  end
  object Label2: TLabel
    Left = 16
    Top = 64
    Width = 54
    Height = 13
    Caption = 'New width:'
  end
  object Label3: TLabel
    Left = 16
    Top = 91
    Width = 58
    Height = 13
    Caption = 'New height:'
  end
  object OKBtn: TButton
    Left = 24
    Top = 151
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 105
    Top = 151
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object ComboBox1: TComboBox
    Left = 56
    Top = 21
    Width = 137
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 2
    Text = 'Percentages'
    Items.Strings = (
      'Percentages'
      'Pixels')
  end
  object Edit1: TEdit
    Left = 76
    Top = 61
    Width = 113
    Height = 21
    TabOrder = 3
    Text = '100'
  end
  object Edit2: TEdit
    Left = 76
    Top = 88
    Width = 113
    Height = 21
    TabOrder = 4
    Text = '100'
  end
  object CheckBox1: TCheckBox
    Left = 16
    Top = 120
    Width = 129
    Height = 17
    Caption = 'Keep aspect ratio'
    Checked = True
    State = cbChecked
    TabOrder = 5
  end
end
