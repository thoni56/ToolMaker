# ToolMaker Manual Sources

AsciiDoc port of the original _ToolMaker Reference Manual_.

> **WIP WARNNING!** — This document is currently still work-in-progress, and many chapters have not yet been ported.

-----

**Table of Contents**

<!-- MarkdownTOC autolink="true" bracket="round" autoanchor="false" lowercase="only_ascii" uri_encoding="true" levels="1,2,3" -->

- [About](#about)
- [Changes](#changes)

<!-- /MarkdownTOC -->

-----

# About

The ToolMaker manual was ported to AsciiDoc by [Tristano Ajmone].

Luckily [Thomas Nilefalk] managed to find a pristine paper copy of the original _ToolMaker Reference Manual_, which he then scanned and added to the repository as a [PDF document], which Tristano was then able to OCR and obtain a plain text file to work on.


# Changes

Adaptation to the AsciiDoc format required some formatting and styles adjustments, in order to better match the AsciiDoc standard way of formatting and organizing books contents, but also to take advantage of its modern editing features and the HTML output format.

Most noticeably, the chapters and sections numbering system is quite different from the original, as a result of the native way by which Asciidoctor handles section numbering.

Furthermore, direct references to page numbers were dropped in favour of auto-generated cross-references and dynamic links, since AsciiDoc is a format-agnostic source notation, were contents and styles are separate, so that there's no way to provide absolute page references, as the original printed manual did.

The _Index_ section will most likely be left out, since Asciidoctor only supports this feature in some formats (e.g. PDF) but not in HTML, which is our main target format at the moment.

The occasional typos were fixed, and consistent wording was enforced (e.g. when a same compound word occurred both with and without separating hyphen), along with similar minor text edits.

Title casing was adjusted from all-caps to the _[Chicago Manual of Style]_ standard, and some terms' letter casing was adapted to the common practices of today.

All of the above mentioned editorial freedoms were aimed to provide the best possible reading experience with the AsciiDoc format and the HTML output format, and none of theme altered the meaning of the original text in any way.

Since the only goal of this new digital edition is to provide an HTML version of the original manual (no intention to reprint on paper), it's our hope that these adjustments result in enhancement in line with the spirit of the  original edition.

<!-----------------------------------------------------------------------------
                               REFERENCE LINKS
------------------------------------------------------------------------------>

[Chicago Manual of Style]: https://www.chicagomanualofstyle.org "Chicago Manual of Style website"

<!-- people -->

[Thomas Nilefalk]: https://github.com/thoni56 "View Thomas Nilefalk's GitHub profile"
[Tristano Ajmone]: https://github.com/tajmone "View Tristano Ajmone's GitHub profile"

<!-- project files and folders -->

[PDF document]: ../../doc/manual.pdf "View PDF document with scanned images of original ToolMaker Reference Manual"

<!-- EOF -->
