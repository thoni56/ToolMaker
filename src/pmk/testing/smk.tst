set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii smk.tst.win32 > smk.tmp
  alias cat dos2unix -ascii
else
  ../pmk smk > smk.tmp
endif
echo +++++ smk.tmk +++++  >> smk.tmp
\cat smk.tmk >> smk.tmp
echo +++++ smk.pml +++++ >> smk.tmp
cat smk.pml >> smk.tmp
echo +++++ smk.pmt +++++ >> smk.tmp
cat smk.pmt >> smk.tmp
echo +++++ smk.voc +++++ >> smk.tmp
cat smk.voc >> smk.tmp
echo +++++ smkCommon.h +++++ >> smk.tmp
cat smkCommon.h >> smk.tmp
echo +++++ smkErr.c +++++ >> smk.tmp
cat smkErr.c >> smk.tmp
echo +++++ smkPaSema.c +++++ >> smk.tmp
cat smkPaSema.c >> smk.tmp
echo +++++ smkParse.c +++++ >> smk.tmp
cat smkParse.c >> smk.tmp
echo +++++ smkParse.h +++++ >> smk.tmp
cat smkParse.h >> smk.tmp
\cat smk.tmp
\rm smk.tmp
