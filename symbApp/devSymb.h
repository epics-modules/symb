/*************************************************************************\
* Copyright (c) 2002 The University of Chicago, as Operator of Argonne
* National Laboratory.
* Copyright (c) 2002 The Regents of the University of California, as
* Operator of Los Alamos National Laboratory.
* This file is distributed subject to a Software License Agreement found
* in the file LICENSE that is included with this distribution. 
\*************************************************************************/

/* $Id$ */


/* This is the device private structure */

struct vxSym {
    void **ppvar;
    void *pvar;
    long index;
};


/* This is the call to create it */

extern int devSymbFind(char *name, struct link *plink, void *pdpvt);
