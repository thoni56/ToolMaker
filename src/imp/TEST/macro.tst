%%SET Foo(Optimize)
%%SET %%(Foo)(Lr0,Merge)
%%INCLUDE("macro.h")% %%-- NOTE! Needs something after it!
%%IF (Optimize(Lr0))
OK
%%ELSE
Error
%%ENDIF
%%SET String("Detta {r en str{ng inneh}llande en dubbelfnutt ("")")
%%(String)
%%(Fie)
%%IF (Optimize(Lr0,Merge))
OK
%%ELSE
Error
%%ENDIF
%%-- Denna rad skall f|rsvinna!
 %%-- Men ej denna!
%%IF (Optimize(Lr0,Split))
Error
%%ELSE
OK
%%ENDIF
%%KEEP
%%IF (Optimize(Lr0,Split))
Error
%%ELSE
OK
%%ENDIF
%%ENDKEEP
%%IF (NOT Optimize(Merge) OR Fie(Merge))
True
%%(Optimize)
%%FOO
%%ELSE
False
%%(Optimize)
%%ENDIF
%%IF (Fie(Fie))
%%IF (Optimize(Merge))
OK
%%ELSE
Error
%%ENDIF
%%ELSE
%%IF (Optimize(Merge))
OK
%%ELSE
Error
%%ENDIF
%%ENDIF
%%IF (Optimize(Split))
Error
%%ELSIF (Fie(Fum))
OK (Fie(Fum))
%%ELSIF (Fie(Fie) OR Fie(Foo))
OK (Fie(Fie) OR Fie(Foo))
%%ELSIF (Optimize(Merge))
OK (Optimize(Merge))
%%ELSE
Error
%%ENDIF

