/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = {"siji:size=11", "IosevkaCustom Nerd Font:size=11"};
static const char dmenufont[]       = "IosevkaCustom Nerd Font:size=11";
static const char norm_bg[]         = "#1F1F28";
static const char norm_border[]     = "#727169";
static const char norm_fg[]         = "#DCD7BA";
static const char sel_fg[]          = "#7E9CD8";
static const char sel_bg[]          = "#1F1F28";
static const char sel_border[]      = "#7FB4CA";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norm_fg, norm_bg, norm_border },
	[SchemeSel]  = { sel_fg, sel_bg,  sel_border  },
};

/* tagging */
static const char *tags[] = { "◯", "◯", "◯", "◯", "◯", "◯", "◯" };
static const char *tagsalt[] = { "⬤", "⬤", "⬤", "⬤", "⬤", "⬤", "⬤" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"", tile}, /* first entry is default */
    {"", NULL}, /* no layout function means floating behavior */
    {"", monocle},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]        = {"dmenu_run", "-m", dmenumon, NULL};
static const char *termcmd[]         = { "alacritty", NULL };
static const char *emacs[]           = { "emacsclient", "-c", "-a", "'emacs'", NULL };
static const char *browser[]         = { "librewolf", NULL };
static const char *ranger[]          = {"alacritty", "-e", "ranger", NULL};
static const char *cmus[]            = {"alacritty", "-e", "cmus", NULL};
static const char *nmtui[]           = { "alacritty", "-e", "nmtui", NULL };
static const char *lockscreen[]      = { "betterlockscreen", "--lock", NULL };
static const char *screenshot[]      = { "flameshot", "gui", NULL };
static const char *brightnessup[]    = { "brightnessctl", "set", "2.5%+", NULL };
static const char *brightnessdown[]  = { "brightnessctl", "set", "2.5%-", NULL };

#include <X11/XF86keysym.h>

static const Key keys[] = {
    /* modifier                     key                       function        argument */
    { MODKEY,                       XK_d,                     spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return,                spawn,          {.v = termcmd } },
    { MODKEY,                       XK_e,                     spawn,          {.v = ranger} },
    { MODKEY,                       XK_c,                     spawn,          {.v = cmus} },
    { MODKEY,                       XK_w,                     spawn,          {.v = browser}},
    { MODKEY|ShiftMask,             XK_w,                     spawn,          {.v = nmtui}},
    { MODKEY,                       XK_x,                     spawn,          {.v = lockscreen}},
    { 0,                            XF86XK_Calculator,        spawn,          {.v = emacs} },
    { 0,                            XK_Print,                 spawn,          {.v = screenshot} },
    { MODKEY,                       XK_BackSpace,             spawn,          SHCMD("sysact")},
    { MODKEY,                       XK_p,                     spawn,          SHCMD("cmus-remote --pause && pkill -RTMIN+20 dwmblocks")},
    { MODKEY,                       XK_bracketleft,           spawn,          SHCMD("cmus-remote --prev && pkill -RTMIN+20 dwmblocks")},
    { MODKEY|ShiftMask,             XK_bracketleft,           spawn,          SHCMD("cmus-remote --seek -10 && pkill -RTMIN+20 dwmblocks")},
    { MODKEY,                       XK_bracketright,          spawn,          SHCMD("cmus-remote --next && pkill -RTMIN+20 dwmblocks")},
    { MODKEY|ShiftMask,             XK_bracketright,          spawn,          SHCMD("cmus-remote --seek +10 && pkill -RTMIN+20 dwmblocks")},
    { 0,                            XF86XK_AudioMute,         spawn,          SHCMD("pamixer -t && pkill -RTMIN+10 dwmblocks")},
    { 0,                            XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pamixer -i 5 && pkill -RTMIN+10 dwmblocks")},
    { 0,                            XF86XK_AudioLowerVolume,  spawn,          SHCMD("pamixer -d 5 && pkill -RTMIN+10 dwmblocks")},
    { 0,                            XF86XK_MonBrightnessUp,   spawn,          {.v = brightnessup}},
    { 0,                            XF86XK_MonBrightnessDown, spawn,          {.v = brightnessdown}},

    { MODKEY,                       XK_b,                     togglebar,      {0} },
    { MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,                     inplacerotate,  {.i = +1} },
    { MODKEY|ShiftMask,             XK_k,                     inplacerotate,  {.i = -1} },
    { MODKEY|ShiftMask,             XK_h,                     inplacerotate,  {.i = +2} },
    { MODKEY|ShiftMask,             XK_l,                     inplacerotate,  {.i = -2} },
    { MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_i,                     incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return,                zoom,           {0} },
    { MODKEY,                       XK_Tab,                   view,           {0} },
    { MODKEY|ShiftMask,             XK_q,                     killclient,     {0} },
    { MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_space,                 setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
    { MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
    { MODKEY,                       XK_Right,                 viewnext,       {0} },
    { MODKEY,                       XK_Left,                  viewprev,       {0} },
    { MODKEY|ShiftMask,             XK_Right,                 tagtonext,      {0} },
    { MODKEY|ShiftMask,             XK_Left,                  tagtoprev,      {0} },
    TAGKEYS(                        XK_1,                                     0)
    TAGKEYS(                        XK_2,                                     1)
    TAGKEYS(                        XK_3,                                     2)
    TAGKEYS(                        XK_4,                                     3)
    TAGKEYS(                        XK_5,                                     4)
    TAGKEYS(                        XK_6,                                     5)
    TAGKEYS(                        XK_7,                                     6)
    { MODKEY|ControlMask|ShiftMask, XK_q,                     quit,           {1} },
};

/* button definitions */
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

/* torus config */
static int torusenabled = 1;
static int wormholedelta = 1; // how close to the edge do we get before we take a wormhole to the other side.
