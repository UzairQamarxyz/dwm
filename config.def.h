/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int swallowfloating =
    0;                        /* 1 means swallow floating windows by default */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const unsigned int gappih = 10; /* horiz inner gap between windows */
static const unsigned int gappiv = 10; /* vert inner gap between windows */
static const unsigned int gappoh =
    10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov =
    10; /* vert outer gap between windows and screen edge */
static int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const int horizpadbar = 2; /* horizontal padding for statusbar */
static const int vertpadbar = 5;  /* vertical padding for statusbar */
static const char *fonts[] = {
    "Iosevka Custom:size=14:antialias=true:autohint=true"};
static const char dmenufont[] =
    "Iosevka Custom:size=14:antialias=true:autohint=true";
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char termcol0[] = "#000000";  /* black   */
static char termcol1[] = "#ff0000";  /* red     */
static char termcol2[] = "#33ff00";  /* green   */
static char termcol3[] = "#ff0099";  /* yellow  */
static char termcol4[] = "#0066ff";  /* blue    */
static char termcol5[] = "#cc00ff";  /* magenta */
static char termcol6[] = "#00ffff";  /* cyan    */
static char termcol7[] = "#d0d0d0";  /* white   */
static char termcol8[] = "#808080";  /* black   */
static char termcol9[] = "#ff0000";  /* red     */
static char termcol10[] = "#33ff00"; /* green   */
static char termcol11[] = "#ff0099"; /* yellow  */
static char termcol12[] = "#0066ff"; /* blue    */
static char termcol13[] = "#cc00ff"; /* magenta */
static char termcol14[] = "#00ffff"; /* cyan    */
static char termcol15[] = "#ffffff"; /* white   */
static char *termcolor[] = {
    termcol0,  termcol1,  termcol2,  termcol3,  termcol4,  termcol5,
    termcol6,  termcol7,  termcol8,  termcol9,  termcol10, termcol11,
    termcol12, termcol13, termcol14, termcol15,
};
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

/* swallow emacs */
static const char emacsclient[] = "emacsclient";
static const char emacsname[] = "emacs@";

