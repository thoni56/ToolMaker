set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii skipcode.tst.win32 > skipcode.tmp
  alias cat dos2unix -ascii
else
  ../pmk skipcode > skipcode.tmp
endif
echo +++++ skipcode.tmk +++++  >> skipcode.tmp
\cat skipcode.tmk >> skipcode.tmp
echo +++++ skipcode.pml +++++ >> skipcode.tmp
cat skipcode.pml >> skipcode.tmp
echo +++++ skipcode.pmt +++++ >> skipcode.tmp
cat skipcode.pmt >> skipcode.tmp
echo +++++ skipcode.voc +++++ >> skipcode.tmp
cat skipcode.voc >> skipcode.tmp
\cat skipcode.tmp
\rm skipcode.tmp
