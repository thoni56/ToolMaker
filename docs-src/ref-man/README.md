# ToolMaker Manual Sources

AsciiDoc port of the original _ToolMaker Reference Manual_.

> **WIP WARNING!** — This document is currently still work-in-progress, and many chapters have not yet been ported.

-----

**Table of Contents**

<!-- MarkdownTOC autolink="true" bracket="round" autoanchor="false" lowercase="only_ascii" uri_encoding="true" levels="1,2,3" -->

- [About](#about)
- [Changes](#changes)
    - [Book Partitioning and Cross References](#book-partitioning-and-cross-references)
    - [Text Changes and Conventions](#text-changes-and-conventions)
        - [Programming Languages Names](#programming-languages-names)

<!-- /MarkdownTOC -->

-----

# About

The ToolMaker manual was ported to AsciiDoc by [Tristano Ajmone].

Luckily [Thomas Nilefalk] managed to find a pristine paper copy of the original _ToolMaker Reference Manual_, which he then scanned and added to the repository as a [PDF document], which Tristano was then able to OCR and obtain a plain text file to work on.


# Changes

Adaptation to the AsciiDoc format required some formatting and styles adjustments, in order to better match the AsciiDoc standard way of formatting and organizing books contents, but also to take advantage of its modern editing features and the HTML output format.

All of these editorial freedoms aim to provide the best possible reading experience with the AsciiDoc to HTML output format, and none of theme altered the meaning of the original text in any way.

Since the only goal of this new digital edition is to provide an HTML version of the original manual (no intention to reprint on paper), it's our hope that these adjustments result in enhancement in line with the spirit of the  original edition.

Below is a detailed list of the changes, their motivations and formatting and styles conventions adopted in this new edition.

## Book Partitioning and Cross References

The chapters and sections numbering system is quite different from the original, as a result of the native way by which Asciidoctor handles section numbering.

Furthermore, direct references to page numbers were dropped in favour of auto-generated cross-references and dynamic links, since AsciiDoc is a format-agnostic source notation where contents and styles are separated, so there's no way to provide absolute page references, as the original printed manual did.

The _Index_ section will most likely be left out, since Asciidoctor only supports this feature in some formats (e.g. PDF) but not in HTML, which is our main target format at the moment.

Title casing was adjusted from all-caps to the _[Chicago Manual of Style]_ standard, and some terms' letter casing was adapted to the common practices of today.

## Text Changes and Conventions

The occasional typos were fixed, and UK English spelling enforced over US English (unless dealing with well established programming terminology borrowed from US English).

Consistent wording was enforced (e.g. when a same compound word occurred both with and without separating hyphen), along with similar minor text edits, which include the adoption of present day spelling of computer related terminology which was less formal in the past.

- `Object oriented` &rarr; `Object-oriented`

### Programming Languages Names

In-text occurrences of the programming languages names spelled as `'c'`, `'ansi-c'` and `'c++'` (code style added for source clarity) where changed to `C`, `ANSI{nbsp}C` (with a non-breaking space entity) and `C++` (i.e. C, ANSI&nbsp;C, C++), except when they clearly referred to their command line parameters counterparts for the target language, in which case their original spelling was retained (without the enclosing single quotes) and styled as inline code in the new edition (i.e. `` `c` ``, `` `ansi-c` `` and `` `c++` ``, in the source).

This was done for three reasons:

1. Avoid the complexity of AsciiDoc requiring backticks for curly quotes (i.e. ``'`c`'``, ``'`ansi-c`'`` and ``'`c++`'``), especially since these language names also appear in sections titles, thus affecting cross reference links.
2. They appear in section titles, and to justify their being lower-case within a title would require styling them as inline code (which would look quite ugly).
3. They would look anachronistic, since the prevalent convention today for spelling these languages is in the forms C, ANSI&nbsp;C and C++.

It's worth noting that although other programming language cited in the original text didn't follow the same convention of being lower-case and enclosed in single quotes (e.g. `FORTAN` and `Pascal`), languages of the C family were _always_ represented in lower-case and within single quotes.

I believe this was a deliberate choice by the original authors, to emphasize the use of these terms in reference to their roles as ToolMaker target languages (i.e. parameters or settings).
But I also believe that thanks to the fact that parameters and settings are now clearly styled as inline code in the new document, spelling these language names plainly (unless clearly referring to ToolMaker targets or parameters) is less confusing, since sometimes the term C refers to the C language in general (including ANSI C), whereas the use of the `c` notation would indicate exclusive reference to the `c` target (not including `ansi-c`).

I strived to preserve the original notation (as inline-code) whenever I felt that the text was referring explicitly to a specific ToolMake target language; but I might have accidentally adopted the plain notation in a few places where the specific target might have been more correct (e.g. in context applying only to the `c` target without `ansi-c`).
Hopefully these mistakes are few in number, and the context in which they occur should dispel any doubts in this regard.

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
