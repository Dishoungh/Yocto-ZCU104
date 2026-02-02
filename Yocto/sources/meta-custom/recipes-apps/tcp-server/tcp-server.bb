#
# This file is the tcp-server recipe.
#

SUMMARY = "Simple tcp-server app"
SECTION = "KCNSC/apps"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# Source Files
SRC_URI += "file://tcp-server.c"
SRC_URI += "file://Makefile"

S = "${WORKDIR}"

# Dependencies

# Build-time Provision
PROVIDES = "tcp-server"

# Tasks
do_compile() {
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 tcp-server ${D}${bindir}
}