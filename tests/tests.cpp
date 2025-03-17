#include <image.h>
#include <gtest/gtest.h>

TEST(ImageTest, constrDefault) {
    Image const img;
    EXPECT_TRUE(img.empty());
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.channels(), 0);
    EXPECT_EQ(img.countRef(), 0);
}


TEST(ImageTest, sizeTest) {
    Image img(3, 4, 2);
    EXPECT_EQ(img.rows(), 3);
    EXPECT_EQ(img.cols(), 4);
    EXPECT_EQ(img.channels(), 2);
    EXPECT_EQ(img.total(), 3 * 4 * 2);
    EXPECT_EQ(img.countRef(), 1);

    for (int i = 0; i < img.total(); ++i) {
        EXPECT_EQ(img.at(i), 0);
    }
}

TEST(ImageTest, dataTest) {
    unsigned char data[] = {1, 2, 3, 4, 5, 6};
    Image img(2, 3, 1, data);
    EXPECT_EQ(img.rows(), 2);
    EXPECT_EQ(img.cols(), 3);
    EXPECT_EQ(img.channels(), 1);
    EXPECT_EQ(img.total(), 6);

    for (int i = 0; i < img.total(); ++i) {
        EXPECT_EQ(img.at(i), data[i]);
    }
}

TEST(ImageTest, copyTest) {
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

TEST(ImageTest, operatorTest) {
    Image img1(2, 2, 1);
    img1.at(0) = 1;
    img1.at(1) = 2;

    Image img2;
    img2 = img1;
    EXPECT_EQ(img1.countRef(), 2);
    EXPECT_EQ(img2.countRef(), 2);

    for (int i = 0; i < img1.total(); ++i) {
        EXPECT_EQ(img1.at(i), img2.at(i));
    }
}

TEST(ImageTest, cloneTest) {
    Image img1(2, 2, 1);
    img1.at(0) = 1;
    img1.at(1) = 2;

    Image img2 = img1.clone();
    EXPECT_EQ(img2.rows(), img1.rows());
    EXPECT_EQ(img2.cols(), img1.cols());
    EXPECT_EQ(img2.channels(), img1.channels());
    EXPECT_EQ(img2.countRef(), 1);

    for (int i = 0; i < img1.total(); ++i) {
        EXPECT_EQ(img1.at(i), img2.at(i));
    }
}

TEST(ImageTest, copyToTest) {
    Image img1(2, 2, 1);
    img1.at(0) = 1;
    img1.at(1) = 2;

    Image img2;
    img1.copyTo(img2);

    EXPECT_EQ(img2.rows(), img1.rows());
    EXPECT_EQ(img2.cols(), img1.cols());
    EXPECT_EQ(img2.channels(), img1.channels());
    EXPECT_EQ(img2.countRef(), 1);

    for (int i = 0; i < img1.total(); ++i) {
        EXPECT_EQ(img1.at(i), img2.at(i));
    }
}

TEST(ImageTest, сreateTest) {
    Image img;
    img.create(3, 3, 1);

    EXPECT_EQ(img.rows(), 3);
    EXPECT_EQ(img.cols(), 3);
    EXPECT_EQ(img.channels(), 1);
    EXPECT_FALSE(img.empty());

    for (int i = 0; i < img.total(); ++i) {
        EXPECT_EQ(img.at(i), 0);
    }
}

TEST(ImageTest, emptyTest) {
    Image img;
    EXPECT_TRUE(img.empty());

    img.create(1, 1, 1);
    EXPECT_FALSE(img.empty());
}

TEST(ImageTest, releaseTest) {
    Image img(3, 3, 1);
    EXPECT_FALSE(img.empty());

    img.release();
    EXPECT_TRUE(img.empty());
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
    EXPECT_EQ(img.channels(), 0);
}

TEST(ImageTest, atTest) {
    Image img(2, 2, 1);
    img.at(0) = 10;
    img.at(1) = 20;
    img.at(2) = 30;
    img.at(3) = 40;

    EXPECT_EQ(img.at(0), 10);
    EXPECT_EQ(img.at(1), 20);
    EXPECT_EQ(img.at(2), 30);
    EXPECT_EQ(img.at(3), 40);
}

TEST(ImageTest, colTest) {
    Image img(3, 3, 1);
    for (int i = 0; i < img.total(); ++i) {
        img.at(i) = i;
    }

    Image colImg = img.col(1);

    EXPECT_EQ(colImg.rows(), 3);
    EXPECT_EQ(colImg.cols(), 1);
    EXPECT_EQ(colImg.channels(), 1);

    for (int row = 0; row < img.rows(); ++row) {
        EXPECT_EQ(colImg.at(row), img.at(row * img.cols() + 1));
    }
}

TEST(ImageTest, rowTest) {
    Image img(3, 3, 1);
    for (int i = 0; i < img.total(); ++i) {
        img.at(i) = i;
    }

    Image rowImg = img.row(1);

    EXPECT_EQ(rowImg.rows(), 1);
    EXPECT_EQ(rowImg.cols(), 3);
    EXPECT_EQ(rowImg.channels(), 1);

    for (int col = 0; col < img.cols(); ++col) {
        EXPECT_EQ(rowImg.at(col), img.at(1 * img.cols() + col));
    }
}

TEST(ImageTest, mirrorTest) {
    Image img(3, 3, 1);
    for (int i = 0; i < img.total(); ++i) {
        img.at(i) = i;
    }

    img.Mirror(MirrorType::Vertical);

    for (int row = 0; row < img.rows(); ++row) {
        for (int col = 0; col < img.cols(); ++col) {
            int origIndex = (img.rows() - 1 - row) * img.cols() + col;
            int newIndex = row * img.cols() + col;
            EXPECT_EQ(img.at(newIndex), origIndex);
        }
    }
}

TEST(ImageTest, rotateTest) {
    unsigned char data[4 * 4 * 1] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };

    {
        Image img(4, 4, 1, data);
        img.Rotate(90);
        EXPECT_EQ(img.rows(), 4);
        EXPECT_EQ(img.cols(), 4);
        EXPECT_EQ(img.channels(), 1);

        unsigned char expectedData90[4 * 4 * 1] = {
            13, 9, 5, 1,
            14, 10, 6, 2,
            15, 11, 7, 3,
            16, 12, 8, 4
        };

        for (int i = 0; i < 4 * 4 * 1; ++i) {
            EXPECT_EQ(img.data()[i], expectedData90[i]);
        }
    }

    {
        Image img(4, 4, 1, data);
        img.Rotate(180);
        EXPECT_EQ(img.rows(), 4);
        EXPECT_EQ(img.cols(), 4);
        EXPECT_EQ(img.channels(), 1);

        unsigned char expectedData180[4 * 4 * 1] = {
            16, 15, 14, 13,
            12, 11, 10, 9,
            8, 7, 6, 5,
            4, 3, 2, 1
        };

        for (int i = 0; i < 4 * 4 * 1; ++i) {
            EXPECT_EQ(img.data()[i], expectedData180[i]);
        }
    }

    {
        Image img(4, 4, 1, data);
        img.Rotate(270);
        EXPECT_EQ(img.rows(), 4);
        EXPECT_EQ(img.cols(), 4);
        EXPECT_EQ(img.channels(), 1);

        unsigned char expectedData270[4 * 4 * 1] = {
            4, 8, 12, 16,
            3, 7, 11, 15,
            2, 6, 10, 14,
            1, 5, 9, 13
        };

        for (int i = 0; i < 4 * 4 * 1; ++i) {
            EXPECT_EQ(img.data()[i], expectedData270[i]);
        }
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}