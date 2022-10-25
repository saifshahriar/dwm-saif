#!/bin/sh

[ $(command -v doas) ] && auth=doas || auth=sudo

make_clean() {
	make clean && $auth make clean install
}

install() {
	$auth make clean install
	$auth cp ./dwm.desktop /usr/share/xsessions/
}

uninstall() {
	$auth make uninstall
}

case "$1" in
	-h)
		echo "-i    or    --install    to install    dwm in   the system"
		echo "-r    or    --remove     to uninstall  dwm from the system"
		echo "-m    or    --make       to run 'make' command"
		echo "-mc                      to run 'make' command"
		echo "-mi                      to run 'make' command"
		;;
	-i)             "$(install)"
		;;
	--install)      "$(install)"
		;;
	-m)             make
		;;
	--make)         make
		;;
	-mc)            make clean
		;;
	-mi)            "$(make_clean)"
		;;
	--make-install) "$(make_clean)"
		;;
	-r)             "$(uninstall)"
		;;
	--remove)       "$(uninstall)"
		;;
esac
