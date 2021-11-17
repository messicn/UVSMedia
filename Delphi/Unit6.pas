unit Unit6;

interface

uses
  { Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ExtCtrls, Vcl.StdCtrls, UVSMedia; }
  Windows, Messages, SysUtils, Variants, Classes, Graphics,
  Controls, Forms, Dialogs, ExtCtrls, StdCtrls, UVSMedia;

type
  TForm6 = class(TForm)
    Video: TPanel;
    Flip: TCheckBox;
    Mirror: TCheckBox;
    AudioEnc: TCheckBox;
    Label1: TLabel;
    Label2: TLabel;
    Rotate: TComboBox;
    Scale: TComboBox;
    VideoCopy: TButton;
    Snapshot: TButton;
    VideoCallback: TButton;
    VideoLock: TButton;
    AudioCallback: TButton;
    AudioLock: TButton;
    EncCallback: TButton;
    AudioCopy: TButton;
    SaveDialog1: TSaveDialog;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure VideoCopyClick(Sender: TObject);
    procedure SnapshotClick(Sender: TObject);
    procedure EncCallbackClick(Sender: TObject);
    procedure VideoCallbackClick(Sender: TObject);
    procedure VideoLockClick(Sender: TObject);
    procedure AudioCopyClick(Sender: TObject);
    procedure AudioCallbackClick(Sender: TObject);
    procedure AudioLockClick(Sender: TObject);
  private
    { Private declarations }
    Dev: UVSDev;
    encStart, videoStart, audioStart: boolean;
    procedure PrintFrameInfo(var frame: TFrameInfo);
    procedure GetFrameConvert(var convert: TFrameConvert);
  public
    { Public declarations }
  end;

var
  Form6: TForm6;

implementation

{$R *.dfm}

procedure FrameCallback(obj: UVSObj; info: PFrameInfo; user: Pointer); stdcall;
begin
  Form6.PrintFrameInfo(info^);
end;

procedure TForm6.AudioCallbackClick(Sender: TObject);
begin
  if Dev.IsValid then
  begin
    if audioStart then
    begin
      Dev.SetAudioRawFrameCallback(nil);
    end
    else
    begin
      Dev.SetAudioRawFrameCallback(FrameCallback);
    end;

    audioStart := not audioStart;
    if audioStart then
    begin
      AudioCallback.Caption := 'Callback Stop';
    end
    else
    begin
      AudioCallback.Caption := 'Audio Frame Callback';
    end;
  end;
end;

procedure TForm6.AudioCopyClick(Sender: TObject);
var
  frame: TFrameInfo;
  buf: array of Byte;
begin
  if Dev.IsValid then
  begin
    FillChar(frame, Sizeof(TFrameInfo), 0);

    { copy to user buffer }
    SetLength(buf, 256 * 1024);
    frame.frameData := @buf[0];
    frame.dataLength := Length(buf);

    { copy to internal buffer }
    { frame.frameData := nil; frame.dataLength := 0; }

    if Dev.CopyAudioRawFrame(frame) then
    begin
      PrintFrameInfo(frame);
    end;
  end;
end;

procedure TForm6.AudioLockClick(Sender: TObject);
var
  frame: TFrameInfo;
begin
  if Dev.IsValid then
  begin
    if Dev.LockAudioRawFrame(frame) then
    begin
      PrintFrameInfo(frame);
      Dev.UnlockAudoRawFrame;
    end;
  end;
end;

procedure TForm6.EncCallbackClick(Sender: TObject);
const
  streamIndex = 0;
var
  config: TEncodeConfig;
