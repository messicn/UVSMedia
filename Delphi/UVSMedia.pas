unit UVSMedia;

interface

uses
  { Winapi.Windows; }
  Windows;

const
  uvsdll = 'UVSMedia.dll';
  { Stream index all }
  UVS_STREAM_ALL = -1;
  { Error code }
  UVS_OK = 0;
  UVS_ERR = -1;
  UVS_ERR_OUTOFMEMORY = -2;
  UVS_ERR_INVALIDARG = -3;
  UVS_ERR_WAIT_TIMEOUT = -4;
  UVS_ERR_NOT_INITIALIZED = -5;
  UVS_ERR_NOT_ENOUGH_BUFFER = -6;
  UVS_ERR_NOT_READY = -7;
  UVS_ERR_NOT_SUPPORT = -8;
  UVS_ERR_FILE_OPEN = -9;
  UVS_ERR_ALREADY_EXISTS = -10;

type
  UVSObj = Pointer;

  {$Z4+}
  PropertyPage = (audio_source_filter, video_crossbar, video_source_filter,
    video_preview_pin, video_capture_pin);
  DrawMode = (draw_stretch, draw_center);
  DevState = (dev_run, dev_pause, dev_stop);
  VideoEffect = (video_brightness, video_contrast, video_hue, video_saturation,
    video_sharpness, video_gamma, video_gain);
  DisplayType = (direct_draw, direct_3d);
  AudioCodec = (codec_anone, codec_MP3, codec_AAC);
  VideoCodec = (codec_vnone, codec_hw_h264, codec_hw_h265, codec_hw_jpeg,
    codec_intel_h264, codec_intel_h265, codec_intel_jpeg, codec_nvidia_h264,
    codec_nvidia_h265, codec_sw_h264);
  TargetUsage = (enc_performance, enc_balance, enc_quality);
  CodecProfile = (profile_auto, profile_baseline, profile_main, profile_high);
  AVCEntropy = (entropy_CABAC, entropy_CAVLC);
  RateControl = (VBR, CBR, CQP, AVBR);
  RotateMode = (rotate_none, rotate_90, rotate_180, rotate_270);
  ScaleUsage = (scale_performance, scale_balance, scale_quality,
    scale_high_quality);
  FrameType = (frame_NONE, video_YUY2, video_UYVY, video_YV12, video_I420,
    video_NV12, video_NV21, video_I422, video_I444,
    video_BGR24, { BGR little endian (rgb in memory) }
    video_RGB24, { RGB little endian (bgr in memory) }
    video_ARGB32, { ARGB little endian (bgra in memory) }
    video_RGBA32, { RGBA little endian (abgr in memory) }
    video_ABGR32, { ABGR little endian (rgba in memory) }
    video_BGRA32, { BGRA little endian (argb in memory) }
    video_MJPG = 37, video_H264_IDR = 40, video_H264_I, video_H264_P,
    video_H264_B, video_H265_IDR = 50, video_H265_I, video_H265_P, video_H265_B,
    audio_PCM = 70, audio_MP3, audio_AAC);
  SourceType = (source_any, source_preview, source_capture);
  DevType = (dev_video_capture, dev_audio_capture, dev_audio_renderer);
  DevNotify = (dev_closed, dev_changed);
  OSDIndex = (base_osd_preview_enc, time_osd_preview_enc = 255,
    base_osd_preview_only, time_osd_preview_only = 511);
  FontStyle = (font_regular, font_bold, font_italic, font_bold_italic,
    font_underline = 4, { composite attribute }
    font_strikeout = 8, { composite attribute }
    font_cleartype = 16 { composite attribute, improves the readability of text on LCDs } );
  StringFormat = (string_regular, rect_multiple_lines = 1,
    direction_vertical = 2, direction_right_to_left = 4, align_near = 8,
    align_center = 16, align_far = 32, line_align_style_near = 64,
    line_align_style_center = 128, line_align_style_far = 256,
    trmming_character = 512, trmming_word = 1024,
    trmming_ellipsis_character = 2048, trmming_ellipsis_word = 4096,
    trmming_ellipsis_path = 8192);
  OSDCommand = (osd_enable, osd_delete, osd_delete_all, osd_get_count,
    osd_get_size, osd_get_position, osd_set_position, get_font_size,
    set_font_size, osd_get_color, osd_set_color, osd_get_opacity,
    osd_set_opacity, get_clip_position, set_clip_position, get_clip_size,
    set_clip_size, osd_get_blink, osd_set_blink);
  DashStyle = (solid, dash, dot, dash_dot);
  FilePosition = (file_begining, file_ending = -1);
  {$Z4-}

  TDevInfo = record
    szFriendlyDevName: array [0 .. 127] of AnsiChar;
  end;

  PDevInfo = ^TDevInfo;

  THardwareInfo = record
    dev, version: DWORD;
    date: array [0 .. 15] of AnsiChar;
    sn: array [0 .. 15] of Byte;
  end;

  PHardwareInfo = ^THardwareInfo;

  TAudioFormat = record
    frame: FrameType;
    audioChannels, samplesPreSec, bitsPreSample: Integer;
  end;

  PAudioFormat = ^TAudioFormat;

  TVideoFormat = record
    frame: FrameType;
    width, height: Integer;
    frameRate: Single;
  end;

  PVideoFormat = ^TVideoFormat;

  TFrameInfo = record
    frame: FrameType;

    param: record
      case Integer of
        0:
          (videoWidth, videoHeight: Word;
            videoDataStride: array [0 .. 1] of Word);
        1:
          (audioChannels, audioBitsPerSample: Word;
            audioSamplesPerSec: LongWord);
    end;

    dataLength: LongWord;
    timeStamp: Int64;
    frameData: PByte;
  end;

  PFrameInfo = ^TFrameInfo;

  TEncodeConfig = record
    usage: TargetUsage;
    profile: CodecProfile;
    avc: AVCEntropy; { AVC(h264) entropy coding mode }
    scale: ScaleUsage;
    scaleWidth, scaleHeight: Integer; { destination video width & height }
    cropX, cropY, cropWidth, cropHeight: Integer;
    frameRate: Single;
    rc: RateControl;
    encBitrate, maxBitrate: Integer; { kbits/sec }
    encQuality: Integer; { encoder quality(1 ~ 51) }
    GOP: Integer;
  end;

  PEncodeConfig = ^TEncodeConfig;

  TEncodeStatus = record
    inputFrameNum, encFrameNum: Integer;
    inputFrameRate, encFrameRate: Single;
  end;

  PEncodeStatus = ^TEncodeStatus;

  TFrameConvert = record
    frame: FrameType;
    mirror, flip: Bool;
    cropX, cropY, cropWidth, cropHeight: Integer;
    scaleWidth, scaleHeight: Integer;
    usage: ScaleUsage;
    rotate: RotateMode;
  end;

  PFrameConvert = ^TFrameConvert;

  TFileName = record
    szFilename: array [0 .. 259] of AnsiChar;
  end;

  PFileName = ^TFileName;

  TURLInfo = record
    szURL: array [0 .. 255] of AnsiChar;
  end;

  PURLInfo = ^TURLInfo;

  TFontInfo = record
    szFontName: array [0 .. 127] of AnsiChar;
    pointSize: Integer;
    style: FontStyle;
    format: StringFormat;
    textColor, backColor: COLORREF;
    textOpacity, backOpacity: Integer;
  end;

  PFontInfo = ^TFontInfo;

  TStyleInfo = record
    lineSize: Integer;
    style: DashStyle;
    lineColor, fillColor: COLORREF;
    lineOpacity, fillOpacity: Integer;
  end;

  PStyleInfo = ^TStyleInfo;

  TLineInfo = record
    lineSize: Integer;
    style: DashStyle;
    color: COLORREF;
    opacity: Integer;
  end;

  PLineInfo = ^TLineInfo;

  TRTPMulticast = record
    ipAddr: PAnsiChar;
    ipPort: Word;
  end;

  PRTPMulticast = ^TRTPMulticast;

  TMP4FileStatus = record
    aCodec: AudioCodec;
    vCodec: VideoCodec;
    audioDuration, videoDuration: Integer; { audio/video track duration in milliseconds }
    videoWidth, videoHeight: Integer;
    videoFrameRate: Single;
  end;

  PMP4FileStatus = ^TMP4FileStatus;

  TMP4FileTitle = record
    font: TFontInfo;
    x, y, width, height: Integer;
    imageOpacity: Integer;
    szImageFile, szText: PAnsiChar;
  end;

  PMP4FileTitle = ^TMP4FileTitle;

  TDevCallback = procedure(notify: DevNotify; info: PDevInfo; obj: UVSObj;
    user: Pointer); stdcall;
  TFrameCallback = procedure(obj: UVSObj; info: PFrameInfo;
    user: Pointer); stdcall;

  UVSDev = class
    dev: UVSObj;
  private
    function GetVolume: Integer;
    procedure SetVolume(n: Integer);
    function GetBalance: Integer;
    procedure SetBalance(n: Integer);

    function GetMirror: boolean;
    procedure SetMirror(n: boolean);
    function GetFlip: boolean;
    procedure SetFlip(n: boolean);

    function GetBrightness: Integer;
    procedure SetBrightness(n: Integer);
    function GetContrast: Integer;
    procedure SetContrast(n: Integer);
    function GetSaturation: Integer;
    procedure SetSaturation(n: Integer);
    function GetGamma: Integer;
    procedure SetGamma(n: Integer);

    function GetFreeze: boolean;
    procedure SetFreeze(n: boolean);

  public
    class function StrCopy(dest: PAnsiChar; const src: AnsiString): PAnsiChar;

    constructor Create; overload;
    constructor Create(videoIndex: Integer; audioIndex: Integer;
      var ret: boolean); overload;
    destructor Destroy; override;

    function IsValid:boolean;

    function DeviceOpen(videoDevIndex:Integer):boolean; overload;
    function DeviceOpen(var videoDevInfo:TDevInfo):boolean; overload;
    procedure DeviceClose;
    function GetDeviceInfo(var info:TDevInfo):boolean;

    function EnumAudioFormat(format:PAudioFormat; var num:Integer):boolean;
    function EnumVideoFormat(format:PVideoFormat; var num:Integer):boolean;

    function SetAudioDevice(audioDev:DevType; audioDevIndex: Integer)
      : boolean; overload;
    function SetAudioDevice(audioDev: DevType; var audioDevInfo: TDevInfo)
      : boolean; overload;

    function DeviceStart: boolean;
    function DevicePause: boolean;
    function DeviceStop: boolean;

    function GetAudioProperty(format: PAudioFormat;
      var codec: AudioCodec): boolean;
    function SetAudioProperty(codec: AudioCodec): boolean;

    function SetAudioMute(mute: boolean): boolean;

    property volume: Integer read GetVolume write SetVolume;
    property balance: Integer read GetBalance write SetBalance;

    function GetVideoProperty(var format: TVideoFormat): boolean;
    function GetVideoStatus(var signal:boolean; var mode:boolean): boolean;

    property mirror: boolean read GetMirror write SetMirror;
    property flip: boolean read GetFlip write SetFlip;

    function GetEffectRange(effect: VideoEffect; var minVal: Integer;
      var maxVal: Integer; var stepVal: Integer;
      var defaultVal: Integer): boolean;
    property brightness: Integer read GetBrightness write SetBrightness;
    property contrast: Integer read GetContrast write SetContrast;
    property saturation: Integer read GetSaturation write SetSaturation;
    property gamma: Integer read GetGamma write SetGamma;

    function GetVideoEncode(streamIndex:integer; var codec:VideoCodec;
      var config: TEncodeConfig): boolean;
    function SetVideoEncode(streamIndex: Integer; codec: VideoCodec;
      var config: TEncodeConfig): boolean;
    function RequestKeyframe(streamIndex: Integer): boolean;
    function GetVideoEncodeStatus(streamIndex: Integer;
      var status: TEncodeStatus): boolean;

    function StartEncode(streamIndex: Integer): boolean;
    function StopEncode(streamIndex: Integer): boolean;

    function SetRecordMetadata(streamIndex: Integer; szTitle: PAnsiChar;
      szComment: PAnsiChar = nil; szArtist: PAnsiChar = nil;
      szGenre: PAnsiChar = nil; szComposer: PAnsiChar = nil): boolean;
    function StartRecord(streamIndex: Integer; szFile1: PAnsiChar;
      szFile2: PAnsiChar; writeAudio: boolean; repairSupport: boolean;
      KBytes: LongWord = 0; MilliSec: LongWord = 0): boolean;
    function GetRecordFilename(streamIndex: Integer; filename: PFileName;
      var num: Integer): boolean;
    function PauseRecord(streamIndex: Integer; recResume: boolean;
      RequestKeyframe: boolean = True): boolean;
    function StopRecord(streamIndex: Integer): boolean;

    function StartPreview(wnd: HWND; disp: DisplayType=direct_3d): boolean;
    function SetPreviewRect(wndRect: PRect; cropRect: PRect;
  color: COLORREF): boolean;
    procedure StopPreview;
    property freeze: boolean read GetFreeze write SetFreeze;

    function SetTimeOSD(OSDIndex: Integer; x: Integer; y: Integer;
      szTimeFormat: PAnsiChar; var info: TFontInfo): boolean;
    function SetTextOSD(OSDIndex: Integer; x: Integer; y: Integer;
      width: Integer; height: Integer; szText: PAnsiChar;
      var info: TFontInfo): boolean;
    function SetImageOSD(OSDIndex: Integer; x: Integer; y: Integer;
      width: Integer; height: Integer; opacity: Integer;
      szFile: PAnsiChar): boolean;
    function SetRectOSD(OSDIndex: Integer; x: Integer; y: Integer;
      width: Integer; height: Integer; var info: TStyleInfo): boolean;
    function SetEllipseOSD(OSDIndex: Integer; x: Integer; y: Integer;
      width: Integer; height: Integer; var info: TStyleInfo): boolean;
    function SetLineOSD(OSDIndex: Integer; x0: Integer; y0: Integer;
      x1: Integer; y1: Integer; var info: TLineInfo): boolean;
    function OSDControl(OSDIndex: Integer; cmd: OSDCommand;
      param0: PInteger = nil; param1: PInteger = nil): boolean;

    function SetVideoRawFrameCallback(cb: TFrameCallback;
      user: Pointer = nil): boolean;
    function SetVideoEncFrameCallback(streamIndex: Integer; cb: TFrameCallback;
      user: Pointer = nil): boolean;
    function SaveVideoSnapshot(szFilename: PAnsiChar;
      convert: PFrameConvert = nil; jpgQuality: LongWord = 100): boolean;
    function LockVideoRawFrame(var frame: TFrameInfo;
      waitMilliSec: LongWord = 1000): boolean;
    function UnlockVideoRawFrame: boolean;
    function CopyVideoFrame(var frame: TFrameInfo; convert: PFrameConvert = nil;
      waitMilliSec: LongWord = 1000): boolean;

    function SetAudioRawFrameCallback(cb: TFrameCallback;
      user: Pointer = nil): boolean;
    function SetAudioEncFrameCallback(cb: TFrameCallback;
      user: Pointer = nil): boolean;
    function LockAudioRawFrame(var frame: TFrameInfo;
      waitMilliSec: LongWord = 1000): boolean;
    function UnlockAudoRawFrame: boolean;
    function CopyAudioRawFrame(var frame: TFrameInfo;
      waitMilliSec: LongWord = 1000): boolean;

    { RTSP server must be created }
    function RTSPStart(streamIndex: Integer; rtspPort: Word; hasAudio: boolean;
      szSessionName: PAnsiChar; multicast: PRTPMulticast = nil): boolean;
    function RTSPStop(streamIndex: Integer): boolean;
    function RTSPGetURL(streamIndex: Integer; var url: TURLInfo): boolean;

    function RTMPSend(streamIndex: Integer; szURL: PAnsiChar;
      hasAudio: boolean): boolean;
    function RTMPStop(streamIndex: Integer): boolean;
    function RTMPGetURL(streamIndex: Integer; var url: TURLInfo): boolean;

    function NDICreate(szSourceName: PAnsiChar; szGroupName: PAnsiChar = nil;
      szXMLMetaData: PAnsiChar = nil; isAsync: boolean = True): boolean;
    function NDIConfig(convert: PFrameConvert;
      skipFrameRate: Integer = 0): boolean;
    function NDIStart(hasAudio: boolean): boolean;
    function NDIStop: boolean;
    function NDIDestroy: boolean;
  end;

