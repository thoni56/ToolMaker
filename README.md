= ToolMaker

== What it is

ToolMaker is a set of tools to make compilers, analyzers and similar
tools. It creates a lexcial scanner (like `lex` et.al) and a parser
(like `yacc` et.al). But in addition it can also generate a lister
(modules handling input text and error messages). It is also build on
top of a powerful macro tool, `imp`, similar in function to m4 and
others.

== License

This is a project which contains original work by Kenth Ericsson,
Jerker Willander and others at SoftLab AB Sweden, including
myself. SoftLab as sold to Rational Software in 1997 which then resold
that to Ericsson some years later.

Although this would strictly be copyrighted material, but considering

- me being one of its authors and also one of the owners of SoftLab
- the almost 20 years that has gone by
- the low commercial value in this technology, given that there are a
  multitude of other tools available
- the missing documentation
- that I am willing to take this down if anyone objects

I'm making this repo of resurrected sources available, mostly for my
own use. Please consult me before creating forks.

== Current state

All licensing is removed, but the source for the licensing mechanism
is still here, but not cleaned or compiled recently. The same goes for
the `toolmake` utility, which creates an initial set of files for your
new ToolMaker-based project.

Otherwise the source compiles on cygwin and all tests run (using
[Jregr](https://github.com/thoni56/jregr).


== Acknowledgement

We, at SoftLab at that time, where all involved in this in some way. Thanks to

- Kenth Ericsson & Jerker Wilander for the theory behind the error
recovery in the parse generated by the ParseMaker.

- Tony Olsson for the core of the scanner logic.

- Myself, Michael Dahlgren, Håkan Pettersson for structuring this as a
  project and filling out the blanks.
