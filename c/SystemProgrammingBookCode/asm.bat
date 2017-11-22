SET EXENAME=%1.exe
ml -c -Zi %1.asm
link /DEBUG /SUBSYSTEM:CONSOLE kernel32.lib user32.lib %1

ML *.asm /link /subsystem:windows