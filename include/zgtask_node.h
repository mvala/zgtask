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

#ifndef ZGTASK_NODE_H_INCLUDED
#define ZGTASK_NODE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


//  @interface
//  Create a new zgtask_node
ZGTASK_EXPORT zgtask_node_t *
    zgtask_node_new (const char *name);

//  Destroy the zgtask_node
ZGTASK_EXPORT void
    zgtask_node_destroy (zgtask_node_t **self_p);

//  Print properties of object
ZGTASK_EXPORT void
    zgtask_node_print (zgtask_node_t *self);

//  Self test of this class
ZGTASK_EXPORT void
    zgtask_node_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
