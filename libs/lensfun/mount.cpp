/*
    Private constructors and destructors
    Copyright (C) 2007 by Andrew Zabolotny
*/

#include "config.h"
#include "lensfun.h"
#include "lensfunprv.h"

lfMount::lfMount ()
{
    Name = NULL;
    Compat = NULL;
}

lfMount::~lfMount ()
{
    lf_free (Name);
    _lf_list_free ((void **)Compat);
}

lfMount::lfMount (const lfMount &other)
{
    Name = lf_mlstr_dup (other.Name);
    Compat = NULL;
    if (other.Compat)
        for (int i = 0; other.Compat [i]; i++)
                AddCompat (other.Compat [i]);
}

lfMount &lfMount::operator = (const lfMount &other)
{
    lf_free (Name);
    Name = lf_mlstr_dup (other.Name);
    lf_free (Compat); Compat = NULL;
    if (other.Compat)
        for (int i = 0; other.Compat [i]; i++)
                AddCompat (other.Compat [i]);

    return *this;
}

bool lfMount::operator == (const lfMount& other)
{
    return _lf_strcmp (Name, other.Name) == 0;
}

void lfMount::SetName (const char *val, const char *lang)
{
    Name = lf_mlstr_add (Name, lang, val);
}

void lfMount::AddCompat (const char *val)
{
    _lf_addstr (&Compat, val);
}

bool lfMount::Check ()
{
    if (!Name)
        return false;

    return true;
}


//---------------------------// The C interface //---------------------------//

lfMount *lf_mount_new ()
{
    return new lfMount ();
}

void lf_mount_destroy (lfMount *mount)
{
    delete mount;
}

cbool lf_mount_check (lfMount *mount)
{
    return mount->Check ();
}
