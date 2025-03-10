/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "qutebrowser"

/* appearance */
static unsigned int borderpx = 4;               /* border pixel of windows */
static unsigned int snap = 32;                  /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 0;               /* 0 means no systray */
static unsigned int gappih = 20;                /* horiz inner gap between windows */
static unsigned int gappiv = 20;                /* vert inner gap between windows */
static unsigned int gappoh = 20;                /* horiz outer gap between windows and screen edge */
static unsigned int gappov = 30;                /* vert outer gap between windows and screen edge */
static int smartgaps = 0;                       /* 1 means no outer gap when there is only one window */
static int swallowfloating = 0;                 /* 1 means swallow floating windows by default */
static int allowkill = 1;												/* allow killing clients by default? */
static int showbar = 1;                         /* 0 means no bar */
static int topbar = 1;                          /* 0 means bottom bar */
static int horizpadbar        = 2;        /* horizontal padding for statusbar */
static int vertpadbar         = 0;        /* vertical padding for statusbar */
static char *fonts[] = { "monospace:size=12", "WenQuanYi Zen Hei Mono:size=12:antialias=true:autohint=true", "NotoColorEmoji:pixelsize=22:antialias=true:autohint=true" };
static char normbgcolor[]     = "#282828";
static char normbordercolor[] = "#504945";
static char normfgcolor[]     = "#bdae93";
static char selfgcolor[]      = "#ebdbb2";
static char selbordercolor[]  = "#cc241d";
// static char selbordercolor[]  = "#89B482";
static char selbgcolor[]      = "#3f6570";
static char normfloatcolor[]  = "#504945";
static char selfloatcolor[]   = "#3f6570";
static char *colors[][4] = {
	/*               fg         bg         border     float */
    [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor, normfloatcolor },
    [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor, selfloatcolor },
};

