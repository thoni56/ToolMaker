%%SET A ()
%%SET B (1)
%%SET C (1,2)
%%SET D (1,2,3)
%%IF (A (1,2))
  Fel 1
%%ELSE
  OK 1
%%ENDIF
%%IF (B (1,2))
  Fel 2
%%ELSE
  OK 2
%%ENDIF
%%IF (C (1,2))
  OK 3
%%ELSE
  Fel 3
%%ENDIF
%%IF (D (1,2))
  OK 4
%%ELSE
  Fel 4
%%ENDIF
%%IF (A ())
  OK 5
%%ELSE
  Fel 5
%%ENDIF
%%IF ({} (1,2))
  Fel 6
%%ELSE
  OK 6
%%ENDIF
%%IF ({1} (1,2))
  Fel 7
%%ELSE
  OK 7
%%ENDIF
%%IF ({1,2} (1,2))
  OK 8
%%ELSE
  Fel 8
%%ENDIF
%%IF ({1,2,3} (1,2))
  OK 9
%%ELSE
  Fel 9
%%ENDIF
%%IF ({%%((1+2+3)/6*UNDEF), "String", String} (%%(UNDEF), "String"))
  OK 10
%%ELSE
  Fel 10
%%ENDIF
%%IF ({%%((1+2+3)/6*UNDEF), "String", String} (%%(UNDEF), String))
  OK 11
%%ELSE
  Fel 11
%%ENDIF
%%IF ({%%((1+2+3)/6*UNDEF), "String", String} (%%(UNDEF), %%("String")))
  OK 12
%%ELSE
  Fel 12
%%ENDIF
%%IF (E (1,2))
`%%IF (E(1,2))       * * * FACIT * * *
%%ENDIF
%%-- More advanced examples resulting in partial evaluation
%%IF ({%%((1+2+3)/6*UNDEF), "String", String} (%%(UNDEF), %%(%%("String"))))
`%%IF ({`%%(UNDEF), String, String} (`%%(String)))
%%ENDIF
%%ESET A (1, 2, 6+NODEF1, NODEF2)
%%ESET B (1, 3*2+NODEF1, NODEF3)
%%IF (A (%%(B)))
`%%IF ({1, 2, `%%(6+NODEF1), `%%(NODEF2)} (`%%(NODEF3)))    * * * FACIT * * *
%%ENDIF
%%IF (C[1] (1))
  OK 13
%%ELSE
  Fel 13
%%ENDIF
