object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = #1050#1077#1088#1072#1084#1080#1082#1072' '
  ClientHeight = 592
  ClientWidth = 818
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 573
    Width = 818
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Text = #1056#1045#1046#1048#1052': '#1082#1072#1083#1080#1073#1088#1086#1074#1082#1072
        Width = 150
      end
      item
        Alignment = taCenter
        Text = #1050#1072#1076#1088' 999999 '#1080#1079' 1000000'
        Width = 150
      end
      item
        Text = #1048#1089#1090#1086#1095#1085#1080#1082' '#1076#1072#1085#1085#1099#1093': '
        Width = 200
      end
      item
        Text = #1048#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077':'
        Width = 50
      end>
    ExplicitWidth = 835
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 555
    Height = 573
    Align = alClient
    TabOrder = 1
    ExplicitWidth = 572
    object Panel3: TPanel
      Left = 1
      Top = 514
      Width = 553
      Height = 58
      Align = alBottom
      TabOrder = 0
      ExplicitWidth = 570
      object SpeedButton4: TSpeedButton
        Left = 241
        Top = 1
        Width = 84
        Height = 56
        Action = viewNextAction
        Align = alLeft
        Flat = True
        Glyph.Data = {
          B6020000424DB602000000000000760000002800000030000000180000000100
          0400000000004002000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFCCFFFCCFFFFFFFFFFFFFFFFFFF77FFF77FFFFFFFFFFFFFFFCCCFFC
          CCFFFFFFFFFFFFFFFFFF777FF777FFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFF
          FFFF7777F7777FFFFFFFFFFFFFCCCCCCCCCCFFFFFFFFFFFFFFFF7777777777FF
          FFFFFFFFFFCCCCCCCCCCCFFFFFFFFFFFFFFF77777777777FFFFFFFFFFFCCCCCC
          CCCCFFFFFFFFFFFFFFFF7777777777FFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFF
          FFFF7777F7777FFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFFFFFFFF777FF777FFFF
          FFFFFFFFFFCCFFFCCFFFFFFFFFFFFFFFFFFF77FFF77FFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
        Layout = blGlyphTop
        NumGlyphs = 2
        ExplicitLeft = 205
        ExplicitTop = 6
        ExplicitHeight = 77
      end
      object SpeedButton1: TSpeedButton
        Left = 325
        Top = 1
        Width = 84
        Height = 56
        Action = viewLastAction
        Align = alLeft
        Flat = True
        Glyph.Data = {
          B6020000424DB602000000000000760000002800000030000000180000000100
          0400000000004002000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCCFF
          FCCCFFFFFFFFFFFFFFFF77FFF777FFFFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFF
          FFFF777FF777FFFFFFFFFFFFFFFFCCCCFCCCFFFFFFFFFFFFFFFF7777F777FFFF
          FFFFFFFFFFFFCCCCCCCCFFFFFFFFFFFFFFFF77777777FFFFFFFFFFFFFFFFCCCC
          CCCCFFFFFFFFFFFFFFFF77777777FFFFFFFFFFFFFFFFCCCCFCCCFFFFFFFFFFFF
          FFFF7777F777FFFFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFFFFFF777FF777FFFF
          FFFFFFFFFFFFCCFFFCCCFFFFFFFFFFFFFFFF77FFF777FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
        Layout = blGlyphTop
        NumGlyphs = 2
        ExplicitLeft = 165
        ExplicitTop = 24
        ExplicitHeight = 412
      end
      object SpeedButton3: TSpeedButton
        Left = 77
        Top = 1
        Width = 84
        Height = 56
        Action = viewPrevAction
        Align = alLeft
        Flat = True
        Glyph.Data = {
          B6020000424DB602000000000000760000002800000030000000180000000100
          0400000000004002000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFCCFFFCCFFFFFFFFFFFFFFFFFFF77FFF77FFFFFFFFFFFFFFCCCF
          FCCCFFFFFFFFFFFFFFFFFF777FF777FFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFF
          FFFFF7777F7777FFFFFFFFFFFFCCCCCCCCCCFFFFFFFFFFFFFFFF7777777777FF
          FFFFFFFFFCCCCCCCCCCCFFFFFFFFFFFFFFF77777777777FFFFFFFFFFFFCCCCCC
          CCCCFFFFFFFFFFFFFFFF7777777777FFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFF
          FFFFF7777F7777FFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFFFFFFFF777FF777FF
          FFFFFFFFFFFFFCCFFFCCFFFFFFFFFFFFFFFFFFF77FFF77FFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
        Layout = blGlyphTop
        NumGlyphs = 2
        ExplicitLeft = 1
        ExplicitTop = -6
        ExplicitHeight = 524
      end
      object SpeedButton2: TSpeedButton
        Left = 1
        Top = 1
        Width = 76
        Height = 56
        Action = viewFirstAction
        Align = alLeft
        Flat = True
        Glyph.Data = {
          B6020000424DB602000000000000760000002800000030000000180000000100
          0400000000004002000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCCCF
          FFCCFFFFFFFFFFFFFFFF777FFF77FFFFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFF
          FFFF777FF777FFFFFFFFFFFFFFFFCCCFCCCCFFFFFFFFFFFFFFFF777F7777FFFF
          FFFFFFFFFFFFCCCCCCCCFFFFFFFFFFFFFFFF77777777FFFFFFFFFFFFFFFFCCCC
          CCCCFFFFFFFFFFFFFFFF77777777FFFFFFFFFFFFFFFFCCCFCCCCFFFFFFFFFFFF
          FFFF777F7777FFFFFFFFFFFFFFFFCCCFFCCCFFFFFFFFFFFFFFFF777FF777FFFF
          FFFFFFFFFFFFCCCFFFCCFFFFFFFFFFFFFFFF777FFF77FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
        Layout = blGlyphTop
        NumGlyphs = 2
        ExplicitLeft = -1
        ExplicitTop = 6
      end
      object SpeedButton9: TSpeedButton
        Left = 161
        Top = 1
        Width = 80
        Height = 56
        Action = viewPlayAction
        Align = alLeft
        AllowAllUp = True
        GroupIndex = 1
        Flat = True
        Glyph.Data = {
          F6040000424DF604000000000000760000002800000060000000180000000100
          0400000000008004000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFCFFFF
          FFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFFFFFFFFFFFFFFCFFFFFFFFFFFFFFFFFFF
          FFFCCCCFCCCCFFFFFFFFFFFFFFFCCFFFFFFFFFFFFFFFFFFFFFFFF77FFFFFFFFF
          FFFFFFFFFFFFCCFFFFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCCFF
          FFFFFFFFFFFFFFFFFFFFF777FFFFFFFFFFFFFFFFFFFFCCCFFFFFFFFFFFFFFFFF
          FFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCFFFFFFFFFFFFFFFFFFFFFF7777FFFFFFF
          FFFFFFFFFFFFCCCCFFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCC
          FFFFFFFFFFFFFFFFFFFFF77777FFFFFFFFFFFFFFFFFFCCCCCFFFFFFFFFFFFFFF
          FFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCCCFFFFFFFFFFFFFFFFFFFF777777FFFFF
          FFFFFFFFFFFFCCCCCCFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCC
          CFFFFFFFFFFFFFFFFFFFF777777FFFFFFFFFFFFFFFFFCCCCCCFFFFFFFFFFFFFF
          FFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCCFFFFFFFFFFFFFFFFFFFFF77777FFFFFF
          FFFFFFFFFFFFCCCCCFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCCCF
          FFFFFFFFFFFFFFFFFFFFF7777FFFFFFFFFFFFFFFFFFFCCCCFFFFFFFFFFFFFFFF
          FFFCCCCFCCCCFFFFFFFFFFFFFFFCCCFFFFFFFFFFFFFFFFFFFFFFF777FFFFFFFF
          FFFFFFFFFFFFCCCFFFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFCCFFF
          FFFFFFFFFFFFFFFFFFFFF77FFFFFFFFFFFFFFFFFFFFFCCFFFFFFFFFFFFFFFFFF
          FFFCCCCFCCCCFFFFFFFFFFFFFFFCFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFFFFF
          FFFFFFFFFFFFCFFFFFFFFFFFFFFFFFFFFFFCCCCFCCCCFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
        Layout = blGlyphTop
        NumGlyphs = 4
        ExplicitLeft = 169
        ExplicitHeight = 77
      end
      object SpeedButton5: TSpeedButton
        Left = 409
        Top = 1
        Width = 84
        Height = 56
        Action = modeExperimentAction
        Align = alLeft
        AllowAllUp = True
        GroupIndex = 2
        Flat = True
        Glyph.Data = {
          F6040000424DF604000000000000760000002800000060000000180000000100
          0400000000008004000000000000000000001000000000000000000000000000
          8000008000000080800080000000800080008080000080808000C0C0C0000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF1111
          11FFFFFFFFFFFFFFFFFFF777777FFFFFFFFFFFFFFFFFF111111FFFFFFFFFFFFF
          FFFFFF999999FFFFFFFFFFFFFF1111111111FFFFFFFFFFFFFFF7777777777FFF
          FFFFFFFFFFF1111111111FFFFFFFFFFFFFFF9999999999FFFFFFFFFFF1111111
          11111FFFFFFFFFFFFF777777777777FFFFFFFFFFFF111111111111FFFFFFFFFF
          FFF999999999999FFFFFFFFF11111111111111FFFFFFFFFFF77777777777777F
          FFFFFFFFF11111111111111FFFFFFFFFFF99999999999999FFFFFFF111111111
          1111111FFFFFFFFF7777777777777777FFFFFFFF1111111111111111FFFFFFFF
          F9999999999999999FFFFFF1111111111111111FFFFFFFFF7777777777777777
          FFFFFFFF1111111111111111FFFFFFFFF9999999999999999FFFFF1111111111
          11111111FFFFFFF777777777777777777FFFFFF111111111111111111FFFFFFF
          999999999999999999FFFF111111111111111111FFFFFFF77777777777777777
          7FFFFFF111111111111111111FFFFFFF999999999999999999FFFF1111111111
          11111111FFFFFFF777777777777777777FFFFFF111111111111111111FFFFFFF
          999999999999999999FFFF111111111111111111FFFFFFF77777777777777777
          7FFFFFF111111111111111111FFFFFFF999999999999999999FFFF1111111111
          11111111FFFFFFF777777777777777777FFFFFF111111111111111111FFFFFFF
          999999999999999999FFFFF1111111111111111FFFFFFFFF7777777777777777
          FFFFFFFF1111111111111111FFFFFFFFF9999999999999999FFFFFF111111111
          1111111FFFFFFFFF7777777777777777FFFFFFFF1111111111111111FFFFFFFF
          F9999999999999999FFFFFFF11111111111111FFFFFFFFFFF77777777777777F
          FFFFFFFFF11111111111111FFFFFFFFFFF99999999999999FFFFFFFFF1111111
          11111FFFFFFFFFFFFF777777777777FFFFFFFFFFFF111111111111FFFFFFFFFF
          FFF999999999999FFFFFFFFFFF1111111111FFFFFFFFFFFFFFF7777777777FFF
          FFFFFFFFFFF1111111111FFFFFFFFFFFFFFF9999999999FFFFFFFFFFFFFF1111
          11FFFFFFFFFFFFFFFFFFF777777FFFFFFFFFFFFFFFFFF111111FFFFFFFFFFFFF
          FFFFFF999999FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
        Layout = blGlyphTop
        NumGlyphs = 4
        ExplicitLeft = 437
        ExplicitTop = 6
      end
    end
    object PhImage1: TPhImage
      Left = 1
      Top = 59
      Width = 553
      Height = 455
      ThumbWidht = 128
      ThumbHeight = 128
      SlideShowInterval = 500
      Align = alClient
      ParentColor = False
      OnMouseMove = PhImage1MouseMove
      AfterOpen = PhImage1AfterOpen
      OnFrameData = PhImage1FrameData
      ExplicitTop = 118
      ExplicitWidth = 570
      ExplicitHeight = 396
    end
    object Panel5: TPanel
      Left = 1
      Top = 1
      Width = 553
      Height = 58
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
      ExplicitWidth = 570
      object SpeedButton10: TSpeedButton
        Left = 3
        Top = 0
        Width = 56
        Height = 56
        Action = fileOpenVideoAction
        Caption = #1060#1072#1081#1083
      end
      object SpeedButton11: TSpeedButton
        Left = 59
        Top = 0
        Width = 56
        Height = 56
        Action = fileConnectToCameraAction
        Caption = #1050#1072#1084#1077#1088#1072
      end
      object SpeedButton12: TSpeedButton
        Left = 121
        Top = 0
        Width = 80
        Height = 56
        Action = modeHandAction
        GroupIndex = 1
      end
      object SpeedButton13: TSpeedButton
        Left = 201
        Top = 0
        Width = 88
        Height = 56
        Action = modeAutoAnalysisAction
        GroupIndex = 1
      end
    end
  end
  object Panel1: TPanel
    Left = 555
    Top = 0
    Width = 256
    Height = 573
    Align = alRight
    TabOrder = 2
    ExplicitLeft = 572
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 254
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
    object Chart1: TChart
      Left = 1
      Top = 112
      Width = 254
      Height = 129
      BackWall.Brush.Gradient.Direction = gdBottomTop
      BackWall.Brush.Gradient.EndColor = clWhite
      BackWall.Brush.Gradient.StartColor = 15395562
      BackWall.Brush.Gradient.Visible = True
      BackWall.Transparent = False
      Foot.Font.Color = clBlue
      Foot.Font.Name = 'Verdana'
      Gradient.Direction = gdBottomTop
      Gradient.EndColor = clWhite
      Gradient.MidColor = 15395562
      Gradient.StartColor = 15395562
      Gradient.Visible = True
      LeftWall.Color = 14745599
      Legend.Font.Name = 'Verdana'
      Legend.Shadow.Transparency = 0
      Legend.Visible = False
      RightWall.Color = 14745599
      Title.Font.Name = 'Verdana'
      Title.Text.Strings = (
        'TChart')
      Title.Visible = False
      BottomAxis.Axis.Color = 4210752
      BottomAxis.Grid.Color = 11119017
      BottomAxis.LabelsFormat.Font.Name = 'Verdana'
      BottomAxis.TicksInner.Color = 11119017
      BottomAxis.Title.Caption = #1074#1088#1077#1084#1103' '#1085#1072#1073#1083#1102#1076#1077#1085#1080#1103
      BottomAxis.Title.Font.Name = 'Verdana'
      DepthAxis.Axis.Color = 4210752
      DepthAxis.Grid.Color = 11119017
      DepthAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthAxis.TicksInner.Color = 11119017
      DepthAxis.Title.Font.Name = 'Verdana'
      DepthTopAxis.Axis.Color = 4210752
      DepthTopAxis.Grid.Color = 11119017
      DepthTopAxis.LabelsFormat.Font.Name = 'Verdana'
      DepthTopAxis.TicksInner.Color = 11119017
      DepthTopAxis.Title.Font.Name = 'Verdana'
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Axis.Color = 4210752
      LeftAxis.Grid.Color = 11119017
      LeftAxis.LabelsFormat.Font.Name = 'Verdana'
      LeftAxis.Maximum = 15.000000000000000000
      LeftAxis.Minimum = 5.000000000000000000
      LeftAxis.TicksInner.Color = 11119017
      LeftAxis.Title.Caption = #1044#1080#1072#1084#1077#1090#1088' ('#1084#1084')'
      LeftAxis.Title.Font.Name = 'Verdana'
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      RightAxis.Axis.Color = 4210752
      RightAxis.Grid.Color = 11119017
      RightAxis.LabelsFormat.Font.Name = 'Verdana'
      RightAxis.Maximum = 15.000000000000000000
      RightAxis.TicksInner.Color = 11119017
      RightAxis.Title.Font.Name = 'Verdana'
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      TopAxis.Axis.Color = 4210752
      TopAxis.Grid.Color = 11119017
      TopAxis.LabelsFormat.Font.Name = 'Verdana'
      TopAxis.TicksInner.Color = 11119017
      TopAxis.Title.Font.Name = 'Verdana'
      TopAxis.Visible = False
      View3D = False
      Zoom.Allow = False
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      DefaultCanvas = 'TGDIPlusCanvas'
      PrintMargins = (
        15
        17
        15
        17)
      ColorPaletteIndex = 13
      object Series1: TFastLineSeries
        Selected.Hover.Visible = True
        Marks.Callout.Length = 20
        SeriesColor = clRed
        LinePen.Color = clRed
        LinePen.Width = 2
        LinePen.EndStyle = esRound
        TreatNulls = tnDontPaint
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 241
      Width = 254
      Height = 331
      Align = alClient
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1072#1083#1075#1086#1088#1080#1090#1084#1072
      TabOrder = 2
      ExplicitLeft = -4
      ExplicitTop = 236
      object Label12: TLabel
        Left = 4
        Top = 39
        Width = 77
        Height = 13
        Caption = #1044#1083#1080#1085#1072' ('#1087#1080#1082#1089') ='
      end
      object Label13: TLabel
        Left = 89
        Top = 39
        Width = 40
        Height = 13
        Caption = '0000.00'
      end
      object Label14: TLabel
        Left = 206
        Top = 39
        Width = 16
        Height = 13
        Caption = 'mm'
      end
      object Label15: TLabel
        Left = 5
        Top = 20
        Width = 131
        Height = 13
        Caption = #1042' '#1086#1076#1085#1086#1084' '#1084#1084' ..... '#1087#1080#1089#1082#1077#1083#1077#1081' '
      end
      object Label16: TLabel
        Left = 5
        Top = 104
        Width = 76
        Height = 13
        Caption = #1056#1072#1079#1084#1077#1088' '#1073#1091#1092#1077#1088#1072
      end
      object Label17: TLabel
        Left = 160
        Top = 104
        Width = 40
        Height = 13
        Caption = #1082#1072#1076#1088#1086#1074' '
      end
      object Label18: TLabel
        Left = 5
        Top = 208
        Width = 38
        Height = 13
        Caption = #1040#1088#1093#1080#1074': '
      end
      object Bevel1: TBevel
        Left = 5
        Top = 158
        Width = 221
        Height = 9
        Shape = bsTopLine
      end
      object Label19: TLabel
        Left = 5
        Top = 235
        Width = 106
        Height = 13
        Caption = #1057#1082#1074#1072#1078#1085#1086#1089#1090#1100' '#1079#1072#1087#1080#1089#1080': '
      end
      object Label20: TLabel
        Left = 192
        Top = 235
        Width = 13
        Height = 13
        Caption = 'ms'
      end
      object Label23: TLabel
        Left = 5
        Top = 291
        Width = 32
        Height = 13
        Caption = #1055#1086#1088#1090': '
      end
      object SpeedButton6: TSpeedButton
        Left = 4
        Top = 164
        Width = 32
        Height = 32
      end
      object SpeedButton7: TSpeedButton
        Left = 36
        Top = 164
        Width = 32
        Height = 32
      end
      object SpeedButton8: TSpeedButton
        Left = 68
        Top = 164
        Width = 32
        Height = 32
      end
      object Edit1: TEdit
        Left = 135
        Top = 36
        Width = 56
        Height = 21
        TabOrder = 0
        Text = '10'
        OnEnter = Edit1Enter
        OnExit = Edit1Change
      end
      object CheckBox1: TCheckBox
        Left = 4
        Top = 81
        Width = 180
        Height = 17
        Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1073#1091#1092#1077#1088#1080#1079#1072#1094#1080#1102
        TabOrder = 1
        OnClick = CheckBox1Click
      end
      object SpinEdit1: TSpinEdit
        Left = 90
        Top = 101
        Width = 57
        Height = 22
        MaxValue = 20
        MinValue = 1
        TabOrder = 2
        Value = 10
        OnChange = SpinEdit1Change
      end
      object Button1: TButton
        Left = 192
        Top = 203
        Width = 33
        Height = 25
        Caption = '...'
        TabOrder = 3
        OnClick = Button1Click
      end
      object Edit2: TEdit
        Left = 49
        Top = 205
        Width = 136
        Height = 21
        Enabled = False
        TabOrder = 4
        Text = 'c:\archive\'
        OnChange = Edit2Change
      end
      object SpinEdit2: TSpinEdit
        Left = 115
        Top = 232
        Width = 70
        Height = 22
        MaxValue = 5000
        MinValue = 500
        TabOrder = 5
        Value = 1000
        OnChange = SpinEdit2Change
      end
      object Memo1: TMemo
        Left = 2
        Top = 312
        Width = 250
        Height = 17
        Align = alBottom
        Lines.Strings = (
          'Memo1')
        TabOrder = 6
        Visible = False
      end
      object SpinEdit3: TSpinEdit
        Left = 43
        Top = 287
        Width = 70
        Height = 22
        MaxValue = 10000
        MinValue = 1024
        TabOrder = 7
        Value = 7000
        OnChange = SpinEdit2Change
      end
      object ComboBox1: TComboBox
        Left = 5
        Top = 260
        Width = 220
        Height = 21
        Style = csDropDownList
        TabOrder = 8
      end
      object CheckBox2: TCheckBox
        Left = 4
        Top = 61
        Width = 180
        Height = 17
        Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1072#1087#1088#1086#1082#1089#1080#1084#1072#1094#1080#1102
        TabOrder = 9
        OnClick = CheckBox2Click
      end
      object CheckBox3: TCheckBox
        Left = 5
        Top = 126
        Width = 180
        Height = 17
        Caption = #1048#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100' '#1084#1072#1089#1082#1091
        TabOrder = 10
        OnClick = CheckBox1Click
      end
    end
  end
  object Panel4: TPanel
    Left = 811
    Top = 0
    Width = 7
    Height = 573
    Align = alRight
    TabOrder = 3
    OnClick = Panel4Click
    ExplicitLeft = 828
  end
  object ActionList1: TActionList
    Left = 56
    Top = 88
    object fileExitAction: TAction
      Category = 'File'
      Caption = #1042#1099#1093#1086#1076
      OnExecute = fileExitActionExecute
    end
    object modeExperimentAction: TAction
      Category = 'Mode'
      Caption = #1047#1072#1087#1080#1089#1100
      GroupIndex = 1
      OnExecute = modeExperimentActionExecute
      OnUpdate = modeExperimentActionUpdate
    end
    object modeAutoAnalysisAction: TAction
      Category = 'Mode'
      Caption = #1053#1072#1073#1083#1102#1076#1077#1085#1080#1077
      GroupIndex = 1
      ImageIndex = 3
      OnExecute = modeAutoAnalysisActionExecute
      OnUpdate = modeAutoAnalysisActionUpdate
    end
    object modeHandAction: TAction
      Category = 'Mode'
      Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072
      Checked = True
      GroupIndex = 1
      ImageIndex = 2
      OnExecute = modeHandActionExecute
      OnUpdate = modeHandActionUpdate
    end
    object viewSourceImageAction: TAction
      Category = 'view'
      Caption = #1048#1089#1093#1086#1076#1085#1086#1077' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077
      Checked = True
      GroupIndex = 2
      Visible = False
      OnExecute = viewSourceImageActionExecute
    end
    object viewAnalysisAreaAction: TAction
      Category = 'view'
      Caption = #1054#1073#1083#1072#1089#1090#1100' '#1072#1085#1072#1083#1080#1079#1072' '#1076#1072#1085#1085#1099#1093' '
      Visible = False
      OnExecute = viewAnalysisAreaActionExecute
      OnUpdate = viewAnalysisAreaActionUpdate
    end
    object viewObjectContourAction: TAction
      Category = 'view'
      Caption = #1050#1086#1085#1090#1091#1088' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
      Checked = True
      ImageIndex = 4
      OnExecute = viewObjectContourActionExecute
      OnUpdate = viewObjectContourActionUpdate
    end
    object viewCenterAction: TAction
      Category = 'view'
      Caption = #1062#1077#1085#1090#1088' '#1084#1072#1089#1089' '#1079#1072#1075#1086#1090#1086#1074#1082#1080
      Checked = True
      OnExecute = viewCenterActionExecute
      OnUpdate = viewCenterActionUpdate
    end
    object viewAxisAction: TAction
      Category = 'view'
      Caption = #1053#1072#1081#1076#1077#1085#1085#1099#1077' '#1087#1086#1083#1091#1086#1089#1080'  '#1101#1083#1083#1080#1087#1089#1072
      Checked = True
      OnExecute = viewAxisActionExecute
      OnUpdate = viewAxisActionUpdate
    end
    object viewEllipseAction: TAction
      Category = 'view'
      Caption = #1040#1087#1087#1088#1086#1082#1089#1080#1084#1080#1088#1091#1102#1097#1080#1081' '#1101#1083#1083#1080#1087#1089
      Checked = True
      ImageIndex = 5
      OnExecute = viewEllipseActionExecute
      OnUpdate = viewEllipseActionUpdate
    end
    object fileOpenImagesAction: TAction
      Category = 'File'
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1080#1079#1086#1073#1088#1072#1078#1077#1085#1080#1103'...'
      OnExecute = fileOpenImagesActionExecute
    end
    object fileOpenVideoAction: TAction
      Category = 'File'
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1074#1080#1076#1077#1086#1092#1072#1081#1083'... '
      ImageIndex = 0
      OnExecute = fileOpenVideoActionExecute
    end
    object fileConnectToCameraAction: TAction
      Category = 'File'
      Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103' '#1082' '#1082#1072#1084#1077#1088#1077'... '
      ImageIndex = 1
      OnExecute = fileConnectToCameraActionExecute
    end
    object fileCloseAction: TAction
      Category = 'File'
      Caption = #1047#1072#1082#1088#1099#1090#1100' '#1080#1089#1090#1086#1095#1085#1080#1082
      OnExecute = fileCloseActionExecute
    end
    object viewFirstAction: TAction
      Category = 'view'
      Caption = #1042' '#1085#1072#1095#1072#1083#1086
      OnExecute = viewFirstActionExecute
      OnUpdate = viewFirstActionUpdate
    end
    object viewPrevAction: TAction
      Category = 'view'
      Caption = #1055#1088#1077#1076#1091#1076#1091#1097'.'
      OnExecute = viewPrevActionExecute
      OnUpdate = viewPrevActionUpdate
    end
    object viewNextAction: TAction
      Category = 'view'
      Caption = #1057#1083#1077#1076#1091#1102#1097'.'
      OnExecute = viewNextActionExecute
      OnUpdate = viewNextActionUpdate
    end
    object viewLastAction: TAction
      Category = 'view'
      Caption = #1042' '#1082#1086#1085#1077#1094
      OnExecute = viewLastActionExecute
      OnUpdate = viewLastActionUpdate
    end
    object viewPlayAction: TAction
      Category = 'view'
      Caption = #1042#1086#1089#1087#1088#1086#1080#1079#1074#1077#1089#1090#1080
      OnExecute = viewPlayActionExecute
      OnUpdate = viewPlayActionUpdate
    end
    object viewBinaryAction: TAction
      Category = 'view'
      Caption = #1048#1079#1086#1073#1088#1072#1078#1077#1085#1080#1077' '#1087#1088#1077#1087#1072#1088#1072#1090#1072
      GroupIndex = 2
      Visible = False
      OnExecute = viewBinaryActionExecute
      OnUpdate = viewBinaryActionUpdate
    end
    object fileClientAction: TAction
      Category = 'File'
      Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100' '#1082#1083#1080#1077#1085#1090
      OnExecute = fileClientActionExecute
    end
    object helpAboutAction: TAction
      Category = 'Help'
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'... '
      OnExecute = helpAboutActionExecute
    end
    object viewVideoControlAction: TAction
      Category = 'view'
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1074#1080#1076#1077#1086'...'
      OnExecute = viewVideoControlActionExecute
      OnUpdate = viewVideoControlActionUpdate
    end
    object viewRawContourAction: TAction
      Category = 'view'
      Caption = #1050#1086#1085#1090#1088#1091#1088' '#1087#1088#1077#1087#1072#1088#1072#1090#1072
      Checked = True
      ImageIndex = 6
      OnExecute = viewRawContourActionExecute
      OnUpdate = viewRawContourActionUpdate
    end
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 88
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083#1099
      object N15: TMenuItem
        Action = fileOpenImagesAction
      end
      object N16: TMenuItem
        Action = fileOpenVideoAction
      end
      object N17: TMenuItem
        Action = fileConnectToCameraAction
      end
      object N5: TMenuItem
        Caption = '-'
      end
      object N19: TMenuItem
        Action = fileCloseAction
      end
      object N18: TMenuItem
        Caption = '-'
      end
      object N21: TMenuItem
        Action = fileClientAction
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object N2: TMenuItem
        Action = fileExitAction
      end
    end
    object N8: TMenuItem
      Caption = #1055#1088#1086#1089#1084#1086#1090#1088
      object N9: TMenuItem
        Action = viewSourceImageAction
      end
      object N20: TMenuItem
        Action = viewBinaryAction
      end
      object N10: TMenuItem
        Action = viewAnalysisAreaAction
      end
      object N11: TMenuItem
        Action = viewObjectContourAction
      end
      object N12: TMenuItem
        Action = viewCenterAction
      end
      object N13: TMenuItem
        Action = viewAxisAction
      end
      object N14: TMenuItem
        Action = viewEllipseAction
      end
      object N25: TMenuItem
        Action = viewRawContourAction
      end
      object N24: TMenuItem
        Caption = '-'
      end
      object viewVideoControlAction1: TMenuItem
        Action = viewVideoControlAction
      end
    end
    object N4: TMenuItem
      Caption = #1056#1077#1078#1080#1084
      object N7: TMenuItem
        Action = modeHandAction
      end
      object N6: TMenuItem
        Action = modeAutoAnalysisAction
      end
    end
    object N22: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      object N23: TMenuItem
        Action = helpAboutAction
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofFileMustExist, ofEnableSizing]
    Left = 88
    Top = 88
  end
  object PhRulerTool1: TPhRulerTool
    PhImage = PhImage1
    Left = 16
    Top = 152
  end
  object PhPaneTool1: TPhPaneTool
    PhImage = PhImage1
    Left = 56
    Top = 152
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 96
    Top = 152
  end
  object IdTCPServer1: TIdTCPServer
    Bindings = <
      item
        IP = '0.0.0.0'
        Port = 12340
      end>
    DefaultPort = 0
    OnConnect = IdTCPServer1Connect
    OnDisconnect = IdTCPServer1Disconnect
    OnExecute = IdTCPServer1Execute
    Left = 144
    Top = 88
  end
  object ImageList1: TImageList
    Left = 152
    Top = 160
    Bitmap = {
      494C0101080018002C0010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080000000
      0000000000000000000080808000000000000000000000000000808080000000
      0000000000000000000080808000000000000000000000000000808080000000
      0000000000000000000080808000000000000000000000000000808080000000
      0000000000000000000080808000000000000000000000000000808080000000
      0000000000000000000080808000000000000000000000000000808080000000
      0000000000000000000080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080000000
      0000808080000000000080808000000000008080800000000000808080000000
      0000808080000000000080808000000000000000000000000000808080000000
      0000808080000000000080808000000000008080800000000000808080000000
      0000808080000000000080808000000000000000000000000000808080000000
      0000808080000000000080808000000000008080800000000000808080000000
      0000808080000000000080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800080808000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800080808000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800080808000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800080808000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF000000000000FFFF0000FFFF0000FFFF000000
      0000FF000000FF000000FF000000000000000000000080808000000000000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000FF000000000080808000000000000000
      FF000000FF0000000000000000000000000000000000FF000000000000000000
      000000000000000000000000FF000000FF000000000080808000000000000000
      FF00000000000000000000000000000000000000000000000000FF0000000000
      0000000000000000000000000000000000000000000080808000000000000000
      00000000FF000000FF000000FF000000000000FFFF0000FFFF0000FFFF000000
      0000FF000000FF000000FF000000000000000000000000000000000000000000
      0000000000000000FF0000000000000000000000000000000000000000000000
      0000000000000000FF0000000000000000000000000000000000000000000000
      0000000000000000FF00000000000000000000000000FF000000000000000000
      0000000000000000FF0000000000000000000000000000000000000000000000
      00000000FF00000000000000FF000000FF0000000000FF00000000000000FF00
      0000000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF000000000000FFFF0000FFFF0000FFFF000000
      0000FF000000FF000000FF000000000000008080800080808000000000008080
      800080808000808080000000FF0080808000FF000000FF000000FF0000008080
      80000000FF008080800080808000808080008080800080808000000000008080
      800080808000808080000000FF008080800080808000FF000000808080008080
      80000000FF008080800080808000808080008080800080808000000000008080
      80000000FF00808080000000FF00808080000000FF008080800080808000FF00
      0000808080008080800080808000808080008080800080808000000000008080
      80000000FF000000FF000000FF008080800000FFFF0000FFFF0000FFFF008080
      8000FF000000FF000000FF000000808080000000000000000000000000000000
      000000000000000000000000FF00FF000000000000000000000000000000FF00
      00000000FF000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF000000000000000000FF000000000000000000
      00000000FF000000000000000000000000000000000000000000000000000000
      0000000000000000FF0000000000000000000000FF0000000000000000000000
      0000FF0000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000000000000000
      0000FF000000FF000000FF000000000000000000000080808000000000000000
      00000000000000000000FF0000000000FF000000000000000000000000000000
      FF00FF0000000000000000000000000000000000000080808000000000000000
      00000000000000000000000000000000FF0000000000FF000000000000000000
      FF0000000000000000000000000000000000000000008080800000000000FF00
      0000000000000000000000000000FF000000000000000000FF00000000000000
      00000000FF000000000000000000000000000000000080808000000000000000
      00000000FF000000FF000000FF00000000000000000000000000000000000000
      0000FF000000FF000000FF000000000000000000000000000000000000000000
      00000000000000000000FF000000000000000000FF000000FF000000FF000000
      0000FF0000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000FF000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF00000000000000FF00000000000000000000000000FF00000000000000
      FF00FF0000000000FF0000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000000000000000
      0000FF000000FF000000FF000000000000008080800080808000000000008080
      80008080800080808000FF000000808080008080800080808000808080008080
      8000FF0000008080800080808000808080008080800080808000000000008080
      80008080800080808000808080008080800080808000FF000000808080008080
      8000808080008080800080808000808080008080800080808000000000008080
      8000FF00000080808000FF0000008080800080808000808080000000FF008080
      800080808000FF0000000000FF00808080008080800080808000000000008080
      8000000000000000000000000000808080008080800080808000808080008080
      8000FF000000FF000000FF000000808080000000000000000000000000000000
      0000000000000000000000000000FF000000000000000000000000000000FF00
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FF00000000000000000000000000000000000000000000000000
      000000000000FF00000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF000000FF000000FF000000000000000000000080808000000000000000
      000000000000000000000000000000000000FF000000FF000000FF0000000000
      0000000000000000000000000000000000000000000080808000000000000000
      00000000000000000000000000000000000000000000FF000000000000000000
      0000000000000000000000000000FF0000000000000080808000000000000000
      000000000000FF00000000000000000000000000000000000000000000000000
      00000000000000000000FF000000000000000000000080808000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008080800080808000000000008080
      8000808080008080800080808000808080008080800080808000808080008080
      8000808080008080800080808000808080008080800080808000000000008080
      8000808080008080800080808000808080008080800080808000808080008080
      8000808080008080800080808000808080008080800080808000000000008080
      8000808080008080800080808000808080008080800080808000808080008080
      8000808080008080800080808000808080008080800080808000000000008080
      8000808080008080800080808000808080008080800080808000808080008080
      8000808080008080800080808000808080000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000080808000808080008080800080808000808080008080
      80008080800000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0
      C00000FFFF000000000000000000000000000000000080808000808080008080
      8000808080008080800000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF00000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF0000000000000000000000000000000000000000000000000000000000FFFF
      FF000000000000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0C00000FF
      FF00C0C0C00000FFFF00000000000000000000000000808080000000FF008080
      800000FF00008080800080808000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000000FFFF00FFFFFF0000FFFF00FFFF
      FF0000FFFF000000000000000000FFFF000000000000000000000000FF000000
      FF000000FF0000000000808080000000000080808000000000000000FF000000
      FF000000FF0000000000000000000000000000000000000000000000000000FF
      FF00FFFFFF000000000000FFFF00C0C0C00000FFFF00C0C0C00000FFFF00C0C0
      C00000FFFF00C0C0C00000FFFF00000000000000000080808000808080008080
      800080808000808080008080800080808000C0C0C000C0C0C000000000000000
      00000000000000000000C0C0C0000000000000000000FFFFFF0000000000FFFF
      0000FFFF0000FFFF0000FFFF0000000000000000000000000000FFFFFF0000FF
      FF00FFFFFF0000FFFF0000000000FFFF0000000000000000FF000000FF000000
      FF00000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000000000000000000000000000000000000000FFFF
      FF0000FFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000080808000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C00080808000C0C0C000C0C0C000000000000000
      00000000000080808000808080000000000000000000FFFFFF00FFFFFF000000
      000000000000FFFFFF0000000000FFFFFF0000FFFF00FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000000000FFFF0000000000000000FF000000FF000000
      0000000000000000000080808000000000008080800000000000000000000000
      00000000FF000000FF00000000000000000000000000000000000000000000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FF
      FF00000000000000000000000000000000000000000080808000000000000000
      00000000000000000000C0C0C00080808000C0C0C000C0C0C000000000008080
      80000000000080808000C0C0C0000000000000000000FFFFFF00FFFF00000000
      000000FFFF000000000000000000000000000000000000000000FFFFFF0000FF
      FF00FFFFFF0000FFFF0000000000FFFF00000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF00000000000000000000FFFF0000000000FFFF
      FF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFF
      FF00000000000000000000000000000000000000000080808000C0C0C000C0C0
      C000C0C0C000C0C0C000C0C0C00080808000C0C0C000C0C0C00000000000C0C0
      C00000000000C0C0C000C0C0C0000000000000000000FFFFFF00FFFFFF00FFFF
      FF0000000000FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000000000FFFF00000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF000000000000000000FFFFFF000000000000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000080808000808080008080
      800080808000808080008080800080808000C0C0C000C0C0C000000000000000
      000000000000C0C0C000C0C0C0000000000000000000FFFFFF00FFFF0000FFFF
      0000FFFF00000000000000000000000000000000000000000000000000000000
      0000FFFFFF0000FFFF0000000000FFFF00000000FF000000FF00000000000000
      0000000000000000000080808000000000008080800000000000000000000000
      0000000000000000000000000000000000000000000000FFFF00FFFFFF000000
      000000FFFF00FFFFFF0000FFFF00FFFFFF000000000000FFFF00000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C000C0C0
      C000000000000000000000000000C0C0C000C0C0C000C0C0C000000000000000
      00000000000000000000C0C0C0000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF000000000000FFFF00000000000000000000FFFF00FFFF
      FF0000FFFF000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000008000000000000000800000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF0000FFFF008080
      80000000000000000000000000000000000080808000FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C0C0C00000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF00000000000000FFFF0000000000000000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      00000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF000000FF000000FF00000000000000000000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000C0C0C0000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000FFFF00000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000FF000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF00000000000000
      000000000000000000000000000000000000000000000000000000000000C0C0
      C000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      0000FFFFFF0000000000FFFFFF0000000000FFFFFF000000000000FFFF000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF00000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000C0C0C000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080000000
      00008080800000000000808080000000000080808000000000000000000000FF
      FF000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF0000000000808080000000000080808000000000000000FF000000
      FF000000FF000000FF000000FF00000000000000000000000000FFFFFF0000FF
      FF00FFFFFF0000FFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C0C0C0000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000808080000000
      0000808080000000000080808000000000008080800000000000000000000000
      00000000FF000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF0000000000000000000000FF00000000000000000080808000000000000000
      0000000000000000000080808000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF000000FF000000FF000000FF00000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000DDDDDDDDDDDDF111D555D555D555FFFF
      0000000000000000DFFFDFBFDFFFD11187FC87BC8FDF9111DBFBDBBBD4AFD111
      0000000000000000DCE7DDB7DB77D1119CE79EAF8EB791F1DD17DF1FD5A3D1F1
      0000000000000000DEEFDFB7DBFBDFF19F1F9F829BFD9FF1DFFFDFB7DFFFDFFF
      0000000000000000FFFFFFFFFFFFFFFFFFFFFC07803FFFFFE0078003001FF83F
      C00300070004E00FC001003C0000C447C000001800008C63C000000000009C73
      8007000000003FF90007000000003EF9000F000000003C7F001F001800003C7F
      001F803C00073C41001FE3FF001F9C61001F87FF000F8C71003F0FFF8007C441
      81FF8FFF8023E00D81FFDFFF5577F83F00000000000000000000000000000000
      000000000000}
  end
end
