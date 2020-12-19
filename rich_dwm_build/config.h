/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 4;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int gappx		    = 24; 	/* set default gaps */
static const int swallowfloating    = 1;	/* 1 means swallow floating by default */
static const char *fonts[]	    = { "Lato Heavy:size=10:antialias=true:autohint=true",
					"JoyPixels:pixelsize=11:antialias=true:autohint=true" };
static const char dmenufont[]	    = "Lato Heavy:size=10:antialias=true:autohint=true";
static const char col_white[]	    = "#ffffff";
static const char col_ltgrey[]	    = "#eeeeee";
static const char col_grey0[]	    = "#303030";
static const char col_grey1[]       = "#161616";
static const char col_black[]	    = "#000000";
static const char col_termblu[]	    = "#282A36";
static const char col_yelloo[]      = "#ffcc00";
static const char col_haiku[]       = "#315683";
static const char *colors[][3]      = {
/*                       bar text,   bar color,   win border */
	[SchemeNorm] = { col_yelloo, col_termblu, col_termblu },
	[SchemeSel]  = { col_yelloo, col_termblu, col_termblu }, };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "🗑" };

static const Rule rules[] = {
	/* class    instance  title  tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",   NULL,     NULL,  1 << 4,    1,          0,          0,         -1 },
	{ "st",	    NULL,     NULL,  0,		0,	    1, 		0,	   -1 }, };

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "🐧",      tile },    /* first layout is default */
	{ "👽",      NULL },    /* no layout function means floating behavior */
	{ "🔍",      monocle }, };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_termblu, "-nf", col_yelloo, "-sb", col_yelloo, "-sf", col_black, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                 key        function        argument */
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

	{ MODKEY,                   XK_minus,  	setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,         XK_minus,  	setlayout,      {.v = &layouts[1]} },
/*	{ MODKEY,                   XK_equal,  	setlayout,      {.v = &layouts[2]} }, */
	{ MODKEY,		    XK_equal, 	fullscreen,	{0} },

/*	{ MODKEY,                   XK_space,  	setlayout,      {0} }, */
	{ MODKEY|ShiftMask,         XK_space,  	togglefloating, {0} },
	{ MODKEY,                   XK_0,      	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,         XK_0,      	tag,            {.ui = ~0 } },
	{ MODKEY,                   XK_comma,  	focusmon,       {.i = -1 } },
	{ MODKEY,                   XK_period, 	focusmon,       {.i = +1 } },
 	{ MODKEY|ShiftMask,         XK_comma,  	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,         XK_period, 	tagmon,         {.i = +1 } },
	{ MODKEY,		    XK_x,  	setgaps,        {.i = +2 } },
	{ MODKEY,		    XK_z,  	setgaps,	{.i = -2 } },
/*	{ MODKEY|ShiftMask,	    XK_equal,  	setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,	    XK_minus,  	setgaps,	{.i = 18 } }, */

	{ MODKEY|ShiftMask,         XK_c,     	killclient,     {0} },
	{ MODKEY,		    XK_q,	killclient,	{0} },
	{ MODKEY|ShiftMask,         XK_q,       quit,           {0} },

	TAGKEYS( XK_1, 0)
	TAGKEYS( XK_2, 1)
	TAGKEYS( XK_3, 2)
	TAGKEYS( XK_4, 3)
	TAGKEYS( XK_5, 4)
	TAGKEYS( XK_6, 5)
	TAGKEYS( XK_7, 6)
	TAGKEYS( XK_8, 7)
	TAGKEYS( XK_9, 8) };

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
	{ ClkTagBar,		0,		Button4,	shiftview,      {.i = +1} },
	{ ClkTagBar,		0,		Button5,	shiftview,	{.i = -1} }, };