function uvs_media_init(flags: Integer): Integer; stdcall; external uvsdll;
procedure uvs_media_exit; stdcall; external uvsdll;
function uvs_get_version: Integer; stdcall; external uvsdll;

function uvs_enum_device(dev: DevType; info: PDevInfo; var num: Integer)
  : Integer; stdcall; external uvsdll;
function uvs_set_device_callback(cb: TDevCallback; user: Pointer): Integer;
  stdcall; external uvsdll;
function uvs_get_device_count: Integer; stdcall; external uvsdll;

function uvs_query_video_encoder(dev: UVSObj; codec: VideoCodec): Integer;
  stdcall; external uvsdll;
function uvs_calc_buffer_size(frame: FrameType; width: Integer; height: Integer;
  stride: Integer): Integer; stdcall; external uvsdll;

function uvs_create_frame(frame: FrameType; width: Integer; height: Integer;
  stride: Integer; var info: TFrameInfo): Integer; stdcall; external uvsdll;
function uvs_destroy_frame(var frame: TFrameInfo): Integer; stdcall; external uvsdll;

function uvs_set_nosignal_image(imageFile: PAnsiChar; draw: DrawMode;
  backColor: COLORREF): Integer; stdcall; external uvsdll;

function uvs_dev_open(var info: TDevInfo; var ret: Integer): UVSObj; stdcall;
  external uvsdll;
