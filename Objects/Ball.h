#pragma once
#include "Object.h"
#include "../Events/EventGenerator.h"
#include "../Input/Key.h"
#include "../Display/Display.h"
#include "../Objects/Object.h"
#include <vector>

class Ball : public Object, public EventGenerator
{
private:

	typedef std::vector<std::shared_ptr<Object>> Coll_obj_vec;

	Coll_obj_vec collision_objects;

public:


	Ball(std::shared_ptr<Display> display_ptr, int x, int y);
	virtual ~Ball();

	virtual void draw();

	virtual void button_pressed(Key k);
	virtual void button_released(Key k);

	virtual void update_position();

	virtual void add_collision_obj(std::shared_ptr<Object> object);

	void reset_position();

};

