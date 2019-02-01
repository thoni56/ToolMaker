%%SET A(ASDFqw)
%%SET B(JKLOqw)
%%(IMP$STRLEN("%%(A)%%(B)"))
%%(IMP$STRLEN("A"))
%%IF((IMP$STRLEN("A")) = 1)
%%("A")
%%ELSE
%%FEL!
%%ENDIF
%%((IMP$STRLEN("ABC")) + 2)
%%IF((IMP$STRLEN(A)) = 6)
%%(A)
%%ELSE
%%FEL!
%%ENDIF
