FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " file://dts-mods.dtsi"
EXTRA_DT_INCLUDE_FILES:append:linux = " dts-mods.dtsi"
EXTRA_DT_INCLUDE_FILES:append:linux-gnueabi = " dts-mods.dtsi"