function uvs_dev_close(dev: UVSObj): Integer; stdcall; external uvsdll;
function uvs_get_dev_info(dev: UVSObj; var info: TDevInfo): Integer; stdcall;
  external uvsdll;

function uvs_query_hardware_info(dev: UVSObj; var info: THardwareInfo): Integer;
  stdcall; external uvsdll;
function uvs_enum_audio_format(dev: UVSObj; format: PAudioFormat;
  var num: Integer): Integer; stdcall; external uvsdll;
function uvs_enum_video_format(dev: UVSObj; source: SourceType;
  format: PVideoFormat; var num: Integer): Integer; stdcall; external uvsdll;

function uvs_set_audio_device(dev: UVSObj; audio: DevType; var info: TDevInfo)
  : Integer; stdcall; external uvsdll;
function uvs_create_property_page(dev: UVSObj; page: PropertyPage; owner: HWND;
  x: Integer; y: Integer; szCaption: PAnsiChar): Integer; stdcall;
  external uvsdll;

function uvs_dev_control(dev: UVSObj; state: DevState): Integer; stdcall;
  external uvsdll;

function uvs_get_audio_property(dev: UVSObj; format: PAudioFormat;
  var codec: AudioCodec): Integer; stdcall; external uvsdll;
function uvs_set_audio_property(dev: UVSObj; format: PAudioFormat;
  codec: AudioCodec): Integer; stdcall; external uvsdll;

function uvs_set_audio_mute(dev: UVSObj; mute: Bool): Integer; stdcall;
  external uvsdll;
