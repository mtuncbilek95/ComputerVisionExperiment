#include "CodeBase/Core/Core.h"

#include <opencv2/core.hpp>
#undef HAVE_OPENCV_IMGCODECS
#undef HAVE_OPENCV_VIDEOIO
#include <opencv2/highgui.hpp>

f64 BaseSinusoidal(f64 amplitude, i32 period, f64 position, f64 phase = 0.0)
{
	return (amplitude / 2) * (1 + sin(((2 * Math::Pi) / period) * position + phase));
}

cv::Mat ComputePhaseMap(const cv::Mat& I1, const cv::Mat& I2, const cv::Mat& I3)
{
    i32 width = I1.cols, height = I1.rows;
    cv::Mat phaseMap(height, width, CV_64F);

    for (u32 y = 0; y < height; ++y)
    {
        for (u32 x = 0; x < width; ++x)
        {
            f64 I1_val = static_cast<double>(I1.at<uint8_t>(y, x));
            f64 I2_val = static_cast<double>(I2.at<uint8_t>(y, x));
            f64 I3_val = static_cast<double>(I3.at<uint8_t>(y, x));

            f64 numerator = std::sqrt(3.0) * (I1_val - I3_val);
            f64 denominator = 2.0 * I2_val - (I1_val + I3_val);
            f64 phi = std::atan2(numerator, denominator);

            phaseMap.at<double>(y, x) = phi;
        }
    }

    return phaseMap;
}

cv::Mat NormalizePhaseMap(const cv::Mat& phaseMap)
{
    i32 width = phaseMap.cols, height = phaseMap.rows;
    cv::Mat normalizedImage(height, width, CV_8UC1);

    for (u32 y = 0; y < height; ++y)
    {
        for (u32 x = 0; x < width; ++x)
        {
            f64 phi = phaseMap.at<f64>(y, x);
            u8 normalizedValue = static_cast<u8>(std::round((phi + Math::Pi) / (2.0 * Math::Pi) * 255.0));
            normalizedImage.at<u8>(y, x) = normalizedValue;
        }
    }

    return normalizedImage;
}

i32 main(i32 argC, i8** argV)
{
    Math::Vec2i resSize = { 1280,720 };

    i32 period = 10;
    f64 amplitude = 255;
    f64 phaseShift[] = { 0, Math::Pi / 2, Math::Pi };

    cv::Mat I1(resSize.y, resSize.x, CV_8UC1);
    cv::Mat I2(resSize.y, resSize.x, CV_8UC1);
    cv::Mat I3(resSize.y, resSize.x, CV_8UC1);

    for (u32 x = 0; x < resSize.x; ++x)
    {
        f64 intensity1 = BaseSinusoidal(amplitude, period, x, phaseShift[0]);
        f64 intensity2 = BaseSinusoidal(amplitude, period, x, phaseShift[1]);
        f64 intensity3 = BaseSinusoidal(amplitude, period, x, phaseShift[2]);

        for (u32 y = 0; y < resSize.y; ++y)
        {
            I1.at<u8>(y, x) = static_cast<u8>(intensity1);
            I2.at<u8>(y, x) = static_cast<u8>(intensity2);
            I3.at<u8>(y, x) = static_cast<u8>(intensity3);
        }
    }

    cv::Mat phaseMap = ComputePhaseMap(I1, I2, I3);
    cv::Mat normMap = NormalizePhaseMap(phaseMap);

    cv::imshow("Phase Map", normMap);
    cv::waitKey(0);
}
