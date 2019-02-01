@rem  Run pmk on .pmk file named by first argument 
@rem  Make .tst.win32 file containing stderr output followed by pmk output. 
@..\pmk %1 > %1.tst.tmp 
@move /Y stderr.txt %1.tst.win32 
@type %1.tst.tmp >> %1.tst.win32 
@del %1.tst.tmp 
