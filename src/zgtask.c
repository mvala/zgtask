#include "../include/zgtask.h"

int
main (int argc, char **argv)
{

    if (argc < 1)
        return 1;

    zyre_t *zyre = zyre_new (argv [1]);

    if (argc > 2)
        zyre_gossip_connect (zyre, "tcp://147.213.192.236:12345");
    else
        zyre_gossip_bind (zyre, "tcp://147.213.192.236:12345");

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
    return 0;
}
