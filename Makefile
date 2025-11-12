# SRC
SRC = $(wildcard src/*.cpp)
ENGINESRC = $(wildcard src/engine/*.cpp)
WEBFLAGS = -Llibraries/web -sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 -Wno-unused-command-line-argument --preload-file ./resources/

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
RAYLIBFLAGS-WEB = \
	-I$(RAYLIB) \ -L$(RAYLIB)web \
	-lraylib \
	-s USE_GLFW=3 \
	-s ASYNCIFY \
	-DPLATFORM_WEB \
	--preload-file resources

# target
OUT = build/out 		# CHANGE THIS TO BE YOUR EXCECUTABLE NAME
BUILDDIR = build/

$(OUT): $(BUILDDIR) $(ENGINEOBJS) $(OBJECTS)
	$(CC) $(ENGINEOBJS) $(OBJECTS) -o $(OUT) $(RAYLIBFLAGS-X86) 

web: $(BUILDDIR) 
	$(WEBCC) \
  	$(SRC) \
		$(ENGINESRC) \
		-O0 \
		-o $(BUILDDIR)index.html \
		-I./external/raylib-5.5/ \
		-L./external/raylib-5.5/web \
		-lraylib \
		-s USE_GLFW=3 \
		-s ASYNCIFY \
		-s FORCE_FILESYSTEM=1 \
		-s TOTAL_MEMORY=134217728 \
		-s ALLOW_MEMORY_GROWTH=1 \
		--shell-file ./external/raylib-5.5/web/minshell.html \
		--preload-file resources/ \
		-lGL \

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
