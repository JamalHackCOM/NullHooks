#include "menu.hpp"

auto do_frame = [&](std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, color bg, color header_text, color header_line, const std::string& name) {
	// Background
	render::draw_filled_rect(x, y, w, h, bg);
	// Header title
	render::draw_filled_rect(x, y, w, 30, header_text);
	render::draw_filled_rect(x, y + 30, w, 2, header_line);
	render::draw_text_string(x + 10, y + 8, render::fonts::watermark_font, name, false, color::white(255));
};

void menu::render() {
	if (!variables::menu::opened) return;

	const int top_margin = 30;
	const int container_margin = 5; // empty space between containers
	const int container_padding = 10; // space before and after item list (top and bottom)

	const int container_left_pos = variables::menu::x + container_margin;
	const int container_width = variables::menu::w - container_margin*2;
	const int item_left_pos = container_left_pos + 10;
	const int item_checkbox_pos = variables::menu::x + container_width - container_margin - 10;	// 10 is the checkbox width

	const int part1_y = variables::menu::y + top_margin + container_margin;
	const int part1_items_num = 4;
	const int part1_base_item_y = part1_y + container_padding;				// container pos + margin
	const int part1_h = (15 * part1_items_num) + (container_padding * 2) - 4;	// top and bottom - 4 necesary because of the items mult

	const int part2_y = part1_y + part1_h + container_margin;
	const int part2_items_num = 1;
	const int part2_base_item_y = part2_y + container_padding;
	const int part2_h = (15 * part2_items_num) + (container_padding * 2) - 4;

	const int part3_y = part2_y + part2_h + container_margin;
	const int part3_items_num = 2;
	const int part3_base_item_y = part3_y + container_padding;
	const int part3_h = (15 * part3_items_num) + (container_padding * 2) - 4;

	// Menu title
	do_frame(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h,
		color(36, 36, 36, 255), color(25, 25, 25, 255), color(36, 36, 36, 255), "NullHooks");

	// TODO: Fix top padding
	menu_framework::group_box(container_left_pos, part1_y, container_width, part1_h, render::fonts::watermark_font, "Visuals", false); {
		menu_framework::check_box(item_left_pos, part1_base_item_y + (15 * 0), item_checkbox_pos,
			render::fonts::watermark_font, "Enable team ESP", variables::showteamesp_bool);
		menu_framework::check_box(item_left_pos, part1_base_item_y + (15 * 1), item_checkbox_pos,
			render::fonts::watermark_font, "Box ESP", variables::boxesp_bool);
		menu_framework::check_box(item_left_pos, part1_base_item_y + (15 * 2), item_checkbox_pos,
			render::fonts::watermark_font, "Name ESP", variables::nameesp_bool);
		menu_framework::check_box(item_left_pos, part1_base_item_y + (15 * 3), item_checkbox_pos,
			render::fonts::watermark_font, "No flash", variables::noflash_bool);
	}

	menu_framework::group_box(container_left_pos, part2_y, container_width, part2_h, render::fonts::watermark_font, "Misc", false); {
		menu_framework::check_box(item_left_pos, part2_base_item_y + (15 * 0), item_checkbox_pos,
			render::fonts::watermark_font, "Custom crosshair", variables::crosshair_bool);
	}

	menu_framework::group_box(container_left_pos, part3_y, container_width, part3_h, render::fonts::watermark_font, "Misc", false); {
		menu_framework::check_box(item_left_pos, part3_base_item_y + (15 * 0), item_checkbox_pos,
			render::fonts::watermark_font, "Bhop", variables::bhop_bool);
		menu_framework::check_box(item_left_pos, part3_base_item_y + (15 * 1), item_checkbox_pos,
			render::fonts::watermark_font, "Spectator list", variables::spectator_list_bool);
	}

	const int buttons_con_margin_pos = variables::menu::y + variables::menu::h - container_margin;	// Bottom left corner of container
	const int button_items_num = 1;
	const int button_items_h = (button_items_num * 15) + (container_padding * 2) - 4;
	const int buttons_con_y = buttons_con_margin_pos - button_items_h;	// Get the top left corner based on the margin pos and the height
	const int buttons_items_base_y = buttons_con_y + container_padding;	// Same as other containers
	menu_framework::group_box(container_left_pos, buttons_con_y, container_width, button_items_h, render::fonts::watermark_font, "Misc", false); {
		custom_menu_framework::button(item_left_pos, buttons_items_base_y + (15 * 0), item_checkbox_pos - 20,	// bigger "checkbox" as button
			render::fonts::watermark_font, "Disconnect (Test button)", 1);
	}
	
	menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, 30);
}

void menu::toggle() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		variables::menu::opened = !variables::menu::opened;
}