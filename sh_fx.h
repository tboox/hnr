#ifndef SH_FX_H
#define SH_FX_H

// fixes image after thinning & deskw & normarlization
inline image_type sh_fx_fixes(image_type const& old_img, int max_n = 2)
{
	// delete
	double k1[9] =	{	1, -1, -1
					,	1, 2, -1
					,	1, -1, -1
					};

	double k2[9] =	{	1, 1, 1
					,	-1, 2, -1
					,	-1, -1, -1
					};

	double k3[9] =	{	-1, -1, 1
					,	-1, 2, 1
					,	-1, -1, 1
					};

	double k4[9] =	{	-1, -1, -1
					,	-1, 2, -1
					,	1, 1, 1
					};

	double k5[9] =	{	1, -1, 2
					,	-1, 1, -1
					,	-1, -1, 1
					};

	double k6[9] =	{	1, -1, -1
					,	-1, 1, -1
					,	2, -1, -1
					};

	double k7[9] =	{	2, -1, 1
					,	-1, 1, -1
					,	1, -1, -1
					};

	double k8[9] =	{	-1, -1, 1
					,	-1, 1, -1
					,	1, -1, 2
					};

	// add
	double k9[9] =	{	1, 1, 1
					,	1, -2, 1
					,	-1, -1, -1
					};

	double k10[9] =	{	-1, 1, 1
					,	-1, -2, 1
					,	-1, 1, 1
					};

	double k11[9] =	{	-1, -1, -1
					,	1, -2, 1
					,	1, 1, 1
					};

	double k12[9] =	{	1, 1, -1
					,	1, -2, -1
					,	1, 1, -1
					};

	/*double k13[9] =	{	1, 1, 1
					,	1, -2, -1
					,	1, -1, -1
					};

	double k14[9] =	{	1, 1, 1
					,	-1, -2, 1
					,	-1, -1, 1
					};

	double k15[9] =	{	1, -1, -1
					,	1, -2, -1
					,	1, 1, 1
					};

	double k16[9] =	{	-1, -1, 1
					,	-1, -2, 1
					,	1, 1, 1
					};*/

	int kn = 3;
	image_type new_img(old_img);
	image_type tmp(new_img);
	while (max_n--)
	{
		int matched_n = 0;
		bool is_matched_k1, is_matched_k2, is_matched_k3, is_matched_k4;
		bool is_matched_k5, is_matched_k6, is_matched_k7, is_matched_k8;
		bool is_matched_k9, is_matched_k10, is_matched_k11, is_matched_k12;
		//bool is_matched_k13, is_matched_k14, is_matched_k15, is_matched_k16;
		for (int py = 0; py < tmp.height() - kn; ++py)
		{
			for (int px = 0; px < tmp.width() - kn; ++px)
			{
				is_matched_k1 = sh_hp_match(tmp, new_img, px, py, k1, 3, 3);
				is_matched_k2 = sh_hp_match(tmp, new_img, px, py, k2, 3, 3);
				is_matched_k3 = sh_hp_match(tmp, new_img, px, py, k3, 3, 3);
				is_matched_k4 = sh_hp_match(tmp, new_img, px, py, k4, 3, 3);
				is_matched_k5 = sh_hp_match(tmp, new_img, px, py, k5, 3, 3);
				is_matched_k6 = sh_hp_match(tmp, new_img, px, py, k6, 3, 3);
				is_matched_k7 = sh_hp_match(tmp, new_img, px, py, k7, 3, 3);
				is_matched_k8 = sh_hp_match(tmp, new_img, px, py, k8, 3, 3);
				is_matched_k9 = sh_hp_match(tmp, new_img, px, py, k9, 3, 3);
				is_matched_k10 = sh_hp_match(tmp, new_img, px, py, k10, 3, 3);
				is_matched_k11 = sh_hp_match(tmp, new_img, px, py, k11, 3, 3);
				is_matched_k12 = sh_hp_match(tmp, new_img, px, py, k12, 3, 3);
				/*is_matched_k13 = sh_hp_match(tmp, new_img, px, py, k13, 3, 3);
				is_matched_k14 = sh_hp_match(tmp, new_img, px, py, k14, 3, 3);
				is_matched_k15 = sh_hp_match(tmp, new_img, px, py, k15, 3, 3);
				is_matched_k16 = sh_hp_match(tmp, new_img, px, py, k16, 3, 3);*/

				if (	is_matched_k1
					||	is_matched_k2
					||	is_matched_k3
					||	is_matched_k4
					||	is_matched_k5
					||	is_matched_k6
					||	is_matched_k7
					||	is_matched_k8
					||	is_matched_k9
					||	is_matched_k10
					||	is_matched_k11
					||	is_matched_k12
					/*||	is_matched_k13
					||	is_matched_k14
					||	is_matched_k15
					||	is_matched_k16*/
					)
				{
					matched_n++;
				}
			}
		}

		if (matched_n <= 0) break;
		else tmp = new_img;
	}
	return new_img;
}
inline image_type sh_fx_roughening(image_type const& old_img, int max_n = 1)
{
	// delete
	double k1[9] =	{	1, 0, -1
					,	1, -2, -1
					,	1, 0, -1
					};

	double k2[9] =	{	1, 1, 1
					,	0, -2, 0
					,	-1, -1, -1
					};

	double k3[9] =	{	-1, 0, 1
					,	-1, -2, 1
					,	-1, 0, 1
					};

	double k4[9] =	{	-1, -1, -1
					,	0, -2, 0
					,	1, 1, 1
					};

	double k5[9] =	{	1, 1, 0
					,	1, -2, -1
					,	0, -1, -1
					};

	double k6[9] =	{	0, 1, 1
					,	-1, -2, 1
					,	-1, -1, 0
					};

	double k7[9] =	{	-1, -1, 0
					,	-1, -2, 1
					,	0, 1, 1
					};

	double k8[9] =	{	0, -1, -1
					,	1, -2, -1
					,	1, 1, 0
					};

	// add
	/*double k9[9] =	{	1, 1, 1
					,	1, -2, 1
					,	-1, -1, -1
					};

	double k10[9] =	{	-1, 1, 1
					,	-1, -2, 1
					,	-1, 1, 1
					};

	double k11[9] =	{	-1, -1, -1
					,	1, -2, 1
					,	1, 1, 1
					};

	double k12[9] =	{	1, 1, -1
					,	1, -2, -1
					,	1, 1, -1
					};*/

	/*double k13[9] =	{	1, 1, 1
					,	1, -2, -1
					,	1, -1, -1
					};

	double k14[9] =	{	1, 1, 1
					,	-1, -2, 1
					,	-1, -1, 1
					};

	double k15[9] =	{	1, -1, -1
					,	1, -2, -1
					,	1, 1, 1
					};

	double k16[9] =	{	-1, -1, 1
					,	-1, -2, 1
					,	1, 1, 1
					};*/

	int kn = 3;
	image_type new_img(old_img);
	image_type tmp(new_img);
	while (max_n--)
	{
		int matched_n = 0;
		bool is_matched_k1, is_matched_k2, is_matched_k3, is_matched_k4;
		bool is_matched_k5, is_matched_k6, is_matched_k7, is_matched_k8;
		//bool is_matched_k9, is_matched_k10, is_matched_k11, is_matched_k12;
		//bool is_matched_k13, is_matched_k14, is_matched_k15, is_matched_k16;
		for (int py = 0; py < tmp.height() - kn; ++py)
		{
			for (int px = 0; px < tmp.width() - kn; ++px)
			{
				is_matched_k1 = sh_hp_match(tmp, new_img, px, py, k1, 3, 3);
				is_matched_k2 = sh_hp_match(tmp, new_img, px, py, k2, 3, 3);
				is_matched_k3 = sh_hp_match(tmp, new_img, px, py, k3, 3, 3);
				is_matched_k4 = sh_hp_match(tmp, new_img, px, py, k4, 3, 3);
				is_matched_k5 = sh_hp_match(tmp, new_img, px, py, k5, 3, 3);
				is_matched_k6 = sh_hp_match(tmp, new_img, px, py, k6, 3, 3);
				is_matched_k7 = sh_hp_match(tmp, new_img, px, py, k7, 3, 3);
				is_matched_k8 = sh_hp_match(tmp, new_img, px, py, k8, 3, 3);
				/*is_matched_k9 = sh_hp_match(tmp, new_img, px, py, k9, 3, 3);
				is_matched_k10 = sh_hp_match(tmp, new_img, px, py, k10, 3, 3);
				is_matched_k11 = sh_hp_match(tmp, new_img, px, py, k11, 3, 3);
				is_matched_k12 = sh_hp_match(tmp, new_img, px, py, k12, 3, 3);*/
				/*is_matched_k13 = sh_hp_match(tmp, new_img, px, py, k13, 3, 3);
				is_matched_k14 = sh_hp_match(tmp, new_img, px, py, k14, 3, 3);
				is_matched_k15 = sh_hp_match(tmp, new_img, px, py, k15, 3, 3);
				is_matched_k16 = sh_hp_match(tmp, new_img, px, py, k16, 3, 3);*/

				if (	is_matched_k1
					||	is_matched_k2
					||	is_matched_k3
					||	is_matched_k4
					||	is_matched_k5
					||	is_matched_k6
					||	is_matched_k7
					||	is_matched_k8
					/*||	is_matched_k9
					||	is_matched_k10
					||	is_matched_k11
					||	is_matched_k12*/
					/*||	is_matched_k13
					||	is_matched_k14
					||	is_matched_k15
					||	is_matched_k16*/
					)
				{
					matched_n++;
				}
			}
		}

		if (matched_n <= 0) break;
		else tmp = new_img;
	}
	return new_img;
}
#endif // SH_FX_H
