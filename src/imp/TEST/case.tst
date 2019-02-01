%%SET foo(fie)
%%SET FOO(FUM)
%%IF(foo(fie) AND NOT foo(FIE) AND FOO(FUM) AND NOT FOO(fum))
OK!
%%ELSE
Error!
%%ENDIF
