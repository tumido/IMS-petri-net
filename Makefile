
# Variables #
#############
CPP = g++
CPPFLAGS = -std=c++11 -fPIC -pedantic -Wall -Werror -g
NAME = ims_project

SRCS = $(shell find . -type f | grep src/.*\.cpp)
HDRS = $(shell find . -type f | grep src/.*\.hpp)
OBJS=$(subst .cpp,.o,$(SRCS))

LOGIN1 = xuchyt03
LOGIN2 = xcoufa09
ARCHIVE_NAME = 02_$(LOGIN1)_$(LOGIN2).tar.gz

# Rules #
#########
all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(NAME) $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@

run:
	./$(NAME)

# Phony #
#########
.PHONY: clean pack
.SILENT: clean pack
clean:
	-rm -rf $(NAME) $(ARCHIVE_NAME) $(OBJS)

pack:
	tar cfz $(ARCHIVE_NAME) $(SRCS) $(HDRS) Makefile
