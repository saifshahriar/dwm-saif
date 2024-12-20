#include "colors.h"
#include "movestack.c"
#include "grid.c"

/* General Appearance and Behaviour */
static const unsigned int alttagsdecor   = 1;        /* 0 means no alternate tags */
static const unsigned int borderpx       = 2;        /* border pixel of windows */
static const unsigned int rect_indicator = 0;        /* 1 means rectangular indicator for active tags */
static const unsigned int smartborder    = 1;        /* 0 means borders are shown around a maximized window */
static const unsigned int smartgaps      = 1;        /* 1 means no outer gap when there is only one window */
static const unsigned int snap           = 32;       /* snap pixel */
static const unsigned int ulinetags      = 0;        /* 1 means underline under tags */
static const unsigned int warp           = 1;        /* 0 means no cursor warp when switching between windows or monitors */
static const char *fonts[]               = { "JetBrainsMono Nerd Font:size=10" };
static char *colors[][3]                 = {         /* Looks for colors in xresources file, if not found colors.h is used */
	/*                fg             bg             border   */
	[SchemeNorm]  = { foreground,    background,    background },
	[SchemeSel]   = { background,    accent,        border },
	[SchemeTitle] = { accent,        background,    NULL }
};

/* Bar */
static const unsigned int showbar  = 1;   /* 0 means no bar */
static const unsigned int topbar   = 1;   /* 0 means bottom bar */
static const unsigned int extrabar = 0;   /* 1 means show an extra bar at the bottom */
static const int user_bh           = 2;   /* 2 is the default spacing around the bar's font */
static const char statussep        = ';'; /* separator between statuses */

/* Gaps */
static const unsigned int gappih = 5;    /* horiz inner gap between windows */
static const unsigned int gappiv = 5;    /* vert inner gap between windows */
static const unsigned int gappoh = 5;    /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 5;    /* vert outer gap between windows and screen edge */

/* First Window Center Patch */
static const float fw_height =  0.7;   /* Window height */
static const float fw_width  =  0.8;   /* Window width */
static const float fw_offy   = -0.05;  /* Y offset */

/* Underline below the tags */
static const unsigned int ulinepad     = 5;    /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke  = 3;    /* thickness / height of the underline, setting the value to 0 hides the underline completely */
static const unsigned int ulinevoffset = 0;    /* how far above the bottom of the bar the line should appear */
static const unsigned int ulineall     = 0;    /* 1 to show underline on all tags, 0 for just the active ones */

/* Tags */
/* static const char *tags[] = { */
/* 	"  ", */
/* 	"  ", */
/* 	"  ", */
/* 	"  ", */
/* 	"  ", */
/* 	"  ", */
/* 	"  ", */
/* 	"  ", */
/* 	"  " */
/* }; */

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

/* Window Rules */
static const Rule rules[] = {
	/* Available values are:
	 *  .class,
	 *  .instance,
	 *  .title,
	 *  .tags,
	 *  .isfloating,
	 *  .iscentered,
	 *  .monitor
	 *
	 * xprop(1):
	 *  WM_CLASS(STRING) = instance, class
	 *  WM_NAME(STRING) = title
	 */
	/* Terminals */
	RULE(.class = "Alacritty",      .iscentered = 1)
	RULE(.class = "St",             .iscentered = 1)
	RULE(.class = "URxvt",          .iscentered = 1)
	RULE(.class = "XTerm",          .iscentered = 1)
	RULE(.class = "kitty",          .iscentered = 1)
	RULE(.class = "st-256color",    .iscentered = 1)
	RULE(.class = "xterm-256color", .iscentered = 1)
	/* Browsers */
	RULE(.class = "Brave-browser", .tags = 1 << 1)
	RULE(.class = "Netsurf-gtk3",  .tags = 1 << 1)
	RULE(.class = "Surf",          .tags = 1 << 1)
	RULE(.class = "firefox",       .tags = 1 << 1)
	/* Floting Apps */
	RULE(.class = "Lxappearance", .isfloating = 1)
	RULE(.class = "Nitrogen",     .isfloating = 1)
	RULE(.class = "Pavucontrol",  .isfloating = 1)
	RULE(.class = "Sxiv", .instance = "float", .isfloating = 1)
	RULE(.class = "float-term",   .isfloating = 1)
	/* Spawn in Respective Tags */
	RULE(.class = "Gimp",            .tags = 1 << 8)
	RULE(.class = "TelegramDesktop", .tags = 1 << 5)
	/* VMs */
	RULE(.class = "Virt-manager",       .tags = 1 << 4)
	RULE(.class = "VirtualBox Manager", .tags = 1 << 4)
};

/* Layout(s) */
static const float mfact          = 0.5;      /* factor of master area size [0.05..0.95] */
static const int   nmaster        = 1;        /* number of clients in master area */
static const int   resizehints    = 1;        /* 1 means respect size hints in tiled resizals */
static const int   lockfullscreen = 1;        /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	{ "[]=",      tile },    /* first entry is default */
	{ ":::",      grid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* Define new layouts from the array */
/* This makes monocle act as maximize layout */
#define MAXIMIZE &layouts[3]
/*#define MAXIMIZE {.v = &layouts[3]}*/

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
	{ MODKEY,                       XK_Tab,    layoutscroll,   {.i = +1 } },
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
	{ MODKEY,                       XK_grave,  view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY,                       XK_b,      toggleextrabar, {0} },
	{ MODKEY|ShiftMask,             XK_b,      toggleextrabar, {0} },
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
	{ ClkExBarLeftStatus,   0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarMiddle,       0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
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
