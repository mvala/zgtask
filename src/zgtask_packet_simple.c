/*  =========================================================================
    zgtask_packet_simple - Zgtask packet simple with min and max value

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
    zgtask_packet_simple - Zgtask packet simple with min and max value
@discuss
@end
*/

#include "../include/zgtask.h"

//  Structure of our class

struct _zgtask_packet_simple_t {
    uint min;
    uint max;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_packet_simple.

zgtask_packet_simple_t *
zgtask_packet_simple_new ()
{
    zgtask_packet_simple_t *self =
        (zgtask_packet_simple_t *) zmalloc (sizeof (zgtask_packet_simple_t));
    assert (self);

    self->min = 0;
    self->max = 0;

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the zgtask_packet_simple.

void
zgtask_packet_simple_destroy (zgtask_packet_simple_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgtask_packet_simple_t *self = *self_p;

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Set min value

void
zgtask_packet_simple_set_min (zgtask_packet_simple_t *self, uint min)
{
    assert (self);
    self->min = min;
}

//  Set max value
//  --------------------------------------------------------------------------

void
zgtask_packet_simple_set_max (zgtask_packet_simple_t *self, uint max)
{
    assert (self);
    self->max = max;
}

//  --------------------------------------------------------------------------
//  Print properties of the zgtask_packet_simple object.

void
zgtask_packet_simple_print (zgtask_packet_simple_t *self)
{
    assert (self);
    zsys_info ("packet_simple min=%ld max=%ld", self->min, self->max);
}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_packet_simple_test (bool verbose)
{
    printf (" * zgtask_packet_simple: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_packet_simple_t *self = zgtask_packet_simple_new ();
    assert (self);
    zgtask_packet_simple_destroy (&self);
    //  @end

    printf ("OK\n");
}
