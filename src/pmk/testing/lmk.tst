set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii lmk.tst.win32 > lmk.tmp
  alias cat dos2unix -ascii
else
  ../pmk lmk > lmk.tmp
endif
echo +++++ lmk.tmk +++++  >> lmk.tmp
\cat lmk.tmk >> lmk.tmp
echo +++++ lmk.pmt +++++ >> lmk.tmp
cat lmk.pmt >> lmk.tmp
echo +++++ lmk.voc +++++ >> lmk.tmp
cat lmk.voc >> lmk.tmp
echo +++++ lmkCommon.h +++++ >> lmk.tmp
cat lmkCommon.h >> lmk.tmp
echo +++++ lmkErr.c +++++ >> lmk.tmp
cat lmkErr.c >> lmk.tmp
echo +++++ lmkPaSema.c +++++ >> lmk.tmp
cat lmkPaSema.c >> lmk.tmp
echo +++++ lmkParse.c +++++ >> lmk.tmp
cat lmkParse.c >> lmk.tmp
echo +++++ lmkParse.h +++++ >> lmk.tmp
cat lmkParse.h >> lmk.tmp
\cat lmk.tmp
\rm lmk.tmp
