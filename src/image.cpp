#include "../include/image.h"

#include <assert.h>
#include <algorithm>

Image::Image() : m_rows(0), m_cols(0), m_channels(0), m_data(nullptr), m_refCount(nullptr) {
}

Image::Image(int rows, int cols, int channels)
    : m_rows(rows), m_cols(cols), m_channels(channels), m_data(nullptr), m_refCount(nullptr) {
    assert(rows > 0 && cols > 0 && channels > 0);

    int total = rows * cols * channels;
    m_data = new unsigned char[total]; // пиксели
    std::fill(m_data, m_data + total, 0);
    m_refCount = new size_t(1);
    // на данное изображение ссылается 1 объект, когда создается новый объект, который является копией существующего, счетчик увеличивается
}

Image::Image(int rows, int cols, int channels, unsigned char *data)
    : m_rows(rows), m_cols(cols), m_channels(channels), m_data(nullptr), m_refCount(nullptr) {
    assert(rows > 0 && cols > 0 && channels > 0);
    assert(data != nullptr);

    int total = rows * cols * channels;
    m_data = new unsigned char[total];
    std::copy(data, data + total, m_data);
    m_refCount = new size_t(1);
}

Image::Image(const Image &image)
    : m_rows(image.m_rows), m_cols(image.m_cols), m_channels(image.m_channels), m_data(image.m_data),
      m_refCount(image.m_refCount) {
    if (m_refCount != nullptr) {
        ++ *m_refCount;
    }
}

Image::~Image() {
    release();
}

Image &Image::operator=(const Image &image) {
    assert(this != &image);

    if (m_refCount) {
        --*m_refCount;
        if (*m_refCount == 0) {
            delete[] m_data;
            delete m_refCount;
        }
    }

    m_rows = image.m_rows;
    m_cols = image.m_cols;
    m_channels = image.m_channels;
    m_data = image.m_data;
    m_refCount = image.m_refCount;

    if (m_refCount != nullptr) {
        ++(*m_refCount);
    }
    return *this;
}

Image Image::clone() const {
    int total = m_rows * m_cols * m_channels;
    unsigned char *newData = new unsigned char[total];
    std::copy(m_data, m_data + total, newData);
    return Image(m_rows, m_cols, m_channels, newData);
}


void Image::copyTo(Image &image) {
    assert(this != &image);

    image.release();

    image.m_rows = m_rows;
    image.m_cols = m_cols;
    image.m_channels = m_channels;

    int total = m_rows * m_cols * m_channels;
    image.m_data = new unsigned char[total];
    std::copy(m_data, m_data + total, image.m_data);
    image.m_refCount = new size_t(1);
}

void Image::create(int rows, int cols, int channels) {
    release();

    m_rows = rows;
    m_cols = cols;
    m_channels = channels;

    int total = m_rows * m_cols * m_channels;
    if (total > 0) {
        m_data = new unsigned char[total];
        std::fill(m_data, m_data + total, 0);
        m_refCount = new size_t(1);
    } else {
        m_data = nullptr;
        m_refCount = nullptr;
    }
}

bool Image::empty() const {
    return m_data == nullptr || (m_rows == 0 && m_cols == 0 && m_channels == 0);
}

void Image::release() {
    if (m_refCount != nullptr) {
        -- *m_refCount;
        if (*m_refCount == 0) {
            delete[] m_data;
            delete m_refCount;
        }
    }
    m_cols = 0;
    m_rows = 0;
    m_channels = 0;
    m_data = nullptr;
    m_refCount = nullptr;
}

Image Image::col(int x) const{
    assert(m_refCount != nullptr);
    assert(x >= 0 && x < m_cols);

    Image res(m_rows, 1, m_channels);
    unsigned char *resultData = res.data();
    for (int row = 0; row < m_rows; row++) {
        for (int channel = 0; channel < m_channels; channel++) {
            // индекс текущего пикселя в исходном изображении
            int sourceIndex = (row * m_cols + x) * m_channels + channel;
            // индекс текущего пикселя в новом изображении
            int resIndex = (row * 1) * m_channels + channel;
            resultData[resIndex] = m_data[sourceIndex];
        }
    }
    return res;
}

Image Image::row(int y) const{
    assert(m_refCount != nullptr);
    assert(y >= 0 && y < m_rows);

    Image res(1, m_cols, m_channels);
    unsigned char *resultData = res.data();
    for (int col = 0; col < m_cols; col++) {
        for (int channel = 0; channel < m_channels; channel++) {
            int sourceIndex = (y * m_cols + col) * m_channels + channel;
            int resIndex = (0 * m_cols + col) * m_channels + channel;
            resultData[resIndex] = m_data[sourceIndex];
        }
    }
    return res;
}

const unsigned char *Image::data() const {
    return m_data;
}

unsigned char *Image::data() {
    return m_data;
}

int Image::rows() const {
    return m_rows;
}

int Image::cols() const {
    return m_cols;
}

int Image::total() const {
    return m_rows * m_cols * m_channels;
}

int Image::channels() const {
    return m_channels;
}

unsigned char &Image::at(int index) {
    assert(index>=0 && index<m_rows * m_cols*m_channels);
    return m_data[index];
}

const unsigned char &Image::at(int index) const {
    assert(index >= 0 && index < (m_rows * m_cols * m_channels));
    return m_data[index];
}


Image Image::zeros(int rows, int cols, int channels) {
    Image res(rows, cols, channels);
    std::fill(res.data(), res.data() + (rows * cols * channels), 0);
    return res;
}

Image Image::values(int rows, int cols, int channels, unsigned char value) {
    Image res(rows, cols, channels);
    std::fill(res.data(), res.data() + (rows * cols * channels), value);
    return res;
}

void Image::Mirror(MirrorType type) const {
    if (type == MirrorType::Vertical) {
        // Отражение по вертикали (по строкам)
        for (int row = 0; row < m_rows / 2; ++row) {
            for (int col = 0; col < m_cols; ++col) {
                for (int ch = 0; ch < m_channels; ++ch) {
                    size_t topIndex = (row * m_cols + col) * m_channels + ch;
                    size_t bottomIndex = ((m_rows - 1 - row) * m_cols + col) * m_channels + ch;
                    std::swap(m_data[topIndex], m_data[bottomIndex]);
                }
            }
        }
    } else {
        if (type == MirrorType::Horizontal) {
            for (int row = 0; row < m_rows; ++row) {
                for (int col = 0; col < m_cols / 2; ++col) {
                    for (int ch = 0; ch < m_channels; ++ch) {
                        size_t leftIndex = (row * m_cols + col) * m_channels + ch;
                        size_t rightIndex = (row * m_cols + (m_cols - 1 - col)) * m_channels + ch;
                        std::swap(m_data[leftIndex], m_data[rightIndex]);
                    }
                }
            }
        }
    }
}

/*void Image::Rotate(double angle) {
    assert(m_data != nullptr);
    while (angle < 0.0) {
        angle += 360.0;
    }
    while (angle >= 360.0) {
        angle -= 360.0;
    }
}*/

size_t Image::countRef() const {
    if (m_refCount) {
        return *m_refCount;
    }
    return 0;
}
