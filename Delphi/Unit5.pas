unit Unit5;

interface

{$WARN UNIT_PLATFORM OFF }

uses
  { Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls, Vcl.FileCtrl, UVSMedia; }
  Windows, Messages, SysUtils, Variants, Classes, Graphics,
  Controls, Forms, Dialogs, StdCtrls, ExtCtrls, FileCtrl, UVSMedia;

type
  TForm5 = class(TForm)
    Video: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    VideoEnc: TComboBox;
    EncUsage: TComboBox;
    FrameRate: TComboBox;
    VideoCrop: TComboBox;
    VideoScale: TComboBox;
    FileDur: TComboBox;
    AudioEnc: TComboBox;
    EncBitrate: TComboBox;
    MaxBitrate: TComboBox;
    RCMode: TComboBox;
    EncScale: TComboBox;
    FileSize: TComboBox;
    MainDir: TEdit;
    SubDir: TEdit;
    MainBrowse: TButton;
    SubBrowse: TButton;
    RecStart: TButton;
    RecPause: TButton;
    Repair: TCheckBox;
    Timer1: TTimer;
    EncStatus: TMemo;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure MainBrowseClick(Sender: TObject);
    procedure SubBrowseClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure RecPauseClick(Sender: TObject);
    procedure RecStartClick(Sender: TObject);
  private
    { Private declarations }
    Dev: UVSDev;
    VFormat: TVideoFormat;
    rec, pause: boolean;
    procedure GetEncodeConfig(var config: TEncodeConfig);
  public
    { Public declarations }
  end;

var
  Form5: TForm5;

implementation

{$WARN UNIT_PLATFORM OFF }
{$R *.dfm}

procedure TForm5.FormCreate(Sender: TObject);
var
ret: boolean;
begin
  Dev := UVSDev.Create(0, 0, ret);
  if Dev.IsValid then
  begin
    Dev.DeviceStart;
    Dev.GetVideoProperty(VFormat);
    FrameRate.Items.Add(FormatFloat('0.00', VFormat.frameRate / 2));
  end;

  MainDir.Text := ExtractFilePath(Application.ExeName);
end;

procedure TForm5.FormDestroy(Sender: TObject);
begin
  Dev.Free;
end;

procedure TForm5.FormShow(Sender: TObject);
begin
  Dev.StartPreview(Video.Handle);
end;

procedure TForm5.MainBrowseClick(Sender: TObject);
var
  str: string;
begin
  if SelectDirectory('', '', str) then
  begin
    MainDir.Text := str;
  end;
end;

procedure TForm5.RecPauseClick(Sender: TObject);
begin
  if Dev.IsValid and rec then
  begin
    Dev.PauseRecord(UVS_STREAM_ALL, pause);
    pause := not pause;
    if pause then
    begin
      RecPause.Caption := 'Rec Resume';
    end
    else
    begin
      RecPause.Caption := 'Rec Pause';
    end;
  end;
end;

procedure TForm5.RecStartClick(Sender: TObject);
const
  mainStream = 0;
  subStream = 1;
  ACodec: array [0 .. 2] of AudioCodec = (codec_anone, codec_AAC, codec_MP3);
  VCodec: array [0 .. 4] of VideoCodec = (codec_intel_h264, codec_intel_h265,
    codec_nvidia_h264, codec_nvidia_h265, codec_sw_h264);
  millSec: array [0 .. 3] of Integer = (0, 60 * 1000, 5 * 60 * 1000,
    15 * 60 * 1000);
  kBytes: array [0 .. 2] of Integer = (0, 32 * 1024, 128 * 1024);
var
  config: TEncodeConfig;
  aenc: AudioCodec;
  venc: VideoCodec;
  sz, dur: Integer;
  flag: boolean;
  str: string;