function uvs_get_audio_volume(dev: UVSObj; var volume: Integer): Integer;
  stdcall; external uvsdll;
function uvs_set_audio_volume(dev: UVSObj; volume: Integer): Integer; stdcall;
  external uvsdll;
function uvs_get_audio_balance(dev: UVSObj; var balance: Integer): Integer;
  stdcall; external uvsdll;
function uvs_set_audio_balance(dev: UVSObj; balance: Integer): Integer;
  stdcall; external uvsdll;

function uvs_get_video_input(dev: UVSObj; var index: Integer;
  var input: Integer; var num: Integer): Integer; stdcall; external uvsdll;
function uvs_set_video_input(dev: UVSObj; index: Integer): Integer; stdcall;
  external uvsdll;

function uvs_get_video_property(dev: UVSObj; source: SourceType;
  var format: TVideoFormat): Integer; stdcall; external uvsdll;
function uvs_set_video_property(dev: UVSObj; source: SourceType;
  var format: TVideoFormat): Integer; stdcall; external uvsdll;

function uvs_get_video_mirror(dev: UVSObj; var horizontal: Bool;
  var vertical: Bool): Integer; stdcall; external uvsdll;
function uvs_set_video_mirror(dev: UVSObj; horizontal: Bool;
  vertical: Bool): Integer; stdcall; external uvsdll;
function uvs_get_video_status(dev: UVSObj; var signal: Bool;
  var mode: Bool): Integer; stdcall; external uvsdll;

function uvs_get_video_effect_range(dev: UVSObj; effect: VideoEffect;
  var minVal: Integer; var maxVal: Integer; var step: Integer;
  var defaultVal: Integer): Integer; stdcall; external uvsdll;
function uvs_get_video_effect(dev: UVSObj; effect: VideoEffect;
  var val: Integer): Integer; stdcall; external uvsdll;
function uvs_set_video_effect(dev: UVSObj; effect: VideoEffect; val: Integer)
  : Integer; stdcall; external uvsdll;

function uvs_set_video_encode_config(dev: UVSObj; streamIndex: Integer;
  codec: VideoCodec; var config: TEncodeConfig): Integer; stdcall; external uvsdll;
function uvs_get_video_encode_config(dev: UVSObj; streamIndex: Integer;
  var codec: VideoCodec; var config: TEncodeConfig): Integer; stdcall;
  external uvsdll;

function uvs_request_video_key_frame(dev: UVSObj; streamIndex: Integer)
  : Integer; stdcall; external uvsdll;
function uvs_get_video_encode_status(dev: UVSObj; streamIndex: Integer;
  var status: TEncodeStatus): Integer; stdcall; external uvsdll;

function uvs_start_encode(dev: UVSObj; streamIndex: Integer): Integer; stdcall;
  external uvsdll;
function uvs_stop_encode(dev: UVSObj; streamIndex: Integer): Integer; stdcall;
  external uvsdll;

function uvs_set_record_metadata(dev: UVSObj; streamIndex: Integer;
  szTitle: PAnsiChar; szComment: PAnsiChar; szArtist: PAnsiChar;
  szGenre: PAnsiChar; szComposer: PAnsiChar): Integer; stdcall; external uvsdll;
function uvs_start_record(dev: UVSObj; streamIndex: Integer;
  szFile1: PAnsiChar; szFile2: PAnsiChar; writeAudio: Bool;
  repairSupport: Bool; KBytes: LongWord; MilliSec: LongWord): Integer;
  stdcall; external uvsdll;
function uvs_get_record_filename(dev: UVSObj; streamIndex: Integer;
  filename: PFileName; var num: Integer): Integer; stdcall; external uvsdll;
function uvs_pause_record(dev: UVSObj; streamIndex: Integer;
  recResume: Bool; requestKeyframe: Bool): Integer; stdcall;
  external uvsdll;
function uvs_stop_record(dev: UVSObj; streamIndex: Integer): Integer; stdcall;
  external uvsdll;

function uvs_start_preview(dev: UVSObj; wnd: HWND; disp: DisplayType): Integer;
  stdcall; external uvsdll;
function uvs_get_preview_freeze(dev: UVSObj; var freeze: Bool): Integer;
  stdcall; external uvsdll;
function uvs_set_preview_freeze(dev: UVSObj; freeze: Bool): Integer;
  stdcall; external uvsdll;
function uvs_set_preview_rect(dev: UVSObj; wndRect: PRect; cropRect: PRect;
  color: COLORREF): Integer; stdcall; external uvsdll;
function uvs_stop_preview(dev: UVSObj): Integer; stdcall; external uvsdll;

function uvs_set_time_osd(dev: UVSObj; OSDIndex: Integer; x: Integer;
  y: Integer; szTimeFormat: PAnsiChar; var info: TFontInfo): Integer; stdcall;
  external uvsdll;
function uvs_set_text_osd(dev: UVSObj; OSDIndex: Integer; x: Integer;
  y: Integer; width: Integer; height: Integer; szText: PAnsiChar;
  var info: TFontInfo): Integer; stdcall; external uvsdll;
function uvs_set_image_osd(dev: UVSObj; OSDIndex: Integer; x: Integer;
  y: Integer; width: Integer; height: Integer; opacity: Integer;
  szFile: PAnsiChar): Integer; stdcall; external uvsdll;
function uvs_set_rect_osd(dev: UVSObj; OSDIndex: Integer; x: Integer;
  y: Integer; width: Integer; height: Integer; var info: TStyleInfo): Integer;
  stdcall; external uvsdll;
function uvs_set_ellipse_osd(dev: UVSObj; OSDIndex: Integer; x: Integer;
  y: Integer; width: Integer; height: Integer; var info: TStyleInfo): Integer;
  stdcall; external uvsdll;
function uvs_set_line_osd(dev: UVSObj; OSDIndex: Integer; x0: Integer;
  y0: Integer; x1: Integer; y1: Integer; var info: TLineInfo): Integer; stdcall;
  external uvsdll;
function uvs_osd_control(dev: UVSObj; OSDIndex: Integer; cmd: OSDCommand;
  param0: PInteger; param1: PInteger): Integer; stdcall; external uvsdll;

function uvs_create_frame_preview(wnd: HWND; disp: DisplayType): UVSObj;
  stdcall; external uvsdll;
function uvs_frame_preview(obj: UVSObj; var frame: TFrameInfo): Integer; stdcall;
  external uvsdll;
function uvs_set_frame_preview_rect(obj: UVSObj; wndRect: PRECT;
  cropRect: PRECT; color: COLORREF): Integer; stdcall; external uvsdll;
