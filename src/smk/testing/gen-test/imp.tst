set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii imp.tst.win32
  alias cat dos2unix -ascii
else
  ../../smk -generate tables -generate source imp
endif
echo "------- imp.smt --------"
cat imp.smt
echo "------- impScan.h --------"
cat impScan.h
echo "------- impScan.c --------"
cat impScan.c
echo "------- impScSema.c --------"
cat impScSema.c
