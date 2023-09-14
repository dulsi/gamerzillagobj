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
volatile int useConnect = 0;

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
    char *url;
    char *username;
    char *password;
};

enum
{
    PROP_0,

    PROP_GAMERZILLAURL,
    PROP_USERNAME,
    PROP_PASSWORD,

    N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, NULL, NULL };

static void
gamerzilla_gamerzillagobj_init (GamerzillaGamerzillaGobj *object)
{
    GamerzillaGamerzillaGobjPrivate *priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (object);
}

static void
gamerzilla_gamerzillagobj_finalize (GObject *object)
{
    GamerzillaGamerzillaGobjPrivate *priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (object);

    g_free (priv->url);
    g_free (priv->username);
    g_free (priv->password);
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
    case PROP_GAMERZILLAURL:
	g_free (priv->url);
	priv->url = g_value_dup_string (value);
	break;
    case PROP_USERNAME:
	g_free (priv->username);
	priv->username = g_value_dup_string (value);
	break;
    case PROP_PASSWORD:
	g_free (priv->password);
	priv->password = g_value_dup_string (value);
	break;
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
    case PROP_GAMERZILLAURL:
	g_value_set_string (value, priv->url);
	break;
    case PROP_USERNAME:
	g_value_set_string (value, priv->username);
	break;
    case PROP_PASSWORD:
	g_value_set_string (value, priv->password);
	break;
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

    /**
     * GamerzillaGobj:url:
     *
     * The url for gamerzilla.
     */
    obj_properties[PROP_GAMERZILLAURL] = 
	g_param_spec_string ("url",
			     "Url",
			     "The url for gamerzilla.",
			     "",
			     G_PARAM_READWRITE |
			     G_PARAM_CONSTRUCT);
    /**
     * GamerzillaGobj:username:
     *
     * The username for gamerzilla.
     */
    obj_properties[PROP_USERNAME] = 
	g_param_spec_string ("username",
			     "Username",
			     "The username for gamerzilla.",
			     "",
			     G_PARAM_READWRITE |
			     G_PARAM_CONSTRUCT);
    /**
     * GamerzillaGobj:password:
     *
     * The password for gamerzilla.
     */
    obj_properties[PROP_PASSWORD] = 
	g_param_spec_string ("password",
			     "Password",
			     "The password for gamerzilla.",
			     "",
			     G_PARAM_READWRITE |
			     G_PARAM_CONSTRUCT);

    g_object_class_install_properties (object_class,
				       N_PROPERTIES,
				       obj_properties);

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
    stop = 0;

    priv = GAMERZILLA_GAMERZILLAGOBJ_GET_PRIVATE (gamerzillagobj);

    pthread_create(&id, NULL, run_server, priv);
}

void gamerzilla_gamerzillagobj_connect (GamerzillaGamerzillaGobj *gamerzillagobj)
{
    useConnect = 1;
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
	GamerzillaGamerzillaGobjPrivate *priv = (GamerzillaGamerzillaGobjPrivate *)arg;
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
	bool init = GamerzillaStart(true, savedir);
	if (!init)
	{
		fprintf(stderr, "Failed to start server\n");
		pthread_exit(&stop);
	}
	if (useConnect)
	{
		if (priv->url != NULL)
			GamerzillaConnect(priv->url, priv->username, priv->password);
		useConnect = 0;
	}
	struct timeval timeout;
	while (!stop)
	{
		if (useConnect)
		{
			if (priv->url != NULL)
				GamerzillaConnect(priv->url, priv->username, priv->password);
			useConnect = 0;
		}
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		GamerzillaServerProcess(&timeout);
	}
	GamerzillaQuit();
	pthread_exit(&stop);
}
