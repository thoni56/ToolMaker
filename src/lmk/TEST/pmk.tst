set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii pmk.tst.win32 > pmk.tmp
  alias cat dos2unix -ascii
else
  ../lmk pmk > pmk.tmp
endif
echo +++++ pmk.tmk +++++  >> pmk.tmp
\cat pmk.tmk >> pmk.tmp
echo +++++ pmk.lmt +++++ >> pmk.tmp
cat pmk.lmt >> pmk.tmp
echo +++++ pmkCommon.h +++++ >> pmk.tmp
cat pmkCommon.h >> pmk.tmp
echo +++++ pmkList.c +++++ >> pmk.tmp
cat pmkList.c >> pmk.tmp
echo +++++ pmkList.h +++++ >> pmk.tmp
cat pmkList.h >> pmk.tmp
\cat pmk.tmp
\rm pmk.tmp
