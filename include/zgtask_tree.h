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

//  Add child
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_add_child (zgtask_tree_t *self, char *name);

//  Add brother
ZGTASK_EXPORT zgtask_tree_t *
    zgtask_tree_add_brother (zgtask_tree_t *self, char *name);

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
