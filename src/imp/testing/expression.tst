%%SET foo(5)
%%SET fie(6, 7)
%%(foo)
%%(-foo)
%%(foo+1)
%%( foo + 1 )
%%(foo + -1)
%%(foo - 8)
%%(foo - -8)
%%(foo + 5 * 8)
%%(foo + 5 * -8)
%%(foo + 8 / 4)
%%(foo + 8 / -4)
%%(8 / 4 + foo)
%%(8 / 4 + -foo)
%%(5 * (foo+3))
%%(5 * (fum+3))
%%IF(foo = 5)
OK!
%%ELSE
Error!
%%ENDIF
%%IF(fie = 6)
Error!
%%ELSE
OK!
%%ENDIF
%%IF(fie = fie)
OK!
%%ELSE
Error!
%%ENDIF
%%IF(fie[1] = 6)
OK!
%%ELSE
Error!
%%ENDIF
%%IF(foo # 6 AND foo > 4 AND foo >= 5 AND foo < 6 AND foo <= 5)
OK!
%%ELSE
Error!
%%ENDIF
%%IF(foo # 5 OR foo > 5 OR foo >= 6 OR foo < 5 OR foo <= 4)
Error!
%%ELSE
OK!
%%ENDIF
%%IF(foo = 3 + 2)
OK!
%%ELSE
Error!
%%ENDIF
%%SET foo(Hej, "Hej")
%%IF(foo[1] = foo[2] AND foo[2] = foo[1])
OK!
%%ELSE
Error!
%%ENDIF
%%IF(foo[1] = "Hej" AND foo[1] # "Hoj" AND foo[1] > "Haj" AND foo[1] >= "Hej" AND foo[1] < "Hoj" AND foo[1] <= "Hej")
OK!
%%ELSE
Error!
%%ENDIF
%%IF(foo[1] = "Haj" OR foo[1] # "Hej" OR foo[1] > "Hej" OR foo[1] >= "Hoj" OR foo[1] < "Hej" OR foo[1] <= "Haj")
Error!
%%ELSE
OK!
%%ENDIF
%%IF(foo[2] = "Hej" AND foo[2] # "Hoj" AND foo[2] > "Haj" AND foo[2] >= "Hej" AND foo[2] < "Hoj" AND foo[2] <= "Hej")
OK!
%%ELSE
Error!
%%ENDIF
%%IF(foo[2] = "Haj" OR foo[2] # "Hej" OR foo[2] > "Hej" OR foo[2] >= "Hoj" OR foo[2] < "Hej" OR foo[2] <= "Haj")
Error!
%%ELSE
OK!
%%ENDIF
