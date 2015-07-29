#include "../include/zgtask.h"

void
usage ()
{
    fprintf (stderr, "usage:\n");
    fprintf (stderr, "\tzgtask_rdr <name> <url parent> <url child>\n");
    fprintf (stderr, "\nexample:\n");
    fprintf (stderr,
             "\tzgtask_rdr rdr1 tcp://127.0.0.1:12345 tpc://127.0.0.1:12346\n");


    exit (EXIT_FAILURE);
}

int
main (int argc, char **argv)
{
    if (argc < 4)
        usage ();

    char *name_node = strdup (argv [1]);
    char *url_node_parent = strdup (argv [2]);
    char *url_node_child = strdup (argv [3]);
    printf ("Creating node '%s' with parent='%s' and child='%s'\n", name_node,
            url_node_parent, url_node_child);

    if (!strcmp (name_node, ""))
        usage ();

    zgtask_node_t *node =
        zgtask_node_new (name_node, url_node_parent, url_node_child);
    zgtask_node_start (node);
    zgtask_node_print (node);
    zgtask_node_loop (node);
    zgtask_node_stop (node);
    zgtask_node_destroy (&node);

    free (name_node);
    free (url_node_parent);
    free (url_node_child);

    return EXIT_SUCCESS;
}
