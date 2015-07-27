/*  =========================================================================
    zgtask_tree - Tree object for zgtask

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef ZGTASK_TREE_H_INCLUDED
#define ZGTASK_TREE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


//  @interface
//  Create a new zgtask_tree
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_new (char *name, zgtask_tree_t *parent);

//  Destroy the zgtask_tree
ZGTASK_EXPORT void
    zgtask_tree_destroy (zgtask_tree_t **self_p);

//  Search for tree
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_lookup (zgtask_tree_t *self, char *name);

//  Returns name
ZGTASK_EXPORT char *
    zgtask_tree_get_name (zgtask_tree_t *self);

//  Returns net object
ZGTASK_EXPORT zgtask_net_t *
    zgtask_tree_get_net (zgtask_tree_t *self);

//  Returns task object
ZGTASK_EXPORT zgtask_task_t *
    zgtask_tree_get_task (zgtask_tree_t *self);

//  Returns child
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_get_child (zgtask_tree_t *self);

//  Returns brother
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_get_brother (zgtask_tree_t *self);

//  Returns parent
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_get_parent (zgtask_tree_t *self);

//  Add net object
ZGTASK_EXPORT zgtask_net_t *
    zgtask_tree_add_net (zgtask_tree_t *self, const char *format, ...);

//  Add task object
ZGTASK_EXPORT zgtask_task_t *
    zgtask_tree_add_task (zgtask_tree_t *self, const char *format, ...);

//  Add child
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_add_child (zgtask_tree_t *self, const char *format, ...);

//  Add brother
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_add_brother (zgtask_tree_t *self, const char *format, ...);

//  Sets subtree status
ZGTASK_EXPORT int
    zgtask_tree_set_status_subtree (zgtask_tree_t *self, char *name, int status);

//  Generates subjobs
ZGTASK_EXPORT int
    zgtask_tree_generate (zgtask_tree_t *self, int min, int max);

//  Import json to tree
ZGTASK_EXPORT int
    zgtask_tree_import_json (zgtask_tree_t *self, json_t *json);

//  Export tree to json
ZGTASK_EXPORT char *
    zgtask_tree_export_json (zgtask_tree_t *self, char *path, json_t *json);

//  Print properties of object
ZGTASK_EXPORT void
    zgtask_tree_print (zgtask_tree_t *self);

//  Self test of this class
ZGTASK_EXPORT void
    zgtask_tree_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
