/*
 * This file contains the functions and defines necessary to modify and
 * use the SuperH page table tree.
 *
 * Copyright (C) 1999 Niibe Yutaka
 * Copyright (C) 2002 - 2007 Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the main directory of this
 * archive for more details.
 */
#ifndef __ASM_SH_PGTABLE_H
#define __ASM_SH_PGTABLE_H

#include <asm-generic/pgtable-nopmd.h>
#include <asm/page.h>

#ifndef __ASSEMBLY__
#include <asm/addrspace.h>
#include <asm/fixmap.h>

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * for zero-mapped memory areas etc..
 */
extern unsigned long empty_zero_page[PAGE_SIZE / sizeof(unsigned long)];
#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

#endif /* !__ASSEMBLY__ */

/*
 * Effective and physical address definitions, to aid with sign
 * extension.
 */
#define NEFF		32
#define	NEFF_SIGN	(1LL << (NEFF - 1))
#define	NEFF_MASK	(-1LL << NEFF)

#ifdef CONFIG_29BIT
#define NPHYS		29
#else
#define NPHYS		32
#endif

#define	NPHYS_SIGN	(1LL << (NPHYS - 1))
#define	NPHYS_MASK	(-1LL << NPHYS)

/*
 * traditional two-level paging structure
 */
/* PTE bits */
#if defined(CONFIG_X2TLB) || defined(CONFIG_SUPERH64)
# define PTE_MAGNITUDE	3	/* 64-bit PTEs on extended mode SH-X2 TLB */
#else
# define PTE_MAGNITUDE	2	/* 32-bit PTEs */
#endif
#define PTE_SHIFT	PAGE_SHIFT
#define PTE_BITS	(PTE_SHIFT - PTE_MAGNITUDE)

/* PGD bits */
#define PGDIR_SHIFT	(PTE_SHIFT + PTE_BITS)
#define PGDIR_SIZE	(1UL << PGDIR_SHIFT)
#define PGDIR_MASK	(~(PGDIR_SIZE-1))

/* Entries per level */
#define PTRS_PER_PTE	(PAGE_SIZE / (1 << PTE_MAGNITUDE))
#define PTRS_PER_PGD	(PAGE_SIZE / sizeof(pgd_t))

#define USER_PTRS_PER_PGD	(TASK_SIZE/PGDIR_SIZE)
#define FIRST_USER_ADDRESS	0

#ifdef CONFIG_32BIT
#define PHYS_ADDR_MASK		0xffffffff
#else
#define PHYS_ADDR_MASK		0x1fffffff
#endif

#define PTE_PHYS_MASK		(PHYS_ADDR_MASK & PAGE_MASK)

#ifdef CONFIG_SUPERH32
#define VMALLOC_START	(P3SEG)
#else
#define VMALLOC_START	(0xf0000000)
#endif
#define VMALLOC_END	(FIXADDR_START-2*PAGE_SIZE)

#if defined(CONFIG_SUPERH32)
#include <asm/pgtable_32.h>
#else
#include <asm/pgtable_64.h>
#endif

/*
 * SH-X and lower (legacy) SuperH parts (SH-3, SH-4, some SH-4A) can't do page
 * protection for execute, and considers it the same as a read. Also, write
 * permission implies read permission. This is the closest we can get..
 *
 * SH-X2 (SH7785) and later parts take this to the opposite end of the extreme,
 * not only supporting separate execute, read, and write bits, but having
 * completely separate permission bits for user and kernel space.
 */
	 /*xwr*/
#define __P000	PAGE_NONE
#define __P001	PAGE_READONLY
#define __P010	PAGE_COPY
#define __P011	PAGE_COPY
#define __P100	PAGE_EXECREAD
#define __P101	PAGE_EXECREAD
#define __P110	PAGE_COPY
#define __P111	PAGE_COPY

#define __S000	PAGE_NONE
#define __S001	PAGE_READONLY
#define __S010	PAGE_WRITEONLY
#define __S011	PAGE_SHARED
#define __S100	PAGE_EXECREAD
#define __S101	PAGE_EXECREAD
#define __S110	PAGE_RWX
#define __S111	PAGE_RWX

typedef pte_t *pte_addr_t;

#define kern_addr_valid(addr)	(1)

#define io_remap_pfn_range(vma, vaddr, pfn, size, prot)		\
		remap_pfn_range(vma, vaddr, pfn, size, prot)

#define pte_pfn(x)		((unsigned long)(((x).pte_low >> PAGE_SHIFT)))

/*
 * No page table caches to initialise
 */
#define pgtable_cache_init()	do { } while (0)

#if !defined(CONFIG_CACHE_OFF) && (defined(CONFIG_CPU_SH4) || \
	defined(CONFIG_SH7705_CACHE_32KB))
struct mm_struct;
#define __HAVE_ARCH_PTEP_GET_AND_CLEAR
pte_t ptep_get_and_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep);
#endif

struct vm_area_struct;
extern void update_mmu_cache(struct vm_area_struct * vma,
			     unsigned long address, pte_t pte);
extern pgd_t swapper_pg_dir[PTRS_PER_PGD];
extern void paging_init(void);
extern void page_table_range_init(unsigned long start, unsigned long end,
				  pgd_t *pgd);

#include <asm-generic/pgtable.h>

#endif /* __ASM_SH_PGTABLE_H */
