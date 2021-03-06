/*************************************************************************\
* Copyright (c) 2002 The University of Chicago, as Operator of Argonne
* National Laboratory.
* Copyright (c) 2002 The Regents of the University of California, as
* Operator of Los Alamos National Laboratory.
* This file is distributed subject to a Software License Agreement found
* in the file LICENSE that is included with this distribution. 
\*************************************************************************/

/* $Id$ */

#include	<vxWorks.h>
#include	<sysSymTbl.h>
#include	<types.h>
#include	<stdioLib.h>
#include	<string.h>
#include	<intLib.h>

#include	<alarm.h>
#include	<dbDefs.h>
#include	<dbAccess.h>
#include	<recSup.h>
#include	<recGbl.h>
#include	<devSup.h>
#include	<mbbiRecord.h>
#include	<devSymb.h>
#include	<epicsExport.h>

/* Create the dset for devMbbiSymb */
static long init_record();
static long read_mbbi();

struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	read_mbbi;
}devMbbiSymb={
	5,
	NULL,
	NULL,
	init_record,
	NULL,
	read_mbbi};
epicsExportAddress( dset, devMbbiSymb );


static long init_record(pmbbi)
    struct mbbiRecord	*pmbbi;
{
    /* determine address of record value */
    if (devSymbFind(pmbbi->name, &pmbbi->inp, &pmbbi->dpvt))
    {
        recGblRecordError(S_db_badField,(void *)pmbbi,
            "devMbbiSymb (init_record) Illegal NAME or INP field");
        return(S_db_badField);
    }

    return(0);		
}

static long read_mbbi(pmbbi)
    struct mbbiRecord	*pmbbi;
{
    int lockKey;
    long status;
    struct vxSym *private = (struct vxSym *) pmbbi->dpvt;

    if (pmbbi->dpvt)
    {
        lockKey = intLock();
        pmbbi->val = *((long *)(*private->ppvar) + private->index);
        intUnlock(lockKey);
        status = 0;
    }
    else
        status = 1;

    if(RTN_SUCCESS(status)) pmbbi->udf=FALSE;

    return(2); /*don't convert*/
}
