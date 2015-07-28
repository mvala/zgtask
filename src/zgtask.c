#include "../include/zgtask.h"

void
usage ()
{
    fprintf (stderr, "usage:\n");
    fprintf (stderr, "\tzgtask --client <name> <url>\n");
    fprintf (stderr, "\tzgtask --node <name> <url parent> <url child>\n");
    fprintf (stderr, "\nexample:\n");
    fprintf (stderr, "\tzgtask --client client tcp://127.0.0.1:12345\n");
    fprintf (stderr,
             "\tzgtask --node node1 tcp://127.0.0.1:12345 tpc://127.0.0.1:12346\n");


    exit (EXIT_FAILURE);
}

int
main (int argc, char **argv)
{

    int i;
    char *name_cli = NULL;
    char *name_node = NULL;
    char *url_cli_parent = NULL;
    char *url_node_parent = NULL;
    char *url_node_child = NULL;
    for (i = 1; i < argc; i++)
    {
        if (strcmp (argv [i], "--client") == 0) {
            if (i + 2 <= argc - 1) {
                i++;
                name_cli = strdup (argv [i]);
                i++;
                url_cli_parent = strdup (argv [i]);
            }
            else
                usage ();
        }
        else
        if (strcmp (argv [i], "--node") == 0) {
            if (i + 3 <= argc - 1) {
                i++;
                name_node = strdup (argv [i]);
                i++;
                url_node_parent = strdup (argv [i]);
                i++;
                url_node_child = strdup (argv [i]);
            }
            else
                usage ();
        }
    }


    if (!name_cli && !name_node)
        usage ();

    if (name_cli) {
        printf ("Creating client '%s' and connecting to '%s' \n", name_cli,
                url_cli_parent);
        zgtask_client_t *client = zgtask_client_new (name_cli, url_cli_parent);
        zgtask_client_start (client);
        zgtask_client_print (client);
        zgtask_client_loop (client);
        zgtask_client_stop (client);
        zgtask_client_destroy (&client);
    }

    if (name_node) {
        printf ("Creating node '%s' with parent='%s' and child='%s'\n", name_node,
                url_node_parent, url_node_child);

        zgtask_node_t *node =
            zgtask_node_new (name_node, url_node_parent, url_node_child);
        zgtask_node_start (node);
        zgtask_node_print (node);
        zgtask_node_loop (node);
        zgtask_node_stop (node);
        zgtask_node_destroy (&node);

    }

    free (name_cli);
    free (name_node);
    free (url_cli_parent);
    free (url_node_parent);
    free (url_node_child);

    return EXIT_SUCCESS;
}
