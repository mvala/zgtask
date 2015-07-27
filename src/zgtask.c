#include "../include/zgtask.h"

void
testZyre (const char *name, bool isBind)
{

    zyre_t *zyre = zyre_new (name);
    if (isBind)
        zyre_gossip_bind (zyre, "tcp://127.0.0.1:12345");
    else
        zyre_gossip_connect (zyre, "tcp://127.0.0.1:12345");

    zyre_start (zyre);

    zyre_join (zyre, "GLOBAL");
    zyre_print (zyre);


    zyre_event_t *zyre_event = zyre_event_new (zyre);
    zyre_event_print (zyre_event);
    zyre_event_destroy (&zyre_event);

    zyre_event = zyre_event_new (zyre);
    zyre_event_print (zyre_event);
    zyre_event_destroy (&zyre_event);

    // One node shouts to GLOBAL
    zmsg_t *msg = zmsg_new ();
    zmsg_addstr (msg, "Hello, World");
    zyre_shout (zyre, "GLOBAL", &msg);

    zyre_event = zyre_event_new (zyre);
    zyre_event_print (zyre_event);
    zyre_event_destroy (&zyre_event);


    zyre_stop (zyre);

    zyre_destroy (&zyre);
}

int
main (int argc, char **argv)
{

    if (argc < 1)
        return 1;

    testZyre (argv [1], argc > 2);


    return 0;
}
