/*
 * Copyright (c) 2017, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */
#ifndef SHARE_VM_OOPS_VALUEKLASS_INLINE_HPP
#define SHARE_VM_OOPS_VALUEKLASS_INLINE_HPP

#include "memory/memRegion.hpp"
#include "memory/iterator.inline.hpp"
#include "oops/klass.hpp"
#include "oops/valueArrayKlass.hpp"
#include "oops/oop.inline.hpp"
#include "oops/valueKlass.hpp"
#include "utilities/macros.hpp"

template <bool nv, typename T, class OopClosureType>
void ValueKlass::oop_iterate_specialized(const address oop_addr, OopClosureType* closure) {
  OopMapBlock* map = start_of_nonstatic_oop_maps();
  OopMapBlock* const end_map = map + nonstatic_oop_map_count();

  for (; map < end_map; map++) {
    T* p = (T*) (oop_addr + map->offset());
    T* const end = p + map->count();
    for (; p < end; ++p) {
      Devirtualizer<nv>::do_oop(closure, p);
    }
  }
}

template <bool nv, typename T, class OopClosureType>
inline void ValueKlass::oop_iterate_specialized_bounded(const address oop_addr, OopClosureType* closure, void* lo, void* hi) {
  OopMapBlock* map = start_of_nonstatic_oop_maps();
  OopMapBlock* const end_map = map + nonstatic_oop_map_count();

  T* const l   = (T*) lo;
  T* const h   = (T*) hi;

  for (; map < end_map; map++) {
    T* p = (T*) (oop_addr + map->offset());
    T* end = p + map->count();
    if (p < l) {
      p = l;
    }
    if (end > h) {
      end = h;
    }
    for (; p < end; ++p) {
      Devirtualizer<nv>::do_oop(closure, p);
    }
  }
}


#endif // SHARE_VM_OOPS_VALUEKLASS_INLINE_HPP
