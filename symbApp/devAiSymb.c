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
#include 	<sysSymTbl.h>
#include	<types.h>
#include	<stdioLib.h>
#include	<string.h>
#include	<intLib.h>

#include	<alarm.h>
#include	<cvtTable.h>
#include	<dbDefs.h>
#include	<dbAccess.h>
#include	<recSup.h>
#include	<recGbl.h>
#include	<devSup.h>
#include	<link.h>
#include	<aiRecord.h>
#include	<devSymb.h>

/* Create the dset for devAiSymb */
static long init_record();
static long read_ai();
struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	read_ai;
	DEVSUPFUN	special_linconv;
}devAiSymb={
	6,
	NULL,
	NULL,
	init_record,
	NULL,
	read_ai,
	NULL};


static long init_record(pai)
    struct aiRecord	*pai;
{
    /* determine address of record value */
    if (devSymbFind(pai->name, &pai->inp, &pai->dpvt))
    {
	recGblRecordError(S_db_badField,(void *)pai,
	    "devAiSymb (init_record) Illegal NAME or INP field");
	return(S_db_badField);
    }

    pai->linr=0;		/* prevent any conversions */
    return(0);
}

static long read_ai(pai)
    struct aiRecord	*pai;
{
    long status;
    struct vxSym *private = (struct vxSym *) pai->dpvt;
	int lockKey;

    if (private)
    {
	   lockKey = intLock();
       pai->val = *((double *)(*private->ppvar) + private->index);
	   intUnlock(lockKey);
       status = 0;
    }
    else
       status = 1;
       
    if(RTN_SUCCESS(status)) pai->udf=FALSE;

    return(2); /*don't convert*/
}
