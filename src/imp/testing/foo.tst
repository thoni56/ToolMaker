%%SET foo("Hej", Hopp)
%%IF (foo(Hej))
Error!
%%ELSE
OK!
%%ENDIF
%%IF (foo("Hopp"))
Error!
%%ELSE
OK!
%%ENDIF
