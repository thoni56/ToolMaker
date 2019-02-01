%%SET A ()
%%IF (A (?))
  OK 1
%%ELSE
  Fel 1
%%ENDIF
%%IF (B (?))
  Fel 2
%%ELSE
  OK 2
%%ENDIF
%%IF ({1} (?))
  OK 3
%%ELSE
  Fel 3
%%ENDIF
%%IF ({} (?))
  OK 4
%%ELSE
  Fel 4
%%ENDIF
%%IF ({1}[2] (?))
  Fel 5
%%ELSE
  OK 5
%%ENDIF
%%IF ({1,2,3}[2] (?))
  OK 6
%%ELSE
  Fel 6
%%ENDIF
%%IF (%%(A) (?))
  Fel 7
%%ELSE
  OK 7
%%ENDIF
%%IF (%%(B) (?))
`%%IF (%%(B)(?))      * * * FACIT * * *
%%ENDIF
