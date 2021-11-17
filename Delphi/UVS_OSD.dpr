program UVS_OSD;

uses
  { Vcl.Forms, }
  Forms,
  Unit4 in 'Unit4.pas' {Form4},
  UVSMedia in 'UVSMedia.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm4, Form4);
  Application.Run;
end.
