set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii pos.tst.win32 > pos.tmp
  alias cat dos2unix -ascii
else
  ../pmk pos > pos.tmp
endif
echo +++++ pos.tmk +++++  >> pos.tmp
\cat pos.tmk >> pos.tmp
echo +++++ pos.pmt +++++ >> pos.tmp
cat pos.pmt >> pos.tmp
\cat pos.tmp
\rm pos.tmp
