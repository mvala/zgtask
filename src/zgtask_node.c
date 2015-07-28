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
    zgtask_tree_t *tree;
    zgtask_net_t *net;
    char *url_parent;
    char *url_child;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_node.

zgtask_node_t *
zgtask_node_new (char *name, const char *url_parent, const char *url_child)
{
    zgtask_node_t *self = (zgtask_node_t *) zmalloc (sizeof (zgtask_node_t));
    assert (self);

    self->tree = zgtask_tree_new (name, 0);
    self->net = zgtask_tree_add_net (self->tree, "%s_net", name);
    self->url_parent = strdup (url_parent);
    self->url_child = strdup (url_child);

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

        zgtask_tree_destroy (&self->tree);
        free (self->url_parent);
        free (self->url_child);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Starts node

void
zgtask_node_start (zgtask_node_t *self)
{
    assert (self);
    zgtask_tree_print (self->tree);
    zyre_t *zyre_parent = zgtask_net_init_zyre_parent (self->net);
    zyre_gossip_bind (zyre_parent, self->url_parent);
    zyre_start (zyre_parent);
    zyre_join (zyre_parent, "GLOBAL");

    zyre_t *zyre_child = zgtask_net_init_zyre_child (self->net);
    zyre_gossip_connect (zyre_child, self->url_child);
    zyre_start (zyre_child);
    zyre_join (zyre_child, "GLOBAL");

}

//  --------------------------------------------------------------------------
//  Main loop

void
zgtask_node_loop (zgtask_node_t *self)
{
    assert (self);

    zyre_t *zyre_parent = zgtask_net_get_zyre_parent (self->net);
    zyre_t *zyre_child = zgtask_net_get_zyre_child (self->net);

    zpoller_t *poller = zpoller_new (zyre_socket (zyre_parent), zyre_socket (
                                         zyre_child),  NULL);

    zyre_event_t *zyre_event = NULL;

    int nparent = 0;
    int nchild = 0;
    int timeout = -1;
    while (!zsys_interrupted) {
        void *which = zpoller_wait (poller, timeout);
        if (zpoller_terminated (poller)) {
            printf ("\nPoller terminated\n");
            break;
        }
        else
        if (zpoller_expired (poller)) {
            printf ("Poller expired\n");
            continue;
        }
        else
        if (which == zyre_socket (zyre_parent)) {
            zyre_event = zyre_event_new (zyre_parent);
            if (!zyre_event)
                break;
            if (zyre_event_type (zyre_event) == ZYRE_EVENT_SHOUT) {
                nparent++;
//                zyre_event_print (zyre_event);
                zmsg_t *msg = zmsg_dup (zyre_event_msg (zyre_event));
                zlist_t *l = zyre_peers (zyre_child);
                char *peer = (char *) zlist_first (l);
                printf ("\rnparent=%d whispers=%d peers=%ld", nparent, nchild, zlist_size (
                            l));
                fflush (stdout);
                if (peer)
                    zyre_whisper (zyre_child, peer, &msg);
            }
            else
            if (zyre_event_type (zyre_event) == ZYRE_EVENT_WHISPER) {
                nchild++;
                printf ("\rnparent=%d nchild=%d", nparent, nchild);
                fflush (stdout);
//                zyre_event_print (zyre_event);
            }
            zyre_event_destroy (&zyre_event);
        }
        else
        if (which == zyre_socket (zyre_child)) {
            zyre_event = zyre_event_new (zyre_child);
            if (!zyre_event)
                break;
            zyre_event_destroy (&zyre_event);
        }



    }

    zpoller_destroy (&poller);

}

//  --------------------------------------------------------------------------
//  Stops node

void
zgtask_node_stop (zgtask_node_t *self)
{
    assert (self);

//    zyre_t *zyre_child = zgtask_net_get_zyre_child (self->net);
//    zyre_leave (zyre_child, "GLOBAL");
//    zyre_stop (zyre_child);

//    zyre_t *zyre_parent = zgtask_net_get_zyre_parent (self->net);
//    zyre_leave (zyre_parent, "GLOBAL");
//    zyre_stop (zyre_parent);
//

}

//  --------------------------------------------------------------------------
//  Print properties of the zgtask_node object.

void
zgtask_node_print (zgtask_node_t *self)
{
    assert (self);
    zyre_t *zyre_parent = zgtask_net_get_zyre_parent (self->net);
    if (zyre_parent)
        zyre_print (zyre_parent);

    zclock_sleep(10);

    zyre_t *zyre_child = zgtask_net_get_zyre_child (self->net);
    if (zyre_child)
        zyre_print (zyre_child);


}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_node_test (bool verbose)
{
    printf (" * zgtask_node: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_node_t *self = zgtask_node_new ("zgtask_node", "inproc://parent",
                                           "inproc://child");
    assert (self);
    zgtask_node_destroy (&self);
    //  @end

    printf ("OK\n");
}
