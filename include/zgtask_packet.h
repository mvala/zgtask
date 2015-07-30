/*  =========================================================================
    zgtask_packet - Zgtask packet simple with min and max value

    Copyright (c) the Contributors as noted in the AUTHORS file.       
    This file is part of CZMQ, the high-level C binding for 0MQ:       
    http://czmq.zeromq.org.                                            
                                                                       
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.           
    =========================================================================
*/

#ifndef ZGTASK_PACKET_SIMPLE_H_INCLUDED
#define ZGTASK_PACKET_SIMPLE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


//  @interface
//  Create a new zgtask_packet
ZGTASK_EXPORT zgtask_packet_t *
    zgtask_packet_new (void);

//  Destroy the zgtask_packet
ZGTASK_EXPORT void
    zgtask_packet_destroy (zgtask_packet_t **self_p);

//  Gets packet with packet size
ZGTASK_EXPORT zgtask_packet_t *
    zgtask_packet_get_packet (zgtask_packet_t *self, uint size);

//  Set min value
ZGTASK_EXPORT void
    zgtask_packet_set_min (zgtask_packet_t *self, uint min);

//  Set max value
ZGTASK_EXPORT void
    zgtask_packet_set_max (zgtask_packet_t *self, uint max);

//  Inports packet to json
ZGTASK_EXPORT void
    zgtask_packet_import_json (zgtask_packet_t *self, json_t *json);

//  Exports packet to json
ZGTASK_EXPORT void
    zgtask_packet_export_json (zgtask_packet_t *self, json_t *json);

//  Print properties of object
ZGTASK_EXPORT void
    zgtask_packet_print (zgtask_packet_t *self);

//  Self test of this class
ZGTASK_EXPORT void
    zgtask_packet_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