begin
  if encStart then
  begin
    Dev.SetAudioEncFrameCallback(nil);
    Dev.SetVideoEncFrameCallback(0, nil);
    Dev.StopEncode(UVS_STREAM_ALL);
    encStart := False;
  end
  else
  begin
    FillChar(config, Sizeof(TEncodeConfig), 0);

    config.profile := profile_auto;
    config.rc := VBR;
    config.encBitrate := 3000;
    config.maxBitrate := 5000;
    config.encQuality := 28;

    { video stream config }
    if Dev.SetVideoEncode(streamIndex, codec_sw_h264, config) then
    begin
      if Dev.SetVideoEncFrameCallback(streamIndex, FrameCallback) then
      begin
        { audio stream config }
        if AudioEnc.Checked then
        begin
          if Dev.SetAudioProperty(codec_AAC) then
          begin
            Dev.SetAudioEncFrameCallback(FrameCallback);
          end;
        end;

        if Dev.StartEncode(streamIndex) then
        begin
          encStart := True;
        end;
      end;
    end;
  end;

  if encStart then
  begin
    EncCallback.Caption := 'Callback Stop';
  end
  else
  begin
    EncCallback.Caption := 'Encode Frame Callback';
  end;

end;

procedure TForm6.FormCreate(Sender: TObject);
var
  ret: boolean;
begin
  Dev := UVSDev.Create(0, 0, ret);

  if Dev.IsValid then
  begin
    Dev.DeviceStart;
  end;
end;

procedure TForm6.FormDestroy(Sender: TObject);
begin
  Dev.Free;
end;

procedure TForm6.FormShow(Sender: TObject);
begin
  Dev.StartPreview(Video.Handle);
end;

procedure TForm6.PrintFrameInfo(var frame: TFrameInfo);
const
  name: array [0 .. 26] of string = ('NONE', 'Video: YUY2', 'Video: UYVY',
    'Video: YV12', 'Video: I420', 'Video: NV12', 'Video: NV21', 'Video: I422',
    'Video: I444', 'Video: BGR24', 'Video: RGB24', 'Video: ARGB32',
    'Video: RGBA32', 'Video: ABGR32', 'Video: BGRA32', 'Video: MJPG',
    'Video: H.264(AVC) IDR', 'Video: H.264(AVC) I', 'Video: H.264(AVC) P',
    'Video: H.264(AVC) B', 'Video: H.265(HEVC) IDR', 'Video: H.265(HEVC) I',
    'Video: H.265(HEVC) P', 'Video: H.265(HEVC) B', 'Audio: PCM', 'Audio: MP3',
    'Audio: AAC');
var
  index: Integer;
  str: string;
begin
  index := 0;
  case frame.frame of
    video_YUY2: index := 1;
    video_UYVY: index := 2;
    video_YV12: index := 3;
    video_I420: index := 4;
    video_NV12: index := 5;
    video_NV21: index := 6;
    video_I422: index := 7;
    video_I444: index := 8;
    video_BGR24: index := 9;
    video_RGB24: index := 10;
    video_ARGB32: index := 11;
    video_RGBA32: index := 12;
    video_ABGR32: index := 13;
    video_BGRA32: index := 14;
    video_MJPG: index := 15;
    video_H264_IDR: index := 16;
    video_H264_I: index := 17;
    video_H264_P: index := 18;
    video_H264_B: index := 19;
    video_H265_IDR: index := 20;
    video_H265_I: index := 21;
    video_H265_P: index := 22;
    video_H265_B: index := 23;
    audio_PCM: index := 24;
    audio_MP3: index := 25;
    audio_AAC: index := 26;
  end;

  str := name[index];
  if index >= 24 then
  begin
    { audio }
    str := str + ' channels ' + IntToStr(frame.param.audioChannels);
    str := str + ' bits per sample ' + IntToStr(frame.param.audioBitsPerSample);
    str := str + ' samples per second ' +
      IntToStr(frame.param.audioSamplesPerSec);
    str := str + ' data ' + Format('%p', [frame.frameData]);
    str := str + ' size ' + IntToStr(frame.dataLength);
    str := str + ' ts ' + IntToStr(frame.timeStamp);
  end
  else if index > 0 then
  begin
    { video }
    str := str + ' width ' + IntToStr(frame.param.videoWidth);
    str := str + ' height ' + IntToStr(frame.param.videoHeight);
    str := str + ' stride ' + IntToStr(frame.param.videoDataStride[0]);
    str := str + ' ' + IntToStr(frame.param.videoDataStride[1]);
    str := str + ' data ' + Format('%p', [frame.frameData]);
    str := str + ' size ' + IntToStr(frame.dataLength);
    str := str + ' ts ' + IntToStr(frame.timeStamp);
  end;

  OutputDebugString(PWideChar(WideString(str)));