function uvs_destroy_frame_preview(obj: UVSObj): Integer; stdcall;
  external uvsdll;

function uvs_set_video_raw_frame_callback(dev: UVSObj; cb: TFrameCallback;
  user: Pointer): Integer; stdcall; external uvsdll;
function uvs_set_video_enc_frame_callback(dev: UVSObj; streamIndex: Integer;
  cb: TFrameCallback; user: Pointer): Integer; stdcall; external uvsdll;

function uvs_convert_video_frame(var convert: TFrameConvert; var src: TFrameInfo;
  var dest: TFrameInfo): Integer; stdcall; external uvsdll;
function uvs_save_video_frame(szFilename: PAnsiChar; convert: PFrameConvert;
  var frame: TFrameInfo; jpgQuality: LongWord): Integer; stdcall; external uvsdll;
function uvs_save_video_snapshot(dev: UVSObj; szFilename: PAnsiChar;
  convert: PFrameConvert; jpgQuality: LongWord): Integer; stdcall;
  external uvsdll;

function uvs_lock_video_raw_frame(dev: UVSObj; var frame: TFrameInfo;
  waitMilliSec: LongWord): Integer; stdcall; external uvsdll;
function uvs_unlock_video_raw_frame(dev: UVSObj): Integer; stdcall;
  external uvsdll;
function uvs_copy_video_frame(dev: UVSObj; convert: PFrameConvert;
  var frame: TFrameInfo; waitMilliSec: LongWord): Integer; stdcall; external uvsdll;

function uvs_set_audio_raw_frame_callback(dev: UVSObj; cb: TFrameCallback;
  user: Pointer): Integer; stdcall; external uvsdll;
function uvs_set_audio_enc_frame_callback(dev: UVSObj; cb: TFrameCallback;
  user: Pointer): Integer; stdcall; external uvsdll;

function uvs_lock_audio_raw_frame(dev: UVSObj; var frame: TFrameInfo;
  waitMilliSec: LongWord): Integer; stdcall; external uvsdll;
function uvs_unlock_audio_raw_frame(dev: UVSObj): Integer; stdcall;
  external uvsdll;
function uvs_copy_audio_raw_frame(dev: UVSObj; var frame: TFrameInfo;
  waitMilliSec: LongWord): Integer; stdcall; external uvsdll;

function uvs_media_server_rtsp_create(rtspPort: Word; httpTunnerPort: Word;
  szUsername: PAnsiChar; szPassword: PAnsiChar): Integer; stdcall;
  external uvsdll;
function uvs_media_server_rtsp_destroy(rtspPort: Word): Integer; stdcall;
  external uvsdll;

function uvs_media_stream_rtsp_start(dev: UVSObj; streamIndex: Integer;
  rtspPort: Word; hasAudio: Bool; szSessionName: PAnsiChar;
  multicast: PRTPMulticast): Integer; stdcall; external uvsdll;
function uvs_media_stream_rtsp_stop(dev: UVSObj; streamIndex: Integer)
  : Integer; stdcall; external uvsdll;
function uvs_media_stream_rtsp_get_url(dev: UVSObj; streamIndex: Integer;
var url: TURLInfo): Integer; stdcall; external uvsdll;

function uvs_media_file_rtsp_start(szFilename: PAnsiChar; rtspPort: Word;
  hasAudio: Bool; szSessionName: PAnsiChar): Integer; stdcall;
  external uvsdll;
function uvs_media_file_rtsp_stop(szFilename: PAnsiChar): Integer; stdcall;
  external uvsdll;
function uvs_media_file_rtsp_get_url(szFilename: PAnsiChar; var url: TURLInfo)
  : Integer; stdcall; external uvsdll;

function uvs_media_stream_rtmp_send(dev: UVSObj; streamIndex: Integer;
  szURL: PAnsiChar; hasAudio: Bool): Integer; stdcall; external uvsdll;
function uvs_media_stream_rtmp_stop(dev: UVSObj; streamIndex: Integer)
  : Integer; stdcall; external uvsdll;
function uvs_media_stream_rtmp_get_send_url(dev: UVSObj; streamIndex: Integer;
  var url: TURLInfo): Integer; stdcall; external uvsdll;

function uvs_media_file_rtmp_send(szFilename: PAnsiChar; szURL: PAnsiChar;
  hasAudio: Bool): Integer; stdcall; external uvsdll;
function uvs_media_file_rtmp_get_progress(szFilename: PAnsiChar;
  var progress: Integer): Integer; stdcall; external uvsdll;
function uvs_media_file_rtmp_stop(szFilename: PAnsiChar): Integer; stdcall;
  external uvsdll;
function uvs_media_file_rtmp_get_send_url(szFilename: PAnsiChar; var url: TURLInfo)
  : Integer; stdcall; external uvsdll;

function uvs_media_stream_ndi_create(dev: UVSObj; szSourceName: PAnsiChar;
  szGroupName: PAnsiChar; szXMLMetaData: PAnsiChar; isAsync: Bool): Integer;
  stdcall; external uvsdll;
function uvs_media_stream_ndi_config(dev: UVSObj; convert: PFrameConvert;
  skipFrameRate: Integer): Integer; stdcall; external uvsdll;
function uvs_media_stream_ndi_start(dev: UVSObj; hasAudio: Bool): Integer;
  stdcall; external uvsdll;
function uvs_media_stream_ndi_stop(dev: UVSObj): Integer; stdcall;
  external uvsdll;
function uvs_media_stream_ndi_destroy(dev: UVSObj): Integer; stdcall;
  external uvsdll;

function uvs_mp4_file_get_status(szFilename: PAnsiChar; var status: TMP4FileStatus)
  : Integer; stdcall; external uvsdll;
function uvs_mp4_file_repair(szFilename: PAnsiChar; szNewFilename: PAnsiChar)
  : Integer; stdcall; external uvsdll;
function uvs_mp4_file_repair_cancel: Integer; stdcall; external uvsdll;
function uvs_mp4_file_get_repair_progress(var progress: Integer): Integer;
  stdcall; external uvsdll;
function uvs_mp4_file_cut(szFilename: PAnsiChar; beginMilliSec: Integer;
  endMilliSec: Integer; szNewFilename: PAnsiChar): Integer; stdcall;
  external uvsdll;
function uvs_mp4_file_get_cut_progress(var progress: Integer): Integer; stdcall;
  external uvsdll;
function uvs_mp4_file_add_title(szFilename: PAnsiChar; beginMilliSec: Integer;
  title: PMP4FileTitle; num: Integer; titleMilliSec: Integer;
  szNewFilename: PAnsiChar): Integer; stdcall; external uvsdll;
