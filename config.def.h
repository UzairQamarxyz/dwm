/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = {
    /*    "Arimo for Powerline:size=10:antialias=true:autohint=true",*/
    "Noto Sans:size=9:antialias=true:autohint=true",
    "siji:antialias=true:autohint=true"
};
//static const char dmenufont[]       = "Noto Sans:size=9";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "  \ue1ec", "  \ue26d", "  \ue1e0", "  \ue05c", "  \ue1dd", "  \ue19a", "  \ue1ed" }; /* Add 2 spaces before tag name to center them */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Termite", NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "",      tile },    /* first entry is default */
    { "",      NULL },    /* no layout function means floating behavior */
    { "",      monocle },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "termite", NULL };
static const char *rangercmd[] = { "termite", "-e", "ranger", NULL };
static const char *cmuscmd[] = { "termite", "-e", "cmus", NULL };

#include "shiftview.c"
#include <X11/XF86keysym.h>

static Key keys[] = {
    /* modifier                     key             function        argument */
    { MODKEY,                       XK_d,           spawn,          {.v = dmenucmd } },
    { MODKEY,		            XK_e,           spawn,	   {.v = rangercmd } },
    { MODKEY,		            XK_c,           spawn,	   {.v = cmuscmd } },
    { MODKEY,			    XK_Return,      spawn,          {.v = termcmd} },
    { MODKEY,                       XK_b,           togglebar,      {0} },
    { MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,           inplacerotate,  {.i = +1} },
    { MODKEY|ShiftMask,             XK_k,           inplacerotate,  {.i = -1} },
    { MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_i,           incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return,      zoom,           {0} },
    { MODKEY,                       XK_Tab,         view,           {0} },
    { MODKEY|ShiftMask,             XK_q,           killclient,     {0} },
    { MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,           setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} },
    { MODKEY,			    XK_Page_Down,   shiftview,      { .i = +1 } },
    { MODKEY,			    XK_Page_Up,	    shiftview, { .i = -1 } },
    { MODKEY,                       XK_space,       setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },
    { MODKEY|ShiftMask,             XK_f,           togglefullscr,  {0} },
    { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
    { MODKEY,                       XK_F5,          xrdb,           {.v = NULL } },
    { MODKEY,			    XK_F9,	    spawn,	    SHCMD("~/.local/bin/dmenumount") },
    { MODKEY,			    XK_F10,	    spawn,	    SHCMD("~/.local/bin/dmenuumount") },
    { MODKEY,			    XK_F7,	    spawn,	    SHCMD("~/.local/bin/displayselect") },
    { MODKEY,			    XK_BackSpace,   spawn,	    SHCMD("~/.local/bin/sysact") },
    //	{ MODKEY,                   XK_minus,       setgaps,        {.i = -1 } },
    //	{ MODKEY,                   XK_equal,       setgaps,        {.i = +1 } },
    //	{ MODKEY|ShiftMask,         XK_equal,       setgaps,        {.i = 0  } },
    { MODKEY,			    XK_w,	    spawn,	    SHCMD("brave") },
    { MODKEY|ShiftMask,		    XK_w,	    spawn,	    SHCMD("termite -e nmtui") },
    { MODKEY,                       XK_x,	    spawn,	    SHCMD("~/.local/bin/i3lock/lock.sh") },
    { MODKEY,			    XK_p,	    spawn,	    SHCMD("cmus-remote --pause && pkill -RTMIN+20 dwmblocks") },
    { MODKEY,			    XK_bracketleft,		    spawn,	SHCMD("cmus-remote --prev && pkill -RTMIN+20 dwmblocks") },
    { MODKEY|ShiftMask,		    XK_bracketleft,		    spawn,	SHCMD("cmus-remote --seek -10 && pkill -RTMIN+20 dwmblocks") },
    { MODKEY,			    XK_bracketright,	     spawn,	SHCMD("cmus-remote --next && pkill -RTMIN+20 dwmblocks") },
    { MODKEY|ShiftMask,		    XK_bracketright,	     spawn,	SHCMD("cmus-remote --seek +10") },
    { MODKEY,			    XK_Print,	             spawn,	SHCMD("maim -u -s -n -l -c 0.157,0.333,0.466,0.4 ~/Pictures/screenshots/$(date +%s).png") },
    { MODKEY|ControlMask,	    XK_Print,	             spawn,	SHCMD("maim -u ~/Pictures/screenshots/$(date +%s).png") },
    { MODKEY|ShiftMask,		    XK_Print,	             spawn,	SHCMD("maim -u | xclip -selection clipboard -t image/png") },
    { 0,		        	XK_Print,	             spawn,	SHCMD("maim -u -s -n -l -c 0.157,0.333,0.466,0.4 | xclip -selection clipboard -t image/png") },
    { 0,				XF86XK_AudioMute,	     spawn,	SHCMD("amixer set Master toggle && pkill -RTMIN+10 dwmblocks") },
    { 0,				XF86XK_AudioRaiseVolume,     spawn,	SHCMD("amixer set Master 5%+ && pkill -RTMIN+10 dwmblocks") },
    { 0,				XF86XK_AudioLowerVolume,     spawn,	SHCMD("amixer set Master 5%- && pkill -RTMIN+10 dwmblocks") },
    { 0,				XF86XK_MonBrightnessUp,	     spawn,	SHCMD("xbacklight -inc 10") },
    { 0,				XF86XK_MonBrightnessDown,    spawn,	SHCMD("xbacklight -dec 10") },	
    TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	/*	TAGKEYS(                        XK_8,                      7)
		TAGKEYS(                        XK_9,                      8)*/
	{ MODKEY,                       XK_Left,            moveresize,     {.v = "-10x 0y 0w 0h" } },
	{ MODKEY,                       XK_Right,           moveresize,     {.v = "10x 0y 0w 0h" } },
	{ MODKEY,                       XK_Down,            moveresize,     {.v = "0x 10y 0w 0h" } },
	{ MODKEY,                       XK_Up,              moveresize,     {.v = "0x -10y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,            moveresize,     {.v = "0x 0y -10w 0h" } },
	{ MODKEY|ShiftMask,             XK_Right,           moveresize,     {.v = "0x 0y 10w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,            moveresize,     {.v = "0x 0y 0w 10h" } },
	{ MODKEY|ShiftMask,             XK_Up,              moveresize,     {.v = "0x 0y 0w -10h" } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY|ShiftMask,         Button1,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/*  dwmc stuff	*/
    void
setlayoutex(const Arg *arg)
{
    setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

    void
viewex(const Arg *arg)
{
    view(&((Arg) { .ui = 1 << arg->ui }));
}

    void
viewall(const Arg *arg)
{
    view(&((Arg){.ui = ~0}));
}

    void
toggleviewex(const Arg *arg)
{
    toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

    void
tagex(const Arg *arg)
{
    tag(&((Arg) { .ui = 1 << arg->ui }));
}

    void
toggletagex(const Arg *arg)
{
    toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

    void
tagall(const Arg *arg)
{
    tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
    /* signum           function */
    { "focusstack",     focusstack },
    { "setmfact",       setmfact },
    { "togglebar",      togglebar },
    { "incnmaster",     incnmaster },
    { "togglefloating", togglefloating },
    { "focusmon",       focusmon },
    { "tagmon",         tagmon },
    { "zoom",           zoom },
    { "view",           view },
    { "viewall",        viewall },
    { "viewex",         viewex },
    { "toggleview",     view },
    { "toggleviewex",   toggleviewex },
    { "tag",            tag },
    { "tagall",         tagall },
    { "tagex",          tagex },
    { "toggletag",      tag },
    { "toggletagex",    toggletagex },
    { "killclient",     killclient },
    { "quit",           quit },
    { "setlayout",      setlayout },
    { "setlayoutex",    setlayoutex },
    { "xrdb",	    xrdb},
};
