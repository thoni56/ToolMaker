set os = "$argv[1]"
if ("$os" == "PC") then
  dos2unix -ascii tmcore.tst.win32
  alias cat dos2unix -ascii
else
  ../../smk tmcore
endif
