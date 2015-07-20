/*  =========================================================================
    zgtask_task - Task infozgtask

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
    zgtask_task - Task infozgtask
@discuss
@end
*/

#include "../include/zgtask.h"

//  Structure of our class
#define MAX_LENGTH 255

struct _zgtask_task_t {
	char command[MAX_LENGTH];
	int required_time;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_task.

zgtask_task_t *
zgtask_task_new ()
{
    zgtask_task_t *self = (zgtask_task_t *) zmalloc (sizeof (zgtask_task_t));
    assert (self);

    //  TODO: Initialize properties

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the zgtask_task.

void
zgtask_task_destroy (zgtask_task_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgtask_task_t *self = *self_p;

        //  TODO: Free class properties

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Print properties of the zgtask_task object.

void
zgtask_task_print (zgtask_task_t *self)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_task_test (bool verbose)
{
    printf (" * zgtask_task: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_task_t *self = zgtask_task_new ();
    assert (self);
    zgtask_task_destroy (&self);
    //  @end

    printf ("OK\n");
}
