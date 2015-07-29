#include "../include/zgtask.h"

void
usage ()
{
    fprintf (stderr, "usage:\n");
    fprintf (stderr, "\tzgtask_wk <name> <url>\n");
    fprintf (stderr, "\nexample:\n");
    fprintf (stderr, "\tzgtask_wk wk1 tcp://127.0.0.1:12345\n");
    exit (EXIT_FAILURE);
}

int
main (int argc, char **argv)
{
    if (argc < 3)
        usage ();

    char *name_cli = strdup (argv [1]);
    char *url_cli_parent = strdup (argv [2]);

    if (strcmp (name_cli, ""))
        usage ();

    printf ("Creating client '%s' and connecting to '%s' \n", name_cli,
            url_cli_parent);
    zgtask_worker_t *client = zgtask_worker_new (name_cli, url_cli_parent);
    zgtask_worker_start (client);
    zgtask_worker_print (client);
    zgtask_worker_loop (client);
    zgtask_worker_stop (client);
    zgtask_worker_destroy (&client);

    free (name_cli);
    free (url_cli_parent);

    return EXIT_SUCCESS;
}
