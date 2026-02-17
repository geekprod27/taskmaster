############
# COMMANDS #
############
CXX   := $(shell which clang++) -c
LINK  := $(shell which clang++)
MKDIR := $(shell which mkdir) -p
RM    := $(shell which rm) -rf

###########
# PROJECT #
###########
NAME := taskmaster

###############
# DIRECTORIES #
###############
DIR_INC := include
DIR_SRC := src
DIR_OBJ := obj
DIR_ELF := elf

#########
# FILES #
#########
SRC := $(strip \
	$(addprefix $(DIR_SRC)/, \
		$(addsuffix .cxx, \
			$(addprefix method/, \
				c_string_array \
				process \
				program \
			) \
			$(addprefix monitor/, \
				core \
			) \
			$(addprefix parser/, \
				core \
			) \
			$(addprefix prompt/, \
				core \
			) \
			error \
			main \
			run \
			usage \
		) \
	) \
)
OBJ := $(patsubst $(DIR_SRC)/%,$(DIR_OBJ)/%,$(SRC:.cxx=.o))
DEP := $(patsubst $(DIR_SRC)/%,$(DIR_OBJ)/%,$(SRC:.cxx=.d))
ELF := $(DIR_ELF)/$(NAME).elf

#########
# FLAGS #
#########
CPPFLAGS := $(strip \
	-I $(DIR_INC) \
	-MMD \
	-MP \
)
CXXFLAGS := $(strip \
	-Wall \
	-Wextra \
	-Wunreachable-code \
	-ferror-limit=1 \
	-std=c++23 \
)
LDFLAGS := $(strip \
)

ifeq ($(DEBUG),1)
CXXFLAGS += $(strip \
	-fsanitize=address \
	-g \
	-O0 \
)
LDFLAGS += $(strip \
	-fsanitize=address \
)
else
CXXFLAGS += -O2
endif

###############
# TPUT COLORS #
###############
BLACK          := 0
RED            := 1
GREEN          := 2
YELLOW         := 3
BLUE           := 4
MAGENTA        := 5
CYAN           := 6
WHITE          := 7
BRIGHT_BLACK   := 8
BRIGHT_RED     := 9
BRIGHT_GREEN   := 10
BRIGHT_YELLOW  := 11
BRIGHT_BLUE    := 12
BRIGHT_MAGENTA := 13
BRIGHT_CYAN    := 14
BRIGHT_WHITE   := 15

#############
# FUNCTIONS #
#############
FWIDTH_OF_STEP       := 9
FWIDTH_OF_COMPLEMENT := 29

# $1: step name
# $2: foreground color for complement text
# $3: complement text
define ANNOUNCE_PROGRESS
	printf '%$(FWIDTH_OF_STEP)s ' $1
	tput setaf $2 bold
	printf %-$(FWIDTH_OF_COMPLEMENT)s '$3'
	tput sgr0
	echo -n ' '
endef

# $1: foreground color for result text
# $2: result text
define ANNOUNCE_DONE
	echo -n '-> '
	tput setaf $1 bold
	echo -n '$2'
	tput sgr0
	echo
endef

#########
# RULES #
#########
.PHONY: all
all: $(ELF)

$(ELF): $(OBJ)
	@$(MKDIR) $(@D)
ifdef TERM
	@$(call ANNOUNCE_PROGRESS,Linking,$(BRIGHT_BLUE),obj/**/*.o)
endif
	@$(LINK) $(LDFLAGS) $(OUTPUT_OPTION) $^
ifdef TERM
	@$(call ANNOUNCE_DONE,$(GREEN),$@)
endif

-include $(DEP)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cxx
	@$(MKDIR) $(@D)
ifdef TERM
	@$(call ANNOUNCE_PROGRESS,Compiling,$(BRIGHT_BLUE),$<)
endif
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OUTPUT_OPTION) $<
ifdef TERM
	@$(call ANNOUNCE_DONE,$(GREEN),$@)
endif

.PHONY: clean
clean:
ifdef TERM
	@$(call ANNOUNCE_PROGRESS,Deleting,$(BRIGHT_RED),$(DIR_OBJ))
endif
	@$(RM) $(DIR_OBJ)
ifdef TERM
	@$(call ANNOUNCE_DONE,$(BRIGHT_BLACK),ø)
	@$(call ANNOUNCE_PROGRESS,Deleting,$(BRIGHT_RED),$(DIR_ELF))
endif
	@$(RM) $(DIR_ELF)
ifdef TERM
	@$(call ANNOUNCE_DONE,$(BRIGHT_BLACK),ø)
endif

.PHONY: re
re: clean all
