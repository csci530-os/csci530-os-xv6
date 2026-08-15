# overall project name for this container/repository
PROJECT_NAME=csci530

# xv6 source code and book repository setup
XV6_GIT_URL=https://github.com/mit-pdos/xv6-riscv.git
XV6_SRC=xv6/xv6-riscv
XV6_BOOK_GIT_URL=https://github.com/mit-pdos/xv6-riscv-book.git
XV6_BOOK_SRC=xv6/xv6-riscv-book

# target directory locations for builds
SRC_DIR := src
OBJ_DIR := obj
DOC_DIR := docs
BIN_DIR := .
INC_DIR := include

# pdf files for repository description documentation
assg_doc  = ${PROJECT_NAME}.pdf
assg_doc := $(patsubst %.pdf, $(DOC_DIR)/%.pdf, $(assg_doc))

# compiler flags, tools and include variables
GCC=g++
GCC_FLAGS=-Wall -Werror -pedantic -g
INCLUDES=-Iinclude
LINKS=
RM=rm -rf

# source file auto formatting
FORMATTER=clang-format
FORMATTER_FLAGS=-i
DOC=doxygen
DOC_FLAGS=config/Doxyfile

# pandoc repository document generation
PANDOC=pandoc
PANDOC_FLAGS=-s --variable geometry:margin=0.75in --variable urlcolor:Blue --variable colorlinks:true
PANDOC_HIGHLIGHT=--highlight-style tango


## List of all valid targets in this project:
## ------------------------------------------------------------------
## all      : by default cause project setup to be performed
##
.PHONY : all
all : setup


## setup    : Setup class resources.  Specifically, download the
##            xv6-riscv source code and the xv6-riscv-book latex
##            book source for use in this class.
##
.PHONY : setup
setup :
	mkdir -p xv6
	if [ ! -d ${XV6_SRC} ]; then \
	    git clone ${XV6_GIT_URL} ${XV6_SRC} ; \
	else \
	    git -C ${XV6_SRC} pull ; \
	fi;
	if [ ! -d ${XV6_BOOK_SRC} ]; then \
	    git clone ${XV6_BOOK_GIT_URL} ${XV6_BOOK_SRC} ; \
	else \
	    git -C ${XV6_BOOK_SRC} pull ; \
	fi;
	cp -f xv6/patch/Makefile.xv6-riscv-book xv6/xv6-riscv-book/Makefile
	cp -f xv6/patch/Makefile.xv6-riscv-src-booklet xv6/xv6-riscv-book/xv6-riscv-src-booklet/Makefile	
	cp -f xv6/patch/runoff xv6/xv6-riscv-book/xv6-riscv-src-booklet/runoff

## assgdocs : Create repository description documentation from
##            README.md project markdown file.
##            Need the following packages in linux DevContainer to
##            build the assgdocs
##                
##            $ sudo apt update
##            $ sudo apt install -y pandoc python3-pweave texlive
##                          texlive-fonts-recommended texlive-latex-recommended
##                          biber texlive-bibtex-extra texlive-fonts-extra
##                          texlive-science ghostscript
##
.PHONY : assgdocs
assgdocs : $(assg_doc)

$(assg_doc) : README.md
	${PANDOC} ${PANDOC_FLAGS} ${PANDOC_HIGHLIGHT} -o $@ $^


## clean    : Remove auto-generated files for a completely
##            clean rebuild
##
.PHONY : clean
clean  :
	$(RM) $(XV6_SRC) $(XV6_BOOK_SRC)


## help     : Get all build targets supported by this build.
##
.PHONY : help
help : Makefile
	@sed -n 's/^##//p' $^
