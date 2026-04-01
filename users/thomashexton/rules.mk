CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes

SRC += $(USER_PATH)/thomashexton.c

ifeq ($(strip $(KEYBOARD)), bastardkb/charybdis/3x5/v2/splinky_3)
	MOUSEKEY_ENABLE = yes
	OPT_DEFS += -DOTHER_KEYMAP_C=\"$(QMK_USERSPACE)/keyboards/bastardkb/charybdis/3x5/v2/splinky_3/keymaps/$(KEYMAP)/keymap.c\"
	OPT_DEFS += -DSPLIT_LAYER_STATE_ENABLE
	CPPFLAGS += -include $(QMK_USERSPACE)/keyboards/bastardkb/charybdis/3x5/v2/splinky_3/keymaps/$(KEYMAP)/config.h
endif
