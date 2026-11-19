FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://custom-motd"

do_install:append() {
    install ${UNPACKDIR}/custom-motd ${D}${sysconfdir}/motd
}
