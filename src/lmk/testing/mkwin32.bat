@rem  Run lmk on .lmk file named by first argument 
@rem  Make .tst.win32 file containing stderr output followed by lmk output. 
@..\lmk %1 > %1.tst.tmp 
@move /Y stderr.txt %1.tst.win32 
@type %1.tst.tmp >> %1.tst.win32 
@del %1.tst.tmp 
