#pragma once
#include <boost/uuid/uuid.hpp>
#include "session.h"




struct Player {

	boost::uuids::uuid p_uuid;
	int actual_column;
	int actual_line;
	bool has_food;
	std::shared_ptr<session> _session;
	
};

