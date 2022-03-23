# ToolMaker Manual Sources

AsciiDoc port of the original _ToolMaker Reference Manual_.

> **DOC STATUS** — The entire _ToolMaker Reference Manual_ has now been ported to AsciiDoc and proofread.
> Although there are still some pending tasks to improve the document in the future, the manual is to be considered completed and production ready.

-----

**Table of Contents**

<!-- MarkdownTOC autolink="true" bracket="round" autoanchor="false" lowercase="only_ascii" uri_encoding="true" levels="1,2,3" -->

- [About](#about)
- [Changes](#changes)
    - [Book Partitioning and Cross References](#book-partitioning-and-cross-references)
    - [Text Changes and Conventions](#text-changes-and-conventions)
        - [Programming Languages Names](#programming-languages-names)
- [XRefs Custom Anchors](#xrefs-custom-anchors)

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


# XRefs Custom Anchors

Unless otherwise required, cross references in the source document rely on the basic AsciiDoc notation of enclosing the target section title within double chevrons (`<<`..`>>`).

But due to symmetric nature of the _ToolMaker Reference Manual_, there are some chapters and section which share the same raw title, so I had to add some custom section IDs in order to allow exact cross-reference targeting.

Below are reference tables indicating the custom anchor IDs which were added, their target section and its page number in the original printed manual.

In case of a chapter and section sharing a same raw title, the distinction is provided via the `ch.` and `sec.` prefixes:

|            anchor ID             |             target section            | page |
|----------------------------------|---------------------------------------|------|
| `ch.ToolMaker-Description-File`  | Ch. 4. The ToolMaker Description File | p.30 |
| `sec.ToolMaker-Description-File` | §3.1. The ToolMaker Description File  | p.27 |

In case of multiple chapters or sections with same raw titles but in different book parts, the distinction is provided by prefixes indicating the Maker tool their refer too (each book Part deals with a single Maker):

|           anchor ID           |          target section         |         Part        |  page |
|-------------------------------|---------------------------------|---------------------|-------|
| `tm.Options-Section`          | §4.1. The Options Section       | I. ToolMaker System | p.30  |
| `pm.Options-Section`          | §8.2.4. The Options Section     | II. ParserMaker     | p.86  |
| `sm.Options-Section`          | §12.2.3. The Options Section    | III. ScannerMaker   | p.140 |
| `lm.Options-Section`          | §16.1.2. The Options Section    | IV. ListerMaker     | p.202 |
| `tm.PL0-Example`              | App. A. The PL/0 Example        | I. ToolMaker System | p.45  |
| `pm.PL0-Example`              | App. E. The PL/0 Example        | II. ParserMaker     | p.111 |
| `sm.PL0-Example`              | App. I. The PL/0 Example        | III. ScannerMaker   | p.172 |
| `lm.PL0-Example`              | App. M. The PL/0 Example        | IV. ListerMaker     | p.220 |
| `pm.Semantic-Actions`         | §7.4. Semantic Actions          | II. ParserMaker     | p.63  |
| `sm.Semantic-Actions`         | §12.2.21. Semantic Actions      | III. ScannerMaker   | p.158 |
| `pm.List-Directive`           | The List Directive              | II. ParserMaker     | p.91  |
| `sm.List-Directive`           | The List Directive              | III. ScannerMaker   | p.144 |
| `pm.Principles-of-Operation`  | §10.1. Principles of Operation  | II. ParserMaker     | p.106 |
| `sm.Principles-of-Operation`  | §14.1. Principles of Operation  | III. ScannerMaker   | p.164 |
| `lm.Principles-of-Operation`  | §18.1. Principles of Operation  | IV. ListerMaker     | p.208 |
| `tm.Principles-of-Operation`  | Ch. 19. Principles of Operation | V. Toolmake         | p.232 |
| `pm.Common-Directives`        | Common Directives               | II. ParserMaker     | p.87  |
| `sm.Common-Directives`        | Common Directives               | III. ScannerMaker   | p.141 |
| `lm.Common-Directives`        | Common Directives               | IV. ListerMaker     | p.202 |
| `tm.Concepts-and-Assumptions` | Ch 1. Concepts and Assumptions  | I. ToolMaker System | p.22  |
| `pm.Concepts-and-Assumptions` | Ch 7. Concepts and Assumptions  | II. ParserMaker     | p.60  |
| `sm.Concepts-and-Assumptions` | Ch 11. Concepts and Assumptions | III. ScannerMaker   | p.134 |
| `lm.Concepts-and-Assumptions` | Ch 15. Concepts and Assumptions | IV. ListerMaker     | p.198 |
| `pm.Options`                  | §9.2. Options                   | II. ParserMaker     | p.104 |
| `sm.Options`                  | §13.2. Options                  | III. ScannerMaker   | p.162 |
| `lm.Options`                  | §17.2. Options                  | IV. ListerMake      | p.206 |
| `tm.Options`                  | §20.2. Options                  | V. Toolmake         | p.233 |
| `pm.The-Trace-Directive`      | The Trace Directive             | II. ParserMaker     | p.88  |
| `sm.The-Trace-Directive`      | The Trace Directive             | III. ScannerMaker   | p.142 |
| `pm.The-Vocabulary-File`      | §8.5. The Vocabulary File       | II. ParserMaker     | p.102 |
| `sm.The-Vocabulary-File`      | §12.4. The Vocabulary File      | III. ScannerMaker   | p.160 |
| `pm.Parameters`               | §9.1 Parameters                 | II. ParserMaker     | p.104 |
| `sm.Parameters`               | §13.1 Parameters                | III. ScannerMaker   | p.162 |
| `lm.Parameters`               | §17.1 Parameters                | IV. ListerMaker     | p.206 |
| `tm.Parameters`               | §20.1 Parameters                | V. Toolmake         | p.233 |
| `pm.Output-Files`             | Output Files                    | II. ParserMaker     | p.78  |
| `sm.Output-Files`             | Output Files                    | III. ScannerMaker   | p.138 |
| `pm.File-Descriptions`        | §8.1.1. File Descriptions       | II. ParserMaker     | p.77  |
| `sm.File-Descriptions`        | §12.1.1. File Descriptions      | III. ScannerMaker   | p.138 |

> **NOTE** — Even though I've added custom prefixes to all sections sharing a same title, it doesn't necessary mean that there are XRefs targetting each one of them (and often this isn't the case).
But I still deemed it worth enforcing the distinctive prefixes for consistency sake.

In other cases a custom section ID anchor was required due to the nature of the raw title, which would fail with the `<<`..`>>` notation.


|                   anchor ID                   |                    target section                    | page |
|-----------------------------------------------|------------------------------------------------------|------|
| `pl0.ToolMaker-Description`                   | A.2. pl0.tmk — The ToolMaker Description File        | p.45 |
| `pl0.Main-Program`                            | A.3. pl0.c — The Main Program                        | p.46 |
| `The-Import-Export-and-Declarations-Sections` | §8.2.5. The Import, Export and Declarations Sections | p.93 |

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
