/*
 * Copyright (c) 2017 Huawei.  All Rights Reserved.
 * Author: zhangyi (F) <yi.zhang@huawei.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write the Free Software Foundation,
 * Inc.,  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OVL_LIB_H
#define OVL_LIB_H

/* Scan layer flag */
#define FS_LAYER_RO	(1 << 0)	/* layer is read-only */
#define FS_LAYER_XATTR	(1 << 1)	/* layer support xattr */

/* Option flags */
#define FL_UPPER	(0x10000000)	/* specify upper layer */
#define FL_OPT_AUTO	(0x20000000)	/* automactically scan dirs and repair */
#define FL_OPT_NO	(0x40000000)	/* no changes to the filesystem */
#define FL_OPT_YES	(0x80000000)	/* yes to all questions */
#define FL_OPT_MASK	(FL_OPT_AUTO|FL_OPT_NO|FL_OPT_YES)


/* Directories scan data structs */
struct scan_dir_data {
       int origins;		/* origin number in this directory (no iterate) */
       int mergedirs;		/* merge subdir number in this directory (no iterate) */
       int redirects;		/* redirect subdir number in this directory (no iterate) */
};

struct scan_result {
	int files;		/* total files */
	int directories;	/* total directories */
	int t_whiteouts;	/* total whiteouts */
	int i_whiteouts;	/* invalid whiteouts */
	int t_redirects;	/* total redirect dirs */
	int i_redirects;	/* invalid redirect dirs */
	int m_impure;		/* missing inpure dirs */
};

struct scan_ctx {
	struct ovl_fs *ofs;		/* scan ovl fs */
	struct ovl_layer *layer;	/* scan layer */
	struct scan_result result;	/* scan count result */

	const char *pathname;	/* path relative to overlay root */
	const char *filename;	/* filename */
	struct stat *st;	/* file stat */
	struct scan_dir_data *dirdata;	/* parent dir data of current (could be null) */
};

/* Directories scan callback operations struct */
struct scan_operations {
	int (*whiteout)(struct scan_ctx *);
	int (*redirect)(struct scan_ctx *);
	int (*origin)(struct scan_ctx *);
	int (*impurity)(struct scan_ctx *);
	int (*impure)(struct scan_ctx *);
};

/* Whiteout */
#define WHITEOUT_DEV	0
#define WHITEOUT_MOD	0

static inline mode_t file_type(const struct stat *status)
{
	return status->st_mode & S_IFMT;
}

static inline bool is_whiteout(const struct stat *status)
{
	return (file_type(status) == S_IFCHR) && (status->st_rdev == WHITEOUT_DEV);
}

static inline bool is_dir(const struct stat *status)
{
	return file_type(status) == S_IFDIR;
}

int scan_dir(struct scan_ctx *sctx, struct scan_operations *sop);
int ask_question(const char *question, int def);
ssize_t get_xattr(int dirfd, const char *pathname, const char *xattrname,
		  char **value, bool *exist);
int set_xattr(int dirfd, const char *pathname, const char *xattrname,
	      void *value, size_t size);
int remove_xattr(int dirfd, const char *pathname, const char *xattrname);

#endif /* OVL_LIB_H */
