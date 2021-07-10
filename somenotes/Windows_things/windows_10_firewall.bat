# WIN10 防火墙批量
# profile=domain/private, dir=in/out,  action=yes/block , protocol  localport
# ADD
netsh advfirewall firewall add rule name=DexSamSungBlock_SamsungDeX dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\SamsungDeX.exe"  action=block enable=yes description="block samsung"
netsh advfirewall firewall add rule name=DexSamSungBlock_LauncherAsUser dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\LauncherAsUser.exe"  action=block enable=yes description="block samsung"
netsh advfirewall firewall add rule name=DexSamSungBlock_LicenseAgreement dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\LicenseAgreement.exe"  action=block enable=yes description="block samsung"
netsh advfirewall firewall add rule name=DexSamSungBlock_ErrorReport dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\ErrorReport.exe"  action=block enable=yes description="block samsung"
netsh advfirewall firewall add rule name=DexSamSungBlock_CmdWifiOn dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\CmdWifiOn.exe"  action=block enable=yes description="block samsung"
netsh advfirewall firewall add rule name=DexSamSungBlock_CmdRegContextMenu dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\CmdRegContextMenu.exe"  action=block enable=yes description="block samsung"
netsh advfirewall firewall add rule name=DexSamSungBlock_CmdFirewall dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\UpdateClient.exe"  action=block enable=yes description="block samsung"
netsh advfirewall firewall add rule name=DexSamSungBlock_UpdateClient dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\CmdFirewall.exe"  action=block enable=yes description="block samsung"
# Delete
netsh advfirewall firewall delete rule name=DexSamSungBlock_SamsungDeX dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\SamsungDeX.exe"
netsh advfirewall firewall delete rule name=DexSamSungBlock_LauncherAsUser dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\LauncherAsUser.exe"
netsh advfirewall firewall delete rule name=DexSamSungBlock_LicenseAgreement dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\LicenseAgreement.exe"
netsh advfirewall firewall delete rule name=DexSamSungBlock_ErrorReport dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\ErrorReport.exe"
netsh advfirewall firewall delete rule name=DexSamSungBlock_CmdWifiOn dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\CmdWifiOn.exe"
netsh advfirewall firewall delete rule name=DexSamSungBlock_CmdRegContextMenu dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\CmdRegContextMenu.exe"
netsh advfirewall firewall delete rule name=DexSamSungBlock_CmdFirewall dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\UpdateClient.exe"
netsh advfirewall firewall delete rule name=DexSamSungBlock_UpdateClient dir=out program="%ProgramFiles% (x86)\Samsung\Samsung DeX\CmdFirewall.exe"
# Show
netsh advfirewall firewall show rule name=DexSamSungBlock_SamsungDeX | findstr 已启用
netsh advfirewall firewall show rule name=DexSamSungBlock_LauncherAsUser | findstr 已启用
netsh advfirewall firewall show rule name=DexSamSungBlock_LicenseAgreement | findstr 已启用
netsh advfirewall firewall show rule name=DexSamSungBlock_ErrorReport | findstr 已启用
netsh advfirewall firewall show rule name=DexSamSungBlock_CmdWifiOn | findstr 已启用
netsh advfirewall firewall show rule name=DexSamSungBlock_CmdRegContextMenu | findstr 已启用
netsh advfirewall firewall show rule name=DexSamSungBlock_CmdFirewall | findstr 已启用
netsh advfirewall firewall show rule name=DexSamSungBlock_UpdateClient | findstr 已启用
