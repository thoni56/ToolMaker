%%LOOP(i<=4)
Hej%%(i)!
%%ENDLOOP(i)
%%--
%%LOOP(i <= 4)
Hopp%%(i)!
%%ENDLOOP(i)
%%KEEP
%%LOOP(i <= 4)
Kept%%(i)!
%%ENDLOOP(i)
%%ENDKEEP
%%LOOP(i <= 0)
Skall ej skrivas ut %%(i)!
%%ENDLOOP(i)
%%SET foo()
%%LOOP(i, foo)
Skall ej skrivas ut %%(i)!
%%ENDLOOP(i)
%%KEEP
%%LOOP(i <= 4)
Kept%%(i)!
%%ENDLOOP(i)
%%ENDKEEP
%%COMMENT
%%LOOP(i <= 4)
Commented%%(i)!
%%ENDLOOP(i)
%%ENDCOMMENT
%%SET foo(hej, hopp, i, lingonskogen)
%%LOOP(i <= foo[0])%%(foo[i]) %%ENDLOOP(i)
%%LOOP(i <= %%(foo[0]))%%(foo[i]) %%ENDLOOP(i)
%%LOOP(i <= %%(foo[1]))
%%(foo[i])
%%ENDLOOP(i)
%%LOOP(i, foo)%%(i) %%ENDLOOP(i)

%%BEGIN(aRegion)
%%LOOP(k <= 5)
%%(k)
%%ENDLOOP(k)
%%END(aRegion)
%%IF(k(?))
Error, k should not be defined!
%%ELSE
OK!
%%ENDIF
%%LOOP(i <= 2)
F|re inre loopen %%(i).
%%LOOP(j <= 2)
I inre loopen %%(i), %%(j).
%%ENDLOOP(j)
Efter inre loopen %%(i).
%%ENDLOOP(i)
%%LOOP(i, foo)
I loopen >%%(i)<
%%ENDLOOP(i)
Efter loopen >%%(i)<
%%LOOP(i <= foo[0])
I loopen >%%(i)<
%%ENDLOOP(i)
Efter loopen >%%(i)<
%%(LVAR)
`%%(LVAR)            * * * FACIT * * *
%%LOOP (LVAR <= 4)
%%(LVAR)
%%ENDLOOP(LVAR)
%%(LVAR)
5                   * * * FACIT * * *
%%LOOP (LVAR, 4)
%%(LVAR)
%%ENDLOOP(LVAR)
"%%(LVAR)"
""                  * * * FACIT * * *
%%SET A (1,2,LVAR,"LVAR")
%%LOOP (LVAR, A)
%%(LVAR)
%%(%%(LVAR))
%%(%%(%%(LVAR)))
%%ENDLOOP (LVAR)
%%LOOP (L, {%%(UNDEF), %%(A)})
%%LOOP (M <= A[2]*UNDEF)
  Iterera mera
%%ENDLOOP (M)
%%ENDLOOP (L)
%%-- Yttre loopen partialevalueras och den inre evalueras tre ggr
%%LOOP (L1 <= L2+3)
Lite text
%%LOOP (L2 <= 3)
En trippelrad
%%ENDLOOP (L2)
%%ENDLOOP(L1)
