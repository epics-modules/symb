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
#include	<boRecord.h>
#include	<devSymb.h>
#include	<epicsExport.h>

static long init_record();
static long write_bo();

/* Create the dset for devBoSymb */

struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	write_bo;
}devBoSymb={
	5,
	NULL,
	NULL,
	init_record,
	NULL,
	write_bo};
epicsExportAddress( dset, devBoSymb );
 

static long init_record(pbo)
    struct boRecord	*pbo;
{
    /* determine address of record value */
    if (devSymbFind(pbo->name, &pbo->out, &pbo->dpvt))
    {
        recGblRecordError(S_db_badField,(void *)pbo,
            "devBoSymb (init_record) Illegal NAME or OUT field");
        return(S_db_badField);
    }

    return(0);		
}

static long write_bo(pbo)
    struct boRecord	*pbo;
{
    int lockKey;
    struct vxSym *private = (struct vxSym *) pbo->dpvt;

    if (private)
    {
        lockKey = intLock();
        *((unsigned short *)(*private->ppvar) + private->index) = pbo->val;
        intUnlock(lockKey);
    }
    else
        return(1);

    pbo->udf=FALSE;

    return(0);
}
