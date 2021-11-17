program UVS_Preview;

uses
  { Vcl.Forms, }
  Forms,
  Unit2 in 'Unit2.pas' {Form2},
  UVSMedia in 'UVSMedia.pas',
  Unit3 in 'Unit3.pas' {Form3};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm2, Form2);
  Application.CreateForm(TForm3, Form3);
  Application.Run;
end.
