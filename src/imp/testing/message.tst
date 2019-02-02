%%SET A (1)
%%MESSAGE (1+2*9-9*A) Lite till i slutet
%%MESSAGE (B*C+D)
Inget f|re n{sta rad
%%MESSAGE("Detta skall skrivas ut")
%%KEEP
%%MESSAGE("Detta skall inte skrivas ut")
%%ENDKEEP
%%COMMENT
%%MESSAGE("Detta skall inte skrivas ut")
%%ENDCOMMENT
%%BEGIN(foo)
%%MESSAGE("Detta skall inte skrivas ut")
%%END(foo)
%%MESSAGE("Detta skall ocks} skrivas ut")
