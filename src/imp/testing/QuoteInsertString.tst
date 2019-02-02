%%--
%%-- Kör detta med imp -i
%%--
%%BEGIN(foo(data))
`%%SET fum ("hej")
%%(data)
%%END(foo)
%%--
%%-- I raden nedan funkar det inte att "eskejpa bort en insert":
%%INCLUDE (foo ("`%%(fum)"))
%%--
%%-- men i nästa rad funkar det:
hemskt mycket `%%(fum)
%%-- och i detta fall ska det inte fungera enligt manualen, även om imp/75
%%-- antyder att det vore bra...
%%INCLUDE (foo ("%`%(fum)"))
%%--
%%-- Jag vill alltså egentligen producera följande (förutom kommentarstecknena):
%%-- %%SET fum ("hej")
%%-- %%(fum)
%%-- hemskt mycket %%(fum)
