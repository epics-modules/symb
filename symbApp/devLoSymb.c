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
#include	<module_types.h>
#include	<longoutRecord.h>
#include	<devSymb.h>

static long init_record();
static long write_longout();

/* Create the dset for devLoSymb */

struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	write_longout;
}devLoSymb={
	5,
	NULL,
	NULL,
	init_record,
	NULL,
	write_longout};
 

static long init_record(plongout)
    struct longoutRecord	*plongout;
{
    /* determine address of record value */
    if (devSymbFind(plongout->name, &plongout->out, &plongout->dpvt))
    {
        recGblRecordError(S_db_badField,(void *)plongout,
            "devLoSymb (init_record) Illegal NAME or OUT field");
        return(S_db_badField);
    }

    return(0);		
}

static long write_longout(plongout)
    struct longoutRecord	*plongout;
{
    struct vxSym *private = (struct vxSym *) plongout->dpvt;
	int lockKey;

    if (private)
	{
	   lockKey = intLock();
       *((long *)(*private->ppvar) + private->index) = plongout->val;
	   intUnlock(lockKey);
	}
    else
       return(1);

    plongout->udf=FALSE;

    return(0);
}