begin
  if Dev.IsValid then
  begin
    if rec then
    begin
      Dev.StopEncode(UVS_STREAM_ALL);
      Dev.StopRecord(UVS_STREAM_ALL);

      rec := False;
      if pause then
      begin
        pause := False;
        RecPause.Caption := 'Record Pause';
      end;
    end
    else
    begin
      GetEncodeConfig(config);

      aenc := codec_anone;
      { audio input is ready? }
      if Dev.GetAudioProperty(nil, aenc) then
      begin
        aenc := ACodec[AudioEnc.ItemIndex];
      end;

      venc := VCodec[VideoEnc.ItemIndex];

      { auto rec limit file size(KB), 0 manual control }
      sz := KBytes[FileSize.ItemIndex];

      { auto rec limit duration(ms), 0 manual control }
      dur := millSec[FileDur.ItemIndex];

      { mp4 file repair support }
      flag := Repair.Checked;

      { main stream config }
      if MainDir.Text <> '' then
      begin
        if not Dev.SetVideoEncode(mainStream, venc, config) then
        begin
          if uvs_query_video_encoder(nil, venc) <> UVS_OK then
          begin
            ShowMessage('HW not support or codec library not found!');
          end;
          Exit;
        end;

        str := 'UVS Main Stream';
        Dev.SetRecordMetadata(mainStream, PAnsiChar(AnsiString(str)));

        { %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
        %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %i stream index, %% % }
        str := ExcludeTrailingPathDelimiter(MainDir.Text) + PathDelim;
        str := str + '%Y%M%D_%H%m%s_%i.mp4';
        if not Dev.StartRecord(mainStream, PAnsiChar(AnsiString(str)), nil,
          aenc <> codec_anone, flag, sz, dur) then
        begin
          Exit;
        end;
      end;

      { sub stream config }
      if SubDir.Text <> '' then
      begin
        { 480P sub stream }
        config.scaleWidth := 640;
        config.scaleHeight := 480;
        config.EncBitrate := 1000;
        config.MaxBitrate := 3000;

        if not Dev.SetVideoEncode(subStream, venc, config) then
        begin
          if uvs_query_video_encoder(nil, venc) <> UVS_OK then
          begin
            ShowMessage('HW not support or codec library not found!');
          end;
          Exit;
        end;

        str := 'UVS Sub Stream';
        Dev.SetRecordMetadata(subStream, PAnsiChar(AnsiString(str)));

        { %M month, %D month of day, %H 24 hours, %h 12 hours, %m minute, %s second, %Y year,
          %t AM/PM, %N month name, %n month short name, %W week name, %w week short name, %i stream index, %% % }
        str := ExcludeTrailingPathDelimiter(SubDir.Text) + PathDelim;
        str := str + '%Y%M%D_%H%m%s_%i.mp4';
        if not Dev.StartRecord(subStream, PAnsiChar(AnsiString(str)), nil,
          aenc <> codec_anone, flag, sz, dur) then
        begin
          Exit;
        end;
      end;

      { audio stream config }
      Dev.SetAudioProperty(aenc);

      if not Dev.StartEncode(UVS_STREAM_ALL) then
      begin
        ShowMessage('Encode failed!');
        Exit;
      end;

      rec := True;
    end;

    if rec then
    begin
      RecStart.Caption := 'Record Stop';
    end
    else
    begin
      RecStart.Caption := 'Record Start';
    end;
  end;
end;

procedure TForm5.GetEncodeConfig(var config: TEncodeConfig);
const
  enc: array [0 .. 2] of TargetUsage = (enc_performance, enc_balance,
    enc_quality);
  encKbps: array [0 .. 2] of Integer = (3000, 5000, 8000);
  maxKbps: array [0 .. 2] of Integer = (8000, 10000, 12000);
  rc: array [0 .. 2] of RateControl = (CBR, CQP, VBR);
  scale: array [0 .. 3] of ScaleUsage = (scale_performance, scale_balance,
    scale_quality, scale_high_quality);
begin
  FillChar(config, Sizeof(TEncodeConfig), 0);

  config.usage := enc[EncUsage.ItemIndex];
  config.profile := profile_auto;
  config.rc := rc[RCMode.ItemIndex];
  config.encBitrate := encKbps[EncBitrate.ItemIndex];
  config.maxBitrate := maxKbps[MaxBitrate.ItemIndex];
  config.encQuality := 28;

  { enc frame rate, 0 same as input }
  if FrameRate.ItemIndex <> 0 then
  begin
    config.frameRate := VFormat.frameRate / 2;
  end;

  { video crop }
  if VideoCrop.ItemIndex <> 0 then
  begin
    config.cropX := 160;
    config.cropY := 120;
    config.cropWidth := 640;
    config.cropHeight := 480;
  end;

  { Video scale after crop }
  if VideoScale.ItemIndex <> 0 then
  begin
    config.scaleWidth := 1280;
    config.scaleHeight := 720;
  end;

  config.scale := scale[EncScale.ItemIndex];
end;

procedure TForm5.SubBrowseClick(Sender: TObject);
var
  str: string;
begin
  if SelectDirectory('', '', str) then
  begin
    SubDir.Text := str;
  end;
end;

procedure TForm5.Timer1Timer(Sender: TObject);
var
str: string;
status: TEncodeStatus;
begin
  if Dev.GetVideoEncodeStatus(0, status) then
  begin
    str := 'Input Frames:';
    str := str + IntToStr(status.inputFrameNum);
    str := str + ' (';
    str := str + FormatFloat('0.00', status.inputFrameRate);
    str := str + 'fps)';
    str := str + sLineBreak;
    str := str + 'Encode Frames:';
    str := str + IntToStr(status.encFrameNum);
    str := str + ' (';
    str := str + FormatFloat('0.00', status.encFrameRate);
    str := str + 'fps)';

    EncStatus.Text := str;
  end;
end;

end.
