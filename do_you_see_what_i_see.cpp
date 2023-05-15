#include <iostream>
#include <opencv2/opencv.hpp>

// Extra Credit 1
void ConvertToFloatArray(const cv::Mat& image, float* float_data, const bool has_alpha_channel) {
    const int height = image.rows;
    const int width = image.cols;
    int data_index = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (has_alpha_channel) {
                cv::Vec4b pixel = image.at<cv::Vec4b>(y, x);
                float_data[data_index++] = static_cast<float>(pixel[2]) / 255.0f; // red channel
                float_data[data_index++] = static_cast<float>(pixel[1]) / 255.0f; // green channel
                float_data[data_index++] = static_cast<float>(pixel[0]) / 255.0f; // blue channel
                float_data[data_index++] = static_cast<float>(pixel[3]) / 255.0f; // alpha channel
            } else {
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
                float_data[data_index++] = static_cast<float>(pixel[2]) / 255.0f; // red channel
                float_data[data_index++] = static_cast<float>(pixel[1]) / 255.0f; // green channel
                float_data[data_index++] = static_cast<float>(pixel[0]) / 255.0f; // blue channel
                float_data[data_index++] = 1.0f; // set alpha to 1.0 if no alpha channel
            }
        }
    }
}

void PrintFloatData(const float* const float_data, const int size_out) {
    std::cerr << "float_data: ";
    for (int i = 0; i < size_out; ++i) {
        std::cerr << float_data[i] << " ";
    }
    std::cerr << std::endl;
}

void PrintData(const uchar* const data, int size_in) {
    std::cerr << "data: ";
    for (int i = 0; i < size_in; ++i) {
        std::cerr << static_cast<int>(data[i]) << " ";
    }
    std::cerr << std::endl;
}

void PrintImageProperties(const cv::Mat& image) {
    std::cerr << "Image Properties:\n\twidth: " << image.cols << "\n\theight: " << image.rows
              << "\n\tNumber of color channels: " << image.channels() << "\n\tBits per pixel: " << image.elemSize() * 8
              << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image_file>" << std::endl;
        return 1;
    }

    // Load the image file
    cv::Mat image = cv::imread(argv[1], cv::IMREAD_UNCHANGED);
    if (image.empty()) {
        std::cerr << "Error: could not open or find the image file" << std::endl;
        return 1;
    }

    PrintImageProperties(image);

    // Set image dimensions to allocate memory for buffer
    const int width = image.cols;
    const int height = image.rows;
    const int channels = image.channels();
    const int channels_out = 4;
    const int size_in = width * height * channels;
    const int size_out = width * height * channels_out; // always accounts for alpha

    // Allocate memory for the input and output pixel data buffers
    uchar* data = new uchar[size_in];
    float* float_data = new float[size_out];

    // Copy the pixel data to the buffer
    int index = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Get the pixel values
            cv::Vec4b pixel = image.at<cv::Vec4b>(y, x);
            // Copy the pixel values to the buffer
            data[index++] = pixel[0]; // Blue channel
            data[index++] = pixel[1]; // Green channel
            data[index++] = pixel[2]; // Red channel
            if (channels == 4) {
                data[index++] = pixel[3]; // Alpha channel (if present)
            }
        }
    }

    // CV_8UC is an 8-bit unsigned char image with a single channel
    cv::Mat input_image_data(height, width, CV_8UC(channels), data);

    // convert input image data to normalized float array and store in float_data
    ConvertToFloatArray(input_image_data, float_data, channels == 4);

    // PrintData(data, size_in);
    // PrintFloatData(float_data, size_out);

    // Deallocate the pixel data buffer
    delete[] data;
    delete[] float_data;

    return 0;
}
