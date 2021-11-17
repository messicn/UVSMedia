unit Unit4;

interface

uses
  { Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ExtCtrls, Vcl.StdCtrls, System.UITypes, UVSMedia; }
  Windows, Messages, SysUtils, Variants, Classes, Graphics,
  Controls, Forms, Dialogs, ExtCtrls, StdCtrls, UVSMedia;

type
  TForm4 = class(TForm)
    Video: TPanel;
    TimeOSD: TCheckBox;
    TextOSD: TCheckBox;
    ImageOSD: TCheckBox;
    RectOSD: TCheckBox;
    EllipseOSD: TCheckBox;
    LineOSD: TCheckBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Date: TComboBox;
    Week: TComboBox;
    Time: TComboBox;
    OSDFont: TButton;
    Text: TEdit;
    Image: TEdit;
    Browse: TButton;
    Label4: TLabel;
    Label5: TLabel;
    RectStyle: TComboBox;
    EllipseStyle: TComboBox;
    MultiLines: TCheckBox;
    Item: TComboBox;
    Control: TComboBox;
    Label6: TLabel;
    Label7: TLabel;
    OpenDialog1: TOpenDialog;
    FontDialog1: TFontDialog;
    Timer1: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
    procedure OSDFontClick(Sender: TObject);
    procedure BrowseClick(Sender: TObject);
    procedure TimeOSDClick(Sender: TObject);
    procedure TextOSDClick(Sender: TObject);
    procedure ImageOSDClick(Sender: TObject);
    procedure RectOSDClick(Sender: TObject);
    procedure EllipseOSDClick(Sender: TObject);
    procedure LineOSDClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure ItemChange(Sender: TObject);
  private
    { Private declarations }
    Dev: UVSDev;
    Font: TFont;
    Format: TVideoFormat;
    OSDIndex, OSDCtrl: Integer;
    procedure DisableOSD(index: Integer);
    procedure GetFontInfo(var info:TFontInfo);
  public
    { Public declarations }
  end;

var
  Form4: TForm4;

const
  timeIndex = Integer(time_osd_preview_enc); { time_osd_index_preview_only }
  baseIndex = Integer(base_osd_preview_enc); { base_osd_preview_only }
  textIndex = baseIndex + 1;
  imageIndex = baseIndex + 2;
  rectIndex = baseIndex + 3;
  ellipseIndex = baseIndex + 4;
  lineIndex0 = baseIndex + 5;
  lineIndex1 = baseIndex + 6;
  lineIndex2 = baseIndex + 7;
  lineIndex3 = baseIndex + 8;

  { OSD item control }
  none = 0;
  blink = 1;
  roll = 2;
  scroll1 = 3;
  scroll2 = 4;
  clean = 5;
  fade = 6;

  osdStyle: array[0..3] of DashStyle = (solid, dash, dot, dash_dot);

implementation

{$R *.dfm}

procedure TForm4.DisableOSD(index: Integer);
{ var flag: Integer; }
begin
  Dev.OSDControl(index, osd_delete);

  { OSD disable(flag=0) / enable(flag=1) for reused }
  { flag := 0; Dev.OSDControl(index, osd_enable, @flag); }
end;

procedure TForm4.EllipseOSDClick(Sender: TObject);
var
  info: TStyleInfo;
begin
  if Dev.IsValid then
  begin
    if EllipseOSD.Checked then
    begin
      info.lineSize := 4;
      info.style := osdStyle[EllipseStyle.ItemIndex];
      info.lineColor := clRed;
      info.fillColor := clWhite;
      info.lineOpacity := 255;
      info.fillOpacity := 128;

      Dev.SetEllipseOSD(ellipseIndex, 300, 200, 200, 200, info);
    end
    else
    begin
      DisableOSD(ellipseIndex);
    end;
  end;
end;

procedure TForm4.GetFontInfo(var info: TFontInfo);
var
  style: Integer;
begin
  FillChar(info, Sizeof(TFontInfo), 0);

  UVSDev.StrCopy(@info.szFontName, AnsiString(Font.Name));
  info.pointSize := Font.Size;
  info.textColor := Font.Color;
  info.textOpacity := 255;

  style := Integer(font_cleartype);
  if fsBold in Font.Style then
  begin
    style := style or Integer(font_bold);
  end;

  if fsItalic in Font.Style then
  begin
    style := style or Integer(font_italic);
  end;

  if fsUnderline in Font.Style then
  begin
    style := style or Integer(font_underline);
  end;

  if fsStrikeOut in Font.Style then
  begin
    style := style or Integer(font_strikeout);
  end;
  info.style := FontStyle(style);
end;

procedure TForm4.ImageOSDClick(Sender: TObject);
begin
  if Dev.IsValid then
  begin
    if ImageOSD.Checked then
    begin
      if Image.Text <> '' then
      begin
        Dev.SetImageOSD(imageIndex, 20, 160, 0, 0, 192,
          PAnsiChar(AnsiString(Image.Text)));
      end;
    end
    else
    begin
      DisableOSD(imageIndex);
    end;
  end;
