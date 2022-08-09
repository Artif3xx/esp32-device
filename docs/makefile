#  vim: set ts=4 sw=4 tw=0 foldenable foldmethod=syntax foldclose=all autochdir:
# Uncomment lines below if you have problems with $PATH
SHELL := /bin/bash
#PATH := /usr/local/bin:$(PATH)
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
DOXYGEN_OUTPUT_DIRECTORY = './doc/docs'

doxygen:
	mkdir $(DOXYGEN_OUTPUT_DIRECTORY)
	sed -i -re "/PROJECT_NUMBER\s+[=]/ s/[=]/& "$$(git rev-parse HEAD)"/" DOXYFILE
	sed -i -re '/^EXTRACT_(ALL)|(PRIVATE)|(STATIC)/ s/NO/YES/g; /^CALL_GRAPH/ s/NO/YES/; /^HAVE_DOT/ s/NO/YES/g' Doxygen
	sed -i -re '/^FILE_PATTERNS/     s/=(.*)/& *.ino *.c *.txt *.h *.cpp /' Doxygen
	sed -i -re '/^EXTENSION_MAPPING/ s/=(.*)/& ino=c/' Doxygen
	sed -i -re '/^OUTPUT_DIRECTORY/  s/=(.*)/& doc/' Doxygen
	sed -i -re '/^ABREVIATE_BRIEF/ s/=/&"The $$name class"   "The $$name widget"  "The $$name file"   is  provides  specifies  contains  represents  a  an  the/' Doxygen
	doxygen DOXYFILE