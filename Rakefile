
require './_assets/rake/globals.rb'
require './_assets/rake/asciidoc.rb'

# ==============================================================================
# --------------------{  P R O J E C T   S E T T I N G S  }---------------------
# ==============================================================================

HTML_DOCS_OUT_DIR = 'doc'

# ==============================================================================
# -------------------------------{  T A S K S  }--------------------------------
# ==============================================================================

task :default => [:manpages, :refman]

## Clean & Clobber
##################
require 'rake/clean'
CLOBBER.include('doc/*.html')

## Man Pages
############
desc "Convert Man Pages to HTML"
task :manpages

MANPAGES_SRC_DIR = 'docs-src/man-pages'
MANPAGES_OUT_DIR = HTML_DOCS_OUT_DIR
MANPAGES_ADOC_DEPS = FileList["#{MANPAGES_SRC_DIR}/shared/*.adoc"]

MANPAGES_ADOC_OPTS = <<~HEREDOC
  --failure-level WARN \
  --verbose \
  --timings \
  --safe-mode unsafe \
  -a source-highlighter=rouge \
  -a rouge-style=thankful_eyes
HEREDOC

CreateAsciiDocHTMLTasksFromFolder(
  :manpages,
  MANPAGES_SRC_DIR,
  MANPAGES_ADOC_DEPS,
  MANPAGES_ADOC_OPTS,
  MANPAGES_OUT_DIR
)

## Reference Manual
###################
REFMAN_SRC = 'docs-src/ref-man/ToolMaker-Manual.asciidoc'
REFMAN_OUT_DIR = HTML_DOCS_OUT_DIR
REFMAN_OUT_DIR_ABSPATH = File.expand_path(REFMAN_OUT_DIR)
REFMAN_HTML = REFMAN_OUT_DIR + '/ToolMaker-Manual.html'
REFMAN_ADOC_DEPS = FileList['docs-src/ref-man/*.adoc']

REFMAN_ADOC_OPTS = <<~HEREDOC
  --failure-level WARN \
  --verbose \
  --timings \
  --safe-mode unsafe \
  -a source-highlighter=rouge \
  -a rouge-style=thankful_eyes \
  -a data-uri \
  -D #{REFMAN_OUT_DIR_ABSPATH}
HEREDOC

desc "Convert Reference Manual to HTML"
task :refman => REFMAN_HTML

file REFMAN_HTML => [REFMAN_SRC, *REFMAN_ADOC_DEPS] do |t|
  AsciidoctorConvert(REFMAN_SRC, REFMAN_ADOC_OPTS)
end
