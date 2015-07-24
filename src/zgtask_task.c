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

/*
@header
    zgtask_task - Task infozgtask
@discuss
@end
*/

#include "../include/zgtask.h"

//  Structure of our class

struct _zgtask_task_t {
    char *command;
    int min;
    int max;
    int status;
    uint required_time;
    uint n_assigned;
    uint n_done;
    uint n_failed;
};


//  --------------------------------------------------------------------------
//  Create a new zgtask_task.

zgtask_task_t *
zgtask_task_new (char *cmd)
{
    zgtask_task_t *self = (zgtask_task_t *) zmalloc (sizeof (zgtask_task_t));
    assert (self);

    // Initialize properties
    self->command = strdup (cmd);
    self->min = -1;
    self->max = -1;
    self->status = -1;
    self->required_time = 0;
    self->n_assigned = 0;
    self->n_done = 0;
    self->n_failed = 0;

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the zgtask_task.

void
zgtask_task_destroy (zgtask_task_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgtask_task_t *self = *self_p;

        // Free class properties
        free (self->command);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Gets command

char *
zgtask_task_get_command (zgtask_task_t *self)
{
    assert (self);
    return self->command;
}


//  --------------------------------------------------------------------------
//  Gets min and max

void
zgtask_task_get_min_max (zgtask_task_t *self, int *min, int *max)
{
    assert (self);
    *min =  self->min;
    *max =  self->max;
}

//  --------------------------------------------------------------------------
//  Sets command
void
zgtask_task_set_command (zgtask_task_t *self, char *cmd)
{
    assert (self);

    free (self->command);
    self->command = strdup (cmd);
}

//  --------------------------------------------------------------------------
//  Sets min and max

void
zgtask_task_set_min_max (zgtask_task_t *self, int min, int max)
{
    assert (self);
    self->min = min;
    self->max = max;
    self->n_assigned = max-min+1;
}

//  --------------------------------------------------------------------------
//  Sets status

void
zgtask_task_set_status (zgtask_task_t *self, int status)
{
    assert (self);
    if (self->n_assigned == 1) self->status = status;
    if (status)
        self->n_failed++;
    else
        self->n_done++;
}


//  --------------------------------------------------------------------------
//  Sets required time

void
zgtask_task_set_required_time (zgtask_task_t *self, uint t)
{
    assert (self);
    self->required_time = t;
}

//  --------------------------------------------------------------------------
//  Sets assigned

void
zgtask_task_set_assigned (zgtask_task_t *self, uint n)
{
    assert (self);
    self->n_assigned = n;
}

//  --------------------------------------------------------------------------
//  Sets done

void
zgtask_task_set_done (zgtask_task_t *self, uint n)
{
    assert (self);
    self->n_done = n;
}

//  --------------------------------------------------------------------------
//  Sets assigned

void
zgtask_task_set_failed (zgtask_task_t *self, uint n)
{
    assert (self);
    self->n_failed = n;
}

//  --------------------------------------------------------------------------
//  Adds assigned jobs

void
zgtask_task_add_assigned (zgtask_task_t *self, uint n)
{
    assert (self);
    self->n_assigned += n;
}

//  --------------------------------------------------------------------------
//  Exports task to json

//  --------------------------------------------------------------------------
//  Adds done jobs

void
zgtask_task_add_done (zgtask_task_t *self, uint n)
{
    assert (self);
    self->n_done += n;
}

//  --------------------------------------------------------------------------
//  Adds failed jobs

void
zgtask_task_add_failed (zgtask_task_t *self, uint n)
{
    assert (self);
    self->n_failed += n;
}

//  --------------------------------------------------------------------------
//  Inports task to json

void
zgtask_task_import_json (zgtask_task_t *self, json_t *json)
{
    assert (self);
    assert (json);

    json_t *js_tmp, *js_tmp2;

    json_t *js_task =  json_object_get (json, "task");
    if (!json_is_object (js_task)) {
        fprintf (stderr, "error: task is not a object\n");
        json_decref (json);
        return;
    }


    js_tmp = json_object_get (js_task, "cmd");
    zgtask_task_set_command (self, (char*)json_string_value (js_tmp));
    js_tmp = json_object_get (js_task, "status");
    zgtask_task_set_status (self,  json_integer_value (js_tmp));
    js_tmp = json_object_get (js_task, "min");
    js_tmp2 = json_object_get (js_task, "max");
    zgtask_task_set_min_max (self,  json_integer_value (js_tmp),
                             json_integer_value (js_tmp2));
    js_tmp = json_object_get (js_task, "assigned");
    zgtask_task_set_assigned (self,  json_integer_value (js_tmp));
    js_tmp = json_object_get (js_task, "done");
    zgtask_task_set_done (self,  json_integer_value (js_tmp));
    js_tmp = json_object_get (js_task, "failed");
    zgtask_task_set_failed (self,  json_integer_value (js_tmp));
}

//  --------------------------------------------------------------------------
//  Exports task to json

void
zgtask_task_export_json (zgtask_task_t *self, json_t *json)
{
    assert (self);
    assert (json);

    json_object_set_new (json, "cmd", json_string (self->command));
    json_object_set_new (json, "min", json_integer (self->min));
    json_object_set_new (json, "max", json_integer (self->max));
    json_object_set_new (json, "status", json_integer (self->status));
    json_object_set_new (json, "assigned", json_integer (self->n_assigned));
    json_object_set_new (json, "done", json_integer (self->n_done));
    json_object_set_new (json, "failed", json_integer (self->n_failed));
}

//  --------------------------------------------------------------------------
//  Print properties of the zgtask_task object.

void
zgtask_task_print (zgtask_task_t *self)
{
    assert (self);

    printf ("cmd='%s' min=%d max=%d A=%d D=%d F=%d status=%d time=%d\n",
            self->command, self->min, self->max, self->n_assigned,
            self->n_done, self->n_failed, self->status, self->required_time);

}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_task_test (bool verbose)
{
    printf (" * zgtask_task: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_task_t *self = zgtask_task_new ("t");
    assert (self);
    zgtask_task_destroy (&self);
    //  @end

    printf ("OK\n");
}
