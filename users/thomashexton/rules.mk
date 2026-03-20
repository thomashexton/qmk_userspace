CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes

SRC += $(USER_PATH)/thomashexton.c

ifeq ($(strip $(KEYBOARD)), bastardkb/charybdis/3x5/v2/splinky_3)
	OPT_DEFS += -DOTHER_KEYMAP_C=\"$(QMK_USERSPACE)/keyboards/bastardkb/charybdis/3x5/v2/splinky_3/keymaps/$(KEYMAP)/keymap.c\"
	CPPFLAGS += -include $(QMK_USERSPACE)/keyboards/bastardkb/charybdis/3x5/v2/splinky_3/keymaps/$(KEYMAP)/config.h
endif
