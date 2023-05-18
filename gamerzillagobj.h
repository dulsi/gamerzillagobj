/* -*- Mode: c; c-basic-offset: 4 -*- 
 *
 * GOBject Introspection Gamerzilla
 * 
 */

#ifndef __GAMERZILLA_GAMERZILLAGOBJ_H__
#define __GAMERZILLA_GAMERZILLAGOBJ_H__

#include <glib.h>
#include <glib-object.h>

#define GAMERZILLA_GAMERZILLAGOBJ_TYPE		\
    (gamerzilla_gamerzillagobj_get_type())
#define GAMERZILLA_GAMERZILLAGOBJ(o)			\
    (G_TYPE_CHECK_INSTANCE_CAST ((o), GAMERZILLA_GAMERZILLAGOBJ_TYPE, GamerzillaGamerzillaGobj))
#define GAMERZILLA_GAMERZILLAGOBJ_CLASS(c)		\
    (G_TYPE_CHECK_CLASS_CAST ((c), GAMERZILLA_GAMERZILLAGOBJ_TYPE, GamerzillaGamerzillaGobjClass))
#define GAMERZILLA_IS_GAMERZILLAGOBJ(o)		\
    (G_TYPE_CHECK_INSTANCE_TYPE ((o), GAMERZILLA_GAMERZILLAGOBJ_TYPE))
#define GAMERZILLA_IS_GAMERZILLAGOBJ_CLASS(c)		\
    (G_TYPE_CHECK_CLASS_TYPE ((c),  GAMERZILLA_GAMERZILLAGOBJ_TYPE))
#define GAMERZILLA_GAMERZILLAGOBJ_GET_CLASS(o)	\
    (G_TYPE_INSTANCE_GET_CLASS ((o), GAMERZILLA_GAMERZILLAGOBJ_TYPE, GamerzillaGamerzillaGobjClass))

typedef struct _GamerzillaGamerzillaGobj		GamerzillaGamerzillaGobj;
typedef struct _GamerzillaGamerzillaGobjPrivate	GamerzillaGamerzillaGobjPrivate;
typedef struct _GamerzillaGamerzillaGobjClass		GamerzillaGamerzillaGobjClass;

struct _GamerzillaGamerzillaGobj {
    GObject parent;
};

struct _GamerzillaGamerzillaGobjClass {
    GObjectClass parent;
};

GType		gamerzilla_gamerzillagobj_get_type	() G_GNUC_CONST;

GamerzillaGamerzillaGobj*	gamerzilla_gamerzillagobj_new		(void);

void		gamerzilla_gamerzillagobj_serverstart	(GamerzillaGamerzillaGobj *gamerzillagobj);
void  gamerzilla_gamerzillagobj_connect(GamerzillaGamerzillaGobj *gamerzillagobj);
void		gamerzilla_gamerzillagobj_serverstop	(GamerzillaGamerzillaGobj *gamerzillagobj);

#endif /* __GAMERZILLA_GAMERZILLAGOBJ_H__ */
