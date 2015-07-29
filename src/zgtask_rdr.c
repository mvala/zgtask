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

    char *name_rdr = strdup (argv [1]);
    char *url_rdr_parent = strdup (argv [2]);
    char *url_rdr_child = strdup (argv [3]);
    printf ("Creating rdr '%s' with parent='%s' and child='%s'\n", name_rdr,
            url_rdr_parent, url_rdr_child);

    if (!strcmp (name_rdr, ""))
        usage ();

    zgtask_redirector_t *rdr =
        zgtask_redirector_new (name_rdr, url_rdr_parent, url_rdr_child);
    zgtask_redirector_start (rdr);
    zgtask_redirector_print (rdr);
    zgtask_redirector_loop (rdr);
    zgtask_redirector_stop (rdr);
    zgtask_redirector_destroy (&rdr);

    free (name_rdr);
    free (url_rdr_parent);
    free (url_rdr_child);

    return EXIT_SUCCESS;
}
