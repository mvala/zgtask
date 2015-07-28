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

#ifndef ZGTASK_CLIENT_H_INCLUDED
#define ZGTASK_CLIENT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


//  @interface
//  Create a new zgtask_client
ZGTASK_EXPORT zgtask_client_t *
    zgtask_client_new (const char *name);

//  Destroy the zgtask_client
ZGTASK_EXPORT void
    zgtask_client_destroy (zgtask_client_t **self_p);

//  Print properties of object
ZGTASK_EXPORT void
    zgtask_client_print (zgtask_client_t *self);

//  Self test of this class
ZGTASK_EXPORT void
    zgtask_client_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
