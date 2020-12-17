//
//  shading.hpp
//  drawinglib
//
//  Created by Rodrigo on 12/3/19.
//

#ifndef SHADING_HPP
#define SHADING_HPP

void flat_shading(Geometry::Polygon *p);

void gouraud_shading(Geometry::Polygon* p);

void phong_lighting(Geometry::Polygon* p);

#endif /* shading_hpp */