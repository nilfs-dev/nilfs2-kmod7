/*
 * kern_feature.h - Kernel dependent features
 *
 * Licensed under GPLv2: the complete text of the GNU General Public
 * License can be found in COPYING file of the nilfs-kmod package.
 */

#ifndef NILFS_KERN_FEATURE_H
#define NILFS_KERN_FEATURE_H

#include <linux/version.h>
#ifndef LINUX_VERSION_CODE
# include <generated/uapi/linux/version.h>
#endif

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
#  define	HAVE_INODE_SET_FLAGS		1
# endif
# if (RHEL_MINOR > 4)
#  define	HAVE_ATOMIC_OPS_VARIANTS	1
#  define	HAVE_REFCOUNT_TYPE		1
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
 * mapping->backing_dev_info was removed at Linux 4.0.
 */
#ifndef HAVE_MAPPING_BACKING_DEV_INFO
# define HAVE_MAPPING_BACKING_DEV_INFO \
	(LINUX_VERSION_CODE < KERNEL_VERSION(4, 0, 0))
#endif
/*
 * vm_ops->remap_pages() was introduced in kernel 3.7 and removed in
 * kernel 4.0.
 */
#ifndef HAVE_VM_OPS_REMAP_PAGES
# define HAVE_VM_OPS_REMAP_PAGES \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 7, 0) &&		\
	 LINUX_VERSION_CODE < KERNEL_VERSION(4, 0, 0))
#endif
/*
 * linux-3.17 and later kernels have d_obtain_root().
 */
#ifndef HAVE_D_OBTAIN_ROOT
# define HAVE_D_OBTAIN_ROOT \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0))
#endif
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
 * linux-3.15, later mainline kernels, and some stable kernels have
 * inode_set_flags() and use it to atomically set i_flags.
 */
#ifndef HAVE_INODE_SET_FLAGS
# define HAVE_INODE_SET_FLAGS \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 15, 0) ||		\
	 (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 12, 34) &&		\
	  LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0)))
#endif
/*
 * bi_sector and bi_size were moved into an iterator at linux-3.14.
 */
#ifndef HAVE_BI_ITER
# define HAVE_BI_ITER \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 14, 0))
#endif
/*
 * set_mask_bits() was introduced at linux-3.14.
 */
#ifndef HAVE_SET_MASK_BITS
# define HAVE_SET_MASK_BITS \
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
/*
 * file_inode() accessor was introduced in kernel 3.9
 */
#ifndef HAVE_FILE_INODE
# define HAVE_FILE_INODE \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0))
#endif
/*
 * MODULE_ALIAS_FS() macro was introduced in kernel 3.9
 */
#ifndef HAVE_MODULE_ALIAS_FS
# define HAVE_MODULE_ALIAS_FS \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0))
#endif
/*
 * wait_for_stable_page() was introduced in kernel 3.9
 */
#ifndef HAVE_WAIT_FOR_STABLE_PAGE
# define HAVE_WAIT_FOR_STABLE_PAGE \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0))
#endif
/*
 * FILEID_INVALID was introduced in kernel 3.8
 */
#ifndef HAVE_FILEID_INVALID
# define HAVE_FILEID_INVALID \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
#endif
/*
 * In kernel 3.8, assoc_mapping member of struct address_space was
 * replaced with a void pointer type member "private_data".
 */
#ifndef HAVE_MAPPING_PRIVATE_DATA
# define HAVE_MAPPING_PRIVATE_DATA \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(3, 8, 0))
#endif
/*
 * VM_CAN_NONLINEAR flag was removed in kernel 3.7.0
 */
#ifndef HAVE_VM_CAN_NONLINEAR
# define HAVE_VM_CAN_NONLINEAR \
	(LINUX_VERSION_CODE < KERNEL_VERSION(3, 7, 0))
#endif
/*
 * __block_page_mkwrite() doesn't call file_update_time() since kernel
 * 3.7
 */
#ifndef HAVE_FILE_UPDATE_TIME_IN_BLOCK_PAGE_MKWRITE
# define HAVE_FILE_UPDATE_TIME_IN_BLOCK_PAGE_MKWRITE \
	(LINUX_VERSION_CODE < KERNEL_VERSION(3, 7, 0))
#endif
/*
 * Variants of some atomic operations such as atomic_cmpxchg were
 * added in kernel 4.2.
 */
#ifndef HAVE_ATOMIC_OPS_VARIANTS
# define HAVE_ATOMIC_OPS_VARIANTS \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(4, 2, 0))
#endif
/*
 * The refcount type was introduced in kernel 4.10.
 */
#ifndef HAVE_REFCOUNT_TYPE
# define HAVE_REFCOUNT_TYPE \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(4, 10, 0))
#endif
/*
 * sb_rdonly() was added in kernel 4.13.
 */
#ifndef HAVE_SB_RDONLY
# define HAVE_SB_RDONLY \
	(LINUX_VERSION_CODE >= KERNEL_VERSION(4, 13, 0))
#endif
#endif /* LINUX_VERSION_CODE */


