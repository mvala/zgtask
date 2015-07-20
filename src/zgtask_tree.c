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

/*
@header
    zgtask_tree - Tree object for zgtask
@discuss
@end
*/

#include "../include/zgtask.h"

//  Structure of our class

struct _zgtask_tree_t {
	zgtask_task_t *task;
	zgtask_tree_t *firstchild;
    zgtask_tree_t *nextsibling;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_tree.

zgtask_tree_t *
zgtask_tree_new ()
{
    zgtask_tree_t *self = (zgtask_tree_t *) zmalloc (sizeof (zgtask_tree_t));
    assert (self);

    //  TODO: Initialize properties
    self->task = zgtask_task_new();
    self->firstchild = 0;
    self->nextsibling = 0;

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the zgtask_tree.

void
zgtask_tree_destroy (zgtask_tree_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgtask_tree_t *self = *self_p;

        //  TODO: Free class properties
        zgtask_task_destroy(&self->task);
        zgtask_tree_destroy(&self->firstchild);
        zgtask_tree_destroy(&self->nextsibling);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Print properties of the zgtask_tree object.

void
zgtask_tree_print (zgtask_tree_t *self)
{
    assert (self);
    zgtask_task_print(self->task);
}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_tree_test (bool verbose)
{
    printf (" * zgtask_tree: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_tree_t *self = zgtask_tree_new ();
    assert (self);
    zgtask_tree_destroy (&self);
    //  @end

    printf ("OK\n");
}
