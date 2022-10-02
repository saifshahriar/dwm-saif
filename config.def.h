#include "colors.h"
#include "movestack.c"
#include "selfrestart.c"

#define ALT_TAG_DECOR_PATCH 1
#if ALT_TAG_DECOR_PATCH
#define UNDERLINETAGS_PATCH 0                   /* Both Patches doesn't work togather */
#endif

/* Appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 12;       /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10" };
static const char *colors[][3]      = {         // Support for Xresources file is there. So set it through the xresources file
	/*               fg             bg            border   */
	[SchemeNorm] = { foreground,    background,   background },
	[SchemeSel]  = { color4,        background,   color4 },
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
static const unsigned int ulinepad	    = 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 3;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int          ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */
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
	/* class        instance    title   tags mask   isfloating  CenterThisWindow?   monitor */
	{ "Alacritty",  NULL,       NULL,   0,          0,          1,                  -1 },
	{ "Gimp",       NULL,       NULL,   0,          1,          0,                  -1 },
	{ "Firefox",    NULL,       NULL,   1 << 8,     0,          0,                  -1 },
};

/* Layout(s) */
static const float mfact            = 0.5;  /* factor of master area size [0.05..0.95] */
static const int   nmaster          = 1;    /* number of clients in master area */
static const int   resizehints      = 1;    /* 1 means respect size hints in tiled resizals */
static const int   lockfullscreen   = 1;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *termcmd[]  = { "alacritty", NULL };

/* Keybindings */
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          SHCMD("dmenu_run -p 'Run:' -fn 'JetBrainsMono Nerd Font:size=10' -h 30")  },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	//{ MODKEY,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
    { MODKEY|ControlMask,           XK_m,      togglemaximize, {0}  },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
    /* Vanitygaps */
	{ MODKEY,                       XK_equal,      incrgaps,       {.i = +1 } },
	{ MODKEY,                       XK_minus,      incrgaps,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,      incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,      incrogaps,      {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_r,      self_restart,   {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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
};
