unit Unit1;

interface

uses
  { Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls, UVSMedia; }
  Windows, Messages, SysUtils, Variants, Classes, Graphics,
  Controls, Forms, Dialogs, StdCtrls, ExtCtrls, UVSMedia;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    Status: TEdit;
    GroupBox1: TGroupBox;
    Label2: TLabel;
    Label3: TLabel;
    Image: TEdit;
    Mode: TComboBox;
    Browse: TButton;
    Color: TButton;
    Apply: TButton;
    Video: TPanel;
    Timer1: TTimer;
    OpenDialog1: TOpenDialog;
    ColorDialog1: TColorDialog;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure ApplyClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure BrowseClick(Sender: TObject);
    procedure ColorClick(Sender: TObject);
  private
    { Private declarations }
    Dev: UVSDev;
    bkColor: TColor;
  public
    { Public declarations }
    procedure PreviewStart;
    procedure PreviewStop;
    procedure DeviceNotify(notify: DevNotify; var info: TDevInfo; obj: UVSObj;
      user: Pointer);
  end;

  TNotify = class(TThread)
  private
    { Private declarations }
    notify: DevNotify;
    info: TDevInfo;
    obj: UVSObj;
    user: Pointer;
  protected
    procedure Execute; override;
    procedure Run;
  public
    constructor Create(notify: DevNotify; info: PDevInfo; obj: UVSObj;
      user: Pointer); overload;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure DeviceCallback(notify: DevNotify; info: PDevInfo; obj: UVSObj;
  user: Pointer); stdcall;
begin
  TNotify.Create(notify, info, obj, user);
end;

procedure TForm1.ApplyClick(Sender: TObject);
var
  Draw: DrawMode;
begin
  if Mode.ItemIndex = 0 then
  begin
    Draw := draw_stretch;
  end
  else
  begin
    Draw := draw_center;
  end;

  if Image.Text = '' then
  begin
    uvs_set_nosignal_image(nil, Draw, bkColor); { No signal image disabled }
  end
  else
  begin
    uvs_set_nosignal_image(PAnsiChar(AnsiString(Image.Text)), Draw, bkColor);
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  ret: boolean;
begin
  Dev := UVSDev.Create(0, -1, ret);

  uvs_set_device_callback(DeviceCallback, nil);
  Dev.DeviceStart;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
  Dev.Free;
end;

procedure TForm1.FormShow(Sender: TObject);
begin
  PreviewStart;
end;

procedure TForm1.PreviewStart;
begin
  Dev.StartPreview(Video.Handle);
end;

procedure TForm1.PreviewStop;
begin
  Dev.StopPreview;
  Video.Refresh;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
  Signal, Mode: boolean;
  str: string;
begin
  if Dev.GetVideoStatus(Signal, Mode) then
  begin
    if Signal then
    begin
      str := 'Signal';
    end
    else
    begin
      str := 'No Signal';
    end;

    if Mode then
    begin
      str := str + '(USB3)';
    end
    else
    begin
      str := str + '(USB2)';
    end;
  end;

  Status.Text := str;
end;

procedure TForm1.BrowseClick(Sender: TObject);
begin
  if OpenDialog1.Execute then
  begin
    Image.Text := OpenDialog1.FileName;
  end;
end;

procedure TForm1.ColorClick(Sender: TObject);
begin
   if ColorDialog1.Execute then
   begin
     bkColor := ColorDialog1.Color;
   end;
end;

procedure TForm1.DeviceNotify(notify: DevNotify; var info: TDevInfo; obj: UVSObj;
  user: Pointer);
begin
  if notify = dev_changed then
  begin
    if not Dev.IsValid then
    begin
      Dev.DeviceOpen(info);
      Dev.DeviceStart;
      PreviewStart;
    end;
  end
  else if Dev.Dev = obj then { dev_closed }
  begin
    PreviewStop;
    Dev.DeviceClose;
  end;
end;

procedure TNotify.Execute;
begin
  Synchronize(Run);
end;

procedure TNotify.Run;
begin
  Form1.DeviceNotify(notify, info, obj, user);
end;

constructor TNotify.Create(notify: DevNotify; info: PDevInfo; obj: UVSObj;
  user: Pointer);
begin
  Self.notify := notify;
  Self.info := info^;
  Self.obj := obj;
  Self.user := user;

  FreeOnTerminate := True;
  inherited Create(False);
end;

end.
