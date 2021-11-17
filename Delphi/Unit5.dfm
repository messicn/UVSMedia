object Form5: TForm5
  Left = 0
  Top = 0
  Caption = 'Form5'
  ClientHeight = 739
  ClientWidth = 710
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
    Left = 25
    Top = 476
    Width = 68
    Height = 13
    Caption = 'Video Encoder'
  end
  object Label2: TLabel
    Left = 25
    Top = 501
    Width = 68
    Height = 13
    Caption = 'Encode Usage'
  end
  object Label3: TLabel
    Left = 25
    Top = 528
    Width = 56
    Height = 13
    Caption = 'Frame Rate'
  end
  object Label4: TLabel
    Left = 25
    Top = 556
    Width = 52
    Height = 13
    Caption = 'Video Crop'
  end
  object Label5: TLabel
    Left = 25
    Top = 582
    Width = 54
    Height = 13
    Caption = 'Video Scale'
  end
  object Label6: TLabel
    Left = 25
    Top = 609
    Width = 60
    Height = 13
    Caption = 'File Duration'
  end
  object Label7: TLabel
    Left = 16
    Top = 636
    Width = 80
    Height = 13
    Caption = 'Rec Main Stream'
  end
  object Label8: TLabel
    Left = 17
    Top = 663
    Width = 76
    Height = 13
    Caption = 'Rec Sub Stream'
  end
  object Label9: TLabel
    Left = 17
    Top = 696
    Width = 69
    Height = 13
    Caption = 'Encode Status'
  end
  object Label10: TLabel
    Left = 376
    Top = 474
    Width = 69
    Height = 13
    Caption = 'Audio Encoder'
  end
  object Label11: TLabel
    Left = 376
    Top = 501
    Width = 70
    Height = 13
    Caption = 'Encode Bitrate'
  end
  object Label12: TLabel
    Left = 376
    Top = 528
    Width = 55
    Height = 13
    Caption = 'Max Bitrate'
  end
  object Label13: TLabel
    Left = 376
    Top = 556
    Width = 70
    Height = 13
    Caption = 'Bitrate Control'
  end
  object Label14: TLabel
    Left = 376
    Top = 582
    Width = 58
    Height = 13
    Caption = 'Scale Usage'
  end
  object Label15: TLabel
    Left = 376
    Top = 609
    Width = 38
    Height = 13
    Caption = 'File Size'
  end
  object Video: TPanel
    Left = 0
    Top = 0
    Width = 710
    Height = 465
    Align = alTop
    Caption = 'Video'
    TabOrder = 0
  end
  object VideoEnc: TComboBox
    Left = 112
    Top = 471
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 1
    Text = 'Intel GPU H.264'
    Items.Strings = (
      'Intel GPU H.264'
      'Intel GPU H.265'
      'Nvidia GPU H.264'
      'NVidia GPU H.265'
      'Open H.264')
  end
  object EncUsage: TComboBox
    Left = 112
    Top = 498
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 2
    Text = 'High Perfomance'
    Items.Strings = (
      'High Perfomance'
      'Balance'
      'High Quality')
  end
  object FrameRate: TComboBox
    Left = 112
    Top = 525
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 3
    Text = 'Default'
    Items.Strings = (
      'Default')
  end
  object VideoCrop: TComboBox
    Left = 112
    Top = 553
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 4
    Text = 'None'
    Items.Strings = (
      'None'
      '640 x 480')
  end
  object VideoScale: TComboBox
    Left = 112
    Top = 579
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 5
    Text = 'None'
    Items.Strings = (
      'None'
      '1280 x 720')
  end
  object FileDur: TComboBox
    Left = 112
    Top = 606
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 6
    Text = 'No Limits'
    Items.Strings = (
      'No Limits'
      '1min'
      '5min'
      '15min')
  end
  object AudioEnc: TComboBox
    Left = 467
    Top = 471
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 7
    Text = 'None'
    Items.Strings = (
      'None'
      'AAC'
      'MP3')
  end
  object EncBitrate: TComboBox
    Left = 467
    Top = 498
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 8
    Text = '3000Kbps'
    Items.Strings = (
      '3000Kbps'
      '5000Kbps'
      '8000Kbps')
  end
  object MaxBitrate: TComboBox
    Left = 467
    Top = 525
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 9
    Text = '8000Kbps'
    Items.Strings = (
      '8000Kbps'
      '10000Kbps'
      '12000Kbps')
  end
  object RCMode: TComboBox
    Left = 467
    Top = 552
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 2
    TabOrder = 10
    Text = 'VBR'
    Items.Strings = (
      'CBR'
      'CQP'
      'VBR')
  end
  object EncScale: TComboBox
    Left = 467
    Top = 579
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 11
    Text = 'High Perfomance'
    Items.Strings = (
      'High Perfomance'
      'Balance'
      'Quality'
      'High Quality')
  end
  object FileSize: TComboBox
    Left = 467
    Top = 606
    Width = 217
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 12
    Text = 'No Limits'
    Items.Strings = (
      'No Limits'
      '32MB'
      '128MB')
  end
  object MainDir: TEdit
    Left = 111
    Top = 633
    Width = 514
    Height = 21
    TabOrder = 13
  end
  object SubDir: TEdit
    Left = 111
    Top = 660
    Width = 514
    Height = 21
    TabOrder = 14
  end
  object MainBrowse: TButton
    Left = 631
    Top = 633
    Width = 53
    Height = 25
    Caption = '...'
    TabOrder = 15
    OnClick = MainBrowseClick
  end
  object SubBrowse: TButton
    Left = 631
    Top = 660
    Width = 53
    Height = 25
    Caption = '....'
    TabOrder = 16
    OnClick = SubBrowseClick
  end
  object RecStart: TButton
    Left = 408
    Top = 687
    Width = 97
    Height = 34
    Caption = 'Rec Start'
    TabOrder = 17
    OnClick = RecStartClick
  end
  object RecPause: TButton
    Left = 528
    Top = 687
    Width = 97
    Height = 34
    Caption = 'Rec Pause'
    TabOrder = 18
    OnClick = RecPauseClick
  end
  object Repair: TCheckBox
    Left = 281
    Top = 695
    Width = 121
    Height = 17
    Caption = 'File Repair Support'
    TabOrder = 19
  end
  object EncStatus: TMemo
    Left = 111
    Top = 687
    Width = 164
    Height = 48
    Lines.Strings = (
      'EncStatus')
    ReadOnly = True
    TabOrder = 20
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 656
    Top = 688
  end
end
