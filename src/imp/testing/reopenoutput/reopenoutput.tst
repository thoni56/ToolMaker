%%PROCESS("reopenoutput.tst.input1","reopenoutput.tst.fie")
%%PROCESS("reopenoutput.tst.input2","reopenoutput.tst.foo")
-- foo
%%INCLUDE("reopenoutput.tst.foo")
-- fie
%%INCLUDE("reopenoutput.tst.fie")
-- foo
%%INCLUDE("reopenoutput.tst.foo")
-- fie
%%INCLUDE("reopenoutput.tst.fie")
%%PROCESS("reopenoutput.tst.input1","reopenoutput.tst.foo")
-- foo
%%INCLUDE("reopenoutput.tst.foo")
-- fie
%%INCLUDE("reopenoutput.tst.fie")
