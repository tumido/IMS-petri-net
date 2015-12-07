
# Variables #
#############
CPP = g++
CPPFLAGS = -std=c++11 -fPIC -pedantic -Wall -Werror -g
NAME = ims_project
SOURCE = $(shell find . -type f | grep src)
LOGIN1 = xuchyt03
LOGIN2 = xcoufa09
ARCHIVE_NAME = 02_$(LOGIN1)_$(LOGIN2)

# Rules #
#########
all:
	$(CPP) $(CPPFLAGS) -o $(NAME) $(SOURCE)

run:
	./$(NAME)

# Phony #
#########
.PHONY: clean pack
.SILENT: clean pack
clean:
	-rm $(NAME)
	-rm $(ARCHIVE_NAME).tar.gz

pack:
	tar cfz $(ARCHIVE_NAME).tar.gz *
