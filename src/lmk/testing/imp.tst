set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii imp.tst.win32 > imp.tmp
  alias cat dos2unix -ascii
else
  ../lmk imp > imp.tmp
endif
echo +++++ imp.tmk +++++  >> imp.tmp
\cat imp.tmk >> imp.tmp
echo +++++ imp.lmt +++++ >> imp.tmp
cat imp.lmt >> imp.tmp
echo +++++ impCommon.h +++++ >> imp.tmp
cat impCommon.h >> imp.tmp
echo +++++ impList.c +++++ >> imp.tmp
cat impList.c >> imp.tmp
echo +++++ impList.h +++++ >> imp.tmp
cat impList.h >> imp.tmp
\cat imp.tmp
\rm imp.tmp
