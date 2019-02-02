set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii pmk.tst.win32
  alias cat dos2unix -ascii
else
  ../../smk -generate tables -generate source pmk
endif
echo "------- pmk.smt --------"
cat pmk.smt
echo "------- pmkScan.h --------"
cat pmkScan.h
echo "------- pmkScan.c --------"
cat pmkScan.c
echo "------- pmkScSema.c --------"
cat pmkScSema.c
