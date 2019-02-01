%%BEGIN (R1)
hejsan%%(R1)%%END (R1)
%%INCLUDE (R1)happ
%%INCLUDE (R1 (1))hopp
%%INCLUDE (R1)hipp
%%INCLUDE (R1 ())hupp
%%INCLUDE (R1)hepp
%%-- Kolla elementen i parameter
%%BEGIN (R2)
%%SET I (1)
%%LOOP (L1, R2)
Parameter nr %%(I) = %%(R2[I])
%%ESET I (I+1)
%%ENDLOOP (L1)
%%END (R2)
%%INCLUDE (R2)
%%INCLUDE (R2 ())
%%INCLUDE (R2 (A))
%%INCLUDE (R2 (A,B,%%(3*4)))
%%INCLUDE (R2)



%%EINCLUDE (%%(G)PELLE    (2,VAR,15-10+h*9))
%%INCLUDE (PELLE    (2,VAR,%%(15-10+h*9)))

%%BEGIN (A (B))
  B = %%(B)
  Hej%%END (A)

%%INCLUDE (A (13)) svejs

%%BEGIN(aStory)
%%(aStory[1]) had a little %%(aStory[2]).
%%END (aStory)

%%BEGIN(bStory (p1, p2))
%%(p1) had a little %%(p2)
%%END (bStory)

%%INCLUDE(aStory(Mary, lamb, hund))
%%INCLUDE(aStory(Peter, cat, hund))
%%INCLUDE(bStory(Mary, lamb))
%%INCLUDE(bStory(Peter, cat))


%%SET A (1,2)

%%BEGIN (R99)
%%(%%(R99[2]))
%%(R99[2])
%%END(R99)

%%EINCLUDE(R99 (0,A,2))
%%INCLUDE(R99 (0,A,2))
%%BEGIN (R21 (P1))
%%(P1)
%%END (R21)
%%INCLUDE (R21 ())
%%INCLUDE (R21 (1))
%%INCLUDE (R21 (1,2))
%%INCLUDE (R21 ({1,2}))
%%BEGIN (R22 (P1, P2))
%%(P1)
%%(P2)
%%END (R22)
%%INCLUDE (R22 ())
%%INCLUDE (R22 (1))
%%INCLUDE (R22 (1,2))
%%INCLUDE (R22 ({1,2}, {3,4}))
%%INCLUDE (R22 (1,2,3,4))
%%SET LOCAL1 ("Global1")
%%SET LOCAL2 ("Global2")
%%SET LOCAL3 ("Global3")
%%SET LOCAL4 ("Global4")
%%BEGIN (R23 (P1, P2, P3, P4), LOCAL1, LOCAL2, LOCAL3, LOCAL4)
%%(P1)                    V{rde p} P1 innan SET-satser
%%(P2)                    V{rde p} P2 innan SET-satser
%%(P3)                    V{rde p} P3 innan SET-satser
%%(P4)                    V{rde p} P4 innan SET-satser
%%(LOCAL1)                V{rde p} LOCAL1 innan SET-satser
%%(LOCAL2)                V{rde p} LOCAL2 innan SET-satser
%%(LOCAL3)                V{rde p} LOCAL3 innan SET-satser
%%(LOCAL4)                V{rde p} LOCAL4 innan SET-satser
%%SET LOCAL1 ("Local1")
%%SET LOCAL2 ("Local2")
%%SET LOCAL3 ("Local3")
%%SET LOCAL4 ("Local4")
%%(P1)                    V{rde p} P1 efter SET-satser
%%(P2)                    V{rde p} P2 efter SET-satser
%%(P3)                    V{rde p} P3 efter SET-satser
%%(P4)                    V{rde p} P4 efter SET-satser
%%(LOCAL1)                V{rde p} LOCAL1 efter SET-satser
%%(LOCAL2)                V{rde p} LOCAL2 efter SET-satser
%%(LOCAL3)                V{rde p} LOCAL3 efter SET-satser
%%(LOCAL4)                V{rde p} LOCAL4 efter SET-satser
%%END (R23)
%%INCLUDE (R23 (LOCAL1, LOCAL2, LOCAL3, LOCAL4))
%%(P1)                    V{rde p} P1 efter INCLUDE-satsen
%%(P2)                    V{rde p} P2 efter INCLUDE-satsen
%%(P3)                    V{rde p} P3 efter INCLUDE-satsen
%%(P4)                    V{rde p} P4 efter INCLUDE-satsen
%%(LOCAL1)                V{rde p} LOCAL1 efter INCLUDE-satsen
%%(LOCAL2)                V{rde p} LOCAL2 efter INCLUDE-satsen
%%(LOCAL3)                V{rde p} LOCAL3 efter INCLUDE-satsen
%%(LOCAL4)                V{rde p} LOCAL4 efter INCLUDE-satsen
%%EINCLUDE (R23 (LOCAL1, LOCAL2, LOCAL3, LOCAL4))
%%(P1)                    V{rde p} P1 efter EINCLUDE-satsen
%%(P2)                    V{rde p} P2 efter EINCLUDE-satsen
%%(P3)                    V{rde p} P3 efter EINCLUDE-satsen
%%(P4)                    V{rde p} P4 efter EINCLUDE-satsen
%%(LOCAL1)                V{rde p} LOCAL1 efter EINCLUDE-satsen
%%(LOCAL2)                V{rde p} LOCAL2 efter EINCLUDE-satsen
%%(LOCAL3)                V{rde p} LOCAL3 efter EINCLUDE-satsen
%%(LOCAL4)                V{rde p} LOCAL4 efter EINCLUDE-satsen
%%BEGIN (R1 (P1, P2), Local1, Local2)
%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
Begin P1 = %%(P1)
%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
R1[1] = %%(R1[1])

%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
Local1 = %%(Local1)
%%ESET Local1 (P1)
%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
Local1 = %%(Local1)

%%IF (P1 # P2)
%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
Including with P1 = %%(P1+1)
%%EINCLUDE (R1 (P1+1, 10))
%%ENDIF

%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
Local1 = %%(Local1)
%%ESET Local1 (P1)
%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
Local1 = %%(Local1)

%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
R1[1] = %%(R1[1])
%%LOOP (L1 <= P1) 
 %%--
%%ENDLOOP(L1)
End P1 = %%(P1)
%%END (R1)
%%EINCLUDE(R1 (0, 10))
