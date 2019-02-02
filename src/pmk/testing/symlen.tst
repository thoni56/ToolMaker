set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii symlen.tst.win32 > symlen.tmp
  alias cat dos2unix -ascii
else
  ../pmk symlen > symlen.tmp
endif
echo +++++ symlen.tmk +++++  >> symlen.tmp
\cat symlen.tmk >> symlen.tmp
echo +++++ symlen.pml +++++ >> symlen.tmp
cat symlen.pml >> symlen.tmp
\cat symlen.tmp
\rm symlen.tmp
