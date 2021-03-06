
# Variables #
#############
CPP = g++
CPPFLAGS = -std=c++11 -fPIC -pedantic -Wall -Werror -g -lrt
NAME = ims_project

BUILDDIR=build
SOURCEDIR=src
SRCS= $(wildcard $(SOURCEDIR)/*.cpp)
HDRS = $(wildcard $(SOURCEDIR)/*.hpp)
OBJS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

LOGIN1 = xuchyt03
LOGIN2 = xcoufa09
ARCHIVE_NAME = 02_$(LOGIN1)_$(LOGIN2).tar.gz

# Rules #
#########
all: build $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) -o $(NAME) $^

$(OBJS): $(BUILDDIR)%.o: $(SOURCEDIR)%.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@

debug: CPPFLAGS += -D DEBUG
debug: build $(NAME)

run:
	./$(NAME) skiers 1000

# Phony #
#########
.PHONY: clean pack build
.SILENT: clean pack build
build:
	-mkdir -p $(BUILDDIR)
clean:
	-rm -rf $(NAME) $(ARCHIVE_NAME) $(BUILDDIR)

pack:
	tar cfz $(ARCHIVE_NAME) $(SRCS) $(HDRS) Makefile dokumentace.pdf
