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
#include	<stringinRecord.h>
#include	<devSymb.h>
#include	<epicsExport.h>

/* Create the dset for devSiSymb */
static long init_record();
static long read_stringin();

struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	read_stringin;
}devSiSymb={
	5,
	NULL,
	NULL,
	init_record,
	NULL,
	read_stringin};
epicsExportAddress( dset, devSiSymb );


static long init_record(pstringin)
    struct stringinRecord	*pstringin;
{
    /* determine address of record value */
    if (devSymbFind(pstringin->name, &pstringin->inp, &pstringin->dpvt))
    {
        recGblRecordError(S_db_badField,(void *)pstringin,
            "devSiSymb (init_record) Illegal NAME or INP field");
        return(S_db_badField);
    }

    return(0);		
}

static long read_stringin(pstringin)
    struct stringinRecord	*pstringin;
{
	int lockKey;
    long status;
    struct vxSym *private = (struct vxSym *) pstringin->dpvt;

    if (private)
    {
        pstringin->val[39] = '\0';
	    lockKey = intLock();
        strncpy(pstringin->val, (char *)(*private->ppvar) + private->index, 39);
        intUnlock(lockKey);
        status = 0;
    }
    else 
        status = 1;

    if(RTN_SUCCESS(status)) pstringin->udf=FALSE;

    return(status);
}
