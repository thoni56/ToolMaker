%%IF(foo(?))
Set to <%%(foo)>
%%ELSE
Not set!
%%ENDIF
%%SET foo(1)
%%IF(foo(?))
Set to <%%(foo)>
%%ELSE
Not set!
%%ENDIF
