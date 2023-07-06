#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat convolución(Mat imagen, Mat kernel)
{
    Mat resultado;
    imagen.copyTo(resultado);

    // borde
    int border = kernel.rows / 2;
    copyMakeBorder(imagen, imagen, border, border, border, border, BORDER_REPLICATE);

    for (int c = 0; c < imagen.channels(); c++)
    {
        for (int i = border; i < imagen.rows - border; i++)
        {
            for (int j = border; j < imagen.cols - border; j++)
            {
                float suma = 0.0;
                for (int k = -border; k <= border; k++)
                {
                    for (int l = -border; l <= border; l++)
                    {
                        suma += imagen.ptr<Vec3b>(i + k)[j + l][c] * kernel.ptr<float>(k + border)[l + border];
                    }
                }
                resultado.ptr<Vec3b>(i - border)[j - border][c] = saturate_cast<uchar>(suma);
            }
        }
    }

    return resultado;
}

Mat gris(Mat imagen)
{
    Mat resultado2 = Mat::zeros(imagen.size(), CV_8UC1);
    for (int i = 0; i < imagen.rows; i++)
    {
        for (int j = 0; j < imagen.cols; j++)
        {
            Vec3b pixel = imagen.ptr<Vec3b>(i)[j];
            uchar b = pixel[0];
            uchar g = pixel[1];
            uchar r = pixel[2];
            resultado2.ptr<uchar>(i)[j] = 0.299 * b + 0.587 * g + 0.114 * r;

        }
    }
    return resultado2;
}

Mat puntos(Mat fuerza, Mat angulo, float umbral)
{
    Mat resultado3 = Mat::zeros(fuerza.size(), CV_32F);

    for (int i = 1; i < fuerza.rows - 1; i++)
    {
        for (int j = 1; j < fuerza.cols - 1; j++)
        {
            float theta = angulo.ptr<float>(i)[j];
            float vecino_i = 0.0, vecino_j = 0.0;

            if (theta >= 0 && theta < 22.5)
            {
                vecino_i = fuerza.ptr<float>(i)[j + 1];
                vecino_j = fuerza.ptr<float>(i)[j - 1];
            }
            else if (theta >= 22.5 && theta < 67.5)
            {
                vecino_i = fuerza.ptr<float>(i + 1)[j - 1];
                vecino_j = fuerza.ptr<float>(i - 1)[j + 1];
            }
            else if (theta >= 67.5 && theta < 112.5)
            {
                vecino_i = fuerza.ptr<float>(i + 1)[j];
                vecino_j = fuerza.ptr<float>(i - 1)[j];
            }
            else
            {
                vecino_i = fuerza.ptr<float>(i - 1)[j - 1];
                vecino_j = fuerza.ptr<float>(i + 1)[j + 1];
            }

            if (fuerza.ptr<float>(i)[j] > umbral)
                resultado3.ptr<float>(i)[j] = fuerza.ptr<float>(i)[j];
        }
    }

    return resultado3;
}

int main(int argc, char** argv)
{
    Mat imagen = imread("C:/Users/rasz2/Downloads/R.jpeg");

    Mat kernel = (Mat_<float>(5, 5) << 2, 4, 5, 4, 2, 4, 9, 12, 9, 4, 5, 12, 15, 12, 5, 4, 9, 12, 9, 4, 2, 4, 5, 4, 2) / 159.0;

    Mat gauss = convolución(imagen, kernel);

    Mat gaussGris = gris(gauss);

    Mat gradienteX, gradienteY;
    int profundidad = CV_32F;
    Sobel(gaussGris, gradienteX, profundidad, 1, 0);
    Sobel(gaussGris, gradienteY, profundidad, 0, 1);

    Mat fuerzagradiente;
    magnitude(gradienteX, gradienteY, fuerzagradiente);

    Mat direcciongradiente;
    phase(gradienteX, gradienteY, direcciongradiente, true);

    Mat bordes = puntos(fuerzagradiente, direcciongradiente, 100.0);

    imshow("Original", imagen);
    imshow("Fuerza gradiente", fuerzagradiente);
    imshow("Direccion gradiente", direcciongradiente);
    imshow("Bordes", bordes);
    waitKey(0);

    return 0;
}
