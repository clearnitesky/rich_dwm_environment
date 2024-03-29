/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int swallowfloating    = 1;	/* swallowing on for floating windows */
static const int gappx		    = 0;	/* initial window gaps */
static const unsigned int snap      = 4;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]	    = { "JetBrainsMono-Regular:size=9",
					"NotoColorEmoji:size=10:antialias=true:autohint=true" };
static const char dmenufont[]	    = "JetBrainsMono-Regular:size=9";

static const char col_themecol0[]    = "#bbbbbb";
static const char col_themecol1[]    = "#eeeeee";
static const char col_themecol2[]    = "#222222";
static const char col_themecol3[]    = "#005577";
static const char col_themecol4[]    = "#444444";
static const char col_themecol5[]    = "#484A56";


static const char *colors[][3]      = {

/*                       bar text,      bar color,     win border    */
	[SchemeNorm] = { col_themecol0, col_themecol2, col_themecol5 },
	[SchemeSel]  = { col_themecol1, col_themecol5, col_themecol5 }, };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "🗑" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance  title  tags mask  isfloating  isterminal  noswallow  monitor */
/*	{ "Gimp",        NULL,     NULL,  0,         1,          0,          0,         -1 }, */
	{ "st",	         NULL,     NULL,  0,         0,          1,         -1,         -1 },
/*	{ "mpvfloat",    NULL,     "mpv", 0,         1,          0,          0,         -1 }, */
	{ NULL,  "guvcview", "guvcview",  0,         1,          0,          0,         -1 },
	{ NULL,     NULL, "Event Tester", 0,         0,          0,          1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "🐧 ",      tile },    /* first layout is default */
	{ "👻 ",      NULL },    /* no layout function means floating behavior */
	{ "🔍 ",      monocle }, };

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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon,
				"-fn", dmenufont,
				"-nb", col_themecol2, "-nf", col_themecol0,
				"-sb", col_themecol5, "-sf", col_themecol1, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                   XK_space,  	spawn,          {.v = dmenucmd } },
	{ MODKEY,	            XK_Return, 	spawn,          {.v = termcmd } },

	{ MODKEY,                   XK_b,      	togglebar,      {0} },
	{ MODKEY,                   XK_j,      	focusstack,     {.i = +1 } },
	{ MODKEY,                   XK_k,      	focusstack,     {.i = -1 } },
	{ MODKEY,                   XK_i,      	incnmaster,     {.i = +1 } },
	{ MODKEY,                   XK_d,      	incnmaster,     {.i = -1 } },
	{ MODKEY,                   XK_h,      	setmfact,       {.f = -0.05} },
	{ MODKEY,                   XK_l,      	setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,         XK_Return, 	zoom,           {0} },
	{ MODKEY,                   XK_Tab,    	view,           {0} },

	{ MODKEY,		    XK_z,       setgaps,       {.i = -2 } },
        { MODKEY,		    XK_x,       setgaps,       {.i = +2 } },

	{ MODKEY,                   XK_equal,  	setlayout,      {.v = &layouts[0]} },
	{ MODKEY,	            XK_minus,  	setlayout,      {.v = &layouts[1]} },
/*	{ MODKEY,                   XK_equal,  	setlayout,      {.v = &layouts[2]} },*/

	{ MODKEY|ShiftMask,         XK_space,  	togglefloating, {0} },
	{ MODKEY,                   XK_0,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,         XK_0,      	tag,            {.ui = ~0 } },
	{ MODKEY,                   XK_comma,  	focusmon,       {.i = -1 } },
	{ MODKEY,                   XK_period, 	focusmon,       {.i = +1 } },
 	{ MODKEY|ShiftMask,         XK_comma,  	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,         XK_period, 	tagmon,         {.i = +1 } },

	{ MODKEY,		    XK_q,	killclient,	{0} },
	{ MODKEY|ShiftMask,         XK_q,       quit,           {0} },

	TAGKEYS( XK_1, 0)
	TAGKEYS( XK_2, 1)
	TAGKEYS( XK_3, 2)
	TAGKEYS( XK_4, 3)
	TAGKEYS( XK_5, 4)
	TAGKEYS( XK_6, 5)
/*	TAGKEYS( XK_7, 6)
	TAGKEYS( XK_8, 7)*/
	TAGKEYS( XK_9, 6) };

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
	{ ClkTagBar,		0,		Button4,	shiftview,	{.i = +1 } },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = -1 } },
};
