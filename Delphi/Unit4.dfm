object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'Form4'
  ClientHeight = 732
  ClientWidth = 802
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 136
    Top = 553
    Width = 23
    Height = 13
    Caption = 'Date'
  end
  object Label2: TLabel
    Left = 312
    Top = 553
    Width = 27
    Height = 13
    Caption = 'Week'
  end
  object Label3: TLabel
    Left = 496
    Top = 553
    Width = 22
    Height = 13
    Caption = 'Time'
  end
  object Label4: TLabel
    Left = 136
    Top = 649
    Width = 24
    Height = 13
    Caption = 'Style'
  end
  object Label5: TLabel
    Left = 136
    Top = 681
    Width = 24
    Height = 13
    Caption = 'Style'
  end
  object Label6: TLabel
    Left = 385
    Top = 681
    Width = 46
    Height = 13
    Caption = 'OSD Item'
  end
  object Label7: TLabel
    Left = 385
    Top = 711
    Width = 59
    Height = 13
    Caption = 'OSD Control'
  end
  object Video: TPanel
    Left = 0
    Top = 0
    Width = 802
    Height = 537
    Align = alTop
    Caption = 'Video'
    TabOrder = 0
  end
  object TimeOSD: TCheckBox
    Left = 16
    Top = 552
    Width = 97
    Height = 17
    Caption = 'Time OSD'
    TabOrder = 1
    OnClick = TimeOSDClick
  end
  object TextOSD: TCheckBox
    Left = 16
    Top = 584
    Width = 97
    Height = 17
    Caption = 'Text OSD'
    TabOrder = 2
    OnClick = TextOSDClick
  end
  object ImageOSD: TCheckBox
    Left = 16
    Top = 616
    Width = 97
    Height = 17
    Caption = 'Image OSD'
    TabOrder = 3
    OnClick = ImageOSDClick
  end
  object RectOSD: TCheckBox
    Left = 16
    Top = 648
    Width = 97
    Height = 17
    Caption = 'Rect OSD'
    TabOrder = 4
    OnClick = RectOSDClick
  end
  object EllipseOSD: TCheckBox
    Left = 16
    Top = 680
    Width = 97
    Height = 17
    Caption = 'Ellipse OSD'
    TabOrder = 5
    OnClick = EllipseOSDClick
  end
  object LineOSD: TCheckBox
    Left = 16
    Top = 707
    Width = 97
    Height = 17
    Caption = 'Line OSD'
    TabOrder = 6
    OnClick = LineOSDClick
  end
  object Date: TComboBox
    Left = 173
    Top = 550
    Width = 125
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 7
    Text = 'YY-MM-DD'
    OnChange = TimeOSDClick
    Items.Strings = (
      'YY-MM-DD'
      'MM-DD-YY'
      'DD-MM-YY'
      'MN DD YY'
      'Mn DD YY')
  end
  object Week: TComboBox
    Left = 357
    Top = 550
    Width = 125
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 8
    Text = 'None'
    OnChange = TimeOSDClick
    Items.Strings = (
      'None'
      'Full Name'
      'Short Name')
  end
  object Time: TComboBox
    Left = 541
    Top = 550
    Width = 125
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 9
    Text = '24 Hour'
    OnChange = TimeOSDClick
    Items.Strings = (
      '24 Hour'
      '12 Hour'
      '12 Hour AMPM')
  end
  object OSDFont: TButton
    Left = 696
    Top = 548
    Width = 75
    Height = 25
    Caption = 'Font'
    TabOrder = 10
    OnClick = OSDFontClick
  end
  object Text: TEdit
    Left = 136
    Top = 582
    Width = 530
    Height = 21
    TabOrder = 11
    Text = 'UVS Text Sample'
  end
  object Image: TEdit
    Left = 136
    Top = 614
    Width = 530
    Height = 21
    TabOrder = 12
  end
  object Browse: TButton
    Left = 696
    Top = 612
    Width = 75
    Height = 25
    Caption = '...'
    TabOrder = 13
    OnClick = BrowseClick
  end
  object RectStyle: TComboBox
    Left = 173
    Top = 646
    Width = 125
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 14
    Text = 'Solid'
    OnChange = RectOSDClick
    Items.Strings = (
      'Solid'
      'Dash'
      'Dot'
      'Dash Dot')
  end
  object EllipseStyle: TComboBox
    Left = 173
    Top = 678
    Width = 125
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 15
    Text = 'Solid'
    OnChange = EllipseOSDClick
    Items.Strings = (
      'Solid'
      'Dash'
      'Dot'
      'Dash Dot')
  end
  object MultiLines: TCheckBox
    Left = 385
    Top = 648
    Width = 128
    Height = 17
    Caption = 'Text Multiple Lines'
    TabOrder = 16
    OnClick = TextOSDClick
  end
  object Item: TComboBox
    Left = 453
    Top = 678
    Width = 156
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 17
    Text = 'Time OSD'
    OnChange = ItemChange
    Items.Strings = (
      'Time OSD'
      'Text OSD'
      'Image OSD'
      'Rect OSD'
      'Ellipse OSD')
  end
  object Control: TComboBox
    Left = 453
    Top = 705
    Width = 156
    Height = 21
    Style = csDropDownList
    ItemIndex = 0
    TabOrder = 18
    Text = 'None'
    OnChange = ItemChange
    Items.Strings = (
      'None'
      'Blink'
      'Roll'
      'Scroll 1'
      'Scroll 2'
      'Clean'
      'Fade')
  end
  object OpenDialog1: TOpenDialog
    Left = 752
    Top = 680
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Left = 688
    Top = 680
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 624
    Top = 680
  end
end
