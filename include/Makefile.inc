# compiler flags, tools and include variables
GCC=g++
GCC_FLAGS=-Wall -Werror -pedantic -g
INCLUDES=-Iinclude
LINKS=

FORMATTER=clang-format
FORMATTER_FLAGS=-i

FORMATTER=clang-format
DOC=doxygen
PANDOC=pandoc
RM=rm -rf

FORMATTER_FLAGS=-i
DOC_FLAGS=config/Doxyfile
PANDOC_FLAGS=-s --variable geometry:margin=0.75in --variable urlcolor:NavyBlue --variable colorlinks:true
PANDOC_HIGHLIGHT=--highlight-style tango

SRC_DIR := src
OBJ_DIR := obj
DOC_DIR := docs
BIN_DIR := .
INC_DIR := include
TEST_TARGET=$(BIN_DIR)/test
SIM_TARGET=$(BIN_DIR)/sim

XV6_GIT_URL=https://github.com/mit-pdos/xv6-riscv.git
XV6_SRC=xv6/xv6-riscv
XV6_BOOK_GIT_URL=https://github.com/mit-pdos/xv6-riscv-book.git
XV6_BOOK_SRC=xv6/xv6-riscv-book

# sources and objects needed to be linked together for unit test executable
test_src := $(patsubst %.cpp, $(SRC_DIR)/%.cpp, $(test_src))
test_obj := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(test_src))
catch_test_obj := $(OBJ_DIR)/catch2-main.o
exception_obj := 

# objects needed to be linked together for main simulation executable
sim_src := $(patsubst %.cpp, $(SRC_DIR)/%.cpp, $(sim_src))
sim_obj := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(sim_src))

# pdf files for assignment description documentation
assg_doc := $(patsubst %.pdf, $(DOC_DIR)/%.pdf, $(assg_doc))

## List of all valid targets in this project:
## ------------------------------------------
## all          : by default generate all executables
##                (test and debug)
##
.PHONY : all
all : $(TEST_TARGET) $(SIM_TARGET)


## test         : Build and link together unit test executable
##
$(TEST_TARGET) : $(test_obj) $(catch_test_obj) $(exception_obj) $(template_files)
	$(GCC) $(GCC_FLAGS) $(test_obj) $(catch_test_obj) $(exception_obj) -o $@


## sim          : Build and link together the main simulation executable
##
$(SIM_TARGET) : $(sim_obj) $(exception_obj) $(template_files)
	$(GCC) $(GCC_FLAGS) $(sim_obj) $(exception_obj) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(GCC) $(GCC_FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@


## setup        : Setup class resources.  Specifically, download the
##                xv6-riscv source code and the xv6-riscv-book latex
##                book source for use in this class.
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

## assgdocs     : Create assignment description documentation from
##                README.md project markdown file.
##                Need the following packages in linux DevContainer to
##                build the assgdocs
##                
##                $ sudo apt update
##                $ sudo apt install -y pandoc python3-pweave texlive texlive-fonts-recommended texlive-latex-recommended biber texlive-bibtex-extra texlive-fonts-extra texlive-science ghostscript
##
.PHONY : assgdocs
assgdocs : $(assg_doc)

$(assg_doc) : README.md
	${PANDOC} ${PANDOC_FLAGS} ${PANDOC_HIGHLIGHT} -o $@ $^


## clean        : Remove auto-generated files for a completely
##                clean rebuild
##
.PHONY : clean
clean  :
	$(RM) $(TEST_TARGET) $(SIM_TARGET) *.o *.gch
	$(RM) output html latex
	$(RM) $(test_obj) $(sim_obj)


## help         : Get all build targets supported by this build.
##
.PHONY : help
help : Makefile include/Makefile.inc
	@sed -n 's/^##//p' $^
