object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 710
  ClientWidth = 787
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 520
    Width = 69
    Height = 13
    Caption = 'Audio Capture'
  end
  object Label2: TLabel
    Left = 392
    Top = 519
    Width = 68
    Height = 13
    Caption = 'Video Capture'
  end
  object Label3: TLabel
    Left = 24
    Top = 552
    Width = 75
    Height = 13
    Caption = 'Audio Renderer'
  end
  object Label4: TLabel
    Left = 392
    Top = 550
    Width = 74
    Height = 13
    Caption = 'Video Renderer'
  end
  object Label5: TLabel
    Left = 24
    Top = 584
    Width = 50
    Height = 13
    Caption = 'Brightness'
  end
  object Label6: TLabel
    Left = 392
    Top = 584
    Width = 42
    Height = 13
    Caption = 'Contrast'
  end
  object Label7: TLabel
    Left = 24
    Top = 608
    Width = 50
    Height = 13
    Caption = 'Saturation'
  end
  object Label8: TLabel
    Left = 392
    Top = 608
    Width = 35
    Height = 13
    Caption = 'Gamma'
  end
  object Label9: TLabel
    Left = 24
    Top = 632
    Width = 34
    Height = 13
    Caption = 'Volume'
  end
  object Label10: TLabel
    Left = 392
    Top = 632
    Width = 37
    Height = 13
    Caption = 'Balance'
  end
  object Video: TPanel
    Left = 0
    Top = 0
    Width = 787
    Height = 513
    Align = alTop
    Caption = 'Video'
    TabOrder = 0
  end
  object AudioCapture: TComboBox
    Left = 112
    Top = 520
    Width = 249
    Height = 21
    Style = csDropDownList
    TabOrder = 1
    OnChange = SelectChange
  end
  object VideoCapture: TComboBox
    Left = 496
    Top = 520
    Width = 265
    Height = 21
    Style = csDropDownList
    TabOrder = 2
    OnChange = SelectChange
  end
  object AudioRender: TComboBox
    Left = 112
    Top = 547
    Width = 249
    Height = 21
    Style = csDropDownList
    TabOrder = 3
    OnChange = SelectChange
  end
  object VideoRender: TComboBox
    Left = 496
    Top = 547
    Width = 265
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 4
    Text = 'Direct 3D'
    OnChange = VideoRenderChange
    Items.Strings = (
      'Direct 3D'
      'Direct Draw')
  end
  object Brightness: TTrackBar
    Left = 112
    Top = 574
    Width = 249
    Height = 23
    TabOrder = 5
    TickStyle = tsNone
    OnChange = BrightnessChange
  end
  object Contrast: TTrackBar
    Left = 488
    Top = 574
    Width = 273
    Height = 23
    TabOrder = 6
    TickStyle = tsNone
    OnChange = ContrastChange
  end
  object Saturation: TTrackBar
    Left = 112
    Top = 603
    Width = 249
    Height = 23
    TabOrder = 7
    TickStyle = tsNone
    OnChange = SaturationChange
  end
  object Gamma: TTrackBar
    Left = 488
    Top = 603
    Width = 273
    Height = 23
    TabOrder = 8
    TickStyle = tsNone
    OnChange = GammaChange
  end
  object Volume: TTrackBar
    Left = 112
    Top = 632
    Width = 249
    Height = 23
    TabOrder = 9
    TickStyle = tsNone
    OnChange = VolumeChange
  end
  object Balance: TTrackBar
    Left = 488
    Top = 632
    Width = 273
    Height = 23
    TabOrder = 10
    TickStyle = tsNone
    OnChange = BalanceChange
  end
  object Zoomout: TButton
    Left = 686
    Top = 672
    Width = 93
    Height = 30
    Caption = 'Zoom Out'
    TabOrder = 11
    OnClick = ZoomoutClick
  end
  object Freeze: TButton
    Left = 560
    Top = 672
    Width = 105
    Height = 30
    Caption = 'Freeze'
    TabOrder = 12
    OnClick = FreezeClick
  end
  object Zoomin: TButton
    Left = 424
    Top = 672
    Width = 107
    Height = 30
    Caption = 'Zoom In'
    TabOrder = 13
    OnClick = ZoominClick
  end
  object Mirror: TCheckBox
    Left = 32
    Top = 661
    Width = 97
    Height = 17
    Caption = 'Mirror'
    TabOrder = 14
    OnClick = MirrorClick
  end
  object Flip: TCheckBox
    Left = 160
    Top = 661
    Width = 97
    Height = 17
    Caption = 'Flip'
    TabOrder = 15
    OnClick = FlipClick
  end
  object Mute: TCheckBox
    Left = 32
    Top = 684
    Width = 97
    Height = 17
    Caption = 'Mute'
    TabOrder = 16
    OnClick = MuteClick
  end
  object Fullscreen: TButton
    Left = 304
    Top = 672
    Width = 97
    Height = 30
    Caption = 'Full Screen'
    TabOrder = 17
    OnClick = FullscreenClick
  end
end
