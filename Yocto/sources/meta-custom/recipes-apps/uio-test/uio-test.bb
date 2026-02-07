#
# This file is the uio-test recipe.
#

SUMMARY = "Zero effort application"
SECTION = "apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI += "file://uio-test.c"
SRC_URI += "file://Makefile"

S = "${WORKDIR}"

do_compile() {
	oe_runmake
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 uio-test ${D}${bindir}
}