#include <linux/pagemap.h>
#include <linux/fs.h>

/*
 * definitions dependent to above macros
 */
#if !HAVE_SET_MASK_BITS
#define set_mask_bits(ptr, _mask, _bits)	\
({								\
	const typeof(*ptr) mask = (_mask), bits = (_bits);	\
	typeof(*ptr) old, new;					\
								\
	do {							\
		old = ACCESS_ONCE(*ptr);			\
		new = (old & ~mask) | bits;			\
	} while (cmpxchg(ptr, old, new) != old);		\
								\
	new;							\
})
#endif

#if !HAVE_TRUNCATE_INODE_PAGES_FINAL
static inline void truncate_inode_pages_final(struct address_space *mapping)
{
	if (mapping->nrpages)
		truncate_inode_pages(mapping, 0);
}
#endif

#if !HAVE_INODE_SET_FLAGS
static inline void inode_set_flags(struct inode *inode, unsigned int flags,
				   unsigned int mask)
{
	unsigned int old_flags, new_flags;

	WARN_ON_ONCE(flags & ~mask);
	do {
		old_flags = ACCESS_ONCE(inode->i_flags);
		new_flags = (old_flags & ~mask) | flags;
	} while (unlikely(cmpxchg(&inode->i_flags, old_flags,
				  new_flags) != old_flags));
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

#if !HAVE_D_OBTAIN_ROOT
static inline struct dentry *d_obtain_root(struct inode *inode)
{
	return d_obtain_alias(inode);
}
#endif

#if !HAVE_FILE_INODE
static inline struct inode *file_inode(struct file *f)
{
	return f->f_dentry->d_inode;
}
#endif

#if !HAVE_MODULE_ALIAS_FS
# define MODULE_ALIAS_FS(NAME) MODULE_ALIAS("fs-" NAME)
#endif

#if !HAVE_WAIT_FOR_STABLE_PAGE
static inline void wait_for_stable_page(struct page *page)
{
	wait_on_page_writeback(page);
}
#endif

#if !HAVE_FILEID_INVALID
# define FILEID_INVALID	0xff
#endif

#if !HAVE_REFCOUNT_TYPE
#include <linux/atomic.h>
#include <linux/spinlock.h>

#if !HAVE_ATOMIC_OPS_VARIANTS
#include <asm/barrier.h>

#define __atomic_op_release(op, args...)				\
({									\
	smp_mb__before_atomic();					\
	op##_relaxed(args);						\
})

#define __atomic_op_fence(op, args...)					\
({									\
	typeof(op##_relaxed(args)) __ret;				\
	smp_mb__before_atomic();					\
	__ret = op##_relaxed(args);					\
	smp_mb__after_atomic();						\
	__ret;								\
})

#ifndef atomic_cmpxchg_relaxed
#define  atomic_cmpxchg_release			atomic_cmpxchg
#else /* atomic_cmpxchg_relaxed */

#ifndef atomic_cmpxchg_release
#define  atomic_cmpxchg_release(...)					\
	__atomic_op_release(atomic_cmpxchg, __VA_ARGS__)
#endif /* atomic_cmpxchg_release */

#ifndef atomic_cmpxchg
#define  atomic_cmpxchg(...)						\
	__atomic_op_fence(atomic_cmpxchg, __VA_ARGS__)
#endif
#endif /* atomic_cmpxchg_relaxed */
#endif /* !HAVE_ATOMIC_OPS_VARIANTS */

typedef struct refcount_struct {
	atomic_t refs;
} refcount_t;

static inline void refcount_set(refcount_t *r, unsigned int n)
{
	atomic_set(&r->refs, n);
}

static inline void refcount_inc(refcount_t *r)
{
	atomic_inc(&r->refs);
}

static inline __must_check bool refcount_dec_and_test(refcount_t *r)
{
	return atomic_dec_and_test(&r->refs);
}

static inline __must_check bool refcount_dec_not_one(refcount_t *r)
{
	unsigned int old, new, val = atomic_read(&r->refs);

	for (;;) {
		if (unlikely(val == UINT_MAX))
			return true;

		if (val == 1)
			return false;

		new = val - 1;
		if (new > val) {
			WARN_ONCE(new > val, "refcount_t: underflow; use-after-free.\n");
			return true;
		}

		old = atomic_cmpxchg_release(&r->refs, val, new);
		if (old == val)
			break;

		val = old;
	}

	return true;
}

static inline __must_check
bool refcount_dec_and_lock(refcount_t *r, spinlock_t *lock)
{
	if (refcount_dec_not_one(r))
		return false;

	spin_lock(lock);
	if (!refcount_dec_and_test(r)) {
		spin_unlock(lock);
		return false;
	}

	return true;
}
#endif /* !HAVE_REFCOUNT_TYPE */

#if !HAVE_SB_RDONLY
static inline bool sb_rdonly(const struct super_block *sb)
{
	return sb->s_flags & MS_RDONLY;
}
#endif

#endif /* NILFS_KERN_FEATURE_H */
