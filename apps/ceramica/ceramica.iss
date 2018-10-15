; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=Ceramica
AppVerName=Ceramica 1.0.1.77
AppPublisher=NN-VideoLab.net
DefaultDirName={pf}\Ceramica
DefaultGroupName=Ceramica
AllowNoIcons=yes
LicenseFile=license_ceramica.txt
OutputDir=..\setup_output\
OutputBaseFilename=setup_ceramica10177
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\..\..\..\bin\Ceramica.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\..\..\bin\CeramClient.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\..\..\bin\awpcvvideo.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\..\..\bin\pgf_wrapper.dll"; DestDir: "{app}"; Flags: ignoreversion

Source: "..\install_libs\borlndmm.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\install_libs\cc32160mt.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\install_libs\cc32250mt.dll"; DestDir: "{app}"; Flags: ignoreversion

Source: "..\install_libs\opencv_ffmpeg300.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\install_libs\opencv_world300.dll"; DestDir: "{app}"; Flags: ignoreversion

Source: "..\install_libs\msvcr120.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\install_libs\msvcp120.dll"; DestDir: "{app}"; Flags: ignoreversion

Source: "manual.pdf"; DestDir: "{app}"; Flags: ignoreversion


; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Ceramica"; Filename: "{app}\Ceramica.exe"
Name: "{group}\{cm:UninstallProgram,Ceramica}"; Filename: "{uninstallexe}"
Name: "{userdesktop}\Ceramica"; Filename: "{app}\Ceramica.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Ceramica"; Filename: "{app}\Ceramica.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\Ceramica.exe"; Description: "{cm:LaunchProgram,Ceramica}"; Flags: nowait postinstall skipifsilent

