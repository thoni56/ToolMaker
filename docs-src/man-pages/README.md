# ToolMaker Man Pages Sources

AsciiDoc ports of the original ToolMaker man pages.


-----

**Table of Contents**

<!-- MarkdownTOC autolink="true" bracket="round" autoanchor="false" lowercase="only_ascii" uri_encoding="true" levels="1,2,3" -->

- [Directory Contents](#directory-contents)
- [Changes](#changes)

<!-- /MarkdownTOC -->

-----

# Directory Contents

- [`/shared/`][shared/] — man pages assets shared.
- [`imp(1).asciidoc`][imp1 adoc] — converted from [`../../src/imp/imp.1`][imp1 man]
- [`lmk(1).asciidoc`][lmk1 adoc] — converted from [`../../src/lmk/lmk.1`][lmk1 man]
- [`pmk(1).asciidoc`][pmk1 adoc] — converted from [`../../src/pmk/pmk.1`][pmk1 man]
- [`smk(1).asciidoc`][smk1 adoc] — converted from [`../../src/smk/smk.1`][smk1 man]
- [`toolmake(1).asciidoc`][toolmake1 adoc] — converted from [`../../src/toolmake/toolmake.1`][toolmake1 man]

# Changes

The man page documents were converted from man page format to AsciiDoc by [Tristano Ajmone].

Styles and formatting were adjusted according to need, especially the BNF definitions in `imp(1)` which underwent alignment and styling optimizations, to improve readability, but the original contents were left unaltered with the exception of a few typos fixes and minor adjustments to improve the AsciiDoc experience.

<!-----------------------------------------------------------------------------
                               REFERENCE LINKS
------------------------------------------------------------------------------>

[Tristano Ajmone]: https://github.com/tajmone "View Tristano Ajmone's GitHub profile"

<!-- project files and folders -->

[shared/]: ./shared/ "Navigate to shared assets folder"

[imp1 adoc]: ./imp(1).asciidoc "View source document"
[lmk1 adoc]: ./lmk(1).asciidoc "View source document"
[pmk1 adoc]: ./pmk(1).asciidoc "View source document"
[smk1 adoc]: ./smk(1).asciidoc "View source document"
[toolmake1 adoc]: ./toolmake(1).asciidoc "View source document"

[imp1 man]: ../../src/imp/imp.1 "View man page source"
[lmk1 man]: ../../src/lmk/lmk.1 "View man page source"
[pmk1 man]: ../../src/pmk/pmk.1 "View man page source"
[smk1 man]: ../../src/smk/smk.1 "View man page source"
[toolmake1 man]: ../../src/toolmake/toolmake.1 "View man page source"

<!-- EOF -->
