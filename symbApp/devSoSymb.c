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
#include	<stringoutRecord.h>
#include	<devSymb.h>
#include	<epicsExport.h>

static long init_record();
static long write_stringout();

/* Create the dset for devSoSymb */

struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	write_stringout;
}devSoSymb={
	5,
	NULL,
	NULL,
	init_record,
	NULL,
	write_stringout};
epicsExportAddress( dset, devSoSymb );
 

static long init_record(pstringout)
    struct stringoutRecord	*pstringout;
{
    /* determine address of record value */
    if (devSymbFind(pstringout->name, &pstringout->out, &pstringout->dpvt))
    {
        recGblRecordError(S_db_badField,(void *)pstringout,
            "devSoSymb (init_record) Illegal NAME or OUT field");
        return(S_db_badField);
    }

    return(0);
}

static long write_stringout(pstringout)
    struct stringoutRecord	*pstringout;
{
	int lockKey;
    struct vxSym *private = (struct vxSym *) pstringout->dpvt;

    if (private)
    {
        pstringout->val[39] = '\0';
	    lockKey = intLock();
        strcpy((char *)(*private->ppvar) + private->index, pstringout->val);
        intUnlock(lockKey);
    }
    else 
        return(1);

    pstringout->udf = FALSE;

    return(0);
}
