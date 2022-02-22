
require './_assets/rake/globals.rb'
require './_assets/rake/asciidoc.rb'

# ==============================================================================
# --------------------{  P R O J E C T   S E T T I N G S  }---------------------
# ==============================================================================

MANPAGES_SRC_DIR = 'docs-src/man-pages'
MANPAGES_OUT_DIR = 'doc'

MANPAGES_ADOC_OPTS = <<~HEREDOC
  --failure-level WARN \
  --verbose \
  --timings \
  --safe-mode unsafe \
  -a source-highlighter=rouge \
  -a rouge-style=thankful_eyes
HEREDOC

# ==============================================================================
# -------------------------------{  T A S K S  }--------------------------------
# ==============================================================================

task :default => [:manpages]

## Clean & Clobber
##################
require 'rake/clean'
CLOBBER.include('doc/*.html')

## Man Pages
############
desc "Convert Man Pages to HTML"
task :manpages
MANPAGES_ADOC_DEPS = FileList["#{MANPAGES_SRC_DIR}/shared/*.adoc"]
CreateAsciiDocHTMLTasksFromFolder(
  :manpages,
  MANPAGES_SRC_DIR,
  MANPAGES_ADOC_DEPS,
  MANPAGES_ADOC_OPTS,
  MANPAGES_OUT_DIR
)
