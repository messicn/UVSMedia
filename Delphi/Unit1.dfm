object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 620
  ClientWidth = 795
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
    Left = 32
    Top = 496
    Width = 60
    Height = 13
    Caption = 'Input Status'
  end
  object Status: TEdit
    Left = 112
    Top = 496
    Width = 193
    Height = 21
    ReadOnly = True
    TabOrder = 0
    Text = 'Status'
  end
  object GroupBox1: TGroupBox
    Left = 24
    Top = 523
    Width = 763
    Height = 89
    Caption = 'No Signal Settings(Valid device reopen)'
    TabOrder = 1
    object Label2: TLabel
      Left = 16
      Top = 24
      Width = 49
      Height = 13
      Caption = 'Image File'
    end
    object Label3: TLabel
      Left = 16
      Top = 56
      Width = 59
      Height = 13
      Caption = 'Image Mode'
    end
    object Image: TEdit
      Left = 88
      Top = 24
      Width = 569
      Height = 21
      TabOrder = 0
    end
    object Mode: TComboBox
      Left = 88
      Top = 51
      Width = 145
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 1
      Text = 'Stretch'
      Items.Strings = (
        'Stretch'
        'Center')
    end
    object Browse: TButton
      Left = 680
      Top = 24
      Width = 75
      Height = 25
      Caption = '...'
      TabOrder = 2
      OnClick = BrowseClick
    end
    object Color: TButton
      Left = 400
      Top = 51
      Width = 128
      Height = 25
      Caption = 'Background Color'
      TabOrder = 3
      OnClick = ColorClick
    end
    object Apply: TButton
      Left = 542
      Top = 51
      Width = 115
      Height = 25
      Caption = 'Apply'
      TabOrder = 4
      OnClick = ApplyClick
    end
  end
  object Video: TPanel
    Left = 0
    Top = 0
    Width = 795
    Height = 491
    Align = alTop
    Caption = 'Video'
    TabOrder = 2
  end
  object Timer1: TTimer
    Interval = 300
    OnTimer = Timer1Timer
    Left = 648
    Top = 496
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Images|*.png;*.bmp;*.jpg|All Files|*.*'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 696
    Top = 496
  end
  object ColorDialog1: TColorDialog
    Left = 752
    Top = 496
  end
end
