object Form6: TForm6
  Left = 0
  Top = 0
  Caption = 'Form6'
  ClientHeight = 673
  ClientWidth = 789
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
    Left = 16
    Top = 608
    Width = 33
    Height = 13
    Caption = 'Rotate'
  end
  object Label2: TLabel
    Left = 16
    Top = 640
    Width = 25
    Height = 13
    Caption = 'Scale'
  end
  object Video: TPanel
    Left = 0
    Top = 0
    Width = 789
    Height = 553
    Align = alTop
    Caption = 'Video'
    TabOrder = 0
  end
  object Flip: TCheckBox
    Left = 16
    Top = 559
    Width = 121
    Height = 17
    Caption = 'Video Frame Flip'
    TabOrder = 1
  end
  object Mirror: TCheckBox
    Left = 16
    Top = 582
    Width = 121
    Height = 17
    Caption = 'Video Frame Mirror'
    TabOrder = 2
  end
  object AudioEnc: TCheckBox
    Left = 224
    Top = 559
    Width = 137
    Height = 17
    Caption = 'Audio Frame Encode'
    TabOrder = 3
  end
  object Rotate: TComboBox
    Left = 72
    Top = 605
    Width = 113
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 4
    Text = 'None'
    Items.Strings = (
      'None'
      '90'
      '180'
      '270')
  end
  object Scale: TComboBox
    Left = 72
    Top = 637
    Width = 113
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 5
    Text = 'None'
    Items.Strings = (
      'None'
      '640 x 480'
      '3840 x 2160')
  end
  object VideoCopy: TButton
    Left = 224
    Top = 600
    Width = 145
    Height = 31
    Caption = 'Video Frame Copy'
    TabOrder = 6
    OnClick = VideoCopyClick
  end
  object Snapshot: TButton
    Left = 224
    Top = 637
    Width = 145
    Height = 33
    Caption = 'Video Snapshot'
    TabOrder = 7
    OnClick = SnapshotClick
  end
  object VideoCallback: TButton
    Left = 424
    Top = 600
    Width = 145
    Height = 31
    Caption = 'Video Frame Callback'
    TabOrder = 8
    OnClick = VideoCallbackClick
  end
  object VideoLock: TButton
    Left = 424
    Top = 637
    Width = 145
    Height = 33
    Caption = 'Video Frame Lock'
    TabOrder = 9
    OnClick = VideoLockClick
  end
  object AudioCallback: TButton
    Left = 616
    Top = 600
    Width = 145
    Height = 31
    Caption = 'Audio Frame Callback'
    TabOrder = 10
    OnClick = AudioCallbackClick
  end
  object AudioLock: TButton
    Left = 616
    Top = 637
    Width = 145
    Height = 33
    Caption = 'Audio Frame Lock'
    TabOrder = 11
    OnClick = AudioLockClick
  end
  object EncCallback: TButton
    Left = 424
    Top = 559
    Width = 145
    Height = 35
    Caption = 'Encode Frame Callback'
    TabOrder = 12
    OnClick = EncCallbackClick
  end
  object AudioCopy: TButton
    Left = 616
    Top = 559
    Width = 145
    Height = 35
    Caption = 'Audio Frame Copy'
    TabOrder = 13
    OnClick = AudioCopyClick
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'png'
    Filter = 'Images|*.png;*.bmp;*.jpg|All Files|*.*'
    Left = 376
    Top = 560
  end
end