function uvs_mp4_file_get_title_progress(var progress: Integer): Integer;
  stdcall; external uvsdll;
function uvs_mp4_file_merge(szFilename: PPAnsiChar; num: Integer;
  szNewFilename: PAnsiChar): Integer; stdcall; external uvsdll;
function uvs_mp4_file_get_merge_progress(var progress: Integer): Integer;
  stdcall; external uvsdll;

implementation

class function UVSDev.StrCopy(dest: PAnsiChar; const src: AnsiString): PAnsiChar;
begin
  Move(PAnsiChar(src)^, dest^, Length(src) + 1);
  Result := dest;
end;

constructor UVSDev.Create;
begin
  inherited;
  uvs_media_init(0);
end;

constructor UVSDev.Create(videoIndex: Integer; audioIndex: Integer;
  var ret: boolean);
begin
  Create;

  ret := DeviceOpen(videoIndex);
  if ret then
  begin
    if audioIndex >= 0 then
    begin
      ret := SetAudioDevice(dev_audio_capture, audioIndex);
    end;
  end;
end;

destructor UVSDev.Destroy;
begin
  DeviceClose;
  uvs_media_exit();
  inherited;
end;

function UVSDev.IsValid: boolean;
begin
  Result := Assigned(dev);
end;

function UVSDev.DeviceOpen(videoDevIndex: Integer): boolean;
var
  num: Integer;
  info: array [0 .. 15] of TDevInfo;
begin
  DeviceClose;

  if videoDevIndex >= 0 then
  begin
    num := Length(info);
    if uvs_enum_device(dev_video_capture, @info[0], num) = UVS_OK then
    begin
      if videoDevIndex < num then
      begin
        Result := DeviceOpen(info[videoDevIndex]);
        exit;
      end;
    end;
  end;
  Result := False;
end;

function UVSDev.DeviceOpen(var videoDevInfo: TDevInfo): boolean;
var
  r: Integer;
begin
  DeviceClose;
  dev := uvs_dev_open(videoDevInfo, r);
  Result := r = UVS_OK;
end;

procedure UVSDev.DeviceClose;
begin
  if IsValid then
  begin
    uvs_dev_close(dev);
    dev := nil;
  end;
end;

function UVSDev.GetDeviceInfo(var info: TDevInfo): boolean;
begin
  Result := uvs_get_dev_info(dev, info) = UVS_OK;
end;

function UVSDev.EnumAudioFormat(format: PAudioFormat; var num: Integer)
  : boolean;
begin
  Result := uvs_enum_audio_format(dev, format, num) = UVS_OK;
end;

function UVSDev.EnumVideoFormat(format: PVideoFormat; var num: Integer)
  : boolean;
begin
  Result := uvs_enum_video_format(dev, source_any, format, num) = UVS_OK;
end;

function UVSDev.SetAudioDevice(audioDev: DevType;
  audioDevIndex: Integer): boolean;
var
  num: Integer;
  info: array [0 .. 15] of TDevInfo;
begin
  if IsValid then
  begin
    num := Length(info);
    if uvs_enum_device(audioDev, @info[0], num) = UVS_OK then
    begin
      if (audioDevIndex >= 0) and (audioDevIndex < num) then
      begin
        Result := SetAudioDevice(audioDev, info[audioDevIndex]);
        exit;
      end;
    end;
  end;
  Result := False;
end;

function UVSDev.SetAudioDevice(audioDev: DevType;
  var audioDevInfo: TDevInfo): boolean;
begin
  Result := uvs_set_audio_device(dev, audioDev, audioDevInfo) = UVS_OK;
end;

function UVSDev.DeviceStart: boolean;
begin
  Result := uvs_dev_control(dev, dev_run) = UVS_OK;
end;

function UVSDev.DevicePause: boolean;
begin
  Result := uvs_dev_control(dev, dev_pause) = UVS_OK;
end;

function UVSDev.DeviceStop: boolean;
begin
  Result := uvs_dev_control(dev, dev_stop) = UVS_OK;
end;

function UVSDev.GetAudioProperty(format: PAudioFormat;
  var codec: AudioCodec): boolean;
begin
  Result := uvs_get_audio_property(dev, format, codec) = UVS_OK;
end;

function UVSDev.SetAudioProperty(codec: AudioCodec): boolean;
begin

  Result := uvs_set_audio_property(dev, nil, codec) = UVS_OK;
end;

function UVSDev.SetAudioMute(mute: boolean): boolean;
begin
  Result := uvs_set_audio_mute(dev, mute) = UVS_OK;
end;

function UVSDev.GetVolume: Integer;
var
  n: Integer;
begin
  if uvs_get_audio_volume(dev, n) = UVS_OK then
  begin
    Result := n;
  end
  else
  begin
    Result := 0;
  end;
end;

procedure UVSDev.SetVolume(n: Integer);
begin
  uvs_set_audio_volume(dev, n);
end;

function UVSDev.GetBalance: Integer;
var
  n: Integer;
begin
  if uvs_get_audio_balance(dev, n) = UVS_OK then
  begin
    Result := n;
  end
  else
  begin
    Result := 0;
  end;
end;

procedure UVSDev.SetBalance(n: Integer);
begin
  uvs_set_audio_balance(dev, n);
end;

function UVSDev.GetMirror: boolean;
var
  flags: array [0 .. 1] of Bool;
begin
  if uvs_get_video_mirror(dev, flags[0], flags[1]) = UVS_OK then
  begin
    Result := flags[0];
  end
  else
  begin
    Result := False;
  end;
end;

procedure UVSDev.SetMirror(n: boolean);
var
  flags: array [0 .. 1] of Bool;
begin
  flags[0] := n;
  flags[1] := flip;
  uvs_set_video_mirror(dev, flags[0], flags[1]);
end;

function UVSDev.GetFlip: boolean;
var
  flags: array [0 .. 1] of Bool;
begin
  if uvs_get_video_mirror(dev, flags[0], flags[1]) = UVS_OK then
  begin
    Result := flags[1];
  end
  else
  begin
    Result := False;
  end;
end;

procedure UVSDev.SetFlip(n: boolean);
var
  flags: array [0 .. 1] of Bool;
begin
  flags[0] := mirror;
  flags[1] := n;
  uvs_set_video_mirror(dev, flags[0], flags[1]);
end;

function UVSDev.GetVideoProperty(var format: TVideoFormat): boolean;
begin
  Result := uvs_get_video_property(dev, source_any, format) = UVS_OK;
