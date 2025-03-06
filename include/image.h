#ifndef IMAGE_H
#define IMAGE_H
#include <cstddef>

enum class MirrorType {
  Vertical,
  Horizontal
};

class Image {

public:
    Image();
    Image(int rows, int cols, int channels);
    Image(int rows, int cols, int channels, unsigned char* data);

    //конструктор копий. Данный конструктор не выделяет новую память, а применяет технику reference counting. Сложность создания копии объекта O(1).
    Image(const Image& image);
    virtual ~Image();

    //оператор присваивания. В некотором роде похож на конструктор. Т.е. не выделяет новую память, а применяет технику reference counting. Сложность данной операции O(1).
    Image& operator=(const Image& image);

    // Вернуть клон изборажения, создает полную копию изображения. Выделяет новую память и производит копирование пикселей. Сложность операции O(n), где n - количество пикселей.
    Image clone() const;
    //Скопировать изображение.
    void copyTo(Image& image);
    void create(int rows, int cols, int channels);
    bool empty() const;

    //декрементирует счетчик ссылок и в случае необходимости освобождает ресурсы (память).
    void release();

//возвращает новое изображение, которое содержит один столбец по индексу x.
    Image col(int x) const;

//аналог метода col(int x) для строк.
    Image row(int y) const;

    const unsigned char* data() const;
    unsigned char* data();

    int rows() const;
    int cols() const;
    int total() const;
    int channels() const;

    //Вернуть ЧАСТЬ пикселя
    unsigned char& at(int index);
    const unsigned char& at(int index) const;

//создает новое изображение, которое инициализируется нулями.
    Image zeros(int rows, int cols, int channels);

//создает новое изображение, которое инициализируется значением value.
    Image values(int rows, int cols, int channels, unsigned char value);

    //Отразить изображение по вертикали или по горизонтали
    void Mirror(MirrorType type) const;

    //Повернуть на угол кратный 90
    //void Rotate(double angle);

    //Возвращает текущее количество ссылок на изображение.
    //Т.е. количество объектов, которые ссылаются на данное изображение. Этот метод нужен для unit test'ов.
    size_t countRef() const;

private:
    int m_rows; // член класса (member variable)
    int m_cols;
    int m_channels;
    unsigned char* m_data; // массив символов изображений
    size_t *m_refCount;
   // double angle;
};

#endif //IMAGE_H
