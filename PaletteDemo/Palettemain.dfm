object Form9: TForm9
  Left = 0
  Top = 0
  Caption = 'Form9'
  ClientHeight = 383
  ClientWidth = 565
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 100
    Top = 0
    Height = 320
    ExplicitLeft = 422
    ExplicitTop = -3
    ExplicitHeight = 340
  end
  object PhPalette1: TPhPalette
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 94
    Height = 314
    Align = alLeft
    Color = clWhite
    MaxValue = 4096.000000000000000000
    TicksVisible = True
    PaletteType = phpalSpectum
  end
  object PhImage1: TPhImage
    AlignWithMargins = True
    Left = 106
    Top = 3
    Width = 319
    Height = 246
    AutoMosaic = True
    ThumbWidht = 128
    ThumbHeight = 128
    SlideShowInterval = 500
    ParentColor = False
  end
  object PhPalette2: TPhPalette
    Left = 0
    Top = 320
    Width = 565
    Height = 63
    Align = alBottom
    Color = clGray
    MaxValue = 255.000000000000000000
    TicksVisible = True
    PaletteType = phpalGlow
  end
  object PhPalette3: TPhPalette
    Left = 264
    Top = 192
    Width = 284
    Height = 81
    Color = clGray
    MaxValue = 255.000000000000000000
    TicksVisible = True
    PaletteType = phpalBluered
  end
end
