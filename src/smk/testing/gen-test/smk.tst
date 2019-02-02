set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii smk.tst.win32
  alias cat dos2unix -ascii
else
  ../../smk -generate tables -generate source smk
endif
echo "------- smk.smt --------"
cat smk.smt
echo "------- smkScan.h --------"
cat smkScan.h
echo "------- smkScan.c --------"
cat smkScan.c
echo "------- smkScSema.c --------"
cat smkScSema.c
