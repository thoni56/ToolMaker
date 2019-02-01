set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii cpp.tst.win32 > cpp.tmp
  alias cat dos2unix -ascii
else
  ../lmk cpp > cpp.tmp
endif
echo +++++ cpp.tmk +++++  >> cpp.tmp
\cat cpp.tmk >> cpp.tmp
echo +++++ cpp.lmt +++++ >> cpp.tmp
cat cpp.lmt >> cpp.tmp
echo +++++ cppCommon.h +++++ >> cpp.tmp
cat cppCommon.h >> cpp.tmp
echo +++++ cppList.cc +++++ >> cpp.tmp
cat cppList.cc >> cpp.tmp
echo +++++ cppList.h +++++ >> cpp.tmp
cat cppList.h >> cpp.tmp
\cat cpp.tmp
\rm cpp.tmp
