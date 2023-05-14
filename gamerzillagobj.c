/* -*- Mode: c; c-basic-offset: 4 -*- 
 *
 * GOBject Introspection Gamerzilla
 * 
 */

#include <stdio.h>
#include <pthread.h>
#include <gamerzilla.h>
#include "gamerzillagobj.h"

pthread_t id;
volatile int stop = 0;

void *run_server(void *arg);

/**
 * SECTION: gamerzilla-gamerzillagobj
 * @short_description: A gamerzillagobj.
 *
 * The #GamerzillaGamerzillaGobj is a class to display friendly greetings.
 */

G_DEFINE_TYPE (GamerzillaGamerzillaGobj, gamerzilla_gamerzillagobj, G_TYPE_OBJECT)

#define GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE(o)	\
    (G_TYPE_INSTANCE_GET_PRIVATE ((o), GAMERZILLA_GAMERZILLAGOBJ_TYPE, GamerzillaGamerzillaGobjPrivate))

struct _GamerzillaGamerzillaGobjPrivate {
    char *placeholder;
};

enum
{
    PROP_0,

    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { };

static void
gamerzilla_gamerzillagobj_init (GamerzillaGamerzillaGobj *object)
{
    GamerzillaGamerzillaGobjPrivate *priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (object);
}

static void
gamerzilla_gamerzillagobj_finalize (GObject *object)
{
    GamerzillaGamerzillaGobjPrivate *priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (object);

    G_OBJECT_CLASS (gamerzilla_gamerzillagobj_parent_class)->finalize (object);
}

static void
gamerzilla_gamerzillagobj_set_property (GObject      *object,
			  guint         property_id,
			  const GValue *value,
			  GParamSpec   *pspec)
{
    GamerzillaGamerzillaGobjPrivate *priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (object);

    switch (property_id) {
    default:
	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
	break;
    }
}

static void
gamerzilla_gamerzillagobj_get_property (GObject    *object,
			  guint       property_id,
			  GValue     *value,
			  GParamSpec *pspec)
{
    GamerzillaGamerzillaGobjPrivate *priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (object);

    switch (property_id) {
    default:
	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
	break;
    }
}

static void
gamerzilla_gamerzillagobj_class_init (GamerzillaGamerzillaGobjClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->set_property = gamerzilla_gamerzillagobj_set_property;
    object_class->get_property = gamerzilla_gamerzillagobj_get_property;
    object_class->finalize = gamerzilla_gamerzillagobj_finalize;

    g_type_class_add_private (object_class, sizeof (GamerzillaGamerzillaGobjPrivate));
}


/**
 * gamerzilla_gamerzillagobj_new:
 *
 * Allocates a new #GamerzillaGamerzillaGobj.
 *
 * Return value: a new #GamerzillaGamerzillaGobj.
 */
GamerzillaGamerzillaGobj*
gamerzilla_gamerzillagobj_new ()
{
    GamerzillaGamerzillaGobj *gamerzillagobj;

    gamerzillagobj = g_object_new (GAMERZILLA_GAMERZILLAGOBJ_TYPE, NULL);
    return gamerzillagobj;
}

/**
 * gamerzilla_gamerzillagobj_serverstart:
 * @gamerzillagobj: a #GamerzillaGamerzillaGobj
 *
 * Runs the server.
 *
 * Return value: nothing.
 */
void
gamerzilla_gamerzillagobj_serverstart (GamerzillaGamerzillaGobj *gamerzillagobj)
{
    GamerzillaGamerzillaGobjPrivate *priv;
    g_return_if_fail (gamerzillagobj != NULL);

    priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (gamerzillagobj);

    pthread_create(&id, NULL, run_server, NULL);
}

/**
 * gamerzilla_gamerzillagobj_serverstop:
 * @gamerzillagobj: a #GamerzillaGamerzillaGobj
 *
 * Stops the server.
 *
 * Return value: nothing.
 */
void
gamerzilla_gamerzillagobj_serverstop (GamerzillaGamerzillaGobj *gamerzillagobj)
{
    GamerzillaGamerzillaGobjPrivate *priv;
    g_return_if_fail (gamerzillagobj != NULL);

    priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (gamerzillagobj);

    stop = 1;
    int* ptr;
    pthread_join(id, &ptr);
}

char *trimend(char *s)
{
	int i = strlen(s);
	for (; (i > 0) && (isspace(s[i - 1])); i--)
		s[i - 1] = 0;
	return s;
}

char *savePath[3] = {".local", "share", "gamerzillaserver"};

void *run_server(void *arg)
{
	char *savedir = NULL;
	char *home = getenv("XDG_DATA_HOME");
	if (!home)
	{
		home = getenv("HOME");
		if (home)
		{
			int len = strlen(home);
			savedir = (char *)malloc(len + 100);
			strcpy(savedir, home);
			if (savedir[len - 1] != '/')
			{
				strcat(savedir, "/");
			}
			for (int i = 0; i < 3; i++)
			{
				strcat(savedir, savePath[i]);
				int err = mkdir(savedir, 0700);
				if ((-1 == err) && (EEXIST != errno))
				{
					fprintf(stderr, "Error creating directory %s\n", savedir);
					exit(2);
				}
				strcat(savedir, "/");
			}
		}
	}
	if (!home)
	{
		savedir = (char *)malloc(100);
		strcpy(savedir, "./gamerzillaserver/");
	}
	char *url = NULL;
	char *name = NULL;
	char *pswd = NULL;
	bool useConfig = true;
	bool useConnect = true;
	char *config  = "server.cfg";
	char *fullconfig = (char *)malloc(strlen(savedir) + strlen(config) + 1);
	strcpy(fullconfig, savedir);
	strcat(fullconfig, config);
	if (useConfig && useConnect)
	{
		char tmp[201];
		FILE *f = fopen(fullconfig, "r");
		if ((f) && (NULL != fgets(tmp, 200, f)))
		{
			url = strdup(trimend(tmp));
			if (NULL != fgets(tmp, 200, f))
				name = strdup(trimend(tmp));
			if (NULL != fgets(tmp, 200, f))
				pswd = strdup(trimend(tmp));
		}
	}
	bool init = GamerzillaStart(true, savedir);
	if (!init)
	{
		fprintf(stderr, "Failed to start server\n");
		pthread_exit(&stop);
	}
	if ((useConnect) && (url != NULL))
		GamerzillaConnect(url, name, pswd);
	struct timeval timeout;
	while (!stop)
	{
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		GamerzillaServerProcess(&timeout);
	}
	pthread_exit(&stop);
}
