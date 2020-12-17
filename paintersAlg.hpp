//
//  paintersAlg.hpp
//  drawinglib
//
//  Created by Rodrigo on 11/28/19.
//

#ifndef PAINTERS_ALG
#define PAINTERS_ALG

#include <vector>

#include "global.hpp"

using r_iter = std::vector<polygon_t>::reverse_iterator;

/* Check if there is overlap between two polygons */
bool depth_overlap(polygon_t& Oi, polygon_t& Sk);

/* Test Case #1
** Test whether the bounding rectangles in the xy direction overlap
*/

 bool xy_overlap(polygon_t& Oi, polygon_t& Sk);

/* Test Case #2
** Test whether a polygon is completely behind another
*/ 
bool behind(polygon_t& Oi, polygon_t& Sk);

/* Test Case #3
** Test whether a polygon is completely in front of another
*/
bool front(polygon_t& Oi, polygon_t& Sk);

/* Test case #4
**
*/
bool boundary_edge(polygon_t& Oi, polygon_t& Sk);

/* Test the overlapping polygons against test cases */
bool test_all(std::vector<r_iter>& O, r_iter Sk);

/* Sort polygons by increasing minimum z-value
** Starting from the last polygon Sk, find the subset of polygons O1,...,Om that have depth overlap with Sk
** Test Oi against 4 test cases: xy_overlap(S,S`) --> behind(S,S`)  --> front(S,S`) --> boundary_edge(S,S`)
*/
void painters_alg(std::vector<polygon_t>& polygon_list);

#endif /* PAINTERSALG_HPP */