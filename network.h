#ifndef NETWORK_H
#define NETWORK_H

#include "prefix.h"
#include "imageconvector.h"

#include <QFile>
#include <QTextStream>

#define TRAIN_COUNT		(200)

template<typename_param_k Wgts>
inline void	save_weights(QTextStream& fout, Wgts const& wgts)
{
	fout << wgts.size() << endl;
	for (int i = 0; i < (int)wgts.size(); ++i)
	{
		fout << wgts[i].value() << endl;
	}
}
template<typename_param_k Wgts>
inline Wgts	load_weights(QTextStream& fin)
{
	typedef Wgts											weights_type;
	typedef typename_type_k weights_type::size_type			size_type;
	typedef typename_type_k weights_type::value_type		weight_type;
	typedef typename_type_k weight_type::float_type			value_type;

	// read the number of the weights
	size_type wgts_n;
	fin >> wgts_n;
	weights_type wgts(wgts_n);

	// read weights
	for (int i = 0; i < (int)wgts_n; ++i)
	{
		value_type val;
		fin >> val;
		wgts[i].value(val);
	}

	return wgts;
}
template<typename_param_k Vtr>
inline void	save_vector(QTextStream& fout, Vtr const& v)
{
	fout << v.size() << endl;
	for (int i = 0; i < (int)v.size(); ++i)
	{
		fout << v[i] << endl;
	}
}
template<typename_param_k Vtr>
inline Vtr load_vector(QTextStream& fin)
{
	typedef Vtr												vector_type;
	typedef typename_type_k vector_type::size_type			size_type;

	// read the number of the weights
	size_type n;
	fin >> n;
	vector_type v(n);

	// read weights
	for (int i = 0; i < (int)n; ++i) fin >> v[i];
	return v;
}
// bp_policy
struct bp_policy
{
	public:
		typedef bp_network<NETWORK_INPUT_N, NETWORK_OUTPUT_N>		network_type;
		typedef network_type::layers_type							layers_type;
		typedef network_type::sample_type							sample_type;
		typedef network_type::samples_type							samples_type;
		typedef network_type::weights_type							weights_type;
		typedef network_type::size_type								size_type;
		typedef network_type::float_type							float_type;
		typedef basic_network_validator<network_type>				validator_type;


	private:
		network_type								m_network;
		validator_type								m_validator;

	public:
		bp_policy()
				: m_network(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
		{}

	public:
		network_type&			network()			{ return m_network;	}
		network_type const&		network() const		{ return m_network;	}

		validator_type&			validator()			{ return m_validator;	}
		validator_type const&	validator() const	{ return m_validator;	}

	/// \name Methods
	/// @{
	public:
		void	train(samples_type& sps)
		{
			network().train(sps, TRAIN_COUNT);
		}
		void	run(sample_type& sp)
		{
			network().run(sp);
		}
		void	save()
		{
			QFile file(NETWORK_DB_PATH);
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return;

			QTextStream fout(&file);

			// save signature
			fout << "bp_network" << endl;

			// save weights
			save_weights(fout, network().weights());
		}
		bool	load()
		{
			QFile file(NETWORK_DB_PATH);
			if (!file.open(QIODevice::ReadOnly))
				return false;

			QTextStream fin(&file);

			// read signature
			QString sig;
			fin >> sig;
			if (sig != "bp_network") return false;

			// load weights
			network().weights(load_weights<weights_type>(fin));

			return true;
		}

		QString	validate(samples_type& sps)
		{
			validator().validate(network(), sps);
			return QObject::tr("bp network:: mse:%1 erate:%2").arg(validator().mse()).arg(validator().erate());
		}
	/// @}
};

// wga_policy
struct wga_policy
{
	public:
		typedef bp_network<NETWORK_INPUT_N, NETWORK_OUTPUT_N>	bp_network_type;
		typedef wga_network<bp_network_type>					network_type;
		typedef bp_network_type::layers_type					layers_type;
		typedef bp_network_type::sample_type					sample_type;
		typedef bp_network_type::samples_type					samples_type;
		typedef bp_network_type::weights_type					weights_type;
		typedef bp_network_type::size_type						size_type;
		typedef bp_network_type::float_type						float_type;
		typedef basic_network_validator<network_type>			validator_type;

