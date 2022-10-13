# DWM - Dynamic Window Manager

My build of dmenu with minimal patches. Go to [patches](https://github.com/saifshahriar/dwm-saif-git#patches) section to know more.

<hr>

### Screenshots
<div align="center">
    <img src="https://github.com/saifshahriar/saifshahriar/blob/master/repo/dwm/Screenshot_2022-10-07-20-32-21_1366x768.png" width="500px">
    <img src="https://raw.githubusercontent.com/saifshahriar/saifshahriar/master/repo/dwm/Screenshot_2022-10-07-20-35-53_1366x768.png" width="500px">
</div>

- Terminal Emulator: Alacritty
- Colorscheme: Tokyonight

<br>
dwm is an extremely fast, small, and dynamic window manager for X.

## Requirements
- In order to build dwm you need the Xlib header files.
- For colour emoji support, install `libxft-bgra`. Heres the [repo](https://github.com/uditkarode/libxft-bgra).

## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

```bash
git clone https://github.com/saifshahriar/dwm-saif dwm --depth=1
cd dwm
make clean install
```

## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

```bash
exec dwm
```

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

```bash
DISPLAY=foo.bar:1 exec dwm
```

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

```bash
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
    sleep 1
done &
exec dwm
```

__If you want a similar status bar like mine, you can get it from my [dotfiles](https://github.com/saifshahriar/dotfiles/blob/master/.config/dwm/dwmbar.sh) repo.__

<div align="right">
    <img src="https://user-images.githubusercontent.com/89329547/194582023-6a81df49-5e77-48bb-a6f7-6dde0bcdc646.png">
</div>


## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Patches
Here are some of the patches that I have applied.

- actualfullscreen    - Actually toggle fullscreen for a window, instead of toggling the status bar and the monocle layout.
- alttagsdecoration   - An alternative text for tags which contain at least one window
- alwayscenter        - Always center floating windows.
- center first window - Center specific window if only one window.
- maximize            - Toggle maximize.
- movestack           - Move stacks in a tag using mod+shift+{j,k}
- noborder            - Noborder when only one window.
- pertag              - dwm pertag patch, which allow different type of window size in different tags and doesn't change if one changed in one tag.
- preserveonrestart   - Don't mashup all windows in a single tag on restarting dmw
- psudogaplessgrid    - Basically `gaplessgrid` layout. Psudo version is modified by me which adds gaps from `vanitygaps` patch.
- selfrestart         - Restart dwm without exiting logging back on.
- status2d            - Allows colors and rectangle drawing in DWM status bar.
- underline tags      - Underline below a tag.
- vanitygaps          - Adds gapps around the windows.
- xrdb                - Read colors from xresources. For this patch to work, run the command `xrdb -load <path-to-xresources>`

