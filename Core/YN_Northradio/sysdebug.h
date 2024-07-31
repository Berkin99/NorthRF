/**
 *    __  __ ____ _  __ ____ ___ __  __
 *    \ \/ // __// |/ //  _// _ |\ \/ /
 *     \  // _/ /    /_/ / / __ | \  /
 *     /_//___//_/|_//___//_/ |_| /_/
 *
 *         Yeniay System Firmware
 *
 *       Copyright (C) 2024 Yeniay
 *
 * This  program  is  free software:   you
 * can  redistribute it  and/or  modify it
 * under  the  terms of  the  GNU  General
 * Public  License as  published  by   the
 * Free Software Foundation, in version 3.
 *
 * You  should  have  received  a  copy of
 * the  GNU  General  Public License along
 * with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef SYSDEBUG_H_
#define SYSDEBUG_H_

#define SYS_TRUE    (1)
#define SYS_FALSE   (0)

#define SYS_OK             (0)
#define SYS_ERR            (-1)

#define SYS_E_NULL_PTR     (-2)
#define SYS_E_OVERWRITE    (-3)
#define SYS_E_OVERFLOW     (-4)
#define SYS_E_COMM_FAIL    (-5)
#define SYS_E_CONF_FAIL    (-6)
#define SYS_E_NOT_FOUND    (-7)
#define SYS_E_TIMEOUT      (-8)

#define SYS_UNDEFINED		NULL

#endif /* SYSDEBUG_H_ */