	private:
		bp_network_type								m_bp;
		network_type								m_network;
		validator_type								m_validator;

	public:
		wga_policy()
				: m_bp(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_network(m_bp)
		{}

	public:
		network_type&			network()			{ return m_network;	}
		network_type const&		network() const		{ return m_network;	}

		validator_type&			validator()			{ return m_validator;	}
		validator_type const&	validator() const	{ return m_validator;	}

	/// \name Methods
	/// @{
	public:
		void	train(samples_type& sps)
		{
			network().train(sps, TRAIN_COUNT);
		}
		void	run(sample_type& sp)
		{
			network().run(sp);
		}
		void	save()
		{
			QFile file(NETWORK_DB_PATH);
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return;

			QTextStream fout(&file);

			// save signature
			fout << "wga_network" << endl;

			// save weights
			save_weights(fout, m_bp.weights());
		}
		bool	load()
		{
			QFile file(NETWORK_DB_PATH);
			if (!file.open(QIODevice::ReadOnly))
				return false;
			QTextStream fin(&file);

			// read signature
			QString sig;
			fin >> sig;
			if (sig != "wga_network") return false;

			// load weights
			m_bp.weights(load_weights<weights_type>(fin));

			return true;
		}

		QString	validate(samples_type& sps)
		{
			validator().validate(network(), sps);
			return QObject::tr("wga network:: mse:%1 erate:%2 generation:%3").arg(validator().mse()).arg(validator().erate()).arg(network().generation());
		}
	/// @}
};
// bagging_policy
struct bagging_policy
{
	public:
		typedef bp_network<NETWORK_INPUT_N, NETWORK_OUTPUT_N>		bp_network_type;
		typedef bagging_networks<bp_network_type>					network_type;
		typedef bp_network_type::layers_type						layers_type;
		typedef bp_network_type::sample_type						sample_type;
		typedef bp_network_type::samples_type						samples_type;

	private:
		bp_network_type								m_bp_0;
		bp_network_type								m_bp_1;
		bp_network_type								m_bp_2;
		bp_network_type								m_bp_3;
		bp_network_type								m_bp_4;
		bp_network_type								m_bp_5;
		bp_network_type								m_bp_6;
		bp_network_type								m_bp_7;
		bp_network_type								m_bp_8;
		bp_network_type								m_bp_9;
		network_type								m_network;

