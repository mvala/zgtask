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
    zgtask_tree_t *last;
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
    self->last = self->tree;
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
//  Set packet

void
zgtask_client_set_packet (zgtask_client_t *self, zgtask_packet_t *packet)
{
    assert (self);
    assert (packet);
    zhashx_t *data  = zgtask_tree_get_data (self->tree);
    zhashx_insert (data, "packet", packet);
}

//  --------------------------------------------------------------------------
//  Return packet with packet size in json format

char *
zgtask_client_get_packet_json (zgtask_client_t *self, int *id, int size)
{
    assert (self);

    zgtask_packet_t *packet = zgtask_tree_get_packet (self->tree);
    zgtask_packet_t *p = zgtask_packet_get_packet(packet, size);
    if (p) {
        zgtask_tree_t *t_p;
        if (*id)
            t_p = zgtask_tree_add_child (self->last, "%d", (*id)++);
        else
            t_p = zgtask_tree_add_brother (self->last, "%d", (*id)++);
        self->last = t_p;
        zhashx_t *data  = zgtask_tree_get_data (t_p);
        zhashx_insert (data, "packet", p);
        return zgtask_tree_export_json (t_p, 0, 0, 1);
    }
    return 0;
}


//  --------------------------------------------------------------------------
//  Starts client

void
zgtask_client_start (zgtask_client_t *self)
{
    assert (self);
    zyre_t *zyre = zgtask_net_init_zyre_parent (self->net);
    zyre_set_header (zyre, "X-ZGTASK-CLI", "%s", zgtask_tree_get_name (self->tree));
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
    zpoller_t *poller = zpoller_new (zyre_socket (zyre), NULL);
    zyre_event_t *zyre_event = NULL;
    zmsg_t *msg;
    int packet_size = 1;
    int id = 0;
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
        if (which == zyre_socket (zyre)) {
            zyre_event = zyre_event_new (zyre);
            if (!zyre_event)
                break;
//            if (zyre_event_type (zyre_event) == ZYRE_EVENT_ENTER)
//                zyre_event_print (zyre_event);
//            else
//            if (zyre_event_type (zyre_event) == ZYRE_EVENT_EXIT)
//                zyre_event_print (zyre_event);
//            else
//            if (zyre_event_type (zyre_event) == ZYRE_EVENT_SHOUT)
//                zyre_event_print (zyre_event);
//            else
            if (zyre_event_type (zyre_event) == ZYRE_EVENT_WHISPER) {
                zyre_event_print (zyre_event);
                msg = zyre_event_msg (zyre_event);
                //  Retrun code
                int rc = atoi (zmsg_popstr(msg));
                if (rc<0)
                	printf ("This is first packet\n");
                else
                	printf ("rc=%d\n",rc);

                //  Packet size request
                packet_size = atoi (zmsg_popstr(msg));
                char *json_packet = zgtask_client_get_packet_json (self, &id, packet_size);
                if (!json_packet)
                	break;
                msg = zmsg_new ();
                zmsg_addstr (msg, json_packet);
                zyre_whisper (zyre, zyre_event_sender (zyre_event), &msg);
            }
            zyre_event_destroy (&zyre_event);
        }
    }

    zpoller_destroy (&poller);
}

//  --------------------------------------------------------------------------
//  Stops client

void
zgtask_client_stop (zgtask_client_t *self)
{
    assert (self);
//    zyre_t *zyre = zgtask_net_get_zyre_parent (self->net);
//    zyre_stop (zyre);
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