typedef struct {
    const char *name;
    const void *cmd;
} Sp;
const char *spcmd1[] = { TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = { TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "qalc", "-c", NULL };
static Sp scratchpads[] = {
    /* name          cmd  */
    { "spterm", spcmd1  },
    { "spcalc", spcmd2  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    	/* xprop(1):
     	 *  WM_CLASS(STRING) = instance, class
     	 *  WM_NAME(STRING) = title
     	 */
    /* class           instance   title      tags mask		allowkill		switchtotag   isfloating   isterminal  noswallow  monitor */
    {"Zathura",          NULL,     NULL,              0,        0,        0,            1,            0,          1,        -1 },
    {"flameshot",        NULL,     NULL,              0,        0,        0,            1,            0,          1,        -1 },
    {"Espanso",          NULL,     NULL,              0,        0,        0,            1,            0,          1,        -1 },
    {"Zoom",             NULL,     NULL,              1 << 6,   0,        1,            1,            0,          0,        -1 },
    {"Gimp",             NULL,     NULL,              1 << 7,   0,        1,            1,            0,          0,        -1 },
    {"MEGAsync",         NULL,     NULL,              0,        0,        0,            1,            0,          0,        -1 },
    {"recoll",           NULL,     NULL,              0,        1,        0,            1,            0,          0,        -1 },
    {"MATLAB",           NULL,     NULL,              0,        0,        0,            1,            0,          0,        -1 },
    {"Spyder",           NULL,     NULL,              0,        0,        0,            1,            0,          0,        -1 },
    {NULL,               NULL,     "Figure",          0,        1,        0,            1,            0,          0,        -1 },
    {NULL,               NULL,     "HG_Peer_OffScreenWindow", 0,1,        0,            1,            1,          1,        -1 },
    {"ij-ImageJ",        NULL,     NULL,              0,        1,        0,            1,            0,          0,        -1 },
    {"gui-twod-ChemDoodleLauncher", NULL,     NULL,   0,        1,        0,            1,            0,          0,        -1 },
    {"fiji-Main",        NULL,     NULL,              0,        1,        0,            1,            0,          0,        -1 },
    {"TelegramDesktop",  NULL,     NULL,              0,        1,        0,            1,            0,          0,        -1 },
    {"stalonetray",      "stalonetray", "stalonetray",0,        0,        0,            1,            0,          1,        -1 },
    {"steam_app_",       NULL,     NULL,              0,        0,        0,            1,            0,          1,        -1 },
    {"steam",            "steamwebhelper", "Steam Games List", 0, 0,      0,            1,            0,          1,        -1 },
    {"steam",            "steamwebhelper", NULL,      0,        0,        0,            1,            0,          1,        -1 },
    {"steam",            NULL,     "Special Offers",  0,        0,        0,            1,            0,          1,        -1 },
    {"steam",            NULL,     "Friends List",    0,        0,        0,            1,            0,          1,        -1 },
    {"Zotero",           "Alert",  NULL,              0,        0,        0,            1,            0,          1,        -1 },
    {TERMCLASS,          NULL,     NULL,              0,        1,        0,            0,            1,          0,        -1 },
    {TERMCLASS,          "bg",     NULL,              1 << 7,   1,        0,            0,            1,          0,        -1 },
    {TERMCLASS,          "spterm", NULL,              SPTAG(0), 1,        0,            1,            1,          0,        -1 },
    {TERMCLASS,          "spcalc", NULL,              SPTAG(1), 1,        0,            1,            1,          0,        -1 },
    {NULL,               NULL,     "兰译",            0,        1,        0,            1,            0,          1,        -1 },
    {NULL,               NULL,     "Event Tester",    0,        1,        0,            0,            0,          1,        -1 },
    {NULL,               NULL,     "Enter LaTeX Formula - TexText 1.9.0", 0, 1, 0,      1,            0,          1,        -1 },
    {NULL,               NULL,     "KLatexFormula",   0,        1,        0,            1,            0,          1,        -1 },
};

/* layout(s) */
#define ICONSIZE 22   /* icon size */
#define ICONSPACING 5 /* space between icon and title */

static float mfact = 0.55;      /* factor of master area size [0.05..0.95] */
static int nmaster = 1;         /* number of clients in master area */
static int resizehints = 0;     /* 1 means respect size hints in tiled resizals */
static int attachbelow = 0;    /* 1 means attach after the currently active window */
//static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1          /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",    tile                   }, /* Default: Master on left, slaves on right */
    { "TTT",    bstack                 }, /* Master on top, slaves on bottom */

    { "[@]",    spiral                 }, /* Fibonacci spiral */
    { "[ \\ ]", dwindle                }, /* Decreasing in size right and leftward */

    { "[D]",    deck                   }, /* Master on left, slaves in monocle-like mode on right */
    { "[M]",    monocle                }, /* All windows on top of eachother */

    { "|M|",    centeredmaster         }, /* Master in middle, slaves on sides */
    { ">M>",    centeredfloatingmaster }, /* Same but master floats */

    { "><>",    NULL                   }, /* no layout function means floating behavior */
    { NULL,     NULL                   },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG) \
    { MODKEY,                           KEY,      view,           { .ui = 1 << TAG } }, \
    { MODKEY | ControlMask,             KEY,      toggleview,     { .ui = 1 << TAG } }, \
    { MODKEY | ShiftMask,               KEY,      tag,            { .ui = 1 << TAG } }, \
    { MODKEY | ControlMask | ShiftMask, KEY,      toggletag,      { .ui = 1 << TAG } },
#define STACKKEYS(MOD, ACTION) \
    { MOD, XK_j,   ACTION ## stack,  { .i = INC(+1) } }, \
    { MOD, XK_k,   ACTION ## stack,  { .i = INC(-1) } }, \
    { MOD, XK_v,   ACTION ## stack,  { .i = 0 } }, \
    /* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
// static const char *termcmd[] = { "at", NULL };
// static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[] = { TERMINAL, NULL };
static const char *layoutmenu_cmd = "layoutmenu";

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
    { "color0",          STRING,         &normbordercolor },
    /* { "color8",      STRING, &selbordercolor }, */
    { "color0",          STRING,         &normbgcolor     },
    { "color4",          STRING,         &normfgcolor     },
    { "color0",          STRING,         &selfgcolor      },
    { "color4",          STRING,         &selbgcolor      },
    { "borderpx",        INTEGER,        &borderpx        },
    { "snap",            INTEGER,        &snap            },
    { "showbar",         INTEGER,        &showbar         },
    { "topbar",          INTEGER,        &topbar          },
    { "nmaster",         INTEGER,        &nmaster         },
    { "resizehints",     INTEGER,        &resizehints     },
    { "mfact",           FLOAT,          &mfact           },
    { "gappih",          INTEGER,        &gappih          },
    { "gappiv",          INTEGER,        &gappiv          },
    { "gappoh",          INTEGER,        &gappoh          },
    { "gappov",          INTEGER,        &gappov          },
    { "swallowfloating", INTEGER,        &swallowfloating },
    { "smartgaps",       INTEGER,        &smartgaps       },
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static const Key keys[] = {
    /* modifier                     key        function        argument */
    STACKKEYS(MODKEY,         focus)
    STACKKEYS(MODKEY | ShiftMask, push)
    {
        /* { MODKEY|ShiftMask,      XK_Escape,  spawn,  SHCMD("") }, */
        MODKEY,           XK_grave,   spawn,  {.v = (const char*[]) { "dmenuunicode", NULL } }
    },
    /* { MODKEY|ShiftMask,      XK_grave,   togglescratch,  SHCMD("") }, */
    TAGKEYS(XK_1,             0)
    TAGKEYS(XK_2,             1)
    TAGKEYS(XK_3,             2)
    TAGKEYS(XK_4,             3)
    TAGKEYS(XK_5,             4)
    TAGKEYS(XK_6,             5)
    TAGKEYS(XK_7,             6)
    TAGKEYS(XK_8,             7)
    TAGKEYS(XK_9,             8)
    // V is automatically bound above in STACKKEYS
    // layout
    { MODKEY,                              XK_t,            setlayout,                   { .v  = &layouts[0] } }, /* tile */
    { MODKEY|ShiftMask,                    XK_t,            setlayout,                   { .v  = &layouts[1] } }, /* bstack */
    { MODKEY,                              XK_y,            setlayout,                   { .v  = &layouts[2] } }, /* spiral */
    { MODKEY|ShiftMask,                    XK_y,            setlayout,                   { .v  = &layouts[3] } }, /* dwindle */
    { MODKEY,                              XK_u,            setlayout,                   { .v  = &layouts[4] } }, /* deck */
    { MODKEY|ShiftMask,                    XK_u,            setlayout,                   { .v  = &layouts[5] } }, /* monocle */
    { MODKEY,                              XK_i,            setlayout,                   { .v  = &layouts[6] } }, /* centeredmaster */
    { MODKEY|ShiftMask,                    XK_i,            setlayout,                   { .v  = &layouts[7] } }, /* centeredfloatingmaster */

    // shortcuts
    { MODKEY,                              XK_a,            togglegaps,                  { 0 } },
    { MODKEY|ShiftMask,                    XK_a,            defaultgaps,                 { 0 } },
    { MODKEY,                              XK_b,            togglebar,                   { 0 } },
    { MODKEY|ShiftMask,                    XK_b,            spawn,                       SHCMD("rofi -show menu -theme $HOME/.config/rofi/themes/spotlight.rasi -modi menu:$HOME/.config/script/rofi-server.sh") },
    { MODKEY,                              XK_c,            spawn,                       { .v = (const char*[]) { "clipmenu", NULL } } },
    { MODKEY|ShiftMask,                    XK_c,            spawn,                       { .v = (const char*[]) { "keym", NULL } } },
    { MODKEY,                              XK_d,            spawn,                       { .v = (const char*[]) { "dmenu_run", NULL } } },
    { MODKEY|ShiftMask,                    XK_d,            spawn,                       { .v = (const char*[]) { "dmenudoc", NULL } } },
    { MODKEY,                              XK_e,            spawn,                       SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks; rmdir ~/.abook") },
    { MODKEY|ShiftMask,                    XK_e,            spawn,                       SHCMD(TERMINAL " -e abook -C ~/.config/abook/abookrc --datafile ~/.config/abook/addressbook") },
    { MODKEY,                              XK_f,            togglefullscreen,            { 0 } },
    { MODKEY|ShiftMask,                    XK_f,            togglefakefullscreen,        { 0 } },
    { MODKEY,                              XK_g,            spawn,                       { .v = (const char*[]) { "egtd", NULL } } },
    { MODKEY|ShiftMask,                    XK_g,            shifttag,                    { .i  = -1 } },
    { MODKEY,                              XK_h,            setmfact,                    { .f  = -0.05 } },
    { MODKEY|ShiftMask,                    XK_h,            setcfact,                    { .f  = +0.25 } },
    { MODKEY|ControlMask,                  XK_j,            pushdown,                    { 0 } },
    { MODKEY|ControlMask,                  XK_k,            pushup,                      { 0 } },
    { MODKEY,                              XK_l,            setmfact,                    { .f  = +0.05 } },
    { MODKEY|ShiftMask,                    XK_l,            setcfact,                    { .f  = -0.25 } },
    { MODKEY,                              XK_m,            spawn,                       { .v = (const char*[]) { TERMINAL, "-e", "ncmpcpp", NULL } } },
    { MODKEY|ShiftMask,                    XK_m,            spawn,                       { .v = (const char*[]) { TERMINAL, "-e", "musicfox", NULL } } },
    { MODKEY,                              XK_n,            spawn,                       { .v = (const char*[]) { "snote", "search", NULL } } },
    { MODKEY|ShiftMask,                    XK_n,            spawn,                       { .v = (const char*[]) { "snote", "new", NULL } } },
    { MODKEY,                              XK_o,            incnmaster,                  { .i  = +1 } },
    { MODKEY|ShiftMask,                    XK_o,            incnmaster,                  { .i  = -1 } },
    { MODKEY,                              XK_p,            spawn,                       { .v = (const char*[]) { "mpc", "toggle", NULL } } },
    { MODKEY|ShiftMask,                    XK_p,            spawn,                       SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                              XK_q,            killclient,                  { 0 } },
    { MODKEY|ShiftMask,                    XK_q,            toggleallowkill,             { 0 } },
    { MODKEY,                              XK_r,            spawn,                       { .v = (const char*[]) { TERMINAL, "-e", "lfub", NULL } } },
    { MODKEY|ShiftMask,                    XK_r,            spawn,                       { .v = (const char*[]) { TERMINAL, "-e", "htop", NULL } } },
    { MODKEY,                              XK_s,            togglesticky,                { 0 } },
    { MODKEY|ShiftMask,                    XK_s,            spawn,                       { .v = (const char*[]) { "mathpix", NULL } } },
    { MODKEY|ShiftMask,                    XK_v,            spawn,                       { .v = (const char*[]) { "extravid", NULL } } },
    { MODKEY,                              XK_w,            spawn,                       SHCMD(BROWSER) },
    { MODKEY|ShiftMask,                    XK_w,            spawn,                       { .v = (const char*[]) { "iwd-dmenu", NULL } } },
    { MODKEY,                              XK_x,            incrgaps,                    { .i  = -3 } },
    { MODKEY,                              XK_z,            incrgaps,                    { .i  = +3 } },
    { MODKEY|ShiftMask,                    XK_z,            spawn,                       { .v = (const char*[]) { "dmenupaper", NULL } } },
    { MODKEY,                              XK_Return,       spawn,                       { .v  = termcmd } },
    { MODKEY|ShiftMask,                    XK_Return,       togglescratch,               { .ui = 0 } },
    { MODKEY,                              XK_space,        zoom,                        { 0 } },
    { MODKEY|ShiftMask,                    XK_space,        togglefloating,              { 0 } },
    { MODKEY,                              XK_comma,        focusmon,                    { .i  = -1 } },
    { MODKEY|ShiftMask,                    XK_comma,        tagmon,                      { .i  = -1 } },
    { MODKEY,                              XK_period,       focusmon,                    { .i  = +1 } },
    { MODKEY|ShiftMask,                    XK_period,       tagmon,                      { .i  = +1 } },
    { MODKEY,                              XK_Page_Up,      shiftview,                   { .i  = -1 } },
    { MODKEY|ShiftMask,                    XK_Page_Up,      shifttag,                    { .i  = -1 } },
    { MODKEY,                              XK_Page_Down,    shiftview,                   { .i  = +1 } },
    { MODKEY|ShiftMask,                    XK_Page_Down,    shifttag,                    { .i  = +1 } },
    { MODKEY,                              XK_apostrophe,   togglescratch,               { .ui = 1 } },
    { MODKEY,                              XK_Tab,          view,                        { 0 } },
    { MODKEY|ShiftMask,                    XK_Tab,          toggleAttachBelow,           { 0 } },
    { MODKEY|ShiftMask,                    XK_apostrophe,   togglesmartgaps,             { 0 } },
    { MODKEY,                              XK_semicolon,    spawn,                       { .v = (const char*[]) { "dt", "-x", NULL } } },
    { MODKEY|ShiftMask,                    XK_semicolon,    shifttag,                    { .i  = 1 } },
    { MODKEY,                              XK_minus,        spawn,                       { .v = (const char*[]) { "changevolume", "down", NULL } } },
    { MODKEY|ShiftMask,                    XK_minus,        spawn,                       { .v = (const char*[]) { "brightness", "down", NULL } } },
    { MODKEY,                              XK_equal,        spawn,                       { .v = (const char*[]) { "changevolume", "up", NULL } } },
    { MODKEY|ShiftMask,                    XK_equal,        spawn,                       { .v = (const char*[]) { "brightness", "up", NULL } } },
    { MODKEY,                              XK_backslash,    spawn,                       { .v = (const char*[]) { "stalonetray-toggle", NULL } } },
    { MODKEY|ShiftMask,                    XK_backslash,    spawn,                       SHCMD("remaps & notify-send \\\"Keyboard remapping...\\\"") },
    { MODKEY,                              XK_bracketleft,  spawn,                       { .v = (const char*[]) { "mpc", "prev", NULL } } },
    { MODKEY|ShiftMask,                    XK_bracketleft,  spawn,                       { .v = (const char*[]) { "mpc", "seek", "-20", NULL } } },
    { MODKEY,                              XK_bracketright, spawn,                       { .v = (const char*[]) { "mpc", "next", NULL } } },
    { MODKEY|ShiftMask,                    XK_bracketright, spawn,                       { .v = (const char*[]) { "mpc", "seek", "+20", NULL } } },
    { MODKEY,                              XK_BackSpace,    spawn,                       { .v = (const char*[]) { "sysact", NULL } } },
    { MODKEY,                              XK_slash,        spawn,                       { .v = (const char*[]) { "rofi-zotero", NULL } } },
    { MODKEY,                              XK_Delete,       spawn,                       { .v = (const char*[]) { "dmenurecord", "kill", NULL } } },
    { MODKEY,                              XK_0,            view,                        { .ui = ~0 } },
    { MODKEY|ShiftMask,                    XK_0,            tag,                         { .ui = ~0 } },
    { MODKEY,                              XK_F1,           spawn,                       { .v = (const char*[]) { "flameshot", "gui", NULL } } },
    { MODKEY,                              XK_F2,           spawn,                       { .v = (const char*[]) { "lpic", "-c", NULL } } },
    { MODKEY,                              XK_F3,           spawn,                       { .v = (const char*[]) { "displayselect", NULL } } },
    { MODKEY,                              XK_F4,           spawn,                       SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
    { MODKEY,                              XK_F5,           xrdb,                        { .v = NULL } },
    { MODKEY,                              XK_F6,           spawn,                       { .v = (const char*[]) { "displayout", NULL } } },
    { MODKEY,                              XK_F7,           spawn,                       { .v = (const char*[]) { "td-toggle", NULL } } },
    { MODKEY,                              XK_F8,           spawn,                       { .v = (const char*[]) { "mailsync", NULL } } },
    { MODKEY,                              XK_F9,           spawn,                       { .v = (const char*[]) { "dmenumount", NULL } } },
    { MODKEY,                              XK_F10,          spawn,                       { .v = (const char*[]) { "dmenuumount", NULL } } },
    { MODKEY,                              XK_F11,          spawn,                       SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
    { MODKEY,                              XK_F12,          spawn,                       SHCMD("remaps & notify-send \\\"⌨️ Keyboard remapping...\\\" \\\"Re-running keyboard defaults for any newly plugged-in keyboards.\\\"") },

    // floating layer
	{ MODKEY,                              XK_Down,         moveresize,                  { .v = "0x 25y 0w 0h" } },
	{ MODKEY|ShiftMask,                    XK_Down,         moveresize,                  { .v = "0x 0y 0w 25h" } },
	{ MODKEY|ControlMask,                  XK_Down,         moveresizeedge,              { .v = "b" } },
	{ MODKEY|ControlMask|ShiftMask,        XK_Down,         moveresizeedge,              { .v = "B" } },
	{ MODKEY,                              XK_Up,           moveresize,                  { .v = "0x -25y 0w 0h" } },
	{ MODKEY|ShiftMask,                    XK_Up,           moveresize,                  { .v = "0x 0y 0w -25h" } },
	{ MODKEY|ControlMask,                  XK_Up,           moveresizeedge,              { .v = "t" } },
	{ MODKEY|ControlMask|ShiftMask,        XK_Up,           moveresizeedge,              { .v = "T" } },
	{ MODKEY,                              XK_Right,        moveresize,                  { .v = "25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,                    XK_Right,        moveresize,                  { .v = "0x 0y 25w 0h" } },
	{ MODKEY|ControlMask,                  XK_Right,        moveresizeedge,              { .v = "r" } },
	{ MODKEY|ControlMask|ShiftMask,        XK_Right,        moveresizeedge,              { .v = "R" } },
	{ MODKEY,                              XK_Left,         moveresize,                  { .v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,                    XK_Left,         moveresize,                  { .v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,                  XK_Left,         moveresizeedge,              { .v = "l" } },
	{ MODKEY|ControlMask|ShiftMask,        XK_Left,         moveresizeedge,              { .v = "L" } },
    { MODKEY|ControlMask|ShiftMask,        XK_minus,        aspectresize,                { .i = +24 } },
    { MODKEY|ControlMask|ShiftMask,        XK_equal,        aspectresize,                { .i = -24 } },

    // others
    { MODKEY,                   XK_Scroll_Lock,             spawn,                       SHCMD("killall screenkey || screenkey &") },
    { 0,                        XK_Print,                   spawn,                       SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
    { MODKEY,                   XK_Print,                   spawn,                       { .v = (const char*[]) { "dmenurecord", NULL } } },
    { ShiftMask,                XK_Print,                   spawn,                       { .v = (const char*[]) { "maimpick", NULL } } },
    { MODKEY|ShiftMask,         XK_Print,                   spawn,                       { .v = (const char*[]) { "dmenurecord", "kill", NULL } } },
    { 0,                        XF86XK_AudioMute,           spawn,                       { .v = (const char*[]) { "changevolume", "mute", NULL } } },
    { 0,                        XF86XK_AudioRaiseVolume,    spawn,                       { .v = (const char*[]) { "changevolume", "up", NULL } } },
    { 0,                        XF86XK_AudioLowerVolume,    spawn,                       { .v = (const char*[]) { "changevolume", "down", NULL } } },
    { 0,                        XF86XK_AudioPrev,           spawn,                       { .v = (const char*[]) { "mpc", "prev", NULL } } },
    { 0,                        XF86XK_AudioNext,           spawn,                       { .v = (const char*[]) { "mpc", "next", NULL } } },
    { 0,                        XF86XK_AudioPause,          spawn,                       { .v = (const char*[]) { "mpc", "pause", NULL } } },
    { 0,                        XF86XK_AudioPlay,           spawn,                       { .v = (const char*[]) { "mpc", "play", NULL } } },
    { 0,                        XF86XK_AudioStop,           spawn,                       { .v = (const char*[]) { "mpc", "stop", NULL } } },
    { 0,                        XF86XK_AudioRewind,         spawn,                       { .v = (const char*[]) { "mpc", "seek", "-10", NULL } } },
    { 0,                        XF86XK_AudioForward,        spawn,                       { .v = (const char*[]) { "mpc", "seek", "+10", NULL } } },
    { 0,                        XF86XK_AudioMedia,          spawn,                       { .v = (const char*[]) { TERMINAL, "-e", "ncmpcpp", NULL } } },
    { 0,                        XF86XK_AudioMicMute,        spawn,                       SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
    { 0,                        XF86XK_PowerOff,            spawn,                       { .v = (const char*[]) { "sysact", NULL } } },
    { 0,                        XF86XK_Calculator,          spawn,                       { .v = (const char*[]) { TERMINAL, "-e", "bc", "-l", NULL } } },
    { 0,                        XF86XK_Sleep,               spawn,                       { .v = (const char*[]) { "sudo", "-A", "zzz", NULL } } },
    { 0,                        XF86XK_WWW,                 spawn,                       { .v = (const char*[]) { BROWSER, NULL } } },
    { 0,                        XF86XK_DOS,                 spawn,                       { .v = termcmd } },
    { 0,                        XF86XK_ScreenSaver,         spawn,                       SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv") },
    { 0,                        XF86XK_TaskPane,            spawn,                       { .v = (const char*[]) { TERMINAL, "-e", "htop", NULL } } },
    { 0,                        XF86XK_Mail,                spawn,                       SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks") },
    { 0,                        XF86XK_MyComputer,          spawn,                       { .v = (const char*[]) { TERMINAL, "-e",  "lfrun",  "/", NULL } } },
    { 0,                        XF86XK_Launch1,             spawn,                       { .v = (const char*[]) { "xset", "dpms", "force", "off", NULL } } },
    { 0,                        XF86XK_TouchpadToggle,      spawn,                       SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
    { 0,                        XF86XK_TouchpadOff,         spawn,                       { .v = (const char*[]) { "synclient", "TouchpadOff=1", NULL } } },
    { 0,                        XF86XK_TouchpadOn,          spawn,                       { .v = (const char*[]) { "synclient", "TouchpadOff=0", NULL } } },
    { 0,                        XF86XK_MonBrightnessUp,     spawn,                       { .v = (const char*[]) { "changebrightness", "up", NULL } } },
    { 0,                        XF86XK_MonBrightnessDown,   spawn,                       { .v = (const char*[]) { "changebrightness", "down", NULL } } },


    /* { 0, XF86XK_Battery,     spawn,      SHCMD("") }, */

    /* { MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } }, */
    /* { MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } }, */
    /* { MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } }, */
    /* { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} }, */
    /* { MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } }, */
    /* { MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } }, */
    /* { MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } }, */
    /* { MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } }, */
    /* { MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } }, */
    /* { MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } }, */
    /* { MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } }, */
    /* { MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } }, */

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click      event mask    button        function        argument */
#ifndef __OpenBSD__
    { ClkTagBar,     MODKEY,    Button1,          tag,          { 0  } },
    { ClkTagBar,     MODKEY,    Button3,          toggletag,    { 0  } },
    { ClkLtSymbol,   0,         Button3,          layoutmenu,   { 0 } },
    { ClkWinTitle,   0,         Button2,          zoom,         { 0  } },
    { ClkStatusText, 0,         Button1,          sigdwmblocks, { .i = 1} },
    { ClkStatusText, 0,         Button2,          sigdwmblocks, { .i = 2} },
    { ClkStatusText, 0,         Button3,          sigdwmblocks, { .i = 3} },
    { ClkStatusText, 0,         Button4,          sigdwmblocks, { .i = 4} },
    { ClkStatusText, 0,         Button5,          sigdwmblocks, { .i = 5} },
    { ClkStatusText, ShiftMask, Button1,          sigdwmblocks, { .i = 6} },
#endif
    { ClkStatusText, ShiftMask, Button3,          spawn,        SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,  MODKEY,    Button1,          moveorplace,    {.i = 1} },
    { ClkClientWin,  MODKEY,    Button2,          defaultgaps,  { 0  } },
    { ClkClientWin,  MODKEY,    Button3,          resizemouse,  { 0  } },
    { ClkClientWin,  MODKEY,    Button4,          incrgaps,     { .i = +1} },
    { ClkClientWin,  MODKEY,    Button5,          incrgaps,     { .i = -1} },
    { ClkTagBar,     0,         Button1,          view,         { 0  } },
    { ClkTagBar,     0,         Button3,          toggleview,   { 0  } },
    { ClkTagBar,     MODKEY,    Button1,          tag,          { 0  } },
    { ClkTagBar,     MODKEY,    Button3,          toggletag,    { 0  } },
    { ClkTagBar,     0,         Button4,          shiftview,    { .i = -1} },
    { ClkTagBar,     0,         Button5,          shiftview,    { .i = 1} },
    { ClkRootWin,    0,         Button2,          togglebar,    { 0  } },
};

void
setlayoutex(const Arg *arg)
{
    setlayout(&((Arg) {
        .v = &layouts[arg->i]
    }));
}

void
viewex(const Arg *arg)
{
    view(&((Arg) {
        .ui = 1 << arg->ui
    }));
}

void
viewall(const Arg *arg)
{
    view(&((Arg) {
        .ui = ~0
    }));
}

void
toggleviewex(const Arg *arg)
{
    toggleview(&((Arg) {
        .ui = 1 << arg->ui
    }));
}

void
tagex(const Arg *arg)
{
    tag(&((Arg) {
        .ui = 1 << arg->ui
    }));
}

void
toggletagex(const Arg *arg)
{
    toggletag(&((Arg) {
        .ui = 1 << arg->ui
    }));
}

void
tagall(const Arg *arg)
{
    tag(&((Arg) {
        .ui = ~0
    }));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
    /* signum                  function */
    { "focusstack",            focusstack           },
    { "setmfact",              setmfact             },
    { "setcfact",              setcfact             },
    { "togglebar",             togglebar            },
    { "incnmaster",            incnmaster           },
	{ "shiftview",             shiftview            },
    { "togglefloating",        togglefloating       },
	{ "togglesticky",          togglesticky         },
    { "focusmon",              focusmon             },
    { "tagmon",                tagmon               },
    { "zoom",                  zoom                 },
    { "view",                  view                 },
    { "viewall",               viewall              },
    { "viewex",                viewex               },
    { "toggleview",            view                 },
    { "toggleviewex",          toggleviewex         },
    { "tag",                   tag                  },
    { "tagall",                tagall               },
    { "tagex",                 tagex                },
    { "toggletag",             tag                  },
    { "toggletagex",           toggletagex          },
    { "togglefullscr",         togglefullscr        },
    { "fullscreen",            fullscreen           },
    { "killclient",            killclient           },
    { "quit",                  quit                 },
    { "setlayout",             setlayout            },
    { "setlayoutex",           setlayoutex          },
	{ "togglefakefullscreen",  togglefakefullscreen },
};
