#include <image.h>
#include <gtest/gtest.h>

TEST(ImageTest, BasicTest) {
    Image img(4, 5, 3);  // 4 строки, 5 столбцов, 3 канала (например, RGB)
    EXPECT_EQ(img.rows(), 4);
    EXPECT_EQ(img.cols(), 5);
    EXPECT_EQ(img.channels(), 3);
    EXPECT_EQ(img.total(), 4 * 5 * 3);
    EXPECT_EQ(img.countRef(), 1);


    // Проверим, что все пиксели инициализированы нулями
    for (int i = 0; i < img.total(); ++i) {
        EXPECT_EQ(img.at(i), 0);
    }
}

TEST(ImageTest, CopyTest) {
    Image img1(2, 2, 3);
    img1.at(0) = 1;
    img1.at(1) = 2;
    img1.at(2) = 3;
    img1.at(3) = 4;

    Image img2 = img1;
    EXPECT_EQ(img1.countRef(), 2);
    EXPECT_EQ(img2.countRef(), 2);

    for (int i = 0; i < img1.total(); ++i) {
        EXPECT_EQ(img1.at(i), img2.at(i));
    }
}

// Тест на извлечение строки и столбца
TEST(ImageTest, RowAndColTest) {
    Image img(3, 3, 1);
    for (int i = 0; i < img.total(); i++) {
        img.at(i) = static_cast<unsigned char>(i);
    }

    // извлечем вторую строку (y = 1)
    Image rowImg = img.row(1);
    EXPECT_EQ(rowImg.rows(), 1);
    EXPECT_EQ(rowImg.cols(), 3);
    for (int col = 0; col < 3; ++col) {
        EXPECT_EQ(rowImg.at(col), img.at(1 * 3 + col));
    }

    // Извлечем второй столбец (x = 1)
    Image colImg = img.col(1);
    EXPECT_EQ(colImg.rows(), 3);
    EXPECT_EQ(colImg.cols(), 1);
    for (int row = 0; row < 3; ++row) {
        EXPECT_EQ(colImg.at(row), img.at(row * 3 + 1));
    }
}

// Тест на отражение изображения
TEST(ImageTest, MirrorMethod) {
    Image img(2, 3, 1);
    for (int i = 0; i < img.total(); i++) {
        img.at(i) = static_cast<unsigned char>(i);
    }

    Image imgVertical = img.clone();
    imgVertical.Mirror(MirrorType::Vertical);
    for (int col = 0; col < img.cols(); col++) {
        EXPECT_EQ(imgVertical.at(col), img.at(1 * img.cols() + col));
        EXPECT_EQ(imgVertical.at(img.cols() + col), img.at(col));
    }

    Image imgHorizontal = img.clone();
    imgHorizontal.Mirror(MirrorType::Horizontal);
    for (int row = 0; row < img.rows(); row++) {
        for (int col = 0; col < img.cols(); col++) {
            int origIndex = row * img.cols() + col;
            int mirroredIndex = row * img.cols() + (img.cols() - 1 - col);
            EXPECT_EQ(imgHorizontal.at(origIndex), img.at(mirroredIndex));
        }
    }
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}