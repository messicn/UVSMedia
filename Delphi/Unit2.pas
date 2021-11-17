unit Unit2;

interface

uses
  { Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls, Vcl.ExtCtrls, UVSMedia; }
  Windows, Messages, SysUtils, Variants, Classes, Graphics,
  Controls, Forms, Dialogs, StdCtrls, ComCtrls, ExtCtrls, UVSMedia;

type
  TForm2 = class(TForm)
    Video: TPanel;
    Label1: TLabel;
    AudioCapture: TComboBox;
    Label2: TLabel;
    VideoCapture: TComboBox;
    Label3: TLabel;
    AudioRender: TComboBox;
    Label4: TLabel;
    VideoRender: TComboBox;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Brightness: TTrackBar;
    Contrast: TTrackBar;
    Saturation: TTrackBar;
    Gamma: TTrackBar;
    Label9: TLabel;
    Label10: TLabel;
    Volume: TTrackBar;
    Balance: TTrackBar;
    Zoomout: TButton;
    Freeze: TButton;
    Zoomin: TButton;
    Mirror: TCheckBox;
    Flip: TCheckBox;
    Mute: TCheckBox;
    Fullscreen: TButton;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure SelectChange(Sender: TObject);
    procedure VideoRenderChange(Sender: TObject);
    procedure BrightnessChange(Sender: TObject);
    procedure ContrastChange(Sender: TObject);
    procedure SaturationChange(Sender: TObject);
    procedure GammaChange(Sender: TObject);
    procedure VolumeChange(Sender: TObject);
    procedure BalanceChange(Sender: TObject);
    procedure MirrorClick(Sender: TObject);
    procedure FlipClick(Sender: TObject);
    procedure MuteClick(Sender: TObject);
    procedure FreezeClick(Sender: TObject);
    procedure ZoominClick(Sender: TObject);
    procedure ZoomoutClick(Sender: TObject);
    procedure FullscreenClick(Sender: TObject);
  private
    { Private declarations }
    Dev: UVSDev;
    Adjust: boolean;
    Zoom: array [0 .. 1] of boolean;
  public
    { Public declarations }
    procedure Start;
    procedure PreviewStart;
    procedure PreviewStop;
  end;

var
  Form2: TForm2;

implementation

uses
  Unit3;

{$R *.dfm}

procedure TForm2.SaturationChange(Sender: TObject);
begin
  if Dev.IsValid and Adjust then
  begin
    Dev.Saturation := Saturation.Position;
  end;
end;

procedure TForm2.SelectChange(Sender: TObject);
begin
  PreviewStop;
  Dev.DeviceClose;
  Start;
end;

procedure TForm2.BalanceChange(Sender: TObject);
begin
  if Dev.IsValid and Adjust then
  begin
    Dev.Balance := Balance.Position;
  end;
end;

procedure TForm2.BrightnessChange(Sender: TObject);
begin
  if Dev.IsValid and Adjust then
  begin
    Dev.Brightness := Brightness.Position;
  end;
end;

procedure TForm2.ContrastChange(Sender: TObject);
begin
  if Dev.IsValid and Adjust then
  begin
    Dev.Contrast := Contrast.Position;
  end;
end;

procedure TForm2.FlipClick(Sender: TObject);
begin
  if Dev.IsValid then
  begin
    Dev.Flip := Flip.Checked;
  end;
end;

procedure TForm2.FormCreate(Sender: TObject);
var
  i, num: Integer;
  info: array [0 .. 15] of TDevInfo;
begin
  Dev := UVSDev.Create;

  num := Length(info);
  if uvs_enum_device(dev_audio_capture, @info[0], num) = UVS_OK then
  begin
    for i := 0 to num-1 do
    begin
      AudioCapture.Items.Add(string(info[i].szFriendlyDevName));
    end;
    AudioCapture.ItemIndex := 0;
  end;

  num := Length(info);
  if uvs_enum_device(dev_video_capture, @info[0], num) = UVS_OK then
  begin
    for i := 0 to num-1 do
    begin
      VideoCapture.Items.Add(string(info[i].szFriendlyDevName));
    end;
    VideoCapture.ItemIndex := 0;
  end;

  num := Length(info);
  if uvs_enum_device(dev_audio_renderer, @info[0], num) = UVS_OK then
  begin
    for i := 0 to num-1 do
    begin
      AudioRender.Items.Add(string(info[i].szFriendlyDevName));
    end;
  end;

  Volume.Min := 0;
  Volume.Max := 100;

  Balance.Min := -100;
  Balance.Max := 100;
end;

procedure TForm2.FormDestroy(Sender: TObject);
begin
  Dev.Free;
end;

procedure TForm2.FormShow(Sender: TObject);
begin
  Start;
end;

procedure TForm2.FreezeClick(Sender: TObject);
begin
  if Dev.IsValid then
  begin
    Dev.Freeze := not Dev.Freeze;
  end;
end;

procedure TForm2.FullscreenClick(Sender: TObject);
var
  disp: DisplayType;
