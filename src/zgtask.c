#include "../include/zgtask.h"

void
testZyre (int argc, char **argv)
{

    char *name = NULL;
    if (argc < 2)
        name = strdup ("zgtask_default");
    else
        name = strdup (argv [1]);

    zyre_t *zyre = zyre_new (name);

    if (argc > 2)
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

    free (name);
}

int
main (int argc, char **argv)
{

    if (argc < 4) {
        printf ("./%s <name> <parent> <child> \"<msg>\"\n", argv [0]);
        printf ("./%s t tcp://127.0.0.1:12345 tcp://127.0.0.1:12345 \n", argv [0]);
        exit (1);
    }

    //  Create testing tree structure
    zgtask_tree_t *t = zgtask_tree_new (argv [1], 0);

    zgtask_net_t *n = zgtask_tree_add_net (t, "%s_net", argv [1]);
    zyre_t *t_p = NULL;
    zyre_t *t_ch = NULL;


    if (strcmp (argv [2], "-1")) {
//    	printf("2=%s\n", argv[2]);
    	t_p = zgtask_net_init_zyre_parent (n);
        zyre_gossip_bind (t_p, argv [2]);
        zyre_start (t_p);
        zyre_join(t_p,"GLOBAL");
    }
    if (strcmp (argv [3], "-1")) {
//    	printf("3=%s\n", argv[3]);
    	t_ch = zgtask_net_init_zyre_child (n);
        zyre_gossip_connect (t_ch, argv [3]);
        zyre_start (t_ch);
        zyre_join(t_ch,"GLOBAL");
    }

    zclock_sleep(250);

    zgtask_tree_print (t);

    zmsg_t *msg = NULL;
//    printf ("ssss=%d %s\n",argc, argv [4]);
    zyre_event_t *zyre_event = NULL;
    if (argc == 5) {
    	msg = zmsg_new();
    	zmsg_addstr(msg, argv [4]);
    	zyre_shout(t_ch, "GLOBAL", &msg);
    }
    else {
    	while (!zsys_interrupted) {
    		zyre_event = zyre_event_new(t_p);
    		if (!zyre_event) {
        		zyre_event_destroy(&zyre_event);
    			break;

    		}
    		zyre_event_print(zyre_event);
    		zyre_event_destroy(&zyre_event);

    	}
    }

    if (t_p) {
    	zyre_leave(t_p, "GLOBAL");
//    	zyre_stop (t_p);
    }

    if (t_ch) {
    	zyre_leave(t_ch, "GLOBAL");
//    	zyre_stop (t_ch);
    }

    //  Cleaning tree
    zgtask_tree_destroy (&t);

    return 0;
}
