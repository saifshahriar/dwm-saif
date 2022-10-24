#!/bin/sh

[ $(command -v doas) ] && auth=doas || auth=sudo

case "$1" in
	-h)
		echo "-i    or    --install    to install   dwm in   the system"
		echo "-r    or    --remove     to uninstall dwm from the system"

		#shellcheck disable=SC2006
		echo "-m    or    --make       to run `make` command"
		
		#shellcheck disable=SC2006
		echo "-mi   or                 to run `make` command"
	;;
	-m) make clean
		;;
	-i) $auth make clean install
		;;
esac
