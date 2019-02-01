%%SET str(klmno)
%%SET str2(Abcklmnoxyz)
%%IF (IMP$STRSEARCH(%%(str),%%(str2),position))
OK!
%%(position)
%%ELSE
FEL!
%%(position)
%%ENDIF

%%IF (IMP$STRSEARCH(%%(str2),%%(str),position))
FEL!
%%(position)
%%ELSE
OK!
%%(position)
%%ENDIF

