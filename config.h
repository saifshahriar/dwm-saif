#include "colors.h"
#include "movestack.c"
#include "psudogaplessgrid.c"

#define ALT_TAG_DECOR_PATCH 1

#if ALT_TAG_DECOR_PATCH
	#define UNDERLINETAGS_PATCH 0                   /* Both Patches doesn't work togather */
#else
	#define UNDERLINETAGS_PATCH 1
#endif

/* Appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int maxborder = 1;        /* 1 means no border is shown when a window is maximized */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int warp               = 1;        /* 0 means no cursor warp when switching between windows or monitors */
static const int user_bh            = 2;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10" };
static char *colors[][3]            = {         /* Looks for colors in xresources file, if not found colors.h is used */
	/*               fg             bg             border   */
	[SchemeNorm] = { foreground,    background,    background },
	[SchemeSel]  = { accent,        background,    border },
};

/* First Window Center Patch */
static const float fw_height =  0.7;      /* Window height */
static const float fw_width  =  0.8;      /* Window width */
static const float fw_offy   = -0.05;     /* Y offset */

#if UNDERLINETAGS_PATCH
	/* Tags */
	static const char *tags[] = {
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		" 漣 "
	};

	/* Underline below the tags */
	static const unsigned int ulinepad     = 5;    /* horizontal padding between the underline and tag */
	static const unsigned int ulinestroke  = 3;    /* thickness / height of the underline */
	static const unsigned int ulinevoffset = 0;    /* how far above the bottom of the bar the line should appear */
	static const int          ulineall     = 0;    /* 1 to show underline on all tags, 0 for just the active ones */
#else
	static const char *tags[] = {
		"dev",
		"www",
		"sys",
		"doc",
		"vbox",
		"chat",
		"mus",
		"vid",
		"gfx"
	};

	static const char *alttags[] = {
		"[dev]",
		"[www]",
		"[sys]",
		"[doc]",
		"[vbox]",
		"[chat]",
		"[mus]",
		"[vid]",
		"[gfx]"
	};
#endif

/* Window Rules */
static const Rule rules[] = {
	/* class            instance    title   tags mask   isfloating  CenterThisWindow?   monitor */
	/* Terminals */
	{ "Alacritty",      NULL,       NULL,   0,          0,          1,                  -1 },
	{ "XTerm",          NULL,       NULL,   0,          0,          1,                  -1 },
	{ "kitty",          NULL,       NULL,   0,          0,          1,                  -1 },
	{ "st-256color",    NULL,       NULL,   0,          0,          1,                  -1 },
	{ "St",             NULL,       NULL,   0,          0,          1,                  -1 },
	{ "URxvt",          NULL,       NULL,   0,          0,          1,                  -1 },
	{ "xterm-256color", NULL,       NULL,   0,          0,          1,                  -1 },
	/* Browsers */
	{ "Brave-browser",  NULL,       NULL,   1 << 1,     0,          0,                  -1 },
	{ "Firefox",        NULL,       NULL,   1 << 1,     0,          0,                  -1 },
	{ "Netsurf-gtk3",   NULL,       NULL,   1 << 1,     0,          0,                  -1 },
	{ "Surf",           NULL,       NULL,   1 << 1,     0,          0,                  -1 },
	/* Floting Apps */
	{ "float-term",     NULL,       NULL,   0,          1,          0,                  -1 },
	{ "Gimp",           NULL,       NULL,   0,          1,          0,                  -1 },
	{ "Lxappearance",   NULL,       NULL,   0,          1,          0,                  -1 },
	{ "Nitrogen",       NULL,       NULL,   0,          1,          0,                  -1 },
	{ "Pavucontrol",    NULL,       NULL,   0,          1,          0,                  -1 },
	{ "TelegramDesktop",NULL,       NULL,   0,          1,          0,                  -1 },
};

/* Layout(s) */
static const float mfact          = 0.493;    /* factor of master area size [0.05..0.95] */
static const int   nmaster        = 1;        /* number of clients in master area */
static const int   resizehints    = 1;        /* 1 means respect size hints in tiled resizals */
static const int   lockfullscreen = 1;        /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	{ "[]=",      tile },
	{ ":::",      gaplessgrid },
};

/* Key Definitions */
#define MODKEY  Mod4Mask
#define META    Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };
static const char *dmenucmd[] = { "dmenu_run", "-p", "Run:", "-fn", "JetBrainsMono Nerd Font:size=10", NULL };

/* Keybindings */
static const Key keys[] = {
	/* modifier                     key        function        argument */
	/* Basic Programmes */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	/* Windows */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ META,                         XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_equal,  incnmaster,     {.i = +1} },
	{ MODKEY|ControlMask,           XK_minus,  incnmaster,     {.i = -1} },
	/* Layouts */
	{ MODKEY,                       XK_Tab,    setlayout,      {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglemaximize, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	/* Vanitygaps */
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,  incrogaps,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_g,      togglegaps,     {0} },
	/* Tags */
	{ MODKEY,                       XK_Left,   viewprev,       {0} },
	{ MODKEY,                       XK_Right,  viewnext,       {0} },
	{ MODKEY|ShiftMask,             XK_Left,   tagtoprev,      {0} },
	{ MODKEY|ShiftMask,             XK_Right,  tagtonext,      {0} },
	{ MODKEY,                       XK_Escape, toggleview,     {.ui = ~0 } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	/* WM Controls */
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	/* 
	 * xrdb_reload
	 * Modify the Xresources file and press the keybindings to apply the color.
	 * No need to run the command `xrdb -merge <Xresources> 
	 * `xrdb_reload` searches for files in two places
	 *     1. ~/.Xresources
	 *     2. ~/.config/X11/xresources
	 * second one is overwritten by the first one.
	 * If no Xresources file is not found in either one of the places,
	 * dwm uses default theme from the colors array.
	 */
	{ MODKEY,                       XK_F5,     xrdb_reload,    {.v = NULL } }, 
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },           /* Reload DWM */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },           /* Quit DWM */
};

/* Mouse Bindings */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkRootWin,           0,              Button1,        spawn,          SHCMD("dwm_menu") },
	{ ClkRootWin,           0,              Button3,        spawn,          SHCMD("dwm_menu") },
};

