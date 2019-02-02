set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii pmk.tst.win32 > pmk.tmp
  alias cat dos2unix -ascii
else
  ../pmk pmk > pmk.tmp
endif
echo +++++ pmk.tmk +++++  >> pmk.tmp
\cat pmk.tmk >> pmk.tmp
echo +++++ pmk.pml +++++ >> pmk.tmp
cat pmk.pml >> pmk.tmp
echo +++++ pmk.pmt +++++ >> pmk.tmp
cat pmk.pmt >> pmk.tmp
echo +++++ pmk.voc +++++ >> pmk.tmp
cat pmk.voc >> pmk.tmp
echo +++++ pmkCommon.h +++++ >> pmk.tmp
cat pmkCommon.h >> pmk.tmp
echo +++++ pmkErr.c +++++ >> pmk.tmp
cat pmkErr.c >> pmk.tmp
echo +++++ pmkPaSema.c +++++ >> pmk.tmp
cat pmkPaSema.c >> pmk.tmp
echo +++++ pmkParse.c +++++ >> pmk.tmp
cat pmkParse.c >> pmk.tmp
echo +++++ pmkParse.h +++++ >> pmk.tmp
cat pmkParse.h >> pmk.tmp
\cat pmk.tmp
\rm pmk.tmp
