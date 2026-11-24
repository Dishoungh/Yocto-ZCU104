FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Custom Bootscript
SRC_URI += "file://custom.boot.cmd"

do_compile:append() {
    mkimage -A arm64 -T script -C none -n "Custom U-Boot Script" -d "${UNPACKDIR}/custom.boot.cmd" boot.scr
}
