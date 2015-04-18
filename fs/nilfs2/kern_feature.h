/*
 * kern_feature.h - Kernel dependent features
 *
 * Licensed under GPLv2: the complete text of the GNU General Public
 * License can be found in COPYING file of the nilfs-kmod package.
 */

#ifndef NILFS_KERN_FEATURE_H
#define NILFS_KERN_FEATURE_H

#include <generated/uapi/linux/version.h>

/*
 * Please define as 0/1 here if you want to override
 */

/*
 * for Red Hat Enterprise Linux 7.x (and clones like CentOS or SL)
 */
#if defined(RHEL_MAJOR) && (RHEL_MAJOR == 7)
#  define	HAVE_TRUNCATE_INODE_PAGES_FINAL	1
#  define	HAVE_D_COUNT			1
# if (RHEL_MINOR > 0)
#  define	HAVE_NEW_TRUNCATE_PAGECACHE	1
# endif
#endif

/*
 * defaults
 */

/*
 * defaults dependent to kernel versions
 */
#ifdef LINUX_VERSION_CODE
/*
 * linux-3.16 and later kernels have iov_iter.
 */
#ifndef HAVE_IOV_ITER
# define HAVE_IOV_ITER \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 16, 0))
#endif
/*
 * linux-3.15 and later kernels have truncate_inode_pages_final()
 * and use it in ->evict_inode() implementation.
 */
#ifndef HAVE_TRUNCATE_INODE_PAGES_FINAL
# define HAVE_TRUNCATE_INODE_PAGES_FINAL \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0))
#endif
/*
 * bi_sector and bi_size were moved into an iterator at linux-3.14.
 */
#ifndef HAVE_BI_ITER
# define HAVE_BI_ITER \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 14, 0))
#endif
/*
 * oldsize argument of truncate_pagecache() was dropped at linux-3.12.
 */
#ifndef HAVE_NEW_TRUNCATE_PAGECACHE
# define HAVE_NEW_TRUNCATE_PAGECACHE \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 12, 0))
#endif
/*
 * linux-3.11 and later kernels have d_count() function and use it to
 * get refcount of dentry.
 */
#ifndef HAVE_D_COUNT
# define HAVE_D_COUNT \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 11, 0))
#endif
/*
 * linux-3.11 altered readdir() implementation.
 */
#ifndef HAVE_NEW_READDIR
# define HAVE_NEW_READDIR \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 11, 0))
#endif
#endif /* LINUX_VERSION_CODE */


#include <linux/fs.h>

/*
 * definitions dependent to above macros
 */
#if !HAVE_TRUNCATE_INODE_PAGES_FINAL
static inline void truncate_inode_pages_final(struct address_space *mapping)
{
	if (mapping->nrpages)
		truncate_inode_pages(mapping, 0);
}
#endif

static inline void
nilfs_truncate_pagecache(struct inode *inode, loff_t oldsize, loff_t newsize)
{
#if HAVE_NEW_TRUNCATE_PAGECACHE
	truncate_pagecache(inode, newsize);
#else
	truncate_pagecache(inode, oldsize, newsize);
#endif
}

#if !HAVE_D_COUNT
static inline unsigned d_count(const struct dentry *dentry)
{
	return dentry->d_count;
}
#endif

#endif /* NILFS_KERN_FEATURE_H */
