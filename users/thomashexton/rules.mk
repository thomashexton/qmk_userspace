CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes

SRC += $(USER_PATH)/thomashexton.c

# Conditionally include maccel feature only if enabled by keyboard
ifeq ($(strip $(MACCEL_ENABLE)), yes)
	include $(USER_PATH)/features/maccel/rules.mk
endif
