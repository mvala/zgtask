#include "../include/zgtask.h"

#include <jansson.h>

zgtask_tree_t *testTree() {
	zgtask_tree_t *tree0 = zgtask_tree_new ("t0", 0);
	zgtask_task_t *task = zgtask_tree_get_task (tree0);
	zgtask_task_set_command (task,"numcal --seed %ID%");
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

	if (!tree40 || !tree12 || !tree23 || !tree222 )
		return tree0;

	zgtask_tree_print(tree0);

	return tree0;

}

zgtask_tree_t *testJobs(int min, int max) {

	zgtask_tree_t *c = zgtask_tree_new ("t", 0);
	zgtask_task_t *task = zgtask_tree_get_task (c);
	zgtask_task_set_command (task,"numcal --seed %ID%");
//	zgtask_task_set_min_max (task, min, max);

	zgtask_tree_generate (c, min, max);
	zgtask_tree_set_status_subtree (c, "t2", 0);
	zgtask_tree_set_status_subtree (c, "t3", 5);
	zgtask_tree_set_status_subtree (c, "t4", 0);
	zgtask_tree_set_status_subtree (c, "t1", 0);
	zgtask_tree_set_status_subtree (c, "t5", 5);
	zgtask_tree_set_status_subtree (c, "t7", 0);

	zgtask_tree_print(c);

	return c;
}


zgtask_tree_t *testJobs2(int min, int max) {

	zgtask_tree_t *client = zgtask_tree_new ("client", 0);
	zgtask_tree_t *ca = zgtask_tree_add_child (client, "ClusterA");
	zgtask_tree_t *cb = zgtask_tree_add_brother (ca, "ClusterB");

	zgtask_task_t *task;
	task = zgtask_tree_get_task (client);
	zgtask_task_set_command (task, "numcal --seed %ID%");

	zgtask_tree_generate (ca, min, max);
	zgtask_tree_generate (cb, min+max, 2*max);

	zgtask_tree_set_status_subtree (client, "t1", 0);
	zgtask_tree_set_status_subtree (client, "t2", 0);
	zgtask_tree_set_status_subtree (client, "t3", 0);
	zgtask_tree_set_status_subtree (client, "t4", 0);
	zgtask_tree_set_status_subtree (client, "t5", 5);
	zgtask_tree_set_status_subtree (client, "t6", 0);
	zgtask_tree_set_status_subtree (client, "t7", 0);
	zgtask_tree_set_status_subtree (client, "t8", 0);
	zgtask_tree_set_status_subtree (client, "t9", 0);
	zgtask_tree_set_status_subtree (client, "t10", 0);

	zgtask_tree_print(client);

	return client;
}


int main(int argc, char **argv) {

	zgtask_tree_t *t = 0;

	// Test tree
	if (argc == 2 && streq (argv [1], "0"))
		t = testTree ();

	// Test jobs
	if (argc == 2 && streq (argv [1], "1"))
		t = testJobs (1, 10);

	// Test jobs
	if (argc == 2 && streq (argv [1], "2"))
		t = testJobs2 (1, 5);

	if (t)
		zgtask_tree_destroy(&t);

	return 0;
}
