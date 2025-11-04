# SRC
SRC = $(wildcard src/*.cpp)
ENGINESRC = $(wildcard src/engine/*.cpp)
WEBFLAGS = -Llibraries/web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 -Wno-unused-command-line-argument --preload-file resources

# OBJECTS
OBJECTS = $(SRC:src/%.cpp=$(BUILDDIR)%.o)
ENGINEOBJS = $(ENGINESRC:src/engine/%.cpp=$(BUILDDIR)%.o)
ENGINEOUT = build/libengine.a

# define misc
CC = g++
WEBCC = em++
RAYLIB ?= ./external/raylib-5.5/

# flags
RAYLIBFLAGS-X86 = -I$(RAYLIB) -L$(RAYLIB)x86 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
RAYLIBFLAGS-WEB = -I$(RAYLIB) -L$(RAYLIB)web -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# target
OUT = build/out 		# CHANGE THIS TO BE YOUR EXCECUTABLE NAME
BUILDDIR = build/

$(OUT): $(BUILDDIR) $(ENGINEOUT) $(OBJECTS) 
	$(CC) $(ENGINEOBJS) $(OBJECTS) -o $(OUT) $(RAYLIBFLAGS-X86) 

web: $(BUILDDIR) $(ENGINEOUT) $(OBJECTS)
	$(WEBCC) $(SRC) $(ENGINESRC) -o $(BUILDDIR)index.html $(RAYLIBFLAGS-WEB) $(WEBFLAGS)

$(ENGINEOUT): $(ENGINEOBJS) # -c makes it not link
	ar rcs $(ENGINEOUT) $(ENGINEOBJS)

$(BUILDDIR)%.o: src/%.cpp | $(BUILDDIR)
	$(CC) -c $< -o $@

$(BUILDDIR)%.o: src/engine/%.cpp | $(BUILDDIR)
	$(CC) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -r $(BUILDDIR)

run: $(OUT)
	$(OUT)

.PHONY: clean run web
