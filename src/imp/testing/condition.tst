%%SET A ()
%%SET B (1)
%%SET C (1,2)
%%SET D (1,2,3)
%%SET E (1,2,3)
%%IF (C[2] = D[2])
  OK 1
%%ELSE
  Fel 1
%%ENDIF
%%IF (C[2] = D[3])
  Fel 2
%%ELSE
  OK 2
%%ENDIF
%%IF (C[2] # D[3])
  OK 3
%%ELSE
  Fel 3
%%ENDIF
%%IF (C[2] # D[2])
  Fel 4
%%ELSE
  OK 4
%%ENDIF
%%IF (C = D)
  Fel 5
%%ELSE
  OK 5
%%ENDIF
%%IF (E = D)
  OK 6
%%ELSE
  Fel 6
%%ENDIF
%%IF ({1,2,3} (%%(D)) AND A (?) OR {1,2,3,4,5,6} (%%(D)) AND {1,3,5}[0] = D[3])
  OK 7
%%ELSE
  Fel 7
%%ENDIF
%%IF ({3,1,2}[2] < {1,2,3,4,5,6}[2])
  OK 8
%%ELSE
  Fel 8
%%ENDIF
%%IF (C[2] < 2)
  Fel 9
%%ELSE
  OK 9
%%ENDIF
%%IF (2 > C[2])
  Fel 10
%%ELSE
  OK 10
%%ENDIF
%%IF (5 > D[3])
  OK 11
%%ELSE
  Fel 11
%%ENDIF
%%IF ({3,1,2}[3] <= {1,2,3,4,5,6}[2])
  OK 12
%%ELSE
  Fel 12
%%ENDIF
%%IF (C[2] <= 2)
  OK 13
%%ELSE
  Fel 13
%%ENDIF
%%IF (2 >= C[2])
  OK 14
%%ELSE
  Fel 14
%%ENDIF
%%IF (5 >= D[3])
  OK 15
%%ELSE
  Fel 15
%%ENDIF
%%SET HEJ (HOPP)
%%SET KALLE (HOPP)
%%IF (HEJ(HOPP))
  OK 16
%%ELSE
  Fel 16
%%ENDIF
%%IF (HEJ(KALLE))
  Fel 17
%%ELSE
  OK 17
%%ENDIF
%%SET VAR1 (1,2)
%%SET VAR2 (1,2)
%%SET VAR3 (2,1)
%%SET VAR4 (1,3)
%%SET VAR5 (3,2)
%%IF (VAR1 = VAR2)
  OK 18
%%ELSE
  Fel 18
%%ENDIF
%%IF (VAR1 = VAR4)
  Fel 19
%%ELSE
  OK 19
%%ENDIF
%%IF (VAR1 = VAR5)
  Fel 20
%%ELSE
  OK 20
%%ENDIF
%%IF (VAR1(%%(VAR3)) AND VAR3(%%(VAR1)))
  OK 21
%%ELSE
  Fel 22
%%ENDIF
%%IF (VAR1(%%(VAR1)))
  OK 23
%%ELSE
  Fel 23
%%ENDIF
%%SET VAR11 (1,2,3,4,5,6,7,8,9)
%%SET VAR12 (3,4)
%%SET VAR13 (5,6,7,8,9)
%%IF (VAR11 (1, 2, %%(VAR12), %%(VAR13)))
  OK 24
%%ELSE
  Fel 24
%%ENDIF
%%-- Partiell evaluaering
%%IF (5 = D[6])
`%%IF (5 = D[6])                                            * * * FACIT * * *
%%ENDIF
%%IF (D[6] # D[6])
`%%IF (D[6] # D[6])                                         * * * FACIT * * *
%%ENDIF
%%IF ({1,2,3}[5] < 7)
`%%IF ({1,2,3}[5] < 7)                                      * * * FACIT * * *
%%ENDIF
%%IF (1*UNDEF*UNDEF[7] > {1,2,3}[0])
`%%IF (UNDEF*UNDEF[7] > 3)                                  * * * FACIT * * * 
%%ENDIF
%%IF (UNDEF <= 94+C[2]+2*D[2])
`%%IF (UNDEF <= 100)                                        * * * FACIT * * *
%%ENDIF
%%IF (UNDEF >= UNDEF)
`%%IF (UNDEF >= UNDEF)                                      * * * FACIT * * *
%%ENDIF
%%IF (1=2)
  Fel 
%%ELSIF (UNDEF > 3)
`%%IF (UNDEF > 3)                                           * * * FACIT * * *
%%ELSIF (3 = 4)
  Fel
%%ELSIF (1=1)
`%%ELSE                                                     * * * FACIT * * *
%%ELSIF (C (D))
  Fel
%%ELSE
  Fel
%%ENDIF
%%IF (VAR11 (1,%%(VAR15), 2, %%(VAR14), %%(VAR13)))
`%%IF ({1, 2, 3, 4, 5, 6, 7, 8, 9} (`%%(VAR15), `%%(VAR14)))  * * * FACIT * * *
%%ENDIF
%%SET VAR15 (3)
%%SET VAR14 (4)
%%IF ({3,4} (1,%%(VAR15),2,%%(VAR14),5,6,7,8,9))
  Fel 25
%%ELSE
  OK 25
%%ENDIF
%%IF ({1,%%(VAR15),2,%%(VAR14),5,6,7,8,9} (3,4))
  OK 26
%%ELSE
  Fel 26
%%ENDIF
