//
//  object.h
//  drawinglib
//
//  Created by Rodrigo on 11/27/19.
//

#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
	int obj_id = -1;
	Object() = default;
	Object(int id) : obj_id(id) {}
	virtual ~Object() = default;
	virtual void draw() = 0;
	int get_id() { return obj_id; }
};

#endif /* OBJECT_H */
