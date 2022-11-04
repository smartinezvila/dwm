/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of tiled windows */
static const unsigned int snap      = 32;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "jetbrains mono:bold:size=10" };
static const char dmenufont[]       = "jetbrains mono:bold:size=10";
static const char col_gray1[]       = "#151515";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#cccccc";
static const char col_gray4[]       = "#eeeeee";
static const char col_purple1[]     = "#4040cc";
static const char col_purple2[]     = "#4040cc";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_purple2,  col_purple1  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gcolor3",  NULL,       NULL,       0,            1,           -1 },
	{ "Galculator",  NULL,       NULL,       0,            1,           -1 },
	{ "stalonetray",  NULL,       NULL,       ~0,            1,           -1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_purple1, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "alacritty", "-t", scratchpadname, NULL };
static const char *roficmd[]  = { "rofi","-show", "run", NULL };
static const char *cliproficmd[]  = { "rofi", "-modi","\"clipboard:greenclip print\"","-show", "clipboard" ,"-run-command" ,"'{cmd}'", NULL };
static const char *hibernatecmd[]  = { "systemctl", "hibernate", NULL };
static const char *filescmd[]  = { "alacritty", "-e","vifm", NULL };
static const char *volup[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *voldown[]  = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *volmute[]  = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *brightup[]  = { "xbacklight", "-inc", "5", NULL};
static const char *brightdown[]  = { "xbacklight", "-dec", "5", NULL};
static const char *screenshot[]  = { "flameshot", "gui", NULL};
static const char *screenwarm[]  = { "redshift", "-P", "-O", "4000", NULL};
static const char *screennormal[]  = { "redshift", "-P", "-O", "6500", NULL};
static const char *musicselect[]  = { "mpd_select", NULL};
static const char *musicnext[]  = { "mpd_next", NULL};
static const char *musicprev[]  = { "mpc", "prev", NULL};
static const char *musicpause[]  = { "mpc", "toggle", NULL};
static const char *musicshuffle[]  = { "mpc", "shuffle", NULL};

static Key keys[] = {
	/* modifier                     key              function        argument */
	{ MODKEY,                       XK_p,                   spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_r,                   spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_v,                   spawn,          {.v = cliproficmd } },
	{ MODKEY,                       XK_f,                   spawn,          {.v = filescmd } },
	{ MODKEY|ShiftMask,             XK_Return,              spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_s,                   togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ControlMask,           XK_h,                   spawn,          {.v = hibernatecmd } },
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,       {.v = volup } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,       {.v = voldown } },
	{ 0,                            XF86XK_AudioMute,          spawn,       {.v = volmute } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,       {.v = brightup } },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,       {.v = brightdown } },
	{ 0,                            XK_Print,               spawn,          {.v = screenshot } },
	{ MODKEY|ControlMask,           XK_z,                   spawn,          {.v = screenwarm } },
	{ MODKEY|ControlMask,           XK_x,                   spawn,          {.v = screennormal } },
	{ MODKEY|ShiftMask,             XK_m,                   spawn,          {.v = musicselect } },
	{ MODKEY,                       XK_Right,               spawn,          {.v = musicnext } },
	{ MODKEY,                       XK_Left,                spawn,          {.v = musicprev } },
	{ MODKEY,                       XK_space,               spawn,          {.v = musicpause } },
	{ MODKEY,                       XK_Down,                spawn,          {.v = musicshuffle } },
	{ MODKEY,                       XK_b,                   togglebar,      {0} },
	{ MODKEY,                       XK_j,                   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                   focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                   incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                   incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                   setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,              zoom,           {0} },
	{ MODKEY,                       XK_Tab,                 view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,                   killclient,     {0} },
	{ MODKEY,                       XK_t,                   setlayout,      {.v = &layouts[0]} },
//	{ MODKEY,                       XK_f,                   setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                   setlayout,      {.v = &layouts[2]} },
//	{ MODKEY,                       XK_space,               setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,               togglefloating, {0} },
	{ MODKEY,                       XK_0,                   view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                   tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,               focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,              focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,               tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,              tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                                   0)
	TAGKEYS(                        XK_2,                                   1)
	TAGKEYS(                        XK_3,                                   2)
	TAGKEYS(                        XK_4,                                   3)
	TAGKEYS(                        XK_5,                                   4)
	TAGKEYS(                        XK_6,                                   5)
	TAGKEYS(                        XK_7,                                   6)
	TAGKEYS(                        XK_8,                                   7)
	TAGKEYS(                        XK_9,                                   8)
	{ MODKEY|ShiftMask,             XK_q,                   quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

