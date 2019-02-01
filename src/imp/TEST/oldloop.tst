%%LOOP(i(4))
Hej%%(i)!
%%ENDLOOP(i)
%%--
%%LOOP(i(4))
Hopp%%(i)!
%%ENDLOOP(i)
%%KEEP
%%LOOP(i(4))
Kept%%(i)!
%%ENDLOOP(i)
%%ENDKEEP
%%LOOP(i(0))
Skall ej skrivas ut %%(i)!
%%ENDLOOP(i)
%%KEEP
%%LOOP(i(4))
Kept%%(i)!
%%ENDLOOP(i)
%%ENDKEEP
%%COMMENT
%%LOOP(i(4))
Commented%%(i)!
%%ENDLOOP(i)
%%ENDCOMMENT
%%SET foo(hej, hopp, i, lingonskogen)
%%LOOP(i(foo))%%(foo(i)) %%ENDLOOP(i)
%%LOOP(i(%%(foo(0))))%%(foo(i)) %%ENDLOOP(i)
%%LOOP(i(%%(foo(1))))
%%(foo(i))
%%ENDLOOP(i)
%%BEGIN(aRegion)
%%LOOP(k(5))
%%(k)
%%ENDLOOP(k)
%%END(aRegion)
%%IF(k(?))
Error, k should not be defined!
%%ELSE
OK!
%%ENDIF
%%LOOP(i(2))
F|re inre loopen %%(i).
%%LOOP(j(2))
I inre loopen %%(i), %%(j).
%%ENDLOOP(j)
Efter inre loopen %%(i).
%%ENDLOOP(i)
