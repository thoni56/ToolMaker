set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii imp.tst.win32 > imp.tmp
  alias cat dos2unix -ascii
else
  ../pmk imp > imp.tmp
endif
echo +++++ imp.tmk +++++  >> imp.tmp
\cat imp.tmk >> imp.tmp
echo +++++ imp.pml +++++ >> imp.tmp
cat imp.pml >> imp.tmp
echo +++++ imp.pmt +++++ >> imp.tmp
cat imp.pmt >> imp.tmp
echo +++++ imp.voc +++++ >> imp.tmp
cat imp.voc >> imp.tmp
echo +++++ impCommon.h +++++ >> imp.tmp
cat impCommon.h >> imp.tmp
echo +++++ impPaSema.c +++++ >> imp.tmp
cat impPaSema.c >> imp.tmp
echo +++++ impParse.c +++++ >> imp.tmp
cat impParse.c >> imp.tmp
echo +++++ impParse.h +++++ >> imp.tmp
cat impParse.h >> imp.tmp
\cat imp.tmp
\rm imp.tmp
