object Form3: TForm3
  Left = 0
  Top = 0
  Caption = #1050#1077#1088#1072#1084#1080#1082#1072' - '#1082#1083#1080#1077#1085#1090'. '
  ClientHeight = 434
  ClientWidth = 315
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 97
    Width = 315
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
  object GroupBox2: TGroupBox
    Left = 0
    Top = 0
    Width = 315
    Height = 49
    Align = alTop
    Caption = #1057#1077#1088#1074#1077#1088
    TabOrder = 1
    object Label11: TLabel
      Left = 72
      Top = 25
      Width = 4
      Height = 13
      Caption = '.'
    end
    object Label12: TLabel
      Left = 109
      Top = 25
      Width = 4
      Height = 13
      Caption = '.'
    end
    object Label13: TLabel
      Left = 144
      Top = 25
      Width = 4
      Height = 13
      Caption = '.'
    end
    object Label14: TLabel
      Left = 6
      Top = 18
      Width = 14
      Height = 13
      Caption = 'IP:'
    end
    object Label15: TLabel
      Left = 190
      Top = 20
      Width = 29
      Height = 13
      Caption = #1055#1086#1088#1090':'
    end
    object Edit1: TEdit
      Left = 42
      Top = 17
      Width = 30
      Height = 21
      Alignment = taCenter
      TabOrder = 0
      Text = '127'
    end
    object Edit2: TEdit
      Left = 78
      Top = 17
      Width = 30
      Height = 21
      Alignment = taCenter
      TabOrder = 1
      Text = '0'
    end
    object Edit3: TEdit
      Left = 114
      Top = 17
      Width = 30
      Height = 21
      Alignment = taCenter
      TabOrder = 2
      Text = '0'
    end
    object Edit4: TEdit
      Left = 150
      Top = 17
      Width = 30
      Height = 21
      Alignment = taCenter
      TabOrder = 3
      Text = '1'
    end
    object SpinEdit3: TSpinEdit
      Left = 227
      Top = 17
      Width = 70
      Height = 22
      MaxValue = 10000
      MinValue = 1024
      TabOrder = 4
      Value = 7000
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 369
    Width = 315
    Height = 65
    Align = alClient
    Lines.Strings = (
      'Memo1')
    TabOrder = 2
  end
  object Panel1: TPanel
    Left = 0
    Top = 208
    Width = 315
    Height = 161
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 3
    object Chart1: TChart
      Left = 0
      Top = 0
      Width = 315
      Height = 161
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
      BottomAxis.Title.Caption = 'qq'
      BottomAxis.Title.Font.Name = 'Verdana'
      BottomAxis.Visible = False
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
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
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
        LinePen.Width = 4
        LinePen.EndStyle = esRound
        TreatNulls = tnDontPaint
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Y'
        YValues.Order = loNone
      end
    end
  end
  object Button1: TButton
    Left = 0
    Top = 49
    Width = 315
    Height = 48
    Align = alTop
    Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103
    TabOrder = 4
    OnClick = Button1Click
  end
  object IdTCPClient1: TIdTCPClient
    OnDisconnected = IdTCPClient1Disconnected
    OnConnected = IdTCPClient1Connected
    ConnectTimeout = 5000
    IPVersion = Id_IPv4
    Port = 0
    ReadTimeout = -1
    Left = 136
    Top = 193
  end
  object IdAntiFreeze1: TIdAntiFreeze
    Left = 184
    Top = 192
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 96
    Top = 192
  end
  object ApplicationEvents1: TApplicationEvents
    OnIdle = ApplicationEvents1Idle
    Left = 256
    Top = 121
  end
end
