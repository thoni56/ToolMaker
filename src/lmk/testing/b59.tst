set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii b59.tst.win32
else
  ../lmk -lib .. b59.lmk
  gcc -o b59 b59List.c b59.c
  b59 -list /unknown b59.c
endif