	public:
		bagging_policy()
				: m_bp_0(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_1(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_2(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_3(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_4(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_5(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_6(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_7(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_8(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_bp_9(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF)
				, m_network(&m_bp_0, &m_bp_1, &m_bp_2, &m_bp_3, &m_bp_4, &m_bp_5, &m_bp_6, &m_bp_7, &m_bp_8, &m_bp_9)
		{}

	public:
		network_type&			network()			{ return m_network;	}
		network_type const&		network() const		{ return m_network;	}
};
// ada_boosting_policy
struct ada_boosting_policy
{
	public:
		typedef bp_network	<	NETWORK_INPUT_N
							,	NETWORK_OUTPUT_N
							,	sample_selector<NETWORK_INPUT_N, NETWORK_OUTPUT_N>::float_sample_type
							>										bp_network_type;
		typedef ada_boosting_n_networks<bp_network_type>			network_type;
		typedef bp_network_type::layers_type						layers_type;
		typedef bp_network_type::sample_type						sample_type;
		typedef bp_network_type::samples_type						samples_type;
		typedef bp_network_type::weights_type						weights_type;
		typedef bp_network_type::size_type							size_type;
		typedef bp_network_type::float_type							float_type;
		typedef basic_network_validator<network_type>				validator_type;
		typedef network_type::floats_type							floats_type;

	private:
		bp_network_type								m_bp_0;
		bp_network_type								m_bp_1;
		bp_network_type								m_bp_2;
		bp_network_type								m_bp_3;
		bp_network_type								m_bp_4;
		bp_network_type								m_bp_5;
		bp_network_type								m_bp_6;
		bp_network_type								m_bp_7;
		bp_network_type								m_bp_8;
		bp_network_type								m_bp_9;
		network_type								m_network;
		validator_type								m_validator;

	public:
		ada_boosting_policy()
		{
			for (e_size_t i = 0; i < 10; ++i)
			{
				m_network.push_back(bp_network_type(layers_type(10), FACTOR_BP_LRATE, FACTOR_BP_MF));
			}
		}

	public:
		network_type&			network()			{ return m_network;		}
		network_type const&		network() const		{ return m_network;		}

		validator_type&			validator()			{ return m_validator;	}
		validator_type const&	validator() const	{ return m_validator;	}

	/// \name Methods
	/// @{
	public:
		void	train(samples_type& sps)
		{
			network().train(sps, TRAIN_COUNT);
		}
		void	run(sample_type& sp)
		{
			network().run(sp);
		}
		void	save()
		{
			QFile file(NETWORK_DB_PATH);
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return;

			QTextStream fout(&file);

			// save signature
			fout << "ada_boosting_network" << endl;

			size_type i;
			// save the weights of the whole network
			floats_type wgts = network().weights();
			fout << wgts.size() << endl;
			for (i = 0; i < wgts.size(); ++i)
			{
				fout << wgts[i] << endl;
			}

			// save the weights of the every base network
			size_type nets_n = network().networks().size();
			fout << nets_n << endl;
			for (i = 0; i < nets_n; ++i)
				save_weights(fout, network().network(i).weights());

		}
		bool	load()
		{
			QFile file(NETWORK_DB_PATH);
			if (!file.open(QIODevice::ReadOnly))
				return false;

			QTextStream fin(&file);

			// read signature
			QString sig;
			fin >> sig;
			if (sig != "ada_boosting_network") return false;

			// read the number of the weights
			size_type wgts_n;
			fin >> wgts_n;
			floats_type wgts(wgts_n);

			// load the weights of the whole network
			size_type i;
			for (i = 0; i < wgts_n; ++i)
			{
				float_type val;
				fin >> val;
				wgts[i] = val;
			}
			network().weights(wgts);

			// read the number of the networks
			size_type nets_n;
			fin >> nets_n;

			// load the weights of the every base network
			for (i = 0; i < nets_n; ++i)
				network().network(i).weights(load_weights<weights_type>(fin));

			return true;
		}

		QString	validate(samples_type& sps)
		{
			validator().validate(network(), sps);
			return QObject::tr("ada-boosting network:: mse:%1 erate:%2").arg(validator().mse()).arg(validator().erate());
		}
	/// @}
};
#if 0
// wga_ada_boosting_policy
struct wga_ada_boosting_policy
{
	public:
		typedef bp_network<NETWORK_INPUT_N, 4>						bp_network_type;
		typedef wga_network<bp_network_type>						wga_network_type;
		typedef ada_boosting_networks<wga_network_type>				network_type;
		typedef bp_network_type::layers_type						layers_type;
		typedef bp_network_type::sample_type						sample_type;
		typedef bp_network_type::samples_type						samples_type;

	private:
		bp_network_type								m_bp_0;
		/*bp_network_type							m_bp_1;
		bp_network_type								m_bp_2;
		bp_network_type								m_bp_3;
		bp_network_type								m_bp_4;
		bp_network_type								m_bp_5;
		bp_network_type								m_bp_6;
		bp_network_type								m_bp_7;
		bp_network_type								m_bp_8;
		bp_network_type								m_bp_9;*/
		wga_network_type							m_wga_0;
		/*wga_network_type							m_wga_1;
		wga_network_type							m_wga_2;
		wga_network_type							m_wga_3;
		wga_network_type							m_wga_4;
		wga_network_type							m_wga_5;
		wga_network_type							m_wga_6;
		wga_network_type							m_wga_7;
		wga_network_type							m_wga_8;
		wga_network_type							m_wga_9;*/
		network_type								m_network;

	public:
		wga_ada_boosting_policy()
				: m_bp_0(layers_type(10), 0.5)
				/*, m_bp_1(layers_type(10), 0.5)
				, m_bp_2(layers_type(10), 0.5)
				, m_bp_3(layers_type(10), 0.5)
				, m_bp_4(layers_type(10), 0.5)
				, m_bp_5(layers_type(10), 0.5)
				, m_bp_6(layers_type(10), 0.5)
				, m_bp_7(layers_type(10), 0.5)
				, m_bp_8(layers_type(10), 0.5)
				, m_bp_9(layers_type(10), 0.5)*/
				, m_wga_0(m_bp_0)
				/*, m_wga_1(m_bp_1)
				, m_wga_2(m_bp_2)
				, m_wga_3(m_bp_3)
				, m_wga_4(m_bp_4)
				, m_wga_5(m_bp_5)
				, m_wga_6(m_bp_6)
				, m_wga_7(m_bp_7)
				, m_wga_8(m_bp_8)
				, m_wga_9(m_bp_9)*/
				, m_network(&m_wga_0/*, &m_wga_1, &m_wga_2, &m_wga_3, &m_wga_4, &m_wga_5, &m_wga_6, &m_wga_7, &m_wga_8, &m_wga_9*/)
		{}

	public:
		network_type&			network()			{ return m_network;	}
		network_type const&		network() const		{ return m_network;	}
};
#endif
#ifdef USING_PCA
// pca_mixed_policy
template<typename_param_k Py>
struct pca_mixed_policy
{
	public:
		typedef Py															basic_policy_type;
		typedef typename_type_k basic_policy_type::network_type				basic_network_type;
		typedef ghia_network<PCA_INPUT_N, PCA_OUTPUT_N>						pca_type;
		typedef pca_mixed_network<pca_type, basic_network_type>				network_type;
		typedef typename_type_k network_type::sample_type					sample_type;
		typedef typename_type_k network_type::samples_type					samples_type;
		typedef typename_type_k network_type::size_type						size_type;
		typedef typename_type_k network_type::float_type					float_type;
		typedef basic_network_validator<network_type>						validator_type;
		typedef typename_type_k pca_type::vector_type						vector_type;

	private:
		network_type														m_network;
		validator_type														m_validator;

	public:
		pca_mixed_policy()
				: m_network(pca_type(), basic_policy_type().network())
		{
		}

	public:
		network_type&			network()			{ return m_network;		}
		network_type const&		network() const		{ return m_network;		}

		validator_type&			validator()			{ return m_validator;	}
		validator_type const&	validator() const	{ return m_validator;	}

	/// \name Methods
	/// @{
	public:
		void	train(samples_type& sps)
		{
			// train
			network().train(sps, TRAIN_COUNT, 10);
		}

		void	run(sample_type& sp)
		{
			network().run(sp);
		}
		void	save()
		{
			QFile file(PCA_DB_PATH);
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return;

			QTextStream fout(&file);

			// save signature
			fout << "pca" << endl;

			// save the weights
			size_type vecs_n = network().pnet().vectors_size();
			for (size_type i = 0; i < vecs_n; ++i)
				save_vector(fout, network().pnet().vector(i));

			// save converters
			save_vector(fout, network().pnet().converter().avgs());
			save_vector(fout, network().pnet().converter().sds());

			save_vector(fout, network().converter().mins());
			save_vector(fout, network().converter().maxs());

			// save network data
			basic_policy_type py;
			py.network() = network().onet();
			py.save();
		}
		bool	load()
		{
			QFile file(PCA_DB_PATH);
			if (!file.open(QIODevice::ReadOnly))
				return false;

			QTextStream fin(&file);

			// read signature
			QString sig;
			fin >> sig;
			if (sig != "pca") return false;

			// load the weights
			size_type vecs_n = network().pnet().vectors_size();
			for (size_type i = 0; i < vecs_n; ++i)
				network().pnet().vector(i) = (load_vector<vector_type>(fin));

			// load converters
			network().pnet().converter().avgs() = load_vector<vector_type>(fin);
			network().pnet().converter().sds() = load_vector<vector_type>(fin);

			network().converter().mins() = load_vector<vector_type>(fin);
			network().converter().maxs() = load_vector<vector_type>(fin);

			// load network data
			basic_policy_type py;
			bool ret = py.load();
			network().onet() = py.network();

			return ret;
		}

		QString	validate(samples_type& sps)
		{
			validator().validate(network(), sps);
			//return QObject::tr("pca mixed network:: mse:%1 erate:%2").arg(validator().mse()).arg(validator().erate());
			return QObject::tr("mse:%1 rate:%2%").arg(validator().mse()).arg((1 - validator().erate()) * 100);
		}
	/// @}
};
// pca_mixed_policy_with_bayes_classifier
template<typename_param_k Py>
struct pca_mixed_policy_with_bayes_classifier
{
	public:
		typedef Py															basic_policy_type;
		typedef typename_type_k basic_policy_type::network_type				basic_network_type;
		typedef ghia_network<PCA_INPUT_N, PCA_OUTPUT_N>						pca_type;
		typedef pca_mixed_network<pca_type, basic_network_type>				network_type;
		typedef typename_type_k network_type::sample_type					sample_type;
		typedef typename_type_k network_type::samples_type					samples_type;
		typedef typename_type_k network_type::size_type						size_type;
		typedef typename_type_k network_type::float_type					float_type;
		typedef bayes_classifier<network_type>								classifier_type;
		typedef basic_classifier_validator<classifier_type>					validator_type;
		typedef typename_type_k pca_type::vector_type						vector_type;

	private:
		network_type														m_network;
		validator_type														m_validator;
		classifier_type														m_classifier;

	public:
		pca_mixed_policy_with_bayes_classifier()
				: m_network(pca_type(), basic_policy_type().network())
				, m_classifier(&m_network)
		{
		}

	public:
		network_type&			network()			{ return m_network;		}
		network_type const&		network() const		{ return m_network;		}

		validator_type&			validator()			{ return m_validator;	}
		validator_type const&	validator() const	{ return m_validator;	}

		classifier_type&		classifier()		{ return m_classifier;	}
		classifier_type const&	classifier() const	{ return m_classifier;	}

	/// \name Methods
	/// @{
	public:
		void	train(samples_type& sps)
		{
			// encode samples
			encode_samples(sps);

			// train
			network().train(sps, TRAIN_COUNT, 10);

			// init classifier
			classifier().init(sps);
		}

		void	run(sample_type& sp)
		{
			classifier().classify(sp);
			decode_sample(sp);
		}
		void	save()
		{
			QFile file(PCA_DB_PATH);
			if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				return;

			QTextStream fout(&file);

			// save signature
			fout << "pca" << endl;

			// save the weights
			size_type vecs_n = network().pnet().vectors_size();
			for (size_type i = 0; i < vecs_n; ++i)
				save_vector(fout, network().pnet().vector(i));

			// save converters
			save_vector(fout, network().pnet().converter().avgs());
			save_vector(fout, network().pnet().converter().sds());

			save_vector(fout, network().converter().mins());
			save_vector(fout, network().converter().maxs());

			// save network data
			basic_policy_type py;
			py.network() = network().onet();
			py.save();
		}
		bool	load()
		{
			QFile file(PCA_DB_PATH);
			if (!file.open(QIODevice::ReadOnly))
				return false;

			QTextStream fin(&file);

			// read signature
			QString sig;
			fin >> sig;
			if (sig != "pca") return false;

			// load the weights
			size_type vecs_n = network().pnet().vectors_size();
			for (size_type i = 0; i < vecs_n; ++i)
				network().pnet().vector(i) = (load_vector<vector_type>(fin));

			// load converters
			network().pnet().converter().avgs() = load_vector<vector_type>(fin);
			network().pnet().converter().sds() = load_vector<vector_type>(fin);

			network().converter().mins() = load_vector<vector_type>(fin);
			network().converter().maxs() = load_vector<vector_type>(fin);

			// load network data
			basic_policy_type py;
			bool ret = py.load();
			network().onet() = py.network();

			return ret;
		}
		void	encode_samples(samples_type& sps)
		{
			/*size_type h[10];
			h[0] = 0; //"0000";
			h[1] = 3; // "0011";
			h[2] = 6; // "0110";
			h[3] = 12; // "1100";
			h[4] = 9; // "1001";
			h[5] = 5; // "0101";
			h[6] = 10; // "1010";
			h[7] = 15; // "1111";
			h[8] = 1; // "0001";
			h[9] = 14; // "1110";
			for (size_type i = 0; i < sps.size(); ++i)
				sps[i].dreal(h[sps[i].dreal()]);

			h[0] = 0; //"0000000000";
			h[1] = 31; // "0000011111";
			h[2] = 62; // "0000111110";
			h[3] = 124; // "0001111100";
			h[4] = 248; // "0011111000";
			h[5] = 496; // "0111110000";
			h[6] = 992; // "1111100000";
			h[7] = 220; // "0011011100";
			h[8] = 803; // "1100100011";
			h[9] = 1023; // "1111111111";
			for (size_type i = 0; i < sps.size(); ++i)
				sps[i].dreal(h[sps[i].dreal()]);*/
		}
		void	decode_sample(sample_type& sp)
		{
			/*typedef typename_type_k hash_selector<size_type, size_type>::hash_type		hash_type;
			hash_type h;
			h[0] = 0; //"0000000000";
			h[31] = 1; // "0000011111";
			h[62] = 2; // "0000111110";
			h[124] = 3; // "0001111100";
			h[248] = 4; // "0011111000";
			h[496] = 5; // "0111110000";
			h[992] = 6; // "1111100000";
			h[220] = 7; // "0011011100";
			h[803] = 8; // "1100100011";
			h[1023] = 9; // "1111111111";
			sp.doutput(h[sp.doutput()]);

			h[0] = 0; //"0000";
			h[3] = 3; // "0011";
			h[6] = 6; // "0110";
			h[12] = 12; // "1100";
			h[9] = 9; // "1001";
			h[5] = 5; // "0101";
			h[10] = 10; // "1010";
			h[15] = 15; // "1111";
			h[1] = 1; // "0001";
			h[14] = 14; // "1110";
			sp.doutput(h[sp.doutput()]);*/
		}
		void	init_classifier(samples_type& trained_sps)
		{
			// init classifier
			m_classifier.init(trained_sps);
		}

		QString	validate(samples_type& sps)
		{
			validator().validate(classifier(), sps);
			//return QObject::tr("pca mixed network:: mse:%1 erate:%2").arg(validator().mse()).arg(validator().erate());
			return QObject::tr("mse:%1 rate:%2%").arg(validator().mse()).arg((1 - validator().erate()) * 100);
		}
	/// @}
};

#endif

// network
template<typename_param_k Py>
class Network
{
public:
	typedef Py													policy_type;
	typedef typename_type_k policy_type::network_type			network_type;
	typedef typename_type_k policy_type::sample_type			sample_type;
	typedef typename_type_k policy_type::samples_type			samples_type;

private:
	policy_type									m_policy;
	samples_type								m_samples;
	bool										m_is_prepared;

public:
	Network()
		: m_policy()
		, m_samples()
		, m_is_prepared(false)
	{
		// save network data
		if (policy().load())
			m_is_prepared = true;
	}

public:
	samples_type&			samples()		{ return m_samples;	}
	samples_type const&		samples() const	{ return m_samples;	}

	policy_type&			policy()			{ return m_policy;	}
	policy_type const&		policy() const		{ return m_policy;	}

	bool					is_prepared() const		{ return m_is_prepared;	}
	QString					info()					{ return policy().validate(samples());	}

	void					add(int digit, QImage const& image)
	{
		if (digit < 0 || digit > 9) return ;

		// add sample
		samples().push_back(convert(digit, image));
	}
	void					clear()
	{
		samples().clear();
	}
	int						recognize(QImage const& image)
	{
		sample_type sp = convert(-1, image);
		policy().run(sp);
		return sp.doutput();
	}
	QString					train()
	{
		// train
		m_is_prepared = false;
		policy().train(samples());
		m_is_prepared = true;

		// save network data
		policy().save();

		// validate
		return policy().validate(samples());
	}

private:
	sample_type				convert(int digit, QImage const& image) const
	{
		image_type img = ImageConvector::convect(image);
		sample_type sp;
		for (int px = 0; px < img.width(); ++px)
		{
			for (int py = 0; py < img.height(); ++py)
			{
				sp.set_binput(px * img.height() + py, img.at(px, py).is_black());
				sp.dreal(digit);
			}
		}

		return sp;
	}
};
#endif // NETWORK_H
