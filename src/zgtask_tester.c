#include "../include/zgtask.h"
int main(int argc, char **argv) {

	zgtask_tree_t *tree = zgtask_tree_new ("t0", 0);

	zgtask_tree_t *tree10 = zgtask_tree_add_child(tree, "t10");

	zgtask_tree_t *tree20 = zgtask_tree_add_brother(tree10, "t20");
	zgtask_tree_t *tree30 = zgtask_tree_add_brother(tree20, "t30");
	zgtask_tree_t *tree40 = zgtask_tree_add_brother(tree30, "t40");


	zgtask_tree_t *tree11 = zgtask_tree_add_child(tree10, "t11");
	zgtask_tree_t *tree12 = zgtask_tree_add_brother(tree11, "t12");


	zgtask_tree_t *tree21 = zgtask_tree_add_child(tree20, "t21");
	zgtask_tree_t *tree22 = zgtask_tree_add_brother(tree21, "t22");

	if (!tree40 || !tree12 || !tree22)
		return 1;
//	zgtask_task_t *t0 = zgtask_tree_get_task (tree);
//	zgtask_task_set_command (t0, "");
//	zgtask_task_set_required_time (t0, 0);

	zgtask_tree_print (tree);

	zgtask_tree_destroy (&tree);

	return 0;
}
