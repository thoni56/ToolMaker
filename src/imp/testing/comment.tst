%%COMMENT
%%KEEP
%%SET Foo(Optimize)
%%SET %%(Foo)(Lr0,Merge)
%%INCLUDE("macro.h") %%-- NOTE! Needs something after it!
%%IF (Optimize(Lr0))
OK
%%ELSE
Error
%%ENDIF
%%IF (Optimize(Lr0,Merge))
OK
%%ELSE
Error
%%ENDIF
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
%%ELSIF (Fie(Fie))
OK
%%ELSIF (Optimize(Merge))
OK (Optimize(Merge))
%%ELSE
Error
%%ENDIF

%%ENDKEEP
%%ENDCOMMENT
