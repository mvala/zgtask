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

#ifndef ZGTASK_NET_H_INCLUDED
#define ZGTASK_NET_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


//  @interface
//  Create a new zgtask_net
ZGTASK_EXPORT zgtask_net_t *
    zgtask_net_new (const char *name);

//  Destroy the zgtask_net
ZGTASK_EXPORT void
    zgtask_net_destroy (zgtask_net_t **self_p);

//  Init zyre parent object
ZGTASK_EXPORT zyre_t *
    zgtask_net_init_zyre_parent (zgtask_net_t *self);

//  Init zyre child object
ZGTASK_EXPORT zyre_t *
    zgtask_net_init_zyre_child (zgtask_net_t *self);

//  Return zyre parent object
ZGTASK_EXPORT zyre_t *
    zgtask_net_get_zyre_parent (zgtask_net_t *self);

//  Return zyre child object
ZGTASK_EXPORT zyre_t *
    zgtask_net_get_zyre_child (zgtask_net_t *self);

//  Print properties of object
ZGTASK_EXPORT void
    zgtask_net_print (zgtask_net_t *self);

//  Self test of this class
ZGTASK_EXPORT void
    zgtask_net_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
