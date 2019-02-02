/*
 * AUTHOR : Tony Olsson
 * DATE   : 1991-01-10/tools@whoozle
 * CREATED: 1990-06-13
 * 
 * SoftLab ab (c) 1990
 *
 * $Header: /Repository/ToolMaker/src/smk/name.h,v 1.1 2002/06/25 20:04:45 Thomas Nilsson Exp $
 *
 * $Log: name.h,v $
 * Revision 1.1  2002/06/25 20:04:45  Thomas Nilsson
 * Initial version of ToolMaker source import
 *
 * Revision 1.1  1993/03/24 09:24:15  tools
 * Ursprunglig version av smk testsvit
 *
 * Revision 1.2  1991/12/11  13:00:32  tools
 * Not modified
 *
 * Revision 1.1  91/01/10  12:23:06  tools
 * Initial revision
 * 
 *
 */

#ifndef _NAME_H_
#define _NAME_H_

typedef char *Name, NameItem;

extern Name nameSearch();
extern void nameRemove();
#endif
