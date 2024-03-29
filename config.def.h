/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 0;        /* horizontal padding for statusbar */
static const int vertpadbar         = 6;        /* vertical padding for statusbar */
static const char *fonts[]          = {"IosevkaCustom Nerd Font:size=12:antialias=true"};
static const char dmenufont[]       = "IosevkaCustom Nerd Font:size=12";
static char normbgcolor[]           = "#222223";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char barcol0[] = "#000000"; /* black   */
static char barcol1[] = "#ff0000"; /* red     */
static char barcol2[] = "#33ff00"; /* green   */
static char barcol3[] = "#ff0099"; /* yellow  */
static char barcol4[] = "#0066ff"; /* blue    */
static char barcol5[] = "#cc00ff"; /* magenta */
static char barcol6[] = "#00ffff"; /* cyan    */
static char barcol7[] = "#d0d0d0"; /* white   */
static char barcol8[]  = "#808080"; /* black   */
static char barcol9[]  = "#ff0000"; /* red     */
static char barcol10[] = "#33ff00"; /* green   */
static char barcol11[] = "#ff0099"; /* yellow  */
static char barcol12[] = "#0066ff"; /* blue    */
static char barcol13[] = "#cc00ff"; /* magenta */
static char barcol14[] = "#00ffff"; /* cyan    */
static char barcol15[] = "#ffffff"; /* white   */
static char *barcolors[] = {
  barcol0,
  barcol1,
  barcol2,
  barcol3,
  barcol4,
  barcol5,
  barcol6,
  barcol7,
  barcol8,
  barcol9,
  barcol10,
  barcol11,
  barcol12,
  barcol13,
  barcol14,
  barcol15,
};
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = {"○", "○", "○", "○", "○", "○", "○"};

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol      arrange function */
    { "",   tile },    /* first entry is default */
    { "",   NULL },    /* no layout function means floating behavior */
    { "",   monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/env", "bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, NULL};
static const char *termcmd[]  = { "alacritty", NULL };
static const char *emacs[]  = { "emacsclient", "-c", "-a", "'emacs'", NULL };
static const char *browser[]  = { "librewolf", NULL };
static const char *ranger[] = {"alacritty", "-e", "ranger", NULL};
static const char *cmus[] = {"alacritty", "-e", "cmus", NULL};
static const char *nmtui[]  = { "alacritty", "-e", "nmtui", NULL };
static const char *lockscreen[]  = { "betterlockscreen", "--lock", NULL };
static const char *screenshot[]  = { "flameshot", "gui", NULL };
static const char *brightnessup[]  = { "brightnessctl", "set", "10%+", NULL };
static const char *brightnessdown[]  = { "brightnessctl", "set", "10%-", NULL };

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
    { 0,                            XF86XK_AudioMute,         spawn,          SHCMD("amixer set Master toggle && pkill -RTMIN+10 dwmblocks")},
    { 0,                            XF86XK_AudioRaiseVolume,  spawn,          SHCMD("amixer set Master 5%+ && pkill -RTMIN+10 dwmblocks")},
    { 0,                            XF86XK_AudioLowerVolume,  spawn,          SHCMD("amixer set Master 5%- && pkill -RTMIN+10 dwmblocks")},
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
    { MODKEY,                       XK_F5,                    xrdb,           {.v = NULL } },
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
/* click can be ClkTagBar, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                  event mask          button          function        argument */
    { ClkStatusText,          0,                  Button2,        spawn,          {.v = termcmd} },
    { ClkClientWin,           MODKEY,             Button1,        movemouse,      {0} },
    { ClkClientWin,           MODKEY,             Button2,        togglefloating, {0} },
    { ClkClientWin,           MODKEY | ShiftMask, Button1,        resizemouse,    {0} },
    { ClkTagBar,              0,                  Button1,        view,           {0} },
    { ClkTagBar,              0,                  Button3,        toggleview,     {0} },
    { ClkTagBar,              MODKEY,             Button1,        tag,            {0} },
    { ClkTagBar,              MODKEY,             Button3,        toggletag,      {0} },
};
