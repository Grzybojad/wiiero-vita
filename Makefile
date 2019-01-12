TARGET		:= Wiiero
TITLE	    := VITALIERO
SOURCES		:= src
			
INCLUDES	:= include

LIBS =  -lSDL_image -lSDL_mixer -lSDL -lvita2d -lfreetype\
	-lmikmod -lvorbisfile -lvorbis -logg -lsndfile -lScePvf_stub \
	-lSceAppMgr_stub -lSceCtrl_stub -lSceTouch_stub -lm -lSceAppUtil_stub -lScePgf_stub -ljpeg \
	-lc -lScePower_stub -lSceCommonDialog_stub -lpng16 -lz -lSceGxm_stub \
	-lSceSysmodule_stub -lSceHid_stub -lSceAudio_stub -lSceDisplay_stub -lSceLibKernel_stub 

CFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.c))
CPPFILES   := $(foreach dir,$(SOURCES), $(wildcard $(dir)/*.cpp))
BINFILES := $(foreach dir,$(DATA), $(wildcard $(dir)/*.bin))
OBJS     := $(addsuffix .o,$(BINFILES)) $(CFILES:.c=.o) $(CPPFILES:.cpp=.o) 

export INCLUDE	:= $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CXX      = $(PREFIX)-g++
CFLAGS  = $(INCLUDE) -g -Wl,-q -O3 -DPSP2
CXXFLAGS  = $(CFLAGS) -fno-exceptions -std=gnu++11 -fpermissive
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

$(TARGET).vpk: $(TARGET).velf
	vita-make-fself -s $< eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE) "$(TARGET)" param.sfo
	cp -f param.sfo sce_sys/param.sfo

%.velf: %.elf
	cp $< $<.unstripped.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET).velf $(TARGET).elf $(OBJS)