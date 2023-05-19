MODULES = 
BOARD ?= edu-ciaa-nxp
MUJU ?= ./muju

include $(MUJU)/module/base/makefile

OUT_DIR = ./build
DOX_DIR = $(OUT_DIR)/doc

$(OUT_DIR):
	mkdir $(OUT_DIR)

$(DOX_DIR): $(OUT_DIR)
	mkdir $(DOX_DIR)

doc: $(DOX_DIR)
	doxygen doxyfile

clean: $(OUT_DIR)
	rm -r $(OUT_DIR)