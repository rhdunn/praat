/* Network_enums.h
 *
 * Copyright (C) 2012 Paul Boersma
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


enums_begin (kNetwork_weightUpdateRule, 0)
	enums_add (kNetwork_weightUpdateRule, 0, HEBBIAN, L"Hebbian")
	enums_add (kNetwork_weightUpdateRule, 1, INSTAR, L"instar")
	enums_add (kNetwork_weightUpdateRule, 2, OUTSTAR, L"outstar")
	enums_add (kNetwork_weightUpdateRule, 3, INOUTSTAR, L"inoutstar")
enums_end (kNetwork_weightUpdateRule, 3, HEBBIAN)


/* End of file Network_enums.h */
