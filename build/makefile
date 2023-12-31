
################ Top configuration.
PRJ_TOP = ..
TARGET = baremetal
OBJDIR = obj

MCU =
#MCU =rv64imc

BUILD_STRICT = TRUE
BUILD_PRINT = FALSE

VER_FILE = version.c
################ source files ##############
# Source file들은 project TOP 에서의 위치를 나타낸다.
CSRC =	\
		cpu/startup.c \
		$(VER_FILE)

CPPSRC =

ASRC =

DATA =

LINK_SCRIPT = cpu/esp8266.ld \
			cpu/esp8266.rom.ld

################ Object ##############
OBJ =	$(CSRC:%.c=$(OBJDIR)/%.c.o) \
		$(CPPSRC:%.cpp=$(OBJDIR)/%.p.o) \
		$(ASRC:%.S=$(OBJDIR)/%.s.o) \
		$(DATA:%.bin=$(OBJDIR)/%.b.o)

LST =	$(OBJ:%.o=%.lst)
DEP =	$(OBJ:%.o=%.d)

################  Define
DEFINE =
#DEFINE += -DWCH_INT
#DEFINE += -D__riscv__

################  Library directory.
PRJ_LIB_DIR = driver

EXT_LIB_DIR = 

LIB_FILE = c_nano

LIB_OPT =	$(patsubst %,-L$(PRJ_TOP)/%,$(PRJ_LIB_DIR)) \
			$(patsubst %,-L%,$(EXT_LIB_DIR)) \
			$(patsubst %,-l%,$(LIB_FILE))

################  Include.
# Add relative path from $(PRJ_TOP)
PRJ_INC = build \
		cpu
		

# Add absolue path. (ex. c:/lib/inc)
EXT_INC =

INCLUDE =	$(patsubst %,-I$(PRJ_TOP)/%,$(PRJ_INC)) \
			$(patsubst %,-I%,$(EXT_INC))

################  Common Options for C, C++, ASM
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
FLAGS =
#FLAGS  = -march=$(MCU)
#FLAGS += -mabi=ilp32
#FLAGS += -mcmodel=medany
#FLAGS += -msmall-data-limit=8
FLAGS += -std=gnu99 # c89, c99, gnu89, gnu99
FLAGS += -mlongcalls
FLAGS += -funsigned-char
FLAGS += -funsigned-bitfields
FLAGS += -fshort-enums
#FLAGS += -fpack-struct  # CAUTION: RISC-V can't handle un-aligned load/save.
FLAGS += -fmessage-length=0

FLAGS += -Os
#FLAGS += -msave-restore 
FLAGS += -ffunction-sections
FLAGS += -fdata-sections 
#FLAGS += -fno-unit-at-a-time
#FLAGS += -mshort-calls

FLAGS += -Wa,-adhlns=$(@:.o=.lst)
FLAGS += -gdwarf-2
FLAGS += -Wno-comment

ifeq ($(BUILD_STRICT), TRUE)
FLAGS += -Wall
FLAGS += -Wunused
FLAGS += -Wextra
FLAGS += -Wstrict-prototypes
#CFLAGS += -Wundef # for undefined macro evaluation
FLAGS += -Wunreachable-code
FLAGS += -Wno-attributes # 
endif

FLAGS += -MMD -MP # dependancy generation.

################  C Options
CFLAGS  = $(FLAGS)
CFLAGS += $(DEP_OPT)
CFLAGS += $(DEFINE)
CFLAGS += $(INCLUDE)

################  C++ Options
CPPFLAGS  = $(FLAGS)
CPPFLAGS += $(DEP_OPT)
CPPFLAGS += $(DEFINE)
CPPFLAGS += $(INCLUDE)

################  Assembler Options
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex 
#       dump that will be displayed for a given single line of source input.
ASFLAGS  = $(FLAGS)
#ASFLAGS += -Wa,-gstabs,--listing-cont-lines=100
ASFLAGS += $(DEP_OPT)
ASFLAGS += $(DEFINE)
ASFLAGS += $(INCLUDE)

################  Linker Options
# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x801100,--defsym=__heap_end=0x80ffff

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--section-start,.data=0x801100,--defsym=__heap_end=0x80ffff

EXTMEMOPTS =

#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDS_OPT = $(patsubst %, -T $(PRJ_TOP)/%, $(LINK_SCRIPT))

LDFLAGS = -g
LDFLAGS += -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += $(LDS_OPT)
LDFLAGS += -nostartfiles
#LDFLAGS += -nodefaultlibs
#LDFLAGS += -nolibc
#LDFLAGS += -nostdlib
LDFLAGS += -Xlinker --gc-sections
LDFLAGS += -Xlinker --print-memory-usage
LDFLAGS += --specs=nosys.specs
#LDFLAGS += --specs=nano.specs
#LDFLAGS += -mcmodel=medany
#LDFLAGS += -msmall-data-limit=8
LDFLAGS += -fmessage-length=0
LDFLAGS += -ffunction-sections
LDFLAGS += -fdata-sections
#LDFLAGS += -fsigned-char
#LDFLAGS += -fno-common
#LDFLAGS += -mabi=lp64
################### Action #################
# add @ for silent.
#GNU_PRIFIX = xtensa-lx106-elf-