end;

function UVSDev.GetVideoStatus(var signal: Boolean; var mode: Boolean): boolean;
var
  flags: array [0 .. 1] of Bool;
begin
  Result := uvs_get_video_status(dev, flags[0], flags[1]) = UVS_OK;
  if Result then
  begin
    signal := flags[0];
    mode := flags[1];
  end
  else
  begin
    signal := False;
    mode := False;
  end;
end;

function UVSDev.GetEffectRange(effect: VideoEffect; var minVal: Integer;
  var maxVal: Integer; var stepVal: Integer; var defaultVal: Integer): boolean;
begin
  Result := uvs_get_video_effect_range(dev, effect, minVal, maxVal, stepVal,
    defaultVal) = UVS_OK;
end;

function UVSDev.GetBrightness: Integer;
var
  n: Integer;
begin
  if uvs_get_video_effect(dev, video_brightness, n) = UVS_OK then
  begin
    Result := n;
  end
  else
  begin
    Result := 0;
  end;
end;

procedure UVSDev.SetBrightness(n: Integer);
begin
  uvs_set_video_effect(dev, video_brightness, n);
end;

function UVSDev.GetContrast: Integer;
var
  n: Integer;
begin
  if uvs_get_video_effect(dev, video_contrast, n) = UVS_OK then
  begin
    Result := n;
  end
  else
  begin
    Result := 0;
  end;
end;

procedure UVSDev.SetContrast(n: Integer);
begin
  uvs_set_video_effect(dev, video_contrast, n);
end;

function UVSDev.GetSaturation: Integer;
var
  n: Integer;
begin
  if uvs_get_video_effect(dev, video_saturation, n) = UVS_OK then
  begin
    Result := n;
  end
  else
  begin
    Result := 0;
  end;
end;

procedure UVSDev.SetSaturation(n: Integer);
begin
  uvs_set_video_effect(dev, video_saturation, n);
end;

function UVSDev.GetGamma: Integer;
var
  n: Integer;
begin
  if uvs_get_video_effect(dev, video_gamma, n) = UVS_OK then
  begin
    Result := n;
  end
  else
  begin
    Result := 0;
  end;
end;

procedure UVSDev.SetGamma(n: Integer);
begin
  uvs_set_video_effect(dev, video_gamma, n);
end;

function UVSDev.GetVideoEncode(streamIndex: Integer; var codec: VideoCodec; var config: TEncodeConfig): boolean;
begin
   Result := uvs_get_video_encode_config(dev, streamIndex, codec, config) = UVS_OK;
end;

function UVSDev.SetVideoEncode(streamIndex: Integer; codec: VideoCodec; var config: TEncodeConfig): boolean;
begin
   Result := uvs_set_video_encode_config(dev, streamIndex, codec, config) = UVS_OK;
end;

function UVSDev.RequestKeyframe(streamIndex: Integer): boolean;
begin
  Result := uvs_request_video_key_frame(dev, streamIndex) = UVS_OK;
end;

function UVSDev.GetVideoEncodeStatus(streamIndex: Integer; var status: TEncodeStatus): boolean;
begin
   Result := uvs_get_video_encode_status(dev, streamIndex, status) = UVS_OK;
end;

function UVSDev.StartEncode(streamIndex: Integer): boolean;
begin
  Result := uvs_start_encode(dev, streamIndex) = UVS_OK;
end;

function UVSDev.StopEncode(streamIndex: Integer): boolean;
begin
  Result := uvs_stop_encode(dev, streamIndex) = UVS_OK;
end;

function UVSDev.SetRecordMetadata(streamIndex: Integer; szTitle: PAnsiChar;
  szComment: PAnsiChar; szArtist: PAnsiChar; szGenre: PAnsiChar;
  szComposer: PAnsiChar): boolean;
begin
  Result := uvs_set_record_metadata(dev, streamIndex, szTitle, szComment,
    szArtist, szGenre, szComposer) = UVS_OK;
end;

function UVSDev.StartRecord(streamIndex: Integer; szFile1: PAnsiChar;
  szFile2: PAnsiChar; writeAudio: boolean; repairSupport: boolean;
  KBytes: LongWord; MilliSec: LongWord): boolean;
begin
  Result := uvs_start_record(dev, streamIndex, szFile1, szFile2, writeAudio,
    repairSupport, KBytes, MilliSec) = UVS_OK;
end;

function UVSDev.GetRecordFilename(streamIndex: Integer; filename: PFileName;
  var num: Integer): boolean;
begin
  Result := uvs_get_record_filename(dev, streamIndex, filename, num) = UVS_OK;
end;

function UVSDev.PauseRecord(streamIndex: Integer; recResume: boolean;
  RequestKeyframe: boolean): boolean;
begin
  Result := uvs_pause_record(dev, streamIndex, recResume,
    RequestKeyframe) = UVS_OK;
end;

function UVSDev.StopRecord(streamIndex: Integer): boolean;
begin
  Result := uvs_stop_record(dev, streamIndex) = UVS_OK;
end;

function UVSDev.StartPreview(wnd: HWND; disp: DisplayType): boolean;
begin
  Result := uvs_start_preview(dev, wnd, disp) = UVS_OK;
end;

function UVSDev.SetPreviewRect(wndRect: PRect; cropRect: PRect; color: COLORREF): boolean;
begin
  Result := uvs_set_preview_rect(dev, wndRect, cropRect, color) = UVS_OK;
end;

procedure UVSDev.StopPreview;
begin
  uvs_stop_preview(dev);
end;

function UVSDev.GetFreeze: boolean;
var
  flag: Bool;
begin
  if uvs_get_preview_freeze(dev, flag) = UVS_OK then
  begin
    Result := flag;
  end
  else
  begin
    Result := False;
  end;
end;

procedure UVSDev.SetFreeze(n: boolean);
begin
  uvs_set_preview_freeze(dev, n);
end;

function UVSDev.SetTimeOSD(OSDIndex: Integer; x: Integer; y: Integer;
  szTimeFormat: PAnsiChar; var info: TFontInfo): boolean;
begin
  Result := uvs_set_time_osd(dev, OSDIndex, x, y, szTimeFormat, info) = UVS_OK;
end;

function UVSDev.SetTextOSD(OSDIndex: Integer; x: Integer; y: Integer;
  width: Integer; height: Integer; szText: PAnsiChar;
  var info: TFontInfo): boolean;
begin
  Result := uvs_set_text_osd(dev, OSDIndex, x, y, width, height, szText,
    info) = UVS_OK;
end;

