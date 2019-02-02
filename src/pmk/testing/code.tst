set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii code.tst.win32 > code.tmp
  alias cat dos2unix -ascii
else
  ../pmk code > code.tmp
endif
echo +++++ code.tmk +++++  >> code.tmp
\cat code.tmk >> code.tmp
echo +++++ code.pml +++++ >> code.tmp
cat code.pml >> code.tmp
echo +++++ code.pmt +++++ >> code.tmp
cat code.pmt >> code.tmp
echo +++++ code.voc +++++ >> code.tmp
cat code.voc >> code.tmp
echo +++++ codeCommon.h +++++ >> code.tmp
cat codeCommon.h >> code.tmp
echo +++++ codeErr.c +++++ >> code.tmp
cat codeErr.c >> code.tmp
echo +++++ codePaSema.c +++++ >> code.tmp
cat codePaSema.c >> code.tmp
echo +++++ codeParse.c +++++ >> code.tmp
cat codeParse.c >> code.tmp
echo +++++ codeParse.h +++++ >> code.tmp
cat codeParse.h >> code.tmp
\cat code.tmp
\rm code.tmp
