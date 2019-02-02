set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii tmk.tst.win32 > tmk.tmp
  alias cat dos2unix -ascii
else
  ../pmk tmk > tmk.tmp
endif
echo +++++ tmk.tmk +++++  >> tmk.tmp
\cat tmk.tmk >> tmk.tmp
echo +++++ tmk.pml +++++ >> tmk.tmp
cat tmk.pml >> tmk.tmp
echo +++++ tmk.pmt +++++ >> tmk.tmp
cat tmk.pmt >> tmk.tmp
echo +++++ tmk.voc +++++ >> tmk.tmp
cat tmk.voc >> tmk.tmp
echo +++++ tmkCommon.h +++++ >> tmk.tmp
cat tmkCommon.h >> tmk.tmp
echo +++++ tmkErr.c +++++ >> tmk.tmp
cat tmkErr.c >> tmk.tmp
echo +++++ tmkPaSema.c +++++ >> tmk.tmp
cat tmkPaSema.c >> tmk.tmp
echo +++++ tmkParse.c +++++ >> tmk.tmp
cat tmkParse.c >> tmk.tmp
echo +++++ tmkParse.h +++++ >> tmk.tmp
cat tmkParse.h >> tmk.tmp
\cat tmk.tmp
\rm tmk.tmp
