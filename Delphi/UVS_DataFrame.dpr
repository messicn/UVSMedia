program UVS_DataFrame;

uses
  { Vcl.Forms, }
  Forms,
  Unit6 in 'Unit6.pas' {Form6},
  UVSMedia in 'UVSMedia.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm6, Form6);
  Application.Run;
end.
