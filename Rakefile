
require './_assets/rake/globals.rb'
require './_assets/rake/asciidoc.rb'

# ==============================================================================
# --------------------{  P R O J E C T   S E T T I N G S  }---------------------
# ==============================================================================

ADOC_ASSETS_DIR = '_assets/adoc'
HTML_DOCS_OUT_DIR = 'doc'

# ==============================================================================
# -------------------------------{  T A S K S  }--------------------------------
# ==============================================================================

task :default => [:manpages, :refman, :docinfo]

## Clean & Clobber
##################
require 'rake/clean'
CLOBBER.include(
  '_assets-src/sass/*.css',
  '_assets/adoc/docinfo.html',
  'doc/*.html'
)

## Sass/CSS => Docinfo File
###########################
SASS_DIR = '_assets-src/sass'
SASS_DEPS = FileList["#{SASS_DIR}/*.scss"]
CSS_TARGET = "#{SASS_DIR}/toolmaker.css"
ADOC_DOCINFO = "#{ADOC_ASSETS_DIR}/docinfo.html"

desc "Build custom CSS via Sass"
task :sass => CSS_TARGET

file CSS_TARGET => SASS_DEPS do |t|
  cd SASS_DIR
  sh "sass toolmaker.scss:toolmaker.css"
  cd $repo_root, verbose: false
end

desc "Build Docinfo file w/CSS"
task :docinfo => ADOC_DOCINFO

file ADOC_DOCINFO => CSS_TARGET do |t|
  puts "\n# building docinfo file from CSS #"
  css_file = File.open(t.source)
  File.open(t.name, "w") do |docinfo_file|
    docinfo_file.write "<style>\n"
    css_file.each_line(chomp: true) do |line|
      docinfo_file.puts line
    end
    docinfo_file.write "</style>\n"
  end
  css_file.close
end

## Man Pages
############
desc "Convert Man Pages to HTML"
task :manpages

MANPAGES_SRC_DIR = 'docs-src/man-pages'
MANPAGES_OUT_DIR = HTML_DOCS_OUT_DIR
MANPAGES_ADOC_DEPS = FileList[
  "#{MANPAGES_SRC_DIR}/shared/*.adoc",
  "#{ADOC_ASSETS_DIR}/docinfo.html"
]

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
REFMAN_ADOC_DEPS = FileList[
  'docs-src/ref-man/*.adoc',
  'docs-src/ref-man/images/*.gif'
]

REFMAN_ADOC_OPTS = <<~HEREDOC
  --failure-level WARN \
  --verbose \
  --timings \
  --safe-mode unsafe \
  -a source-highlighter=rouge \
  -a rouge-style=thankful_eyes \
  -a docinfodir=#{$repo_root}/#{ADOC_ASSETS_DIR} \
  -a docinfo@=shared-head \
  -a data-uri \
  -D #{REFMAN_OUT_DIR_ABSPATH}
HEREDOC

desc "Convert Reference Manual to HTML"
task :refman => REFMAN_HTML

file REFMAN_HTML => [REFMAN_SRC, *REFMAN_ADOC_DEPS] do |t|
  AsciidoctorConvert(REFMAN_SRC, REFMAN_ADOC_OPTS)
end
