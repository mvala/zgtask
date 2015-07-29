#include "../include/zgtask.h"

void
usage ()
{
    fprintf (stderr, "usage:\n");
    fprintf (stderr, "\tzgtask --client <name> <url>\n");
    fprintf (stderr, "\tzgtask --rdr <name> <url parent> <url child>\n");
    fprintf (stderr, "\nexample:\n");
    fprintf (stderr, "\tzgtask --client client tcp://127.0.0.1:12345\n");
    fprintf (stderr,
             "\tzgtask --rdr rdr1 tcp://127.0.0.1:12345 tpc://127.0.0.1:12346\n");


    exit (EXIT_FAILURE);
}

int
main (int argc, char **argv)
{

    int i;
    char *name_cli = NULL;
    char *name_rdr = NULL;
    char *url_cli_parent = NULL;
    char *url_rdr_parent = NULL;
    char *url_rdr_child = NULL;
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
        if (strcmp (argv [i], "--rdr") == 0) {
            if (i + 3 <= argc - 1) {
                i++;
                name_rdr = strdup (argv [i]);
                i++;
                url_rdr_parent = strdup (argv [i]);
                i++;
                url_rdr_child = strdup (argv [i]);
            }
            else
                usage ();
        }
    }


    if (!name_cli && !name_rdr)
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

    if (name_rdr) {
        printf ("Creating rdr '%s' with parent='%s' and child='%s'\n", name_rdr,
                url_rdr_parent, url_rdr_child);

        zgtask_redirector_t *rdr =
            zgtask_redirector_new (name_rdr, url_rdr_parent, url_rdr_child);
        zgtask_redirector_start (rdr);
        zgtask_redirector_print (rdr);
        zgtask_redirector_loop (rdr);
        zgtask_redirector_stop (rdr);
        zgtask_redirector_destroy (&rdr);

    }

    free (name_cli);
    free (name_rdr);
    free (url_cli_parent);
    free (url_rdr_parent);
    free (url_rdr_child);

    return EXIT_SUCCESS;
}
