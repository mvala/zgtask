/*  =========================================================================
    zgtask_net - Zgtask network object

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
    zgtask_net - Zgtask network object
@discuss
@end
*/

#include "../include/zgtask.h"

//  Structure of our class

struct _zgtask_net_t {
    zyre_t *zyre;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_net.

zgtask_net_t *
zgtask_net_new (const char *name)
{
    zgtask_net_t *self = (zgtask_net_t *) zmalloc (sizeof (zgtask_net_t));
    assert (self);

    //  TODO: Initialize properties
    self->zyre = zyre_new (name);

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the zgtask_net.

void
zgtask_net_destroy (zgtask_net_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgtask_net_t *self = *self_p;

        //  TODO: Free class properties
        zyre_destroy (&self->zyre);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Print properties of the zgtask_net object.

void
zgtask_net_print (zgtask_net_t *self)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_net_test (bool verbose)
{
    printf (" * zgtask_net: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_net_t *self = zgtask_net_new ("zgtask_zyre");
    assert (self);
    zgtask_net_destroy (&self);
    //  @end

    printf ("OK\n");
}
