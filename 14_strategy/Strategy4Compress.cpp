#include <iostream>
#include <string>

using namespace std;

// 策略接口 - 图像压缩
class ImageCompressionStrategy {
public:
    virtual void compress(const string& fileName) = 0;
};

// 具体策略 - JPEG 压缩
class JpegCompression : public ImageCompressionStrategy {
public:
    void compress(const string& fileName) override {
        cout << "Compressing " << fileName << " using JPEG compression." << endl;
        // 实际的 JPEG 压缩逻辑
    }
};

// 具体策略 - PNG 压缩
class PngCompression : public ImageCompressionStrategy {
public:
    void compress(const string& fileName) override {
        cout << "Compressing " << fileName << " using PNG compression." << endl;
        // 实际的 PNG 压缩逻辑
    }
};

// 上下文 - 图像处理器
class ImageProcessor {
public:
    ImageProcessor(ImageCompressionStrategy* compressionStrategy) : m_compressionStrategy(compressionStrategy) {}

    void setCompressionStrategy(ImageCompressionStrategy* compressionStrategy) {
        m_compressionStrategy = compressionStrategy;
    }

    void processImage(const string& fileName) {
        if (m_compressionStrategy) {
            m_compressionStrategy->compress(fileName);
        }
    }

private:
    ImageCompressionStrategy* m_compressionStrategy;
};

int main() {
    ImageCompressionStrategy* jpegCompression = new JpegCompression();
    ImageCompressionStrategy* pngCompression = new PngCompression();

    ImageProcessor imageProcessor(jpegCompression);
    imageProcessor.processImage("image1.jpg");

    imageProcessor.setCompressionStrategy(pngCompression);
    imageProcessor.processImage("image2.png");

    delete jpegCompression;
    delete pngCompression;

    return 0;
}
