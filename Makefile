
# Variables #
#############
CPP = g++
CPPFLAGS = -std=c++11 -fPIC -pedantic -Wall -Werror -g
NAME = ims_project
SOURCE = src/main.cpp src/component.hpp src/connection.hpp src/place.hpp src/token.hpp src/transition.hpp
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
clean:
	-rm $(NAME)
	-rm $(ARCHIVE_NAME).tar.gz

pack:
	tar cfz $(ARCHIVE_NAME).tar.gz *
