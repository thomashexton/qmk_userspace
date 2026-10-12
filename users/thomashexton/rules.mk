CAPS_WORD_ENABLE = yes
ifneq ($(strip $(KEYBOARD)),gpk60l_63r)
SRC += $(USER_PATH)/thomashexton.c
COMBO_ENABLE = yes
endif

ifeq ($(strip $(KEYBOARD)), bastardkb/charybdis/3x5/splinky_3)
	MOUSEKEY_ENABLE = yes
	OPT_DEFS += -DOTHER_KEYMAP_C=\"$(QMK_USERSPACE)/keyboards/bastardkb/charybdis/3x5/splinky_3/keymaps/$(KEYMAP)/keymap.c\"
	CPPFLAGS += -include $(QMK_USERSPACE)/keyboards/bastardkb/charybdis/3x5/splinky_3/keymaps/$(KEYMAP)/config.h
endif
