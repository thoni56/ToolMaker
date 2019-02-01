..\lmk -lib .. b59.lmk > b59.tst.tmp 
move /Y stderr.txt b59.tst.win32 
type b59.tst.tmp >> b59.tst.win32 
cl -DWIN32 -o b59 b59List.c b59.c 
b59.exe -list unknown\unknown b59.c >> b59.tst.tmp 
type stderr.txt >> b59.tst.win32 
type b59.tst.tmp >> b59.tst.win32 
del b59.tst.tmp 
