/*  =========================================================================
    zgtask_client - Zgtask client object

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
    zgtask_client - Zgtask client object
@discuss
@end
*/

#include "../include/zgtask.h"

//  Structure of our class

struct _zgtask_client_t {
    char *name;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_client.

zgtask_client_t *
zgtask_client_new (const char *name)
{
    zgtask_client_t *self = (zgtask_client_t *) zmalloc (sizeof (zgtask_client_t));
    assert (self);

    self->name = strdup(name);
    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the zgtask_client.

void
zgtask_client_destroy (zgtask_client_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgtask_client_t *self = *self_p;

        free (self->name);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Print properties of the zgtask_client object.

void
zgtask_client_print (zgtask_client_t *self)
{
    assert (self);
}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_client_test (bool verbose)
{
    printf (" * zgtask_client: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_client_t *self = zgtask_client_new ("zgtask_client");
    assert (self);
    zgtask_client_destroy (&self);
    //  @end

    printf ("OK\n");
}
