/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2003-2010 H. Peter Anvin - All Rights Reserved
 *   Copyright 2010 Shao Miller
 *   Copyright 2010 Michal Soltys
 *
 *   Permission is hereby granted, free of charge, to any person
 *   obtaining a copy of this software and associated documentation
 *   files (the "Software"), to deal in the Software without
 *   restriction, including without limitation the rights to use,
 *   copy, modify, merge, publish, distribute, sublicense, and/or
 *   sell copies of the Software, and to permit persons to whom
 *   the Software is furnished to do so, subject to the following
 *   conditions:
 *
 *   The above copyright notice and this permission notice shall
 *   be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 *
 * ----------------------------------------------------------------------- */

/*
 * partiter.h
 *
 * Provides disk / partition iteration.
 */

#ifndef _SYSLINUX_PARTITER_H
#define _SYSLINUX_PARTITER_H

#include <stdint.h>
#include <syslinux/disk.h>

struct itertype;
struct part_iter;

struct itertype {
	int (*ctor)(struct part_iter *, va_list *);
	void (*dtor)(struct part_iter *);
	struct part_iter *(*next) (struct part_iter *);
};

#define PI_GPTLABSIZE ((int)sizeof(((struct disk_gpt_part_entry *)0)->name))

struct part_iter {
    const struct itertype *type;
    char *record;
    uint64_t start_lba;
    int index;
    struct disk_info di;
    /* internal */
    char *data;
    union _sub {
	struct _dos {
	    uint32_t disk_sig;
	    /* internal */
	    uint32_t ebr_start;
	    uint32_t ebr_size;
	    uint32_t bebr_start;
	    uint32_t bebr_size;
	    int index0;
	    int bebr_index0;
	} dos;
	struct _gpt {
	    struct guid disk_guid;
	    struct guid part_guid;
	    char part_label[PI_GPTLABSIZE/2+1];
	    /* internal */
	    int pe_count;
	    int pe_size;
	    int index0;
	} gpt;
    } sub;
};

extern const struct itertype * const typedos;
extern const struct itertype * const typegpt;

struct part_iter *pi_begin(const struct disk_info *);
struct part_iter *pi_new(const struct itertype *, ...);
void *pi_del(struct part_iter **);
struct part_iter *pi_next(struct part_iter **);

#endif

/* vim: set ts=8 sts=4 sw=4 noet: */
