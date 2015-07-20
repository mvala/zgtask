#include "../include/zgtask.h"
int main(int argc, char **argv) {

	zgtask_tree_t *tree00 = zgtask_tree_new ("t00", 0);

	zgtask_tree_t *tree10 = zgtask_tree_add_child(tree00, "t10");

	zgtask_tree_t *tree11 = zgtask_tree_add_child(tree10, "t11");
	zgtask_tree_t *tree12 = zgtask_tree_add_brother(tree11, "t12");

	zgtask_tree_t *tree20 = zgtask_tree_add_brother(tree10, "t20");
	zgtask_tree_t *tree21 = zgtask_tree_add_child(tree20, "t21");
	zgtask_tree_t *tree22 = zgtask_tree_add_brother(tree21, "t22");
	zgtask_tree_t *tree23 = zgtask_tree_add_brother(tree22, "t23");

	zgtask_tree_t *tree30 = zgtask_tree_add_brother(tree20, "t30");
	zgtask_tree_t *tree40 = zgtask_tree_add_brother(tree30, "t40");

	if (!tree40 || !tree12 || !tree23)
		return 1;

	zgtask_tree_print (tree00);
	return 0;
}
