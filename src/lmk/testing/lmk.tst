set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii lmk.tst.win32 > lmk.tmp
  alias cat dos2unix -ascii
else
  ../lmk lmk > lmk.tmp
endif
echo +++++ lmk.tmk +++++  >> lmk.tmp
\cat lmk.tmk >> lmk.tmp
echo +++++ lmk.lmt +++++ >> lmk.tmp
cat lmk.lmt >> lmk.tmp
echo +++++ lmkCommon.h +++++ >> lmk.tmp
cat lmkCommon.h >> lmk.tmp
echo +++++ lmkList.c +++++ >> lmk.tmp
cat lmkList.c >> lmk.tmp
echo +++++ lmkList.h +++++ >> lmk.tmp
cat lmkList.h >> lmk.tmp
\cat lmk.tmp
\rm lmk.tmp
