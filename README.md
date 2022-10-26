# DWM - Dynamic Window Manager

My build of dwm with minimal patches. Go to [patches](https://github.com/saifshahriar/dwm-saif-git#patches) section to know more.

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

## Why another DWM fork?
DWM comes in pretty good shape. This fork of DWM tries to be minimal yet some features
that I thought is missing (for my personal use obviously). The word *minimal* is different from person to person. To be
fair, I even tried to get rid of the bar. Lol! Also, one of the main purpose for
this project is learning the *beautifully unsafe C programming language* that
dwm is written in. :/

### Features:
- Simple edited `config.def.h` file.
- Ability reload dwm without logging out. Default key for this is
`Mod4 + Shift + r`.
- Gaps and the ability to change the gaps on the fly. See `keybindings` section.
- *Smartgaps*: Show no gaps when there is only one window.
- Ability to set colours from `~/.Xresources` or `~/.config/X11/xresources` file. See more at [Xresources Section](https://github.com/saifshahriar/dwm-saif#xresources-settings).
- Centers terminal windows (or any windows defined in the config) to the center
if it is the only window in that tag. Also change the `height`, `width` and the
`y-offset` of that window.
- Custom height for bar.
- `Gaplessgrid` layout, but with gaps.
- Toggle minimize.
- No border when a window is minimized (can change the behaviour from the 
config).

### More to come?
- Maybe a `lua` config file. Not too crazy like `awesomewm`. I am not sure. Heh.

## Requirements
- In order to build dwm you need the Xlib header files.
- For colour emoji support, install `libxft-bgra`. Heres the [repo](https://github.com/uditkarode/libxft-bgra).

## Installation
Clone the repo:
```bash
git clone https://github.com/saifshahriar/dwm-saif dwm --depth=1
cd dwm
```

Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).
```bash
chmod +x ./install.sh
./install -i
```

*This script also copies the current contents of the folder to `/opt/dwm-saif`*

Enter the following command to build and install dwm after every change to the
files (if necessary as root):
```bash
make clean install
```

## Running dwm
### Startx
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

### Display Manager
If you are using a display manager (i.e. lightdm, sddm, gdm) and if you have
already ran the `./install -i` command, you should see it in the login screen
list.

### Status Bar
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


If you are using a display manager (i.e. `lightdm`, `sddm`), you might need to copy the minimum text below into `/usr/share/xsession/dwm.desktop` file:
```ini
[Desktop Entry]
Name=DWM
Exec=dwm
Type=XSession
```

## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Patches
Here are some of the patches that I have applied.

- actualfullscreen    - Actually toggle fullscreen for a window, instead of toggling the status bar and the monocle layout.
- alttagsdecoration   - An alternative text for tags which contain at least one window
- alwayscenter        - Always center floating windows.
- center first window - Center specific window if only one window.
- focusonnetactive	  - Focus when a window gets active even in some other tag.
- focusadjacenttag	  - Focus adjacent tag using left/right arrow keys.
- maximize            - Toggle maximize.
- movestack           - Move stacks in a tag using mod+shift+{j,k}
- noborder            - Noborder when only one window.
- pertag              - dwm pertag patch, which allow different type of window size in different tags and doesn't change if one changed in one tag.
- preserveonrestart   - Don't mashup all windows in a single tag on restarting dmw
- psudogaplessgrid    - Basically `gaplessgrid` layout. Psudo version is modified by me which adds gaps from `vanitygaps` patch.
- restartsig		  - Restart dwm without exiting logging back on.
- status2d            - Allows colors and rectangle drawing in DWM status bar.
- underline tags      - Underline below a tag.
- vanitygaps          - Adds gapps around the windows.
- xrdb                - Read colors from xresources. For this patch to work, run the command `xrdb -load <path-to-xresources>`

## Xresources Settings
This is an example for all the variables you can use to customize the colours of
dwm using `Xresources` file.

__Note that__, dwm will look for the config file first in the
`~/.config/X11/xresources` file. If not found, it will look for the
`~/.Xresources` file. You have to press `Mod4 + F5` to make the changes take
effect. This basically runs the `xrdb -merge <xresources>` command
```scss
! TokyoNight colors for Xresources
*background: #1a1b26
*foreground: #c0caf5

*color0: #15161e
*color1: #f7768e
*color2: #9ece6a
*color3: #e0af68
*color4: #7aa2f7
*color5: #bb9af7
*color6: #7dcfff
*color7: #a9b1d6

*color8: #414868
*color9: #f7768e
*color10: #9ece6a
*color11: #e0af68
*color12: #7aa2f7
*color13: #bb9af7
*color14: #7dcfff
*color15: #c0caf5
```

## Major Keybindings
`Super`(Mod4) key in the `Modkey`
| Keys                            | Events                                        |
|---------------------------------|-----------------------------------------------|
| Mod + Return                    | Open a terminal (Alacritty)                   |
| Mod + d                         | Launch `dmenu_run`                            |
| Mod + c                         | Close focused window                          |
| Mod + {k, j}                    | Move focus to the {next, prev} windows        |
| Mod + Shift + {k, j}            | Move focused window in stack                  |
| Mod + {h, l}                    | {Increase, Decrease} master pane size         |
| Alt + Tab                       | Cycle focus between windows                   |
| Mod + Tab                       | Toggle between `tile` and `grid` layout       |
| Mod + f                         | Toggle `fullscreen`                           |
| Mod + Space                     | Toggle `floating`                             |
| Mod + Shift + Space             | Toggle `maximize`                             |
| Mod + {1-9}                     | Goto tag {1-9}                                |
| Mod + Shift + {1-9}             | Move focused window to tag {1-9}              |
| Mod + {Left, Right}             | Goto {next, prev} tag                         |
| Mod + Shift + {Left, Right}     | Move focused window to {next, prev} tag       |
| Mod + {equal, minus}            | {Increase, Decrease} gaps                     |
| Mod + Shift + g                 | Toggle gaps                                   |
| Mod + Shift + q                 | Quit DWM                                      |
| Mod + Shift + r                 | Restart DWM                                   |

_See more keybinds from [`config.def.h`](https://github.com/saifshahriar/dwm-saif/blob/master/config.def.h)_
