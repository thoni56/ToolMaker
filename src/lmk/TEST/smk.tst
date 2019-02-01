set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii smk.tst.win32 > smk.tmp
  alias cat dos2unix -ascii
else
  ../lmk smk > smk.tmp
endif
echo +++++ smk.tmk +++++  >> smk.tmp
\cat smk.tmk >> smk.tmp
echo +++++ smk.lmt +++++ >> smk.tmp
cat smk.lmt >> smk.tmp
echo +++++ smkCommon.h +++++ >> smk.tmp
cat smkCommon.h >> smk.tmp
echo +++++ smkList.c +++++ >> smk.tmp
cat smkList.c >> smk.tmp
echo +++++ smkList.h +++++ >> smk.tmp
cat smkList.h >> smk.tmp
\cat smk.tmp
\rm smk.tmp