begin
  if Dev.IsValid then
  begin
    if Zoom[0] then
    begin
      ZoominClick(Zoomin);
    end;

    if Zoom[1] then
    begin
      ZoomoutClick(Zoomout);
    end;

    PreviewStop;

    if Form3.Visible then
    begin
      Form3.Hide;
      PreviewStart;
    end
    else
    begin
      Form3.Show;
      if VideoRender.ItemIndex = 0 then
      begin
        disp := direct_3d;
      end
      else
      begin
        disp := direct_draw;
      end;
      Dev.StartPreview(Form3.Video.Handle, disp);
    end;
  end;
end;

procedure TForm2.GammaChange(Sender: TObject);
begin
  if Dev.IsValid and Adjust then
  begin
    Dev.Gamma := Gamma.Position;
  end;
end;

procedure TForm2.MirrorClick(Sender: TObject);
begin
  if Dev.IsValid then
  begin
    Dev.Mirror := Mirror.Checked;
  end;
end;

procedure TForm2.MuteClick(Sender: TObject);
begin
  if Dev.IsValid then
  begin
    Dev.SetAudioMute(Mute.Checked);
  end;
end;

procedure TForm2.Start;
var
  val: array [0 .. 3] of Integer;
begin
  if Dev.DeviceOpen(VideoCapture.ItemIndex) then
  begin
    if AudioCapture.ItemIndex >= 0 then
    begin
      Dev.SetAudioDevice(dev_audio_capture, AudioCapture.ItemIndex);
    end;

    if AudioRender.ItemIndex >= 0 then
    begin
      Dev.SetAudioDevice(dev_audio_renderer, AudioRender.ItemIndex);
    end;

    Dev.DeviceStart;
    PreviewStart;

    Adjust := False;

    if uvs_get_video_effect_range(Dev.Dev, video_brightness, val[0], val[1],
      val[2], val[3]) = UVS_OK then
    begin
      Brightness.Min := val[0];
      Brightness.Max := val[1];
      Brightness.Position := Dev.brightness;
    end;

    if uvs_get_video_effect_range(Dev.Dev, video_contrast, val[0], val[1],
      val[2], val[3]) = UVS_OK then
    begin
      Contrast.Min := val[0];
      Contrast.Max := val[1];
      Contrast.Position := Dev.contrast;
    end;

    if uvs_get_video_effect_range(Dev.Dev, video_saturation, val[0], val[1],
      val[2], val[3]) = UVS_OK then
    begin
      Saturation.Min := val[0];
      Saturation.Max := val[1];
      Saturation.Position := Dev.saturation;
    end;

    if uvs_get_video_effect_range(Dev.Dev, video_gamma, val[0], val[1],
      val[2], val[3]) = UVS_OK then
    begin
      Gamma.Min := val[0];
      Gamma.Max := val[1];
      Gamma.Position := Dev.gamma;
    end;

    Volume.Position := Dev.volume;
    Balance.Position := Dev.balance;

    Adjust := True;

    Mirror.Checked := False;
    Flip.Checked := False;
    Mute.Checked := False;

    Zoom[0] := False;
    Zoom[1] := False;
  end;
end;

procedure TForm2.VideoRenderChange(Sender: TObject);
begin
  PreviewStop;
  PreviewStart;
end;

procedure TForm2.VolumeChange(Sender: TObject);
begin
  if Dev.IsValid and Adjust then
  begin
    Dev.Volume := Volume.Position;
  end;
end;

procedure TForm2.ZoominClick(Sender: TObject);
var
  format: TVideoFormat;
  rc: TRect;
begin
  if Zoom[0] then
  begin
    Dev.SetPreviewRect(nil, nil, 0);
    Zoom[0] := False;
  end
  else if Dev.GetVideoProperty(format) then
  begin { Zoom 2X }
    rc.Left := format.width div 4;
    rc.Top := format.height div 4;
    rc.Right := format.width * 3 div 4;
    rc.Bottom := format.height * 3 div 4;
    Dev.SetPreviewRect(nil, @rc, clSilver);
    Zoom[0] := True;
    Zoom[1] := False;
  end;
end;

procedure TForm2.ZoomoutClick(Sender: TObject);
var
  rc: TRect;
begin
  if Zoom[1] then
  begin
    Dev.SetPreviewRect(nil, nil, 0);
    Zoom[1] := False;
  end
  else if Dev.IsValid then
  begin { Zoom 1/2 }
    rc.Left := Video.width div 4;
    rc.Top := Video.height div 4;
    rc.Right := Video.width * 3 div 4;
    rc.Bottom := Video.height * 3 div 4;
    Dev.SetPreviewRect(@rc, nil, clSilver);
    Video.Refresh;
    Zoom[0] := False;
    Zoom[1] := True;
  end;
end;

procedure TForm2.PreviewStart;
var
  disp: DisplayType;
begin
  if VideoRender.ItemIndex = 0 then
  begin
    disp := direct_3d;
  end
  else
  begin
    disp := direct_draw;
  end;
  Dev.StartPreview(Video.Handle, disp);
end;

procedure TForm2.PreviewStop;
begin
  Dev.StopPreview;
  Video.Refresh;
end;

end.
