set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii ansi.tst.win32 > ansi.tmp
  alias cat dos2unix -ascii
else
  ../lmk ansi > ansi.tmp
endif
echo +++++ ansi.tmk +++++  >> ansi.tmp
\cat ansi.tmk >> ansi.tmp
echo +++++ ansi.lmt +++++ >> ansi.tmp
cat ansi.lmt >> ansi.tmp
echo +++++ ansiCommon.h +++++ >> ansi.tmp
cat ansiCommon.h >> ansi.tmp
echo +++++ ansiList.c +++++ >> ansi.tmp
cat ansiList.c >> ansi.tmp
echo +++++ ansiList.h +++++ >> ansi.tmp
cat ansiList.h >> ansi.tmp
\cat ansi.tmp
\rm ansi.tmp
