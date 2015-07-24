/*  =========================================================================
    zgtask_tree - Tree object for zgtask

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
    zgtask_tree - Tree object for zgtask
@discuss
@end
*/

#include "../include/zgtask.h"

//  Structure of our class

struct _zgtask_tree_t {
    char *name;
    zgtask_task_t *task;
    zgtask_tree_t *parent;
    zgtask_tree_t *child;
    zgtask_tree_t *brother;

};


//  --------------------------------------------------------------------------
//  Create a new zgtask_tree.

zgtask_tree_t *
zgtask_tree_new (char *name, zgtask_tree_t *parent)
{
    zgtask_tree_t *self = (zgtask_tree_t *) zmalloc (sizeof (zgtask_tree_t));
    assert (self);

    // Initialize properties
    self->name = strdup (name);
    self->task = zgtask_task_new ("");
    self->parent = parent;
    self->child = 0;
    self->brother = 0;

    return self;
}

//  --------------------------------------------------------------------------
//  Destroy the zgtask_tree.

void
zgtask_tree_destroy (zgtask_tree_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        zgtask_tree_t *self = *self_p;

        // Free class properties
        free (self->name);
        zgtask_task_destroy (&self->task);
        zgtask_tree_destroy (&self->child);
        zgtask_tree_destroy (&self->brother);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

//  --------------------------------------------------------------------------
//  Search for tree

zgtask_tree_t *
zgtask_tree_lookup (zgtask_tree_t *self, char *name)
{
    if (!self)
        return 0;
    if (!self->child && !self->brother)
        return 0;

    if (self->child)
        if (strcmp (zgtask_tree_get_name (self->child), name) == 0)
            return self->child;
    if (self->brother)
        if (strcmp (zgtask_tree_get_name (self->brother), name) == 0)
            return self->brother;
    zgtask_tree_t *t;
    t = zgtask_tree_lookup (self->child, name);
    if (t)
        return t;
    t = zgtask_tree_lookup (self->brother, name);
    if (t)
        return t;

    return 0;
}

//  --------------------------------------------------------------------------
//  Returns name

char *
zgtask_tree_get_name (zgtask_tree_t *self)
{
    assert (self);
    return self->name;
}


//  --------------------------------------------------------------------------
//  Return task object

zgtask_task_t *
zgtask_tree_get_task (zgtask_tree_t *self)
{
    return self->task;
}

//  --------------------------------------------------------------------------
//  Return child

zgtask_tree_t *
zgtask_tree_get_child (zgtask_tree_t *self)
{
    if (!self) return 0;
    return self->child;
}

//  --------------------------------------------------------------------------
//  Return brother

zgtask_tree_t *
zgtask_tree_get_brother (zgtask_tree_t *self)
{
    if (!self) return 0;
    return self->brother;
}

//  --------------------------------------------------------------------------
//  Returns parent

zgtask_tree_t *
zgtask_tree_get_parent (zgtask_tree_t *self)
{
    if (!self) return 0;
    return self->parent;
}

//  --------------------------------------------------------------------------
//  Add child

zgtask_tree_t *
zgtask_tree_add_child (zgtask_tree_t *self,  const char *format, ...)
{
    assert (self);
    assert (format);

    va_list argptr;
    va_start (argptr, format);
    char *name = zsys_vprintf (format, argptr);
    if (!name)
        return 0;

    va_end (argptr);

    if (!self->child)
        self->child = zgtask_tree_new (name, self);

    return self->child;
}

//  --------------------------------------------------------------------------
//  Add brother

zgtask_tree_t *
zgtask_tree_add_brother (zgtask_tree_t *self,  const char *format, ...)
{
    assert (self);
    assert (format);

    va_list argptr;
    va_start (argptr, format);
    char *name = zsys_vprintf (format, argptr);
    if (!name)
        return 0;

    va_end (argptr);

    if (!self->brother)
        self->brother = zgtask_tree_new (name, zgtask_tree_get_parent (self));

    return self->brother;
}

//  --------------------------------------------------------------------------
//  Sets subtree status

int
zgtask_tree_set_status_subtree (zgtask_tree_t *self, char *name, int status)
{
    assert (self);

    zgtask_tree_t *t = zgtask_tree_lookup (self, name);
    if (!t) return -1;

    //  Sets status to tree with name
    zgtask_task_t *task = zgtask_tree_get_task (t);
    zgtask_task_set_status (task, status);

    //  Sets status to current tree also
    zgtask_tree_t *p = zgtask_tree_get_parent (t);
    while (p) {
        task = zgtask_tree_get_task (p);
        zgtask_task_set_status (task, status);
        p = zgtask_tree_get_parent (p);
    }
    return 0;
}

//  --------------------------------------------------------------------------
//  Generates subjobs

int
zgtask_tree_generate (zgtask_tree_t *self, int min, int max)
{
    assert (self);

    uint n = 0;
    zgtask_task_t *task = zgtask_tree_get_task (self);
    zgtask_tree_t *t = zgtask_tree_add_child (self, "t%d", min);
    zgtask_task_t *subtask = zgtask_tree_get_task (t);
    zgtask_task_set_command (subtask, zgtask_task_get_command (task));
    zgtask_task_set_min_max (subtask, min, min);
    n++;

    int i;
    for (i = min+1; i <= max; i++) {
        t = zgtask_tree_add_brother (t, "t%d", i);
        zgtask_task_t *subtask = zgtask_tree_get_task (t);
        zgtask_task_set_command (subtask, zgtask_task_get_command (task));
        zgtask_task_set_min_max (subtask, i, i);
        n++;
    }

    //  Sets status to current tree also
    zgtask_tree_t *p = zgtask_tree_get_parent (t);
    while (p) {
        task = zgtask_tree_get_task (p);
        zgtask_task_add_assigned (task, n);
        p = zgtask_tree_get_parent (p);
    }
    return n;
}

//  --------------------------------------------------------------------------
//  Import json to tree
int
zgtask_tree_import_json (zgtask_tree_t *self, json_t *json)
{
    assert (self);
    assert (json);

    zgtask_tree_t *tree = self;
    json_t *js_data;
    json_t *js_name;
    json_t *array = json_object_get (json, "array");
    uint i;
    for (i = 0; i < json_array_size (array); i++)
    {

        js_data = json_array_get (array, i);
        if (!json_is_object (js_data)) {
            fprintf (stderr, "error: commit data %d is not an object\n", i + 1);
            json_decref (json);
            return 1;
        }
        js_name =  json_object_get (js_data, "name");
        if (!json_is_string (js_name)) {
            fprintf (stderr, "error: commit %d: name is not a string\n", i + 1);
            json_decref (json);
            return 1;
        }
        if (!i)
            tree = zgtask_tree_add_child (tree, json_string_value (js_name));
        else tree = zgtask_tree_add_brother (tree, json_string_value (js_name));
        zgtask_task_import_json (zgtask_tree_get_task (tree), js_data);

        zgtask_tree_import_json (tree, js_data);

    }
    return 0;
}

//  --------------------------------------------------------------------------
//  Export tree to json
char *
zgtask_tree_export_json (zgtask_tree_t *self, char *path, json_t *json)
{
    assert (self);
    if (!json)
        json = json_object ();
    assert (json);

    json_t *array = NULL;
    json_t *obj_array = json_object ();
    if (!json_is_array (json)) {
        array = json_array ();
        json_object_set (json, "array", array);
    }
    else
        array = json;
    json_array_append (array, obj_array);


    json_object_set (obj_array, "name", json_string (self->name));
    json_t *obj_task = json_object ();
    json_object_set (obj_array, "task", obj_task);
    zgtask_task_t *task = zgtask_tree_get_task (self);
    zgtask_task_export_json (task, obj_task);

    if (self->brother)
        zgtask_tree_export_json (self->brother, 0, array);

    if (self->child)
        zgtask_tree_export_json (self->child, 0, obj_array);

    if (self->parent)
        return 0;

    if (path)
        json_dump_file (json, path, JSON_COMPACT);
    return json_dumps (json, JSON_STRICT);
}

//  --------------------------------------------------------------------------
//  Print properties of the zgtask_tree object.

void
zgtask_tree_print (zgtask_tree_t *self)
{
    assert (self);

    zgtask_tree_t *p = self->parent;
    while (p) {
        if (p) printf (" ");
        p = (zgtask_tree_t *) zgtask_tree_get_parent (p);
    }
    printf ("name=%s ", self->name);
    zgtask_task_print (self->task);
    if (self->child) zgtask_tree_print (self->child);
    if (self->brother) zgtask_tree_print (self->brother);
}


//  --------------------------------------------------------------------------
//  Self test of this class.

void
zgtask_tree_test (bool verbose)
{
    printf (" * zgtask_tree: ");

    //  @selftest
    //  Simple create/destroy test
    zgtask_tree_t *self = zgtask_tree_new ("t1", 0);
    assert (self);
    zgtask_tree_destroy (&self);
    //  @end

    printf ("OK\n");
}
