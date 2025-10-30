# SRC
SRC = $(wildcard src/*.cpp)
ENGINESRC = $(wildcard src/engine/*.cpp)

# OBJECTS
OBJECTS = $(SRC:src/%.cpp=$(BUILDDIR)%.o)
ENGINEOBJS = $(ENGINESRC:src/engine/%.cpp=$(BUILDDIR)%.o)
ENGINEOUT = build/libengine.a

# define misc
CC = g++
RAYLIB ?= ./external/raylib-5.5/

# flags
ENGINEFLAGS = $(ENGINEOUT) -L$(BUILDDIR) -lengine
RAYLIBFLAGS = -I$(RAYLIB) -L$(RAYLIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LDFLAGS =

# target
OUT = build/out 		# CHANGE THIS TO BE YOUR EXCECUTABLE NAME
BUILDDIR = build/

$(OUT): $(BUILDDIR) $(ENGINEOUT) $(OBJECTS) 
	$(CC) $(OBJECTS) -o $(OUT) $(LDFLAGS) $(RAYLIBFLAGS) $(ENGINEFLAGS)

$(ENGINEOUT): $(ENGINEOBJS) # -c makes it not link
	ar rcs $(ENGINEOUT) $(ENGINEOBJS)

$(BUILDDIR)%.o: src/%.cpp $(BUILDDIR)
	$(CC) -c $< -o $@

$(BUILDDIR)%.o: src/engine/%.cpp $(BUILDDIR)
	$(CC) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -r $(BUILDDIR)

run: $(OUT)
	$(OUT)

.PHONY: clean game
