/*
 * kern_feature.h - Kernel dependent features
 *
 * Licensed under GPLv2: the complete text of the GNU General Public
 * License can be found in COPYING file of the nilfs-kmod package.
 */

#ifndef NILFS_KERN_FEATURE_H
#define NILFS_KERN_FEATURE_H

#include <linux/version.h>

/*
 * Please define as 0/1 here if you want to override
 */

/*
 * for Red Hat Enterprise Linux 7.x (and clones like CentOS or SL)
 */
#if defined(RHEL_MAJOR) && (RHEL_MAJOR == 7)
#  define	HAVE_TRUNCATE_INODE_PAGES_FINAL	1
#  define	HAVE_D_COUNT			1
#endif

/*
 * defaults
 */

/*
 * defaults dependent to kernel versions
 */
#ifdef LINUX_VERSION_CODE
/*
 * linux-3.15 and later kernels have truncate_inode_pages_final()
 * and use it in ->evict_inode() implementation.
 */
#ifndef HAVE_TRUNCATE_INODE_PAGES_FINAL
# define HAVE_TRUNCATE_INODE_PAGES_FINAL \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0))
#endif
/*
 * linux-3.11 and later kernels have d_count() function and use it to
 * get refcount of dentry.
 */
#ifndef HAVE_D_COUNT
# define HAVE_D_COUNT \
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

#if !HAVE_D_COUNT
static inline unsigned d_count(const struct dentry *dentry)
{
	return dentry->d_count;
}
#endif

#endif /* NILFS_KERN_FEATURE_H */