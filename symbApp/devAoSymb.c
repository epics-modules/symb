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
#include	<link.h>
#include	<special.h>
#include	<aoRecord.h>
#include	<devSymb.h>
#include	<epicsExport.h>


/* Create the dset for devAoSymb */
static long init_record();
static long write_ao();
struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	write_ao;
	DEVSUPFUN	special_linconv;
}devAoSymb={
	6,
	NULL,
	NULL,
	init_record,
	NULL,
	write_ao,
	NULL};
epicsExportAddress( dset, devAoSymb );


static long init_record(pao)
    struct aoRecord	*pao;
{
    /* determine address of record value */
    if (devSymbFind(pao->name, &pao->out, &pao->dpvt))
    {
        recGblRecordError(S_db_badField,(void *)pao,
            "devAoSymb (init_record) Illegal NAME or OUT field");
        return(S_db_badField);
    }

    return(2);			/* don't convert */
}

static long write_ao(pao)
    struct aoRecord	*pao;
{
    struct vxSym *private = (struct vxSym *) pao->dpvt;
	int lockKey;

    if (private)
    {
	   lockKey = intLock();
       *((double *)(*private->ppvar) + private->index) = pao->val;
	   intUnlock(lockKey);
    }
    else
       return(1);

    return(0);
}
