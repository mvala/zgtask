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
    zyre_t *parent;
    zyre_t *child;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_net.

zgtask_net_t *
zgtask_net_new (const char *name)
{
    zgtask_net_t *self = (zgtask_net_t *) zmalloc (sizeof (zgtask_net_t));
    assert (self);

    self->parent = NULL;
    self->child = NULL;

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

        //  Cleaning parent
        if (self->parent) {
            zyre_stop (self->parent);
            zyre_destroy (&self->parent);
        }

        //  Cleaning child
        if (self->child) {
            zyre_stop (self->child);
            zyre_destroy (&self->child);

        }
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Init zyre parent object

zyre_t *
zgtask_net_init_zyre_parent (zgtask_net_t *self)
{
    assert (self);
    if (!self->parent)
        self->parent = zyre_new ("parent");
    return self->parent;
}

//  --------------------------------------------------------------------------
//  Init zyre child object

zyre_t *
zgtask_net_init_zyre_child (zgtask_net_t *self)
{
    assert (self);
    if (!self->child)
        self->child = zyre_new ("child");
    return self->child;
}


//  --------------------------------------------------------------------------
//  Return zyre parent object

zyre_t *
zgtask_net_get_zyre_parent (zgtask_net_t *self)
{
    assert (self);
    return self->parent;
}

//  --------------------------------------------------------------------------
//  Return zyre child object

zyre_t *
zgtask_net_get_zyre_child (zgtask_net_t *self)
{
    assert (self);
    return self->child;
}

//  --------------------------------------------------------------------------
//  Print properties of the zgtask_net object.

void
zgtask_net_print (zgtask_net_t *self)
{
    assert (self);
    if (self->parent)
        zyre_print (self->parent);
    if (self->child)
        zyre_print (self->child);
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
