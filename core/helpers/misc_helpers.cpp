#include "misc_helpers.hpp"

void custom_helpers::print_to_console(const char* text) {
	if (text == nullptr) return;
	interfaces::console->console_printf(text);
}

void custom_helpers::state_to_console(const char* tag,  const char* text) {
	if (text == nullptr || tag == nullptr) return;
	interfaces::console->console_printf("[NullHooks] [%s] %s\n", tag, text);
}

void custom_helpers::state_to_console_color(const char* tag, const char* text) {
	if (text == nullptr || tag == nullptr) return;
	
	// ???
	interfaces::console->console_color_printf(color::red(255), "[NullHooks] [%s] %s\n", tag, text);
	interfaces::console->console_color_printf(color::blue(255), "[NullHooks] [%s] %s\n", tag, text);
	interfaces::console->console_color_printf(color::green(255), "[NullHooks] [%s] %s\n", tag, text);
}

color custom_helpers::hsv2color(float H, float S, float V) {
    color col;
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    } else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    } else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    } else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    } else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    } else {
        r = C, g = 0, b = X;
    }
    col.r = (r + m) * 255;
    col.g = (g + m) * 255;
    col.b = (b + m) * 255;
    col.a = 255;
    return col;
}

color custom_helpers::hsv2color_v2(float H, float S, float V) {
	float fC = V * S; // Chroma
	float fHPrime = fmod(H / 60.0, 6);
	float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
	float fM = V - fC;

	if (0 <= fHPrime && fHPrime < 1)
		return color(fC*255, fX*255, 0, 255);
	else if (1 <= fHPrime && fHPrime < 2)
		return color(fX*255, fC*255, 0, 255);
	else if (2 <= fHPrime && fHPrime < 3)
		return color(0, fC*255, fX*255, 255);
	else if (3 <= fHPrime && fHPrime < 4)
		return color(0, fX*255, fC*255, 255);
	else if (4 <= fHPrime && fHPrime < 5)
		return color(fX*255, 0, fC*255, 255);
	else if (5 <= fHPrime && fHPrime < 6)
		return color(fC*255, 0, fX*255, 255);
	else
		return color(0, 0, 0);
}

color custom_helpers::float2color(float* id) {
	if (*id < 1.f)				return color(255, 0, 0);
	else if (*id < 2.f)			return color(255, 128, 0);
	else if (*id < 3.f)			return color(255, 255, 0);
	else if (*id < 4.f)			return color(128, 255, 0);
	else if (*id < 5.f)			return color(0, 255, 0);
	else if (*id < 6.f)			return color(0, 255, 128);
	else if (*id < 7.f)			return color(0, 255, 255);
	else if (*id < 8.f)			return color(0, 128, 255);
	else if (*id < 9.f)			return color(0, 0, 255);
	else if (*id < 10.f)		return color(128, 0, 255);
	else if (*id < 11.f)		return color(255, 0, 255);
	else if (*id < 12.f)		return color(255, 0, 128);
	else						*id = 0.f;

	return color(255, 0, 0);
}

void custom_helpers::draw_bomb_text(float time) {
	char exp_time[64];
	sprintf_s(exp_time, "%.2f", time);

	const std::string exp_time_str_base = "Bomb will explode in: ";
	const std::string exp_time_str = std::string(exp_time);
	const std::string total = exp_time_str_base + exp_time_str;
	const std::wstring c_exp_time_str_base = std::wstring(exp_time_str_base.begin(), exp_time_str_base.end());
	const std::wstring c_exp_time_str = std::wstring(exp_time_str.begin(), exp_time_str.end());
	const std::wstring c_total = std::wstring(total.begin(), total.end());

	const color base_color = color(255, 130, 0, 255);
	const color bomb_color_text_color = (time > 10.f) ? color(255, 190, 0, 255) : color::red(255);

	int screen_width, screen_height;
	interfaces::engine->get_screen_size(screen_width, screen_height);

	int width, height;
	interfaces::surface->draw_text_font(render::fonts::watermark_font);
	interfaces::surface->get_text_size(render::fonts::watermark_font, c_total.c_str(), width, height);
	const int x_pos = screen_width / 2 - width / 2;
	const int y_pos = 95;

	interfaces::surface->draw_text_pos(x_pos, y_pos);

	interfaces::surface->set_text_color(base_color.r, base_color.g, base_color.b, base_color.a);
	interfaces::surface->draw_render_text(c_exp_time_str_base.c_str(), wcslen(c_exp_time_str_base.c_str()));

	interfaces::surface->set_text_color(bomb_color_text_color.r, bomb_color_text_color.g, bomb_color_text_color.b, bomb_color_text_color.a);
	interfaces::surface->draw_render_text(c_exp_time_str.c_str(), wcslen(c_exp_time_str.c_str()));
}