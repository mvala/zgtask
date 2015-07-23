/*  =========================================================================
    zgtask_task - Task infozgtask

    Copyright (c) the Contributors as noted in the AUTHORS file.
    This file is part of CZMQ, the high-level C binding for 0MQ:
    http://czmq.zeromq.org.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    =========================================================================
*/

#ifndef ZGTASK_TASK_H_INCLUDED
#define ZGTASK_TASK_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


//  @interface
//  Create a new zgtask_task
ZGTASK_EXPORT zgtask_task_t *
zgtask_task_new (char *cmd);

//  Destroy the zgtask_task
ZGTASK_EXPORT void
zgtask_task_destroy (zgtask_task_t **self_p);

//  Gets command
ZGTASK_EXPORT char *
zgtask_task_get_command (zgtask_task_t *self);

//  Gets min and max
ZGTASK_EXPORT void
zgtask_task_get_min_max (zgtask_task_t *self, int *min, int *max);

//  Sets command
ZGTASK_EXPORT void
zgtask_task_set_command (zgtask_task_t *self, char *cmd);

//  Sets min and max
ZGTASK_EXPORT void
zgtask_task_set_min_max (zgtask_task_t *self, int min, int max);

//  Sets status
ZGTASK_EXPORT void
zgtask_task_set_status (zgtask_task_t *self, int status);

//  Sets required time
ZGTASK_EXPORT void
zgtask_task_set_required_time (zgtask_task_t *self, uint t);

//  Adds assigned jobs
ZGTASK_EXPORT void
zgtask_task_add_assigned (zgtask_task_t *self, uint n);

//  Exports task to json
ZGTASK_EXPORT void
zgtask_task_export_json (zgtask_task_t *self, json_t *json);

//  Print properties of object
ZGTASK_EXPORT void
zgtask_task_print (zgtask_task_t *self);

//  Self test of this class
ZGTASK_EXPORT void
zgtask_task_test (bool verbose);
//  @end

#ifdef __cplusplus
}
#endif

#endif
