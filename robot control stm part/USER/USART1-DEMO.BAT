SET PATH=D:\Keil_v5\ARM\ARMCC\Bin;E:\A\Anacond\exe;E:\A\Anacond\exe\Library\mingw-w64\bin;E:\A\Anacond\exe\Library\usr\bin;E:\A\Anacond\exe\Library\bin;E:\A\Anacond\exe\Scripts;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files (x86)\Rockwell Software\RSCommon;C:\windows\system32;C:\windows;C:\windows\System32\Wbem;C:\windows\System32\WindowsPowerShell\v1.0\;C:\windows\System32\OpenSSH\;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\Program Files (x86)\Common Files\Rockwell\;E:\JJIJJ\runtime\win64;E:\JJIJJ\bin;E:\JJIJJ\polyspace\bin;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\dotnet\;E:\weixingkaifa\微信web开发者工具\dll;E:\Min;W64\mingw64\bin;E:\cmake\cmake-3.20.2-windows-x86_64\bin;E:\opencv\OpenCV-MinGW-Build-OpenCV-4.5.2-x64\x64\mingw\bin;D:\Matlab\program files\runtime\win64;D:\Matlab\program files\bin;D:\Matlab\program files\polyspace\bin;E:\Nanchang uni\Raspberry  Pi\PUTTY\;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;E:\NC UI\硕\课题_机械喷头清刷\PDFtk\PDFtk\bin\;;E:\NC U;\PDFtk\bin\;C:\Program Files (x86)\PDFtk Server\bin\;E:\iron\Scripts\;E:\iron\;C:\Users\Administrator\AppData\Local\Microsoft\WindowsApps;E:\Bandzip_压缩\;%PyCharm%;D:\pycharm\py\PyCharm Community Edition 2022.2\bin;;D:\vscode\Microsoft VS Code\bin;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=USART1-DEMO
SET CPU_CLOCK=0x00B71B00
"D:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\startup_stm32f10x_hd._ia"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\main.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_it.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\usart1.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\message.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\ikunc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\site.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_gpio.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_rcc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_usart.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\misc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_sdio.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\core_cm3.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\system_stm32f10x.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\STM32-DEMO.lnp"
"D:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\STM32-DEMO.axf" --i32combined --output ".\STM32-DEMO.hex"
