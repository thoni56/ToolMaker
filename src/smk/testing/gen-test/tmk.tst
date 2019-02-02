set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii tmk.tst.win32
  alias cat dos2unix -ascii
else
  ../../smk -generate tables -generate source tmk
endif
echo "------- tmk.smt --------"
cat tmk.smt
echo "------- tmkScan.h --------"
cat tmkScan.h
echo "------- tmkScan.c --------"
cat tmkScan.c
echo "------- tmkScSema.c --------"
cat tmkScSema.c
