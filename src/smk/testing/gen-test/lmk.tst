set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii lmk.tst.win32
  alias cat dos2unix -ascii
else
  ../../smk -generate tables -generate source lmk
endif
echo "------- lmk.smt --------"
cat lmk.smt
echo "------- lmkScan.h --------"
cat lmkScan.h
echo "------- lmkScan.c --------"
cat lmkScan.c
echo "------- lmkScSema.c --------"
cat lmkScSema.c
