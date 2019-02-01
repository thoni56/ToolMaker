-- Vanlig tilldelning ett element
%%SET V1 (11)
%%(V1)
11                                          * * * FACIT * * *   
-- Ut|ka med tv} element
%%SET V1 (,12,13)
%%(V1)
11,12,13                                    * * * FACIT * * *   
-- Vanlig tilldelning ett element
%%SET V1 (11)
%%(V1)
11                                          * * * FACIT * * *  
%%SET NULL ()
"%%(NULL)"
""                                          * * * FACIT * * *
%%SET STRINGS (A,B,"C","FLERA TECKEN", FLERA TECKEN)
%%(STRINGS)
A,B,C,FLERA TECKEN,FLERATECKEN              * * * FACIT * * *
%%SET SUBLIST (1, {2,3},4)
%%(SUBLIST)
1,{2,3},4                                   * * * FACIT * * *
%%SET V22 (12)
%%SET A (%%(V1) ,%%(V22), %%(V3))
%%(A)
11,12,`%%(V3)                                * * * FACIT * * *
%%SET V1 (21)
%%SET V22 (22)
%%(A)
11,12,`%%(V3)                                * * * FACIT * * *
%%SET V1 (31)
%%SET V22 (32)
%%(A)
11,12,`%%(V3)                                * * * FACIT * * *
%%SET V1 (1,2)
%%SET V3 (V1)
%%SET A (%%(V1), %%(V2), %%(V3))
%%SET %%(VAR) (%%(V1), %%(V2), %%(V3))
`%%SET `%%(VAR) (1,2,`%%(V2),V1)               * * * FACIT * * * 
%%SET %%(VAR2) (%%(V1), %%(6*87+9-VAR3), %%(V3))
`%%SET `%%(VAR2) (1,2,`%%(531-VAR3),V1)        * * * FACIT * * * 
%%(A)
1,2,`%%(V2),V1                               * * * FACIT * * *
%%SET V2 (3)
%%(A)
1,2,3,V1                                    * * * FACIT * * *
%%SET SUBLIST (1, %%(2), %%({3,4}))
%%(SUBLIST)
1,2,{3,4}                                   * * * FACIT * * *
%%({1,2})
{1,2}                                       * * * FACIT * * *
%%({1,{3,4,fem},2})
{1,{3,4,fem},2}                             * * * FACIT * * *
%%SET SUBLIST (1, {2,3},4)
%%(SUBLIST[0])
3                                           * * * FACIT * * *
%%(SUBLIST[1])
1                                           * * * FACIT * * *
%%(SUBLIST[2])
{2,3}                                       * * * FACIT * * *
%%(SUBLIST[3])
4                                           * * * FACIT * * *
%%(SUBLIST[4])
`%%(SUBLIST[4])                              * * * FACIT * * *
%%(SUBLIST[5])
`%%(SUBLIST[5])                              * * * FACIT * * *
%%(SUBLIST)
1,{2,3},4                                   * * * FACIT * * *
%%SET SUBLIST (1, %%(2), %%({3,4}))
%%(SUBLIST[0])
3                                           * * * FACIT * * *
%%(SUBLIST[1])
1                                           * * * FACIT * * *
%%(SUBLIST[2])
2                                           * * * FACIT * * *
%%(SUBLIST[3])
{3,4}                                       * * * FACIT * * *
%%(SUBLIST[4])
`%%(SUBLIST[4])                              * * * FACIT * * *
%%(SUBLIST[5])
`%%(SUBLIST[5])                              * * * FACIT * * *
%%(SUBLIST)
1,2,{3,4}                                   * * * FACIT * * *