end;

procedure TForm4.ItemChange(Sender: TObject);
const
  index: array [0 .. 4] of Integer = (timeIndex, textIndex, imageIndex,
    rectIndex, ellipseIndex);
var
  show, hide, x, y, width, height: Integer;
  info: TStyleInfo;
begin
  if Dev.IsValid then
  begin
    if OSDCtrl = blink then
    begin
      show := 0;
      hide := 0;
      { clear show / hide period }
      Dev.OSDControl(OSDIndex, osd_set_blink, @show, @hide);
    end
    else if (OSDCtrl = scroll1) or (OSDCtrl = scroll2) or
      (OSDCtrl = clean) then
    begin
      width := 0;
      height := 0;
      { clear clip size }
      Dev.OSDControl(OSDIndex, set_clip_size, @width, @height);
      if OSDCtrl = scroll2 then
      begin
        { delete background rect }
        Dev.OSDControl(baseIndex, osd_delete);
      end;
    end;

    OSDIndex := index[Item.ItemIndex];
    OSDCtrl := Control.ItemIndex;
    if OSDCtrl = blink then
    begin
      show := 800;
      hide := 600;
      Dev.OSDControl(OSDIndex, osd_set_blink, @show, @hide);
    end
    else if (OSDCtrl = scroll1) or (OSDCtrl = scroll2) or
      (OSDCtrl = clean) then
    begin
      if Dev.OSDControl(OSDIndex, osd_get_size, @width, @height) then
      begin
        x := 0;
        if Format.width > width then
        begin
          { center }
          x := (Format.width - width) div 2;
        end;

        { x & width must be even }
        if Odd(x) then
        begin
          x := x - 1;
        end;

        if Odd(width) then
        begin
          width := width + 1;
        end;

        Dev.OSDControl(OSDIndex, osd_set_position, @x);
        Dev.OSDControl(OSDIndex, set_clip_position, @x);
        Dev.OSDControl(OSDIndex, set_clip_size, @width, @height);

        if OSDCtrl = scroll2 then
        begin
          info.lineSize := 2;
          info.style := solid;
          info.lineColor := clBlack;
          info.lineOpacity := 128;
          info.fillColor := clGreen;
          info.fillOpacity := 128;
          { create background rect }
          Dev.OSDControl(OSDIndex, osd_get_position, nil, @y);
          Dev.SetRectOSD(baseIndex, x, y, width, height, info);
        end;
      end;
    end;
  end;
end;

procedure TForm4.LineOSDClick(Sender: TObject);
const
  lineSize = 4;
  rectX = 20;
  rectY = 420;
  rectWidth = 800;
  rectHeight = 400;
var
  info: TLineInfo;
  x0, y0, x1, y1, flag: Integer;
begin
  if Dev.IsValid then
  begin
    if LineOSD.Checked then
    begin
      info.lineSize := lineSize;
      info.style := solid;
      info.Color := clAqua;
      info.opacity := 255;

      flag := 1;

      { draw horiz line0 }
      x0 := rectX;
      x1 := rectX + rectWidth;
      if not Dev.OSDControl(lineIndex0, osd_enable, @flag) then
      begin
        y0 := rectY;
        y1 := rectY;
        Dev.SetLineOSD(lineIndex0, x0, y0, x1, y1, info);
      end;

      { draw horiz line1 }
      if not Dev.OSDControl(lineIndex1, osd_enable, @flag) then
      begin
        y0 := rectY + rectHeight - lineSize;
        y1 := y0;
        Dev.SetLineOSD(lineIndex1, x0, y0, x1, y1, info);
      end;

      { draw vertical line0 }
      y0 := rectY + lineSize;
      y1 := rectY + rectHeight - lineSize;
      if not Dev.OSDControl(lineIndex2, osd_enable, @flag) then
      begin
        x0 := rectX;
        x1 := rectX;
        Dev.SetLineOSD(lineIndex2, x0, y0, x1, y1, info);
      end;

      { draw vertical line1 }
      if not Dev.OSDControl(lineIndex3, osd_enable, @flag) then
      begin
        x0 := rectX + rectWidth - lineSize;
        x1 := x0;
        Dev.SetLineOSD(lineIndex3, x0, y0, x1, y1, info);
      end;
    end
    else
    begin
      { hide lines }
      flag := 0;
      Dev.OSDControl(lineIndex0, osd_enable, @flag);
      Dev.OSDControl(lineIndex1, osd_enable, @flag);
      Dev.OSDControl(lineIndex2, osd_enable, @flag);
      Dev.OSDControl(lineIndex3, osd_enable, @flag);
    end;
  end;
end;

procedure TForm4.BrowseClick(Sender: TObject);
begin
  if OpenDialog1.Execute then
  begin
    Image.Text := OpenDialog1.FileName;
  end;
end;

procedure TForm4.OSDFontClick(Sender: TObject);
begin
  FontDialog1.Font := Font;
  if FontDialog1.Execute then
  begin
    Font := FontDialog1.Font;
  end;
