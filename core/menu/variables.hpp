#pragma once

namespace variables {
	
	// Legitbot
	inline bool aimbot_bool = false;
	inline float aimbot_fov = 0.f;
	inline float aimbot_smoothing = 2.f;
	inline bool aimbot_isvisiblecheck = true;

	// Visuals
	inline bool showteamesp_bool = false;
	inline bool boxesp_bool = false;
	inline bool nameesp_bool = false;
	
	inline bool noflash_bool  = true;

	// Misc
	inline bool bhop_bool = true;
	inline bool crosshair_bool = false;
	inline bool spectator_list_bool = true;

	namespace crosshair {
		const inline bool only_engine_crosshair = true;		// Edit here
		inline bool using_cs_crosshair = true;

		inline int crosshair_w = 4;
		inline int crosshair_len = 5;
		inline int crosshair_gap = 1;
	};

	namespace menu {
		inline bool opened = false;
		inline int x = 300, y = 200;
		inline int w = 300, h = 250;
	};

	namespace watermark {
		inline int y = 10;
		inline int x = 15;
	};
}