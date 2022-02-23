# ToolMaker Documentation Sources

AsciiDoc port of the original documentation, converted by [Tristano Ajmone].


-----

**Table of Contents**

<!-- MarkdownTOC autolink="true" bracket="round" autoanchor="false" lowercase="only_ascii" uri_encoding="true" levels="1,2,3" -->

- [Directory Contents](#directory-contents)
- [Building](#building)
- [System Requirements](#system-requirements)

<!-- /MarkdownTOC -->

-----

# Directory Contents

- [`/man-pages/`][man-pages/] — man pages sources.
- [`/ref-man/`][ref-man/] — _ToolManker Reference Manual_ sources (WIP).


# Building

The documentation is automated via [Rake], which is now included with Ruby.

Open the CMD/shell in any repository folder and just type:

    rake

For more info on the available Rake tasks, type:

    rake -T


# System Requirements

In order to build the documentation from source you'll need:

- Ruby 3
- Asciidoctor (>= 2.0.17)
- [Rouge] (>= 3.27.0)

<!-----------------------------------------------------------------------------
                               REFERENCE LINKS
------------------------------------------------------------------------------>

[Tristano Ajmone]: https://github.com/tajmone "View Tristano Ajmone's GitHub profile"

[Rake]: https://ruby.github.io/rake/ "Visit Rake website"
[Rouge]: https://rouge-ruby.github.io/ "Visit Rouge website"

<!-- project files and folders -->

[man-pages/]: ./man-pages/ "Navigate to man pages source folder"
[ref-man/]: ./ref-man/ "Navigate to Reference Manual source folder"

<!-- EOF -->
