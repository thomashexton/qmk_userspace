# Pull in the shared users/thomashexton/ userspace. QMK auto-includes
# users/<keymap-name>/, which only works when the keymap is literally named
# "thomashexton"; this variant has a different name, so point it explicitly.
USER_NAME = thomashexton

VIA_ENABLE = yes
VIAL_ENABLE = yes
VIAL_INSECURE = yes
LTO_ENABLE = yes

QMK_SETTINGS = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
