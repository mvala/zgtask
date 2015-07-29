/*  =========================================================================
    zgtask_worker - Zgtask worker object

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of CZMQ, the high-level C binding for 0MQ:       
    http://czmq.zeromq.org.                                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef ZGTASK_WORKER_H_INCLUDED
#define ZGTASK_WORKER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


//  @interface
//  Create a new zgtask_worker
ZGTASK_EXPORT zgtask_worker_t *
    zgtask_worker_new (char *name, const char *url_parent);

//  Destroy the zgtask_worker
ZGTASK_EXPORT void
    zgtask_worker_destroy (zgtask_worker_t **self_p);

//  Starts client
ZGTASK_EXPORT void
    zgtask_worker_start (zgtask_worker_t *self);

//  Main loop
ZGTASK_EXPORT void
    zgtask_worker_loop (zgtask_worker_t *self);

//  Stops client
ZGTASK_EXPORT void
    zgtask_worker_stop (zgtask_worker_t *self);

//  Print properties of object
ZGTASK_EXPORT void
    zgtask_worker_print (zgtask_worker_t *self);

//  Self test of this class
ZGTASK_EXPORT void
    zgtask_worker_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
