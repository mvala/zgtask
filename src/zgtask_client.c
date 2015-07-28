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
    zgtask_tree_t *tree;
    zgtask_net_t *net;
    char *url_parent;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_client.

zgtask_client_t *
zgtask_client_new (char *name, const char *url_parent)
{
    zgtask_client_t *self = (zgtask_client_t *) zmalloc (sizeof (zgtask_client_t));
    assert (self);

    self->tree = zgtask_tree_new (name, 0);
    self->net = zgtask_tree_add_net (self->tree, "%s_net", name);
    self->url_parent = strdup (url_parent);
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

        zgtask_tree_destroy (&self->tree);
        free (self->url_parent);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Starts client

void
zgtask_client_start (zgtask_client_t *self)
{
    assert (self);
    zyre_t *zyre = zgtask_net_init_zyre_parent (self->net);
    zyre_gossip_connect (zyre, self->url_parent);
    zyre_start (zyre);
    zyre_join (zyre, "GLOBAL");

    zclock_sleep (250);
}

//  --------------------------------------------------------------------------
//  Main loop

void
zgtask_client_loop (zgtask_client_t *self)
{
    assert (self);
    zyre_t *zyre = zgtask_net_get_zyre_parent (self->net);
    zmsg_t *msg;
    int j;
    for (j = 0; j < 10; ++j) {
        msg = zmsg_new ();
        zmsg_addstr (msg, "Hello world");
        zyre_shout (zyre, "GLOBAL", &msg);
    }
}

//  --------------------------------------------------------------------------
//  Stops client

void
zgtask_client_stop (zgtask_client_t *self)
{
    assert (self);
    zyre_t *zyre = zgtask_net_get_zyre_parent (self->net);
    zyre_stop (zyre);
}

//  --------------------------------------------------------------------------
//  Print properties of the zgtask_client object.

void
zgtask_client_print (zgtask_client_t *self)
{
    assert (self);
    zyre_t *zyre = zgtask_net_init_zyre_parent (self->net);
    zyre_print (zyre);
}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_client_test (bool verbose)
{
    printf (" * zgtask_client: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_client_t *self = zgtask_client_new ("zgtask_client", "inproc://parent");
    assert (self);
    zgtask_client_destroy (&self);
    //  @end

    printf ("OK\n");
}
