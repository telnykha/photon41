object mainForm: TmainForm
  Left = 0
  Top = 0
  Caption = #1040#1085#1072#1083#1080#1079' '#1086#1087#1090#1080#1095#1077#1089#1082#1086#1081' '#1087#1083#1086#1090#1085#1086#1089#1090#1080' '#1090#1088#1086#1084#1073#1086#1094#1080#1090#1086#1074
  ClientHeight = 422
  ClientWidth = 599
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 324
    Top = 81
    Height = 322
    Align = alRight
    ExplicitLeft = 424
    ExplicitTop = 328
    ExplicitHeight = 100
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 599
    Height = 81
    Align = alTop
    TabOrder = 0
    object Button1: TButton
      Left = 8
      Top = 8
      Width = 75
      Height = 67
      Action = fileOpenAction
      TabOrder = 0
    end
    object Button2: TButton
      Left = 82
      Top = 8
      Width = 75
      Height = 67
      Action = viewMosaicAction
      Images = ImageList1
      TabOrder = 1
    end
    object Button7: TButton
      Left = 156
      Top = 8
      Width = 75
      Height = 67
      Action = fileReportAction
      TabOrder = 2
    end
    object Button8: TButton
      Left = 231
      Top = 8
      Width = 75
      Height = 67
      Action = helpCallAction
      TabOrder = 3
    end
    object GroupBox1: TGroupBox
      Left = 312
      Top = 8
      Width = 281
      Height = 67
      Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099
      TabOrder = 4
      object Label1: TLabel
        Left = 7
        Top = 18
        Width = 74
        Height = 13
        Caption = #1063#1091#1074#1089#1090#1074#1080#1090': (%)'
      end
      object Label2: TLabel
        Left = 95
        Top = 18
        Width = 39
        Height = 13
        Caption = #1052#1080#1085'. dX'
      end
      object Label3: TLabel
        Left = 144
        Top = 18
        Width = 39
        Height = 13
        Caption = #1052#1080#1085'. dY'
      end
      object Label10: TLabel
        Left = 195
        Top = 18
        Width = 62
        Height = 13
        Caption = #1056#1072#1076#1080#1091#1089': (%)'
      end
      object SpinEdit1: TSpinEdit
        Left = 7
        Top = 35
        Width = 74
        Height = 22
        MaxValue = 100
        MinValue = 0
        TabOrder = 0
        Value = 50
        OnChange = SpinEdit1Change
      end
      object SpinEdit2: TSpinEdit
        Left = 95
        Top = 35
        Width = 42
        Height = 22
        MaxValue = 20
        MinValue = 0
        TabOrder = 1
        Value = 2
        OnChange = SpinEdit2Change
      end
      object SpinEdit3: TSpinEdit
        Left = 144
        Top = 35
        Width = 45
        Height = 22
        MaxValue = 20
        MinValue = 0
        TabOrder = 2
        Value = 2
        OnChange = SpinEdit3Change
      end
      object SpinEdit4: TSpinEdit
        Left = 195
        Top = 35
        Width = 74
        Height = 22
        MaxValue = 100
        MinValue = 75
        TabOrder = 3
        Value = 90
        OnChange = SpinEdit1Change
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 81
    Width = 324
    Height = 322
    Align = alClient
    Caption = 'Panel2'
    TabOrder = 1
    object PhImage1: TPhImage
      Left = 1
      Top = 1
      Width = 322
      Height = 248
      ThumbWidht = 320
      ThumbHeight = 240
      SlideShowInterval = 500
      Align = alClient
      ParentColor = False
      PopupMenu = PopupMenu2
      OnMouseMove = PhImage1MouseMove
      AfterOpen = PhImage1AfterOpen
      OnMosaic = PhImage1Mosaic
      OnFrame = PhImage1Frame
    end
    object Panel6: TPanel
      Left = 1
      Top = 249
      Width = 322
      Height = 72
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 1
      object SpeedButton4: TSpeedButton
        Left = 168
        Top = 0
        Width = 84
        Height = 72
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
      end
      object SpeedButton3: TSpeedButton
        Left = 84
        Top = 0
        Width = 84
        Height = 72
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
      end
      object SpeedButton2: TSpeedButton
        Left = 0
        Top = 0
        Width = 84
        Height = 72
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
      end
      object SpeedButton1: TSpeedButton
        Left = 252
        Top = 0
        Width = 84
        Height = 72
        Action = viewFinishAction
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
      end
      object Panel7: TPanel
        Left = 336
        Top = 0
        Width = 185
        Height = 72
        Align = alLeft
        BevelOuter = bvNone
        TabOrder = 0
      end
    end
  end
  object Panel3: TPanel
    Left = 327
    Top = 81
    Width = 272
    Height = 322
    Align = alRight
    TabOrder = 2
    object Splitter2: TSplitter
      Left = 1
      Top = 129
      Width = 270
      Height = 3
      Cursor = crVSplit
      Align = alTop
      ExplicitTop = 177
      ExplicitWidth = 217
    end
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 270
      Height = 128
      Align = alTop
      Caption = 'Panel4'
      TabOrder = 0
      object Chart1: TChart
        Left = 1
        Top = 1
        Width = 268
        Height = 126
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
        BottomAxis.Axis.Color = 4210752
        BottomAxis.Grid.Color = 11119017
        BottomAxis.LabelsFormat.Font.Name = 'Verdana'
        BottomAxis.TicksInner.Color = 11119017
        BottomAxis.Title.Caption = 'qq'
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
        LeftAxis.Axis.Color = 4210752
        LeftAxis.Grid.Color = 11119017
        LeftAxis.LabelsFormat.Font.Name = 'Verdana'
        LeftAxis.TicksInner.Color = 11119017
        LeftAxis.Title.Font.Name = 'Verdana'
        RightAxis.Axis.Color = 4210752
        RightAxis.Grid.Color = 11119017
        RightAxis.LabelsFormat.Font.Name = 'Verdana'
        RightAxis.TicksInner.Color = 11119017
        RightAxis.Title.Font.Name = 'Verdana'
        TopAxis.Axis.Color = 4210752
        TopAxis.Grid.Color = 11119017
        TopAxis.LabelsFormat.Font.Name = 'Verdana'
        TopAxis.TicksInner.Color = 11119017
        TopAxis.Title.Font.Name = 'Verdana'
        View3D = False
        Zoom.Allow = False
        Align = alClient
        BevelOuter = bvNone
        PopupMenu = PopupMenu1
        TabOrder = 0
        DefaultCanvas = 'TGDIPlusCanvas'
        PrintMargins = (
          15
          17
          15
          17)
        ColorPaletteIndex = 13
        object Series1: TBarSeries
          Selected.Hover.Visible = False
          BarBrush.Gradient.EndColor = 10708548
          BarPen.Color = 10708548
          BarPen.EndStyle = esFlat
          BarPen.SmallDots = True
          Marks.Visible = False
          Marks.Callout.Length = 8
          Emboss.Visible = True
          Gradient.EndColor = 10708548
          Shadow.Visible = False
          Sides = 30
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Bar'
          YValues.Order = loNone
        end
      end
    end
    object Panel5: TPanel
      Left = 1
      Top = 225
      Width = 270
      Height = 96
      Align = alClient
      TabOrder = 1
      object ListView1: TListView
        Left = 1
        Top = 1
        Width = 268
        Height = 94
        Align = alClient
        Columns = <
          item
            Caption = #1053#1086#1084#1077#1088
          end
          item
            Caption = #1055#1083#1086#1090#1085#1086#1089#1090#1100
            Width = 66
          end
          item
            Caption = #1055#1083#1086#1097#1072#1076#1100
            Width = 60
          end
          item
            Caption = #1055#1077#1088#1080#1084#1077#1090#1088
            Width = 70
          end>
        GridLines = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnSelectItem = ListView1SelectItem
      end
    end
    object Panel8: TPanel
      Left = 1
      Top = 132
      Width = 270
      Height = 93
      Align = alTop
      TabOrder = 2
      object Label4: TLabel
        Left = 5
        Top = 36
        Width = 132
        Height = 19
        Caption = #1054#1087#1090'. '#1087#1083#1086#1090#1085#1086#1089#1090#1100':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label5: TLabel
        Left = 5
        Top = 63
        Width = 84
        Height = 19
        Caption = #1055#1083#1086#1097#1072#1076#1100':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label6: TLabel
        Left = 5
        Top = 10
        Width = 141
        Height = 19
        Caption = #1063#1080#1089#1083#1086' '#1086#1073#1098#1077#1082#1090#1086#1074':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label7: TLabel
        Left = 157
        Top = 10
        Width = 40
        Height = 19
        Caption = '0000'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label8: TLabel
        Left = 157
        Top = 36
        Width = 65
        Height = 19
        Caption = '0000.00'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label9: TLabel
        Left = 157
        Top = 63
        Width = 65
        Height = 19
        Caption = '0000.00'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -16
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 403
    Width = 599
    Height = 19
    Panels = <
      item
        Width = 200
      end
      item
        Alignment = taCenter
        Width = 90
      end
      item
        Width = 120
      end
      item
        Width = 100
      end>
  end
  object ActionList1: TActionList
    Left = 24
    Top = 105
    object fileOpenAction: TAction
      Category = 'File'
      Caption = #1054#1090#1082#1088#1099#1090#1100'...'
      OnExecute = fileOpenActionExecute
    end
    object fileExitAction: TFileExit
      Category = 'File'
      Caption = #1042#1099#1093#1086#1076
      Hint = #1042#1099#1093#1086#1076'|'#1047#1072#1082#1088#1099#1090#1100' '#1087#1088#1080#1083#1086#1078#1077#1085#1080#1077
      ImageIndex = 43
    end
    object viewMosaicAction: TAction
      Category = 'View'
      Caption = #1040#1085#1072#1083#1080#1079
      OnExecute = viewMosaicActionExecute
      OnUpdate = viewMosaicActionUpdate
    end
    object viewFirstAction: TAction
      Category = 'View'
      Caption = #1042' '#1085#1072#1095#1072#1083#1086
      OnExecute = viewFirstActionExecute
      OnUpdate = viewFirstActionUpdate
    end
    object viewPrevAction: TAction
      Category = 'View'
      Caption = #1055#1088#1077#1076#1099#1076#1091#1097'. '
      OnExecute = viewPrevActionExecute
      OnUpdate = viewPrevActionUpdate
    end
    object viewNextAction: TAction
      Category = 'View'
      Caption = #1057#1083#1077#1076#1091#1102#1097#1080#1081
      OnExecute = viewNextActionExecute
      OnUpdate = viewNextActionUpdate
    end
    object viewFinishAction: TAction
      Category = 'View'
      Caption = #1042' '#1082#1086#1085#1077#1094
      OnExecute = viewFinishActionExecute
      OnUpdate = viewFinishActionUpdate
    end
    object viewAnalysisAreaAction: TAction
      Category = 'View'
      Caption = #1053#1072#1081#1076#1077#1085#1085#1099#1077' '#1086#1073#1098#1077#1082#1090#1099
      Checked = True
      OnExecute = viewAnalysisAreaActionExecute
      OnUpdate = viewAnalysisAreaActionUpdate
    end
    object chartViewDensityAction: TAction
      Category = 'View'
      Caption = #1056#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1087#1083#1086#1090#1085#1086#1089#1090#1080
      Checked = True
      GroupIndex = 1
      OnExecute = chartViewDensityActionExecute
      OnUpdate = chartViewDensityActionUpdate
    end
    object chartViewSquareAction: TAction
      Category = 'View'
      Caption = #1056#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1087#1083#1086#1097#1072#1076#1080
      GroupIndex = 1
      OnExecute = chartViewSquareActionExecute
      OnUpdate = chartViewSquareActionUpdate
    end
    object chartViewPerimeterAction: TAction
      Category = 'View'
      Caption = #1056#1072#1089#1087#1088#1077#1076#1077#1083#1077#1085#1080#1077' '#1087#1077#1088#1080#1084#1077#1090#1088#1072
      GroupIndex = 1
      OnExecute = chartViewPerimeterActionExecute
      OnUpdate = chartViewPerimeterActionUpdate
    end
    object viewContoursAction: TAction
      Category = 'View'
      Caption = #1050#1086#1085#1090#1091#1088#1072
      OnExecute = viewContoursActionExecute
      OnUpdate = viewContoursActionUpdate
    end
    object chartViewDensityAnalysisAction: TAction
      Category = 'View'
      Caption = #1055#1083#1086#1090#1085#1086#1089#1090#1100' '#1086#1090' '#1074#1088#1077#1084#1077#1085#1080
      GroupIndex = 2
      OnExecute = chartViewDensityAnalysisActionExecute
      OnUpdate = chartViewDensityAnalysisActionUpdate
    end
    object chartViewNumberAnalysisAction: TAction
      Category = 'View'
      Caption = #1063#1080#1089#1083#1086' '#1086#1073#1098#1077#1082#1090#1086#1074' '#1086#1090' '#1074#1088#1077#1084#1077#1085#1080
      Checked = True
      GroupIndex = 2
      OnExecute = chartViewNumberAnalysisActionExecute
      OnUpdate = chartViewNumberAnalysisActionUpdate
    end
    object chartViewSquareAnalysisAction: TAction
      Category = 'View'
      Caption = #1054#1073#1097#1072#1103' '#1087#1083#1086#1097#1072#1076#1100' '#1086#1090' '#1074#1088#1077#1084#1077#1085#1080
      GroupIndex = 2
      OnExecute = chartViewSquareAnalysisActionExecute
      OnUpdate = chartViewSquareAnalysisActionUpdate
    end
    object chartViewPerimeterAnalysisAction: TAction
      Category = 'View'
      Caption = #1055#1077#1088#1080#1084#1077#1090#1088' '#1086#1090' '#1074#1088#1077#1084#1077#1085#1080
      GroupIndex = 2
      OnExecute = chartViewPerimeterAnalysisActionExecute
      OnUpdate = chartViewPerimeterAnalysisActionUpdate
    end
    object editCopyImageAction: TAction
      Category = 'Edit'
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      OnExecute = editCopyImageActionExecute
      OnUpdate = editCopyImageActionUpdate
    end
    object editCopyChartAction: TAction
      Category = 'Edit'
      Caption = #1050#1086#1087#1080#1088#1086#1074#1072#1090#1100
      OnExecute = editCopyChartActionExecute
      OnUpdate = editCopyChartActionUpdate
    end
    object viewAreaAction: TAction
      Category = 'View'
      Caption = #1054#1073#1083#1072#1089#1090#1100' '#1072#1085#1072#1083#1080#1079#1072
      OnExecute = viewAreaActionExecute
      OnUpdate = viewAreaActionUpdate
    end
    object fileReportAction: TAction
      Category = 'File'
      Caption = #1054#1090#1095#1077#1090'...'
      OnExecute = fileReportActionExecute
      OnUpdate = fileReportActionUpdate
    end
    object helpCallAction: TAction
      Category = 'help'
      Caption = #1055#1086#1084#1086#1097#1100
      OnExecute = helpCallActionExecute
    end
    object helpAboutAction: TAction
      Category = 'help'
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'... '
      OnExecute = helpAboutActionExecute
    end
    object fileCloseAction: TAction
      Category = 'File'
      Caption = #1047#1072#1082#1088#1099#1090#1100
      OnExecute = fileCloseActionExecute
      OnUpdate = fileCloseActionUpdate
    end
  end
  object MainMenu1: TMainMenu
    Left = 80
    Top = 105
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083#1099
      object N2: TMenuItem
        Action = fileOpenAction
      end
      object N54: TMenuItem
        Action = fileCloseAction
      end
      object N55: TMenuItem
        Caption = '-'
      end
      object N48: TMenuItem
        Action = fileReportAction
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object N4: TMenuItem
        Action = fileExitAction
      end
    end
    object N5: TMenuItem
      Caption = #1055#1088#1086#1089#1084#1086#1090#1088
      object N6: TMenuItem
        Action = viewMosaicAction
      end
      object N7: TMenuItem
        Caption = '-'
      end
      object N8: TMenuItem
        Action = viewFirstAction
      end
      object N12: TMenuItem
        Action = viewPrevAction
      end
      object N11: TMenuItem
        Action = viewNextAction
      end
      object N13: TMenuItem
        Action = viewFinishAction
      end
      object N14: TMenuItem
        Caption = '-'
      end
      object N15: TMenuItem
        Action = viewAnalysisAreaAction
      end
      object N22: TMenuItem
        Action = viewContoursAction
      end
      object N46: TMenuItem
        Action = viewAreaAction
      end
      object N9: TMenuItem
        Caption = '-'
      end
      object N16: TMenuItem
        Action = chartViewDensityAction
      end
      object N17: TMenuItem
        Action = chartViewSquareAction
      end
      object N18: TMenuItem
        Action = chartViewPerimeterAction
      end
      object N23: TMenuItem
        Caption = '-'
      end
      object N24: TMenuItem
        Action = chartViewDensityAnalysisAction
      end
      object N25: TMenuItem
        Action = chartViewNumberAnalysisAction
      end
      object N26: TMenuItem
        Action = chartViewSquareAnalysisAction
      end
      object N27: TMenuItem
        Action = chartViewPerimeterAnalysisAction
      end
    end
    object N10: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100' '
      object N52: TMenuItem
        Action = helpCallAction
      end
      object N53: TMenuItem
        Action = helpAboutAction
      end
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = #1060#1072#1081#1083#1099' '#1092#1086#1088#1084#1072#1090#1072' PNG |*.png'
    Left = 128
    Top = 105
  end
  object ImageList1: TImageList
    Left = 184
    Top = 105
  end
  object PopupMenu1: TPopupMenu
    Left = 378
    Top = 123
    object N19: TMenuItem
      Action = chartViewDensityAction
    end
    object N20: TMenuItem
      Action = chartViewSquareAction
    end
    object N21: TMenuItem
      Action = chartViewPerimeterAction
    end
    object N28: TMenuItem
      Caption = '-'
    end
    object N29: TMenuItem
      Action = chartViewDensityAnalysisAction
    end
    object N30: TMenuItem
      Action = chartViewNumberAnalysisAction
    end
    object N31: TMenuItem
      Action = chartViewSquareAnalysisAction
    end
    object N32: TMenuItem
      Action = chartViewPerimeterAnalysisAction
    end
    object N44: TMenuItem
      Caption = '-'
    end
    object N45: TMenuItem
      Action = editCopyChartAction
    end
  end
  object PopupMenu2: TPopupMenu
    Left = 240
    Top = 105
    object N51: TMenuItem
      Action = fileOpenAction
    end
    object N50: TMenuItem
      Action = fileReportAction
    end
    object N49: TMenuItem
      Caption = '-'
    end
    object N41: TMenuItem
      Action = viewMosaicAction
    end
    object N40: TMenuItem
      Caption = '-'
    end
    object N33: TMenuItem
      Action = viewAnalysisAreaAction
    end
    object N34: TMenuItem
      Action = viewContoursAction
    end
    object N47: TMenuItem
      Action = viewAreaAction
    end
    object N35: TMenuItem
      Caption = '-'
    end
    object N36: TMenuItem
      Action = viewFirstAction
    end
    object N37: TMenuItem
      Action = viewPrevAction
    end
    object N38: TMenuItem
      Action = viewNextAction
    end
    object N39: TMenuItem
      Action = viewFinishAction
    end
    object N42: TMenuItem
      Caption = '-'
    end
    object N43: TMenuItem
      Action = editCopyImageAction
    end
  end
end