end;

procedure TForm4.RectOSDClick(Sender: TObject);
var
  info: TStyleInfo;
begin
  if Dev.IsValid then
  begin
    if RectOSD.Checked then
    begin
      info.lineSize := 4;
      info.style := osdStyle[RectStyle.ItemIndex];
      info.lineColor := clRed;
      info.fillColor := clWhite;
      info.lineOpacity := 255;
      info.fillOpacity := 128;

      Dev.SetRectOSD(rectIndex, 20, 200, 200, 200, info);
    end
    else
    begin
      DisableOSD(rectIndex);
    end;
  end;
end;

procedure TForm4.TextOSDClick(Sender: TObject);
var
  width, height: Integer;
  info: TFontInfo;
begin
  if Dev.IsValid then
  begin
    if TextOSD.Checked then
    begin
      if Text.Text <> '' then
      begin

        GetFontInfo(info);

        width := 0;
        height := 0;
        if MultiLines.Checked then
        begin
          width := 200;
          height := 100;
          info.format := rect_multiple_lines;
        end;

        Dev.SetTextOSD(textIndex, 20, 100, width, height,
          PAnsiChar(AnsiString(Text.Text)), info);
      end;
    end
    else
    begin
      DisableOSD(textIndex);
    end;
  end;
end;

procedure TForm4.TimeOSDClick(Sender: TObject);
const
  strDate: array [0 .. 4] of string = ('%Y-%M-%D', '%M-%D-%Y', '%D-%M-%Y',
    '%N %D %Y', '%n %D %Y');
  strWeek: array [0 .. 2] of string = ('', ' %W', ' %w');
  strTime: array [0 .. 2] of string = (' %H:%m:%s', ' %h:%m:%s',
    ' %h:%m:%s %t');
var
  str: string;
  info: TFontInfo;
begin
  if Dev.IsValid then
  begin
    if TimeOSD.Checked then
    begin
      str := strDate[Date.ItemIndex];
      str := str + strWeek[Week.ItemIndex];
      str := str + strTime[Time.ItemIndex];

      GetFontInfo(info);

      { %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
        %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %% % }
      Dev.SetTimeOSD(timeIndex, 20, 20, PAnsiChar(AnsiString(str)), info);
    end
    else
    begin
      DisableOSD(timeIndex);
    end;
  end;
end;

procedure TForm4.Timer1Timer(Sender: TObject);
var
  x, pos, width, height, opacity, bkopacity: Integer;
begin
  if Dev.IsValid then
  begin
    if (OSDCtrl = roll) or (OSDCtrl = scroll1) or (OSDCtrl = scroll2) then
    begin
      Dev.OSDControl(OSDIndex, osd_get_position, @x);
      Dev.OSDControl(OSDIndex, osd_get_size, @width);

      pos := 0;
      if (OSDCtrl = scroll1) or (OSDCtrl = scroll2) then
      begin
        Dev.OSDControl(OSDIndex, get_clip_position, @pos);
      end;

      if x + width > pos then
      begin
        { move left }
        x := x - 4;
      end
      else if OSDCtrl = roll then
      begin
        { right beginning }
        x := Format.width;
      end
      else
      begin
        x := pos + width;
      end;

      Dev.OSDControl(OSDIndex, osd_set_position, @x);
    end
    else if OSDCtrl = clean then
    begin
      Dev.OSDControl(OSDIndex, get_clip_size, @width, @height);
      if (width > 0) and (height > 0) then
      begin
        { reduce clip size }
        width := width * 9 div 10;
        height := height * 9 div 10;
      end
      else
      begin
        Dev.OSDControl(OSDIndex, osd_get_size, @width, @height);
      end;

      if Odd(width) then
      begin
        width := width + 1;
      end;

      Dev.OSDControl(OSDIndex, set_clip_size, @width, @height);
    end
    else if OSDCtrl = fade then
    begin
      Dev.OSDControl(OSDIndex, osd_get_opacity, @opacity, @bkopacity);
      if opacity > 20 then
      begin
        opacity := opacity * 9 div 10;
        bkopacity := bkopacity * 9 div 10;
      end
      else
      begin
        opacity := 255;
        bkopacity := 192;
      end;

      Dev.OSDControl(OSDIndex, osd_set_opacity, @opacity, @bkopacity);
    end;
  end;
end;

procedure TForm4.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Dev.Free;
end;

procedure TForm4.FormCreate(Sender: TObject);
var
  ret: boolean;
begin
  Dev := UVSDev.Create(0, -1, ret);
  if Dev.IsValid then
  begin
    Dev.DeviceStart;
    Dev.GetVideoProperty(Format);
  end;

  Font := TFont.Create;
  Font.Name := 'Arial';
  Font.Color := clBlue;
  Font.Style := [fsBold];
  Font.Size := 28;
end;

procedure TForm4.FormShow(Sender: TObject);
begin
  Dev.StartPreview(Video.Handle);
end;

end.
