%%SET FOO("Foo string")%%SET FIE(FIE,"Hej hopp")
%%(FOO),%%(FIE)
%%IF (FOO(%%(FOO)))
Yes! (FOO)
%%ELSE
No! (FOO)
%%ENDIF
%%IF (FIE(%%(FIE)))
Yes! (FIE)
%%ELSE
No! (FIE)
%%ENDIF
%%IF (FOO(*))
Yes! (FOO)
%%ELSE
No! (FOO)
%%ENDIF
%%IF (FIE(*))
Yes! (FIE)
%%ELSE
No! (FIE)
%%ENDIF
%%SET FOO(Fum)%%SET FIE(Fum2)
%%(FOO),%%(FIE)
%%IF (FOO(%%(FOO)))
Yes! (FOO)
%%ELSE
No! (FOO)
%%ENDIF
%%IF (FIE(%%(FIE)))
Yes! (FIE)
%%ELSE
No! (FIE)
%%ENDIF