function UVSDev.SetImageOSD(OSDIndex: Integer; x: Integer; y: Integer;
  width: Integer; height: Integer; opacity: Integer; szFile: PAnsiChar)
  : boolean;
begin
  Result := uvs_set_image_osd(dev, OSDIndex, x, y, width, height, opacity,
    szFile) = UVS_OK;
end;

function UVSDev.SetRectOSD(OSDIndex: Integer; x: Integer; y: Integer;
  width: Integer; height: Integer; var info: TStyleInfo): boolean;
begin
  Result := uvs_set_rect_osd(dev, OSDIndex, x, y, width, height, info) = UVS_OK;
end;

function UVSDev.SetEllipseOSD(OSDIndex: Integer; x: Integer; y: Integer;
  width: Integer; height: Integer; var info: TStyleInfo): boolean;
begin
  Result := uvs_set_ellipse_osd(dev, OSDIndex, x, y, width, height,
    info) = UVS_OK;
end;

function UVSDev.SetLineOSD(OSDIndex: Integer; x0: Integer; y0: Integer;
  x1: Integer; y1: Integer; var info: TLineInfo): boolean;
begin
  Result := uvs_set_line_osd(dev, OSDIndex, x0, y0, x1, y1, info) = UVS_OK;
end;

function UVSDev.OSDControl(OSDIndex: Integer; cmd: OSDCommand; param0: PInteger;
  param1: PInteger): boolean;
begin
  Result := uvs_osd_control(dev, OSDIndex, cmd, param0, param1) = UVS_OK;
end;

function UVSDev.SetVideoRawFrameCallback(cb: TFrameCallback;
  user: Pointer): boolean;
begin
  Result := uvs_set_video_raw_frame_callback(dev, cb, user) = UVS_OK;
end;

function UVSDev.SetVideoEncFrameCallback(streamIndex: Integer;
  cb: TFrameCallback; user: Pointer): boolean;
begin
  Result := uvs_set_video_enc_frame_callback(dev, streamIndex, cb,
    user) = UVS_OK;
end;

function UVSDev.SaveVideoSnapshot(szFilename: PAnsiChar; convert: PFrameConvert;
  jpgQuality: LongWord): boolean;
begin
  Result := uvs_save_video_snapshot(dev, szFilename, convert,
    jpgQuality) = UVS_OK;
end;

function UVSDev.LockVideoRawFrame(var frame: TFrameInfo;
  waitMilliSec: LongWord): boolean;
begin
  Result := uvs_lock_video_raw_frame(dev, frame, waitMilliSec) = UVS_OK;
end;

function UVSDev.UnlockVideoRawFrame: boolean;
begin
  Result := uvs_unlock_video_raw_frame(dev) = UVS_OK;
end;

function UVSDev.CopyVideoFrame(var frame: TFrameInfo; convert: PFrameConvert; waitMilliSec: LongWord): boolean;
begin
  Result := uvs_copy_video_frame(dev, convert, frame, waitMilliSec) = UVS_OK;
end;

function UVSDev.SetAudioRawFrameCallback(cb: TFrameCallback;
  user: Pointer): boolean;
begin
  Result := uvs_set_audio_raw_frame_callback(dev, cb, user) = UVS_OK;
end;

function UVSDev.SetAudioEncFrameCallback(cb: TFrameCallback;
  user: Pointer): boolean;
begin
  Result := uvs_set_audio_enc_frame_callback(dev, cb, user) = UVS_OK;
end;

function UVSDev.LockAudioRawFrame(var frame: TFrameInfo;
  waitMilliSec: LongWord): boolean;
begin
  Result := uvs_lock_audio_raw_frame(dev, frame, waitMilliSec) = UVS_OK;
end;

function UVSDev.UnlockAudoRawFrame;
begin
  Result := uvs_unlock_audio_raw_frame(dev) = UVS_OK;
end;

function UVSDev.CopyAudioRawFrame(var frame: TFrameInfo;
  waitMilliSec: LongWord): boolean;
begin
  Result := uvs_copy_audio_raw_frame(dev, frame, waitMilliSec) = UVS_OK;
end;

function UVSDev.RTSPStart(streamIndex: Integer; rtspPort: Word;
  hasAudio: boolean; szSessionName: PAnsiChar;
  multicast: PRTPMulticast): boolean;
begin
  Result := uvs_media_stream_rtsp_start(dev, streamIndex, rtspPort, hasAudio,
    szSessionName, multicast) = UVS_OK;
end;

function UVSDev.RTSPStop(streamIndex: Integer): boolean;
begin
  Result := uvs_media_stream_rtsp_stop(dev, streamIndex) = UVS_OK;
end;

function UVSDev.RTSPGetURL(streamIndex: Integer; var url: TURLInfo): boolean;
begin
  Result := uvs_media_stream_rtsp_get_url(dev, streamIndex, url) = UVS_OK;
end;

function UVSDev.RTMPSend(streamIndex: Integer; szURL: PAnsiChar;
  hasAudio: Boolean): boolean;
begin
  Result := uvs_media_stream_rtmp_send(dev, streamIndex, szURL, hasAudio)
    = UVS_OK;
end;

function UVSDev.RTMPStop(streamIndex: Integer): boolean;
begin
  Result := uvs_media_stream_rtmp_stop(dev, streamIndex) = UVS_OK;
end;

function UVSDev.RTMPGetURL(streamIndex: Integer; var url: TURLInfo): boolean;
begin
  Result := uvs_media_stream_rtmp_get_send_url(dev, streamIndex, url) = UVS_OK;
end;

function UVSDev.NDICreate(szSourceName: PAnsiChar; szGroupName: PAnsiChar;
  szXMLMetaData: PAnsiChar; isAsync: boolean): boolean;
begin
  Result := uvs_media_stream_ndi_create(dev, szSourceName, szGroupName,
    szXMLMetaData, isAsync) = UVS_OK;
end;

function UVSDev.NDIConfig(convert: PFrameConvert;
  skipFrameRate: Integer): boolean;
begin
  Result := uvs_media_stream_ndi_config(dev, convert, skipFrameRate) = UVS_OK;
end;

function UVSDev.NDIStart(hasAudio: Boolean): boolean;
begin
  Result := uvs_media_stream_ndi_start(dev, hasAudio) = UVS_OK;
end;

function UVSDev.NDIStop: boolean;
begin
  Result := uvs_media_stream_ndi_stop(dev) = UVS_OK;
end;

function UVSDev.NDIDestroy: boolean;
begin
  Result := uvs_media_stream_ndi_destroy(dev) = UVS_OK;
end;

end.
