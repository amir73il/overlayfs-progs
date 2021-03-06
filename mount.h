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

#ifndef OVL_MOUNT_H
#define OVL_MOUNT_H

struct ovl_config {
	char *lowerdir;
	char *upperdir;
	char *workdir;
};

void ovl_parse_opt(char *opt, struct ovl_config *config);
void ovl_free_opt(struct ovl_config *config);
int ovl_get_dirs(struct ovl_config *config, char ***lowerdir,
		 int *lowernum, char **upperdir, char **workdir);
int ovl_check_mount(struct ovl_fs *ofs, bool *mounted);

#endif /* OVL_MOUNT_H */
