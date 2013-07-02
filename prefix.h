#ifndef PREFIX_H
#define PREFIX_H

// extl library
//#define EXTL_DEBUG
#include "extl\prefix.h"
#include "extl\graphic\graphic.h"
#include "extl\memory\buffer.h"
#include "extl\container\pair.h"
#include "extl\math\math.h"
#include "extl\intelligence\ann\ann.h"
using namespace extl;
using namespace extl::graphic;
using namespace extl::intelligence;
typedef basic_point<int>						point_type;
typedef basic_rect<int>							rect_type;
typedef basic_size<int>							size_type;
typedef basic_image								image_type;
typedef scoped_buffer<image_type>				images_type;
typedef scoped_buffer<point_type>				points_type;

#include <QImage>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDebug>

// for vc 2003
#ifdef EXTL_COMPILER_IS_MSVC
#	include "windows.h"
#	pragma comment(lib, "user32.lib")
#endif

// test
#define SAMPLES_DB_PATH "..\\samples\\samples.mdb"

// release
//#define SAMPLES_DB_PATH "samples\\samples.mdb"
//#define NETWORK_DB_PATH "samples\\network.txt"

// \note haven't been finished
#define USING_BAYES_CLASSIFIER

// pca switch
#define USING_PCA
#ifdef USING_PCA
#	define PCA_INPUT_N		(IMAGE_W * IMAGE_H)
#	define PCA_OUTPUT_N		(24)
#	define NETWORK_INPUT_N	(PCA_OUTPUT_N)
#	define NETWORK_OUTPUT_N	(4)
//#	define MODE_16_32
//#	define MODE_10_20
#	define MODE_8_16
#else
#	define PCA_INPUT_N		(1)
#	define PCA_OUTPUT_N		(1)
#	define NETWORK_INPUT_N	(IMAGE_W * IMAGE_H)
#	define NETWORK_OUTPUT_N	(4)
#	define MODE_8_16
#endif

// image mode
#if defined(MODE_8_16)
#	define IMAGE_W				(8)
#	define IMAGE_H				(16)
#	define TRAIN_SAMPLE_DB_NAME	"TRAIN_SAMPLES_8_16"
#	define TEST_SAMPLE_DB_NAME	"TEST_SAMPLES_8_16"
#	define NETWORK_DB_PATH		"..\\samples\\network_8_16.txt"
#	define PCA_DB_PATH			"..\\samples\\pca_8_16.txt"
#elif defined(MODE_10_20)
#	define IMAGE_W				(10)
#	define IMAGE_H				(20)
#	define TRAIN_SAMPLE_DB_NAME	"TRAIN_SAMPLES_10_20"
#	define TEST_SAMPLE_DB_NAME	"TEST_SAMPLES_10_20"
#	define NETWORK_DB_PATH		"..\\samples\\network_10_20.txt"
#	define PCA_DB_PATH			"..\\samples\\pca_10_20.txt"
#elif defined(MODE_12_24)
#	define IMAGE_W				(12)
#	define IMAGE_H				(24)
#	define TRAIN_SAMPLE_DB_NAME	"TRAIN_SAMPLES_12_24"
#	define TEST_SAMPLE_DB_NAME	"TEST_SAMPLES_12_24"
#	define NETWORK_DB_PATH		"..\\samples\\network_12_24.txt"
#	define PCA_DB_PATH			"..\\samples\\pca_12_24.txt"
#elif defined(MODE_14_28)
#	define IMAGE_W				(14)
#	define IMAGE_H				(28)
#	define TRAIN_SAMPLE_DB_NAME	"TRAIN_SAMPLES_14_28"
#	define TEST_SAMPLE_DB_NAME	"TEST_SAMPLES_14_28"
#	define NETWORK_DB_PATH		"..\\samples\\network_14_28.txt"
#	define PCA_DB_PATH			"..\\samples\\pca_14_28.txt"
#else
#	define IMAGE_W				(16)
#	define IMAGE_H				(32)
#	define TRAIN_SAMPLE_DB_NAME	"TRAIN_SAMPLES_16_32"
#	define TEST_SAMPLE_DB_NAME	"TEST_SAMPLES_16_32"
#	define NETWORK_DB_PATH		"..\\samples\\network_16_32.txt"
#	define PCA_DB_PATH			"..\\samples\\pca_16_32.txt"
#endif

//#define USING_THINNING


// modified factors
#define FACTOR_BP_LRATE		(0.5)	// the learning rate for bp
#define FACTOR_BP_MF		(0.6)	// the momentum term factor for bp

#endif // PREFIX_H
