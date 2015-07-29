/*  =========================================================================
    zgtask_redirector - Zgtask node object

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
//  Create a new zgtask_redirector
ZGTASK_EXPORT zgtask_redirector_t *
    zgtask_redirector_new (char *name, const char *url_parent, const char *url_child);

//  Destroy the zgtask_redirector
ZGTASK_EXPORT void
    zgtask_redirector_destroy (zgtask_redirector_t **self_p);

//  Starts node
ZGTASK_EXPORT void
    zgtask_redirector_start (zgtask_redirector_t *self);

//  Main loop
ZGTASK_EXPORT void
    zgtask_redirector_loop (zgtask_redirector_t *self);

//  Stops node
ZGTASK_EXPORT void
    zgtask_redirector_stop (zgtask_redirector_t *self);

//  Print properties of object
ZGTASK_EXPORT void
    zgtask_redirector_print (zgtask_redirector_t *self);

//  Self test of this class
ZGTASK_EXPORT void
    zgtask_redirector_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
