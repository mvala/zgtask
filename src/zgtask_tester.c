#include "../include/zgtask.h"

#include <jansson.h>

#define JSON_FILENAME "/tmp/zgtask_test.json"

zgtask_tree_t *
testTree ()
{
    //  Create testing tree structure
    zgtask_tree_t *tree0 = zgtask_tree_new ("t0", 0);

    //  Adding task
    zgtask_tree_add_task (tree0, "numcal --seed %ID%");

    zgtask_task_t *task = zgtask_tree_get_task (tree0);
    if (task)
        zgtask_task_set_min_max (task, 0, 100);

    zgtask_tree_t *tree10 = zgtask_tree_add_child (tree0, "t10");

    zgtask_tree_t *tree11 = zgtask_tree_add_child (tree10, "t11");
    zgtask_tree_t *tree12 = zgtask_tree_add_brother (tree11, "t12");

    zgtask_tree_t *tree20 = zgtask_tree_add_brother (tree10, "t20");
    zgtask_tree_t *tree21 = zgtask_tree_add_child (tree20, "t21");
    zgtask_tree_t *tree22 = zgtask_tree_add_brother (tree21, "t22");

    zgtask_tree_t *tree221 = zgtask_tree_add_child (tree22, "t221");
    zgtask_tree_t *tree222 = zgtask_tree_add_brother (tree221, "t222");

    zgtask_tree_t *tree23 = zgtask_tree_add_brother (tree22, "t23");


    zgtask_tree_t *tree30 = zgtask_tree_add_brother (tree20, "t30");
    zgtask_tree_t *tree40 = zgtask_tree_add_brother (tree30, "t40");

    if (!tree40 || !tree12 || !tree23 || !tree222)
        return tree0;

    zgtask_tree_print (tree0);

    return tree0;

}

zgtask_tree_t *
testJobs (int min, int max)
{
    //  Creare initial tree structure
    zgtask_tree_t *c = zgtask_tree_new ("t", 0);

    //  Adding task
    zgtask_tree_add_task (c, "numcal --seed %ID%");

    //  Generate tree structure
    zgtask_tree_generate (c, min, max);

    //  Sets status to some tasks
    zgtask_tree_set_status_subtree (c, "t2", 0);
    zgtask_tree_set_status_subtree (c, "t3", 5);
    zgtask_tree_set_status_subtree (c, "t4", 0);
    zgtask_tree_set_status_subtree (c, "t1", 0);
    zgtask_tree_set_status_subtree (c, "t5", 5);
    zgtask_tree_set_status_subtree (c, "t7", 0);

    zgtask_tree_print (c);

    return c;
}


zgtask_tree_t *
testJobs2 (int min, int max)
{
    //  Creare initial tree structure
    zgtask_tree_t *client = zgtask_tree_new ("client", 0);
    zgtask_tree_t *ca = zgtask_tree_add_child (client, "ClusterA");
    zgtask_tree_t *cb = zgtask_tree_add_brother (ca, "ClusterB");

    char *cmd = strdup ("numcal --seed %ID%");
    //  Adding task
    zgtask_tree_add_task (client, cmd);
    zgtask_tree_add_task (ca, cmd);
    zgtask_tree_add_task (cb, cmd);

    //  Generate tree structure
    zgtask_tree_generate (ca, min, max);
    zgtask_tree_generate (cb, min+max, 2*max);

    //  Sets status to some tasks
    zgtask_tree_set_status_subtree (client, "t1", 0);
    zgtask_tree_set_status_subtree (client, "t2", 0);
    zgtask_tree_set_status_subtree (client, "t3", 0);
    zgtask_tree_set_status_subtree (client, "t4", 0);
    zgtask_tree_set_status_subtree (client, "t5", 5);
    zgtask_tree_set_status_subtree (client, "t11", 0);
    zgtask_tree_set_status_subtree (client, "t12", 0);
    zgtask_tree_set_status_subtree (client, "t13", 0);
    zgtask_tree_set_status_subtree (client, "t14", 0);
    zgtask_tree_set_status_subtree (client, "t15", 0);

    //  Prints client tree
    zgtask_tree_print (client);

    free (cmd);

    return client;
}


zgtask_tree_t *
testJsonExport (int min, int max)
{

    zgtask_tree_t *client = testJobs2 (min, max);
    char *json_str = zgtask_tree_export_json (client, JSON_FILENAME, 0, 0);
    if (json_str)
        printf ("%s\n", json_str);

    free (json_str);
    return client;
}

zgtask_tree_t *
testJsonImport (int min, int max)
{
    zgtask_tree_t *t = NULL;
    //  Generate input json file, if doesn't exist
    if (!zsys_file_exists (JSON_FILENAME))
        t = testJsonExport (min, max);

    //  Create new tree
    zgtask_tree_t *json_import = zgtask_tree_new ("json_import", 0);

    //  Load json file
    json_error_t err;
    json_t *json = json_load_file (JSON_FILENAME, JSON_STRICT, &err);

    //  Imports json to tree
    if (json)
        zgtask_tree_import_json (json_import, json);

    //  Cleaning json
    json_decref (json);

    //  Prints json imported tree
    zgtask_tree_print (json_import);

    //  Cleaning exported tree
    if (t)
        zgtask_tree_destroy (&t);

    return json_import;
}

zgtask_tree_t *
testPacketSimple (int min, int max)
{
    zgtask_tree_t *root = zgtask_tree_new ("root", 0);
    zhashx_t *data  = zgtask_tree_get_data (root);

    zgtask_packet_t *packet = zgtask_packet_new ();
    zgtask_packet_set_min (packet, min);
    zgtask_packet_set_max (packet, max);
    zhashx_insert (data, "packet", packet);

    packet = (zgtask_packet_t *) zgtask_tree_get_packet (root);
    zgtask_packet_print (packet);

    int id = 0;
    zgtask_packet_t *p = zgtask_packet_get_packet (packet, 1);
//    zgtask_packet_print (p);

    zgtask_tree_t *t_p = zgtask_tree_add_child (root, "%d", ++id);
    data  = zgtask_tree_get_data (t_p);
    zhashx_insert (data, "packet", p);
    char *json_str;
    while (p) {
        p = zgtask_packet_get_packet (packet, 3);
        if (!p)
            break;
//        zgtask_packet_print (p);
        t_p = zgtask_tree_add_brother (t_p, "%d", ++id);
        data  = zgtask_tree_get_data (t_p);
        zhashx_insert (data, "packet", p);
    }

    zgtask_tree_print (t_p);

    //  Print last packet
    json_str = zgtask_tree_export_json (t_p, 0, 0, 0);
    printf ("%s\n", json_str);

    return root;
}

int
main (int argc, char **argv)
{

    zgtask_tree_t *t = 0;

    // Test tree
    if (argc == 2 && streq (argv [1], "0"))
        t = testTree ();

    // Test jobs
    if (argc == 2 && streq (argv [1], "1"))
        t = testJobs (1, 10);

    // Test jobs
    if (argc == 2 && streq (argv [1], "2"))
        t = testJobs2 (1, 10);

    // Test jobs
    if (argc == 2 && streq (argv [1], "3"))
        t = testJsonExport (1, 10);

    // Test jobs
    if (argc == 2 && streq (argv [1], "4"))
        t = testJsonImport (1, 10);

    // Test Packet Simple
    if (argc == 2 && streq (argv [1], "5"))
        t = testPacketSimple (1, 10);

    if (t)
        zgtask_tree_destroy (&t);

    return 0;
}