end;

procedure TForm6.SnapshotClick(Sender: TObject);
var
  convert: TFrameConvert;
begin
  if SaveDialog1.Execute then
  begin
    GetFrameConvert(convert);

    if convert.Mirror or convert.Flip or (convert.Rotate <> rotate_none) or
      ((convert.scaleWidth > 0) and (convert.scaleHeight > 0)) then
    begin
      Dev.SaveVideoSnapshot(PAnsiChar(AnsiString(SaveDialog1.FileName)),
        @convert);
    end
    else
    begin
      { without conversion }
      Dev.SaveVideoSnapshot(PAnsiChar(AnsiString(SaveDialog1.FileName)));
    end;
  end;
end;

procedure TForm6.GetFrameConvert(var convert: TFrameConvert);
const
  mode: array [0 .. 3] of RotateMode = (rotate_none, rotate_90, rotate_180,
    rotate_270);
  width: array [0 .. 2] of Integer = (0, 640, 3840);
  height: array [0 .. 2] of Integer = (0, 480, 2160);
begin
  FillChar(convert, sizeof(TFrameConvert), 0);

  { video mirror }
  convert.Mirror := Mirror.Checked;
  convert.Flip := Flip.Checked;

  { video rotate }
  convert.rotate := mode[Rotate.ItemIndex];

  { video scale }
  convert.usage := scale_performance;
  convert.scaleWidth := width[Scale.ItemIndex];
  convert.scaleHeight := height[Scale.ItemIndex];
end;

procedure TForm6.VideoCallbackClick(Sender: TObject);
begin
  if Dev.IsValid then
  begin
    if videoStart then
    begin
      Dev.SetVideoRawFrameCallback(nil);
    end
    else
    begin
      Dev.SetVideoRawFrameCallback(FrameCallback);
    end;

    videoStart := not videoStart;
    if videoStart then
    begin
      VideoCallback.Caption := 'Callback Stop';
    end
    else
    begin
      VideoCallback.Caption := 'Video Frame Callback';
    end;
  end;
end;

procedure TForm6.VideoCopyClick(Sender: TObject);
var
  frame: TFrameInfo;
  convert: TFrameConvert;
  buf: array of Byte;
begin
  if Dev.IsValid then
  begin

    GetFrameConvert(convert);

    FillChar(frame, Sizeof(TFrameInfo), 0);

    { copy to user buffer }
    SetLength(buf, 4 * 3840 * 2160);
    { copy data stride, 0 default }
    { frame.param.videoDataStride[0] := 0; frame.param.videoDataStride[1] := 0; }
    frame.frameData := @buf[0];
    frame.dataLength := Length(buf);

    { copy to internal buffer }
    { frame.frameData := nil; frame.dataLength := 0; }

    if convert.Mirror or convert.Flip or (convert.Rotate <> rotate_none) or
      ((convert.scaleWidth > 0) and (convert.scaleHeight > 0)) then
    begin
      if Dev.CopyVideoFrame(frame, @convert) then
      begin
        PrintFrameInfo(frame);
      end;
    end
    else if Dev.CopyVideoFrame(frame) then
    begin
      { without conversion }
      PrintFrameInfo(frame);
    end;
  end;
end;

procedure TForm6.VideoLockClick(Sender: TObject);
var
  frame: TFrameInfo;
begin
  if Dev.IsValid then
  begin
    if Dev.LockVideoRawFrame(frame) then
    begin
      PrintFrameInfo(frame);
      Dev.UnlockVideoRawFrame;
    end;
  end;
end;

end.
