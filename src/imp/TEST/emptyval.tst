%%SET foo()
%%SET fie( )
%%SET fum(Hej)
foo >%%(foo)<, fie >%%(fie)<, fum >%%(fum)<
%%IF(foo() AND fie( ) AND fum())
OK!
%%ELSE
Error!
%%ENDIF
%%IF(NOT foo(*) AND NOT fie(*) AND fum(*))
OK!
%%ELSE
Error!
%%ENDIF
