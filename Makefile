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
			$(addprefix monitor/, \
				core \
			) \
			$(addprefix parser/, \
				core \
			) \
			$(addprefix prompt/, \
				core \
			) \
			$(addprefix method/, \
				c_string_array \
			$(addprefix type/, \
				process \
				program \
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

#########################
# ANSI ESCAPE SEQUENCES #
#########################
ERASE_LINE := \e[2K

RESET_GRAPHICS    := \e[0m
SET_BOLD          := \e[1m
SET_FAINT         := \e[2m
SET_ITALIC        := \e[3m
SET_UNDERLINE     := \e[4m
SET_BLINK         := \e[5m
SET_INVERSE       := \e[7m
SET_HIDDEN        := \e[8m
SET_STRIKETHROUGH := \e[9m

RESET_BOLD          := \e[22m
RESET_FAINT         := \e[22m
RESET_ITALIC        := \e[23m
RESET_UNDERLINE     := \e[24m
RESET_BLINK         := \e[25m
RESET_INVERSE       := \e[27m
RESET_HIDDEN        := \e[28m
RESET_STRIKETHROUGH := \e[29m

SET_FOREGROUND_BLACK   := \e[30m
SET_FOREGROUND_RED     := \e[31m
SET_FOREGROUND_GREEN   := \e[32m
SET_FOREGROUND_YELLOW  := \e[33m
SET_FOREGROUND_BLUE    := \e[34m
SET_FOREGROUND_MAGENTA := \e[35m
SET_FOREGROUND_CYAN    := \e[36m
SET_FOREGROUND_WHITE   := \e[37m
SET_FOREGROUND_DEFAULT := \e[39m
SET_BACKGROUND_BLACK   := \e[40m
SET_BACKGROUND_RED     := \e[41m
SET_BACKGROUND_GREEN   := \e[42m
SET_BACKGROUND_YELLOW  := \e[43m
SET_BACKGROUND_BLUE    := \e[44m
SET_BACKGROUND_MAGENTA := \e[45m
SET_BACKGROUND_CYAN    := \e[46m
SET_BACKGROUND_WHITE   := \e[47m
SET_BACKGROUND_DEFAULT := \e[49m

SET_FOREGROUND_BRIGHT_BLACK   := \e[90m
SET_FOREGROUND_BRIGHT_RED     := \e[91m
SET_FOREGROUND_BRIGHT_GREEN   := \e[92m
SET_FOREGROUND_BRIGHT_YELLOW  := \e[93m
SET_FOREGROUND_BRIGHT_BLUE    := \e[94m
SET_FOREGROUND_BRIGHT_MAGENTA := \e[95m
SET_FOREGROUND_BRIGHT_CYAN    := \e[96m
SET_FOREGROUND_BRIGHT_WHITE   := \e[97m
SET_BACKGROUND_BRIGHT_BLACK   := \e[100m
SET_BACKGROUND_BRIGHT_RED     := \e[101m
SET_BACKGROUND_BRIGHT_GREEN   := \e[102m
SET_BACKGROUND_BRIGHT_YELLOW  := \e[103m
SET_BACKGROUND_BRIGHT_BLUE    := \e[104m
SET_BACKGROUND_BRIGHT_MAGENTA := \e[105m
SET_BACKGROUND_BRIGHT_CYAN    := \e[106m
SET_BACKGROUND_BRIGHT_WHITE   := \e[107m

#############
# FUNCTIONS #
#############
FWIDTH_OF_STEP       := 9
FWIDTH_OF_COMPLEMENT := 30

define ANNOUNCE_LINKAGE_PROGRESS
	printf '%$(FWIDTH_OF_STEP)s $(SET_BOLD)$(SET_FOREGROUND_BRIGHT_BLUE)%-$(FWIDTH_OF_COMPLEMENT)s$(RESET_GRAPHICS)' \
		'Linking' \
		'obj/**/*.o'
endef

define ANNOUNCE_LINKAGE_DONE
	printf '-> $(SET_BOLD)$(SET_FOREGROUND_GREEN)$@$(RESET_GRAPHICS)\n'
endef

define ANNOUNCE_COMPILATION_PROGRESS
	printf '%$(FWIDTH_OF_STEP)s $(SET_BOLD)$(SET_FOREGROUND_BRIGHT_BLUE)%-$(FWIDTH_OF_COMPLEMENT)s$(RESET_GRAPHICS)' \
		'Compiling' \
		'$<'
endef

define ANNOUNCE_COMPILATION_DONE
	printf '-> $(SET_BOLD)$(SET_FOREGROUND_GREEN)$@$(RESET_GRAPHICS)\n'
endef

define ANNOUNCE_DELETION_PROGRESS
	printf '%$(FWIDTH_OF_STEP)s $(SET_BOLD)$(SET_FOREGROUND_RED)%s$(RESET_GRAPHICS)... ' \
		Deleting \
		'$1'
endef

define ANNOUNCE_DELETION_DONE
	printf '$(SET_FOREGROUND_GREEN)done$(RESET_GRAPHICS)\n'
endef

#########
# RULES #
#########
.PHONY: all
all: $(ELF)

$(ELF): $(OBJ)
	@$(MKDIR) $(@D)
	@$(call ANNOUNCE_LINKAGE_PROGRESS)
	@$(LINK) $(LDFLAGS) $(OUTPUT_OPTION) $^
	@$(call ANNOUNCE_LINKAGE_DONE)

-include $(DEP)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cxx
	@$(MKDIR) $(@D)
	@$(call ANNOUNCE_COMPILATION_PROGRESS)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OUTPUT_OPTION) $<
	@$(call ANNOUNCE_COMPILATION_DONE)

.PHONY: clean
clean:
	@$(call ANNOUNCE_DELETION_PROGRESS,$(DIR_OBJ) and $(DIR_ELF))
	@$(RM) $(DIR_OBJ) $(DIR_ELF)
	@$(call ANNOUNCE_DELETION_DONE)

.PHONY: re
re: clean all
