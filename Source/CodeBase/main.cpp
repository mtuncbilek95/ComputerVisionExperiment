#include "CodeBase/Core/Core.h"

#include <opencv2/core.hpp>
#undef HAVE_OPENCV_IMGCODECS
#undef HAVE_OPENCV_VIDEOIO
#include <opencv2/highgui.hpp>

static cv::Mat MakeSinusoidalPatternImage(f64 phaseShift, f64 amplitude = 255, i32 period = 10, Math::Vec2i res = { 1280, 720 })
{
	cv::Mat img(res.y, res.x, CV_8UC1);

	for (u32 i = 0; i < res.x; ++i)
	{
		f64 coFactor = amplitude / 2;
		f64 rad = (2 * Math::Pi * i) / period;

		// Pattern value
		f64 val = coFactor * (1 + sin(rad + phaseShift));

		for (u32 j = 0; j < res.y; j++)
			img.at<u8>(j, i) = static_cast<u8>(val);
	}

	return img;
}

cv::Mat ComputePhaseMap(const cv::Mat& I1, const cv::Mat& I2, const cv::Mat& I3)
{
	Math::Vec2i res = { I1.cols, I1.rows };
	cv::Mat phaseMap(res.y, res.x, CV_8UC1);

	for (u32 y = 0; y < res.y; ++y)
	{
		for (u32 x = 0; x < res.x; ++x)
		{
			f64 I1_val = I1.at<u8>(y, x);
			f64 I2_val = I2.at<u8>(y, x);
			f64 I3_val = I3.at<u8>(y, x);

			f64 numerator = std::sqrt(3.0) * (I1_val - I3_val);
			f64 denominator = 2.0 * I2_val - (I1_val + I3_val);
			f64 phi = std::atan2(numerator, denominator);

			phaseMap.at<u8>(y, x) = static_cast<u8>(phi);
		}
	}

	return phaseMap;
}

cv::Mat HarmonicMeanWithLimitation(const cv::Mat& p1, const cv::Mat& p2)
{
	Math::Vec2i res = { p1.cols, p1.rows };
	cv::Mat phaseMap(res.y, res.x, CV_8UC1);

	for (u32 y = 0; y < res.y; ++y)
	{
		for (u32 x = 0; x < res.x; ++x)
		{
			f64 phi1 = p1.at<u8>(y, x);
			f64 phi2 = p1.at<u8>(y, x);

			f64 diff = phi2 - phi1;

			if (diff > CV_PI)
				phi2 -= 2.0f * CV_PI;
			else if (diff < -CV_PI)
				phi2 += 2.0f * CV_PI;

			f64 phaseVal = (phi1 + phi2) / 2.0f;

			if (phaseVal > CV_PI)
				phaseVal -= 2.0f * CV_PI;
			else if (phaseVal < -CV_PI)
				phaseVal += 2.0f * CV_PI;

			phaseMap.at<u8>(y, x) = phaseVal;
		}
	}

	return phaseMap;
}

i32 main(i32 argC, i8** argV)
{
	i32 period = 10;
	f64 amplitude = 255;

	std::vector<cv::Mat> imgs(6);
	for (u32 i = 0; i < imgs.size(); ++i)
		imgs[i] = MakeSinusoidalPatternImage(i * Math::Pi / 3);

	std::vector<cv::Mat> pMaps(2);
	for (u32 i = 0; i < pMaps.size(); ++i)
		pMaps[i] = ComputePhaseMap(imgs[i * 3], imgs[(i * 3) + 1], imgs[(i * 3) + 2]);

	cv::Mat result = HarmonicMeanWithLimitation(pMaps[0], pMaps[1]);

	cv::imshow("Phase", result);
	cv::waitKey(0);
}
