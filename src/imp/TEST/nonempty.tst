%%SET A ()
%%SET B (1)
%%IF (A (*))
  Fel 1
%%ELSE
  OK 1
%%ENDIF
%%IF (B (*))
  OK 2
%%ELSE
  Fel 2
%%ENDIF
%%IF ({1} (*))
  OK 3
%%ELSE
  Fel 3
%%ENDIF
%%IF ({} (*))
  Fel 4
%%ELSE
  OK 4
%%ENDIF
%%IF ({1,2,3}[2] (*))
  OK 5
%%ELSE
  Fel 5
%%ENDIF
%%IF ({1,2,{},4}[3] (*))
  Fel 6
%%ELSE
  OK 6
%%ENDIF
%%IF (C (*))
`%%IF (C(*))         * * * FACIT * * *
%%ENDIF
%%IF ({1}[2] (*))
`%%IF ({1}[2](*))    * * * FACIT * * *
%%ENDIF
%%IF (%%(A) (*))
`%%IF (<NULL>(*))    * * * FACIT * * *
%%ENDIF
%%IF (%%(C) (*))
`%%IF (`%%(C)(*))     * * * FACIT * * *
%%ENDIF
