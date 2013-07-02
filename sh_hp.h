#ifndef SH_HP_H
#define SH_HP_H

// helper
#include "prefix.h"

// 1: exist & not delete
// -1: not exist & not add
// 0: optional & not modify
// -2: not exist & add
// +2: exist & delete
// -3: optional & delete
// +3: optional & add
// tp: template
inline bool sh_hp_match(image_type const& old_img, image_type& new_img, int x, int y, double const* tp, int tp_w, int tp_h)
{
	bool is_matched = true;
	int k = 0;
	for (k = 0; k < (tp_w * tp_h); ++k)
	{
		if (0 == tp[k] || 3 == tp[k] || -3 == tp[k]) continue;
		if ((old_img.at(x + k % tp_w, y + k / tp_w).is_black()? 1 : -1) != tp[k]
			&& (old_img.at(x + k % tp_w, y + k / tp_w).is_black()? 2 : -2) != tp[k])
		{
			is_matched = false;
			break;
		}
	}
	if (is_matched)
	{
		for (k = 0; k < (tp_w * tp_h); ++k)
		{
			if (tp[k] == -2 || tp[k] == +3) new_img.at(x + k % tp_w, y + k / tp_w).is_black(true);
			if (tp[k] == +2 || tp[k] == -3) new_img.at(x + k % tp_w, y + k / tp_w).is_black(false);
		}
	}

	return is_matched;
}

#endif // SH_HP_H
