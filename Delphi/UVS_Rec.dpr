program UVS_Rec;

uses
  { Vcl.Forms, }
  Forms,
  Unit5 in 'Unit5.pas' {Form5},
  UVSMedia in 'UVSMedia.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm5, Form5);
  Application.Run;
end.
