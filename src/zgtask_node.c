/*  =========================================================================
    zgtask_node - Zgtask node object

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
    zgtask_node - Zgtask node object
@discuss
@end
*/

#include "../include/zgtask.h"

//  Structure of our class

struct _zgtask_node_t {
    char *name;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_node.

zgtask_node_t *
zgtask_node_new (const char *name)
{
    zgtask_node_t *self = (zgtask_node_t *) zmalloc (sizeof (zgtask_node_t));
    assert (self);

    self->name = strdup (name);

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the zgtask_node.

void
zgtask_node_destroy (zgtask_node_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgtask_node_t *self = *self_p;

        free (self->name);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Print properties of the zgtask_node object.

void
zgtask_node_print (zgtask_node_t *self)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_node_test (bool verbose)
{
    printf (" * zgtask_node: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_node_t *self = zgtask_node_new ("zgtask_node");
    assert (self);
    zgtask_node_destroy (&self);
    //  @end

    printf ("OK\n");
}
