set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii gep.tst.win32
else
  ../pmk gep
endif