/* tagging */
static const char *tags[] = {"", "", "", "", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal
       noswallow  monitor */
    {"Alacritty", NULL, NULL, 0, 0, 1, 0, -1},
    {NULL, NULL, "Event Tester", 0, 0, 0, 1, -1}, /* xev */
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle}, {"H[]", deck}, {"|M|", centeredmaster}, {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {1, {{MODKEY, KEY}}, view, {.ui = 1 << TAG}},                                \
      {1, {{MODKEY | ControlMask, KEY}}, toggleview, {.ui = 1 << TAG}},        \
      {1, {{MODKEY | ShiftMask, KEY}}, tag, {.ui = 1 << TAG}},                 \
      {1,                                                                      \
       {{MODKEY | ControlMask | ShiftMask, KEY}},                              \
       toggletag,                                                              \
       {.ui = 1 << TAG}},                                                      \
      {1, {{MODKEY | ControlMask, KEY}}, focusnthmon, {.i = TAG}},             \
      {1, {{MODKEY | ControlMask | ShiftMask, KEY}}, tagnthmon, {.i = TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, NULL};
static const char *termcmd[] = {"alacritty", NULL};
static const char *emacs[] = {"emacs", NULL};
static const char *rangercmd[] = {"alacritty", "-e", "ranger", NULL};
static const char *cmuscmd[] = {"alacritty", "-e", "cmus", NULL};

#include <X11/XF86keysym.h>

static Keychord keychords[] = {
    /* modifier                     key             function        argument */
    // APPLICATIONS
    {1, {{MODKEY, XK_d}}, spawn, {.v = dmenucmd}},
    {2, {{MODKEY, XK_e}, {0, XK_e}}, spawn, {.v = rangercmd}},
    {2, {{MODKEY, XK_e}, {0, XK_D}}, spawn, SHCMD("alacritty -e ranger ~/Documents")},
    {2, {{MODKEY, XK_e}, {0, XK_d}}, spawn, SHCMD("alacritty -e ranger ~/Downloads")},
    {2, {{MODKEY, XK_e}, {0, XK_c}}, spawn, SHCMD("alacritty -e ranger ~/.config")},
    {2, {{MODKEY, XK_e}, {0 | ShiftMask, XK_c}}, spawn, SHCMD("alacritty -e ranger ~/.cache")},
    {3, {{MODKEY, XK_e}, {0, XK_w}, {0, XK_c}}, spawn, SHCMD("alacritty -e ranger ~/Documents/work/copebit")},
    {3, {{MODKEY, XK_e}, {0, XK_w}, {0, XK_x}}, spawn, SHCMD("alacritty -e ranger ~/Documents/work/xgrid")},
    {3, {{MODKEY, XK_e}, {0, XK_w}, {0, XK_t}}, spawn, SHCMD("alacritty -e ranger ~/Documents/work/testing")},
    {2, {{MODKEY, XK_e}, {0, XK_g}}, spawn, SHCMD("alacritty -e ranger ~/Documents/git")},
    {1, {{MODKEY, XK_c}}, spawn, {.v = cmuscmd}},
    {1, {{NULL, XF86XK_Calculator}}, spawn, SHCMD("emacsclient -c -a 'emacs'")},
    {1, {{MODKEY, XK_Return}}, spawn, {.v = termcmd}},
    {1, {{MODKEY | ShiftMask, XK_q}}, killclient, {0}},

    // LAYOUTS
    {1, {{MODKEY, XK_j}}, focusstack, {.i = +1}},
    {1, {{MODKEY, XK_k}}, focusstack, {.i = -1}},
    {1, {{MODKEY | ShiftMask, XK_j}}, inplacerotate, {.i = +1}},
    {1, {{MODKEY | ShiftMask, XK_k}}, inplacerotate, {.i = -1}},
    {1, {{MODKEY, XK_i}}, incnmaster, {.i = +1}},
    {1, {{MODKEY | ShiftMask, XK_i}}, incnmaster, {.i = -1}},
    {1, {{MODKEY, XK_h}}, setmfact, {.f = -0.05}},
    {1, {{MODKEY, XK_l}}, setmfact, {.f = +0.05}},
    {1, {{MODKEY, XK_t}}, setlayout, {.v = &layouts[0]}},
    {1, {{MODKEY, XK_f}}, setlayout, {.v = &layouts[1]}},
    {1, {{MODKEY, XK_m}}, setlayout, {.v = &layouts[2]}},
    {1, {{MODKEY | ShiftMask, XK_d}}, setlayout, {.v = &layouts[3]}},
    {1, {{MODKEY | ShiftMask, XK_m}}, setlayout, {.v = &layouts[4]}},
    {1, {{MODKEY, XK_Page_Down}}, viewnext, {.i = +1}},
    {1, {{MODKEY | ShiftMask, XK_Page_Down}}, tagtonext, {.i = +1}},
    {1, {{MODKEY, XK_Page_Up}}, viewprev, {.i = -1}},
    {1, {{MODKEY | ShiftMask, XK_Page_Up}}, tagtoprev, {.i = +1}},
    {1, {{MODKEY, XK_space}}, setlayout, {0}},
    {1, {{MODKEY | ShiftMask, XK_space}}, togglefloating, {0}},
    {1, {{MODKEY | ShiftMask, XK_f}}, togglefullscr, {0}},
    {1, {{MODKEY | ShiftMask, XK_Return}}, zoom, {0}},

    // WORKSPACES
    {1, {{MODKEY, XK_b}}, togglebar, {0}},
    {1, {{MODKEY, XK_Tab}}, view, {0}},
    {1, {{MODKEY, XK_0}}, view, {.ui = ~0}},
    {1, {{MODKEY | ShiftMask, XK_0}}, tag, {.ui = ~0}},

    // HOTKEYS
    {1, {{MODKEY, XK_F5}}, xrdb, {.v = NULL}},
    {1, {{MODKEY, XK_F9}}, spawn, SHCMD("~/.local/bin/dmenumount")},
    {1, {{MODKEY, XK_F10}}, spawn, SHCMD("~/.local/bin/dmenumount")},
    {1, {{MODKEY, XK_F7}}, spawn, SHCMD("~/.local/bin/displayselect")},
    {1, {{MODKEY, XK_BackSpace}}, spawn, SHCMD("~/.local/bin/sysact")},
    {2, {{MODKEY, XK_w}, {0, XK_1}}, spawn, SHCMD("chromium --profile-directory='Default'")},
    {2, {{MODKEY, XK_w}, {0, XK_2}}, spawn, SHCMD("chromium --profile-directory='Profile 1'")},
    {2, {{MODKEY, XK_w}, {0, XK_3}}, spawn, SHCMD("chromium --profile-directory='Profile 2'")},
    {2, {{MODKEY, XK_w}, {0, XK_4}}, spawn, SHCMD("chromium --profile-directory='Profile 3'")},
    {1, {{MODKEY | ShiftMask, XK_w}}, spawn, SHCMD("alacritty -e nmtui connect")},
    {1, {{MODKEY, XK_x}}, spawn, SHCMD("~/.local/bin/i3lock/lock.sh")},
    {1,
     {{MODKEY, XK_p}},
     spawn,
     SHCMD("cmus-remote --pause && pkill -RTMIN+20 dwmblocks")},
    {1,
     {{MODKEY, XK_bracketleft}},
     spawn,
     SHCMD("cmus-remote --prev && pkill -RTMIN+20 dwmblocks")},
    {1,
     {{MODKEY | ShiftMask, XK_bracketleft}},
     spawn,
     SHCMD("cmus-remote --seek -10 && pkill -RTMIN+20 dwmblocks")},
    {1,
     {{MODKEY, XK_bracketright}},
     spawn,
     SHCMD("cmus-remote --next && pkill -RTMIN+20 dwmblocks")},
    {1,
     {{MODKEY | ShiftMask, XK_bracketright}},
     spawn,
     SHCMD("cmus-remote --seek +10")},
    //	{MODKEY, XK_p, spawn,
    //		SHCMD("qdbus org.mpris.MediaPlayer2.spotify
    /// org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.PlayPause && pkill
    // -RTMIN+20 dwmblocks")}, 	{MODKEY, XK_bracketleft, spawn,
    // SHCMD("qdbus
    // org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2
    // org.mpris.MediaPlayer2.Player.Previous && pkill -RTMIN+20 dwmblocks")},
    //	{MODKEY, XK_bracketright, spawn,
    //		SHCMD("qdbus org.mpris.MediaPlayer2.spotify
    /// org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Next && pkill
    // -RTMIN+20 dwmblocks")},
    {1, {{0, XK_Print}}, spawn, SHCMD("/usr/bin/flameshot gui")},
    {1,
     {{0, XF86XK_AudioMute}},
     spawn,
     SHCMD("amixer set Master toggle && pkill -RTMIN+10 dwmblocks")},
    {1,
     {{0, XF86XK_AudioRaiseVolume}},
     spawn,
     SHCMD("amixer set Master 5%+ && pkill -RTMIN+10 dwmblocks")},
    {1,
     {{0, XF86XK_AudioLowerVolume}},
     spawn,
     SHCMD("amixer set Master 5%- && pkill -RTMIN+10 dwmblocks")},
    {1, {{0, XF86XK_MonBrightnessUp}}, spawn, SHCMD("brightnessctl set 10%+")},
    {1,
     {{0, XF86XK_MonBrightnessDown}},
     spawn,
     SHCMD("brightnessctl set 10%-")},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6)
    /*	TAGKEYS(                        XK_8,                      7)
            TAGKEYS(                        XK_9,                      8)*/
    {1, {{MODKEY, XK_Left}}, moveresize, {.v = "-10x 0y 0w 0h"}},
    {1, {{MODKEY, XK_Right}}, moveresize, {.v = "10x 0y 0w 0h"}},
    {1, {{MODKEY, XK_Down}}, moveresize, {.v = "0x 10y 0w 0h"}},
    {1, {{MODKEY, XK_Up}}, moveresize, {.v = "0x -10y 0w 0h"}},
    {1, {{MODKEY | ShiftMask, XK_Left}}, moveresize, {.v = "0x 0y -10w 0h"}},
    {1, {{MODKEY | ShiftMask, XK_Right}}, moveresize, {.v = "0x 0y 10w 0h"}},
    {1, {{MODKEY | ShiftMask, XK_Down}}, moveresize, {.v = "0x 0y 0w 10h"}},
    {1, {{MODKEY | ShiftMask, XK_Up}}, moveresize, {.v = "0x 0y 0w -10h"}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY | ShiftMask, Button1, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};

void setlayoutex(const Arg *arg) { setlayout(&((Arg){.v = &layouts[arg->i]})); }

void viewex(const Arg *arg) { view(&((Arg){.ui = 1 << arg->ui})); }

void viewall(const Arg *arg) { view(&((Arg){.ui = ~0})); }

void toggleviewex(const Arg *arg) { toggleview(&((Arg){.ui = 1 << arg->ui})); }

void tagex(const Arg *arg) { tag(&((Arg){.ui = 1 << arg->ui})); }

void toggletagex(const Arg *arg) { toggletag(&((Arg){.ui = 1 << arg->ui})); }

void tagall(const Arg *arg) { tag(&((Arg){.ui = ~0})); }

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"`
 */
static Signal signals[] = {
    /* signum           function */
    {"focusstack", focusstack},
    {"setmfact", setmfact},
    {"togglebar", togglebar},
    {"incnmaster", incnmaster},
    {"togglefloating", togglefloating},
    {"focusmon", focusmon},
    {"tagmon", tagmon},
    {"zoom", zoom},
    {"view", view},
    {"viewall", viewall},
    {"viewex", viewex},
    {"toggleview", view},
    {"toggleviewex", toggleviewex},
    {"tag", tag},
    {"tagall", tagall},
    {"tagex", tagex},
    {"toggletag", tag},
    {"toggletagex", toggletagex},
    {"killclient", killclient},
    {"quit", quit},
    {"setlayout", setlayout},
    {"setlayoutex", setlayoutex},
    {"xrdb", xrdb},
};