CC 		= $(GNU_PREFIX)gcc
OBJCOPY	= $(GNU_PREFIX)objcopy
OBJDUMP	= $(GNU_PREFIX)objdump
SIZE	= $(GNU_PREFIX)size
AR		= $(GNU_PREFIX)ar rcs
NM		= $(GNU_PREFIX)nm

SHELL = sh
REMOVE = rm -f
REMOVEDIR = rm -rf
COPY = cp

ifeq ($(BUILD_PRINT), TRUE)
# some trick.
C_MAKE	= $(CC)
CPP_MAKE= $(CC)
ASM_MAKE= $(CC)
ELF_MAKE= $(CC)
else
# some trick.
C_MAKE	= @$(CC)
CPP_MAKE= @$(CC)
ASM_MAKE= @$(CC)
ELF_MAKE= @$(CC)
endif

INFO 	= @echo Making: $@
DIR_CHK = @mkdir -p $(@D)

################ Object file
$(OBJDIR)/%.b.o : $(PRJ_TOP)/%.bin
	$(INFO)
	$(DIR_CHK)
	$(OBJCOPY) -I binary -O elf32 $< $@

$(OBJDIR)/%.c.o : $(PRJ_TOP)/%.c
	$(INFO)
	$(DIR_CHK)
	$(C_MAKE) -c $(CFLAGS) $< -o $@ 

$(OBJDIR)/%.p.o : $(PRJ_TOP)/%.cpp
	$(INFO)
	$(DIR_CHK)
	$(CPP_MAKE) -c $(CPPFLAGS) $< -o $@ 

$(OBJDIR)/%.s.o : $(PRJ_TOP)/%.S
	$(INFO)
	$(DIR_CHK)
	$(ASM_MAKE) -c $(ASFLAGS) $< -o $@

################### File Creation #################
all: elf lst hex size bin

$(PRJ_TOP)/$(VER_FILE):
	$(INFO)
	@echo "char* gpVersion = \"$$(date +%Y%m%d_%H%M%S)\";" > $@

%.elf: $(OBJ)
	$(INFO)
	$(DIR_CHK)
	$(ELF_MAKE) $(LDFLAGS) $^ $(LIB_OPT) -o $@ 

%.hex: %.elf
	$(INFO)
	$(DIR_CHK)
	$(OBJCOPY) -O ihex  $< $@

#%.bin: %.elf
#	$(INFO)
#	$(DIR_CHK)
#	$(OBJCOPY) -O binary $< $@

%.lss: %.elf
	$(INFO)
	$(DIR_CHK)
	$(OBJDUMP) -h -S -z $< > $@

%.sym: %.elf
	$(INFO)
	$(DIR_CHK)
	$(NM) -n $< > $@

%.a: $(OBJ)
	$(INFO)
	$(DIR_CHK)
	$(AR) $@ $^

################ Actions.
TARGET_ALL=	$(TARGET).elf $(TARGET).a \
			$(TARGET).hex $(TARGET).bin \
			$(TARGET).lss $(TARGET).sym $(TARGET).map

version:
	@echo "char* gpVersion = \"$$(date +%Y%m%d_%H%M%S)\";" > $(PRJ_TOP)/$(VER_FILE)

obj: $(OBJ)
lib: $(TARGET).a
elf: $(TARGET).elf
lst: $(TARGET).lss $(TARGET).sym
#bin: $(TARGET).bin $(TARGET).hex

size: $(TARGET).elf
	@$(SIZE) --format=sysv --radix=16 --common $<

# esptool.py --chip esp32c3 image_info $(TARGET).bin
# esptool.py --chip esp32c3 elf2image $(TARGET).elf
# esptool.py --chip esp32c3 -p COM17 write_flash 0 $(TARGET).bin
# esptool.py --chip esp32c3 -p COM17 write_flash --flash_freq 20m --flash_mode dio 0 $(TARGET).bin
# DoNotChgBin in download tool.

bin: $(TARGET).elf
	esptool --chip esp8266 elf2image --flash_mode dio --flash_size 4MB --flash_freq 20m $(TARGET).elf --output $(TARGET).
	@echo To program >> esptool --chip esp8266 -p COM3 write_flash 0 $(BIN_FILE)
	@echo BPS: 74880
prog:
	esptool --chip esp8266 -p COM3 write_flash 0 $(TARGET).0x00000.bin

# Display compiler version information.
gccversion : 
	$(CC) --version

clean:
	$(REMOVE) $(TARGET).*
	$(REMOVEDIR) $(OBJDIR)

# Include the dependency files.
-include $(patsubst %.c,$(OBJDIR)/%.c.d,$(CSRC))
-include $(patsubst %.cpp,$(OBJDIR)/%.p.d,$(CPPSRC))
-include $(patsubst %.S,$(OBJDIR)/%.S.d,$(ASRC))

# Listing of phony targets.
.PHONY : all obj elf bin hex lst size gccversion clean version
