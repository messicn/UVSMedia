unit Unit3;

interface

uses
  { Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ExtCtrls; }
  Windows, Messages, SysUtils, Variants, Classes, Graphics,
  Controls, Forms, Dialogs, ExtCtrls;

type
  TForm3 = class(TForm)
    Video: TPanel;
    procedure FormCreate(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form3: TForm3;

implementation

uses
  Unit2;

{$R *.dfm}

procedure TForm3.FormCreate(Sender: TObject);
begin
  SetBounds(0, 0, Screen.Width, Screen.Height);
  Video.SetBounds(0, 0, Screen.Width, Screen.Height);
end;

procedure TForm3.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key = VK_ESCAPE then
  begin
    Form2.FullscreenClick(Form2.Fullscreen);
  end;
end;

end.
