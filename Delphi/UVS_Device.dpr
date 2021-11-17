program UVS_Device;

uses
  { Vcl.Forms, }
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  UVSMedia in 'UVSMedia.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
