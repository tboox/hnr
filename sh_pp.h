#ifndef SH_PP_H
#define SH_PP_H

#include "prefix.h"
#include "sh_hp.h"
#include "sh_oh.h"
#include "sh_gy.h"
#include "sh_th.h"
#include "sh_cs.h"
#include "sh_rl.h"
#include "sh_dn.h"
#include "sh_zm.h"
#include "sh_dk.h"
#include "sh_tn.h"
#include "sh_ed.h"
#include "sh_sc.h"
#include "sh_fx.h"

// image pre-processing
inline image_type sh_pp_preprocess(image_type const& old_img, bool is_online, pimages_info_row_type* ppir = NULL)
{
	// copy
	image_type img(old_img);

	// image binarization
	if (is_online)
	{
		img = sh_th_global_basic_threshold(img);
		img = sh_oh_trim(img);
	}
	else img = sh_th_partial_otsu_threshold(img);

	// adjust image size for better processing
	//img = sh_dn_discrete_denoising(img);
	//img = sh_dn_discrete_denoising(img);

#ifdef USING_THINNING
	// thinning image
	img = sh_tn_thinning(img);		// need improve
#endif

	// split image
	pimages_info_row_type pir = sh_rl_labeling_split_to_row(img, !is_online);

	// deskew iamges
	sh_oh_deskew_from_pimgs_info_row(pir);

	// fixes images
	sh_oh_fixes_from_pimgs_info_row(pir);		// need improve

	// trim margin
	sh_oh_trim_from_pimgs_info_row(pir);

	// fill margin for 1
	sh_oh_fill_margin_for_1_from_pimgs_info_row(pir, IMAGE_W, IMAGE_H);

	// normalize images
	if (is_online) sh_oh_normalize_from_pimgs_info_row(pir, IMAGE_W, IMAGE_H);		// need improve
	else sh_oh_normalize2_from_pimgs_info_row(pir, IMAGE_W, IMAGE_H);

	// fixes images
	sh_oh_fixes_from_pimgs_info_row(pir);		// need improve

#ifdef USING_THINNING
	// images thinning
	sh_oh_thinning_from_pimgs_info_row(pir);
#endif

	// merge images
	img = sh_oh_merge_from_pimgs_info_row(pir);

	// return images info
	if (ppir) *ppir = pir;

	return img;
}
#endif // SH_PP_H
