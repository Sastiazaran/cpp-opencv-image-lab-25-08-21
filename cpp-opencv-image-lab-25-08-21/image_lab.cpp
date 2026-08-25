// cpp-opencv-image-lab-25-08-21
// Laboratorio de procesamiento de imagenes con OpenCV (21 de agosto de 2025)
// OpenCV image processing lab (August 21, 2025)

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

namespace {

const int WAIT_MS = 0; // Presiona una tecla para continuar / Press any key to continue

// Muestra una ventana y espera / Show a window and wait for a key press
void showResult(const string& windowName, const Mat& image)
{
    imshow(windowName, image);
    cout << "  -> Ventana: \"" << windowName << "\" (presiona una tecla)" << endl;
    waitKey(WAIT_MS);
}

// Recorta dos imagenes al area comun minima / Crop two images to their common minimum size
void cropToCommonSize(const Mat& image1, const Mat& image2, Mat& cropped1, Mat& cropped2)
{
    const int commonRows = min(image1.rows, image2.rows);
    const int commonCols = min(image1.cols, image2.cols);

    cropped1 = image1(Rect(0, 0, commonCols, commonRows)).clone();
    cropped2 = image2(Rect(0, 0, commonCols, commonRows)).clone();
}

// --- Tecnicas originales corregidas / Fixed original techniques ---

Mat blendAverage(const Mat& image1, const Mat& image2)
{
    Mat img1, img2;
    cropToCommonSize(image1, image2, img1, img2);

    Mat result(img1.rows, img1.cols, CV_8U);
    for (int row = 0; row < img1.rows; ++row)
    {
        for (int col = 0; col < img1.cols; ++col)
        {
            result.at<uchar>(row, col) = static_cast<uchar>(
                (img1.at<uchar>(row, col) + img2.at<uchar>(row, col)) / 2);
        }
    }
    return result;
}

Mat brightenImage(const Mat& source, int amount)
{
    Mat result = source.clone();
    for (int row = 0; row < result.rows; ++row)
    {
        for (int col = 0; col < result.cols; ++col)
        {
            const int value = result.at<uchar>(row, col) + amount;
            result.at<uchar>(row, col) = static_cast<uchar>(min(value, 255));
        }
    }
    return result;
}

// Gradiente vertical: de image2 (arriba) a image1 (abajo)
// Vertical gradient: image2 at top, image1 at bottom
Mat blendVerticalGradient(const Mat& image1, const Mat& image2)
{
    Mat img1, img2;
    cropToCommonSize(image1, image2, img1, img2);

    Mat result(img1.rows, img1.cols, CV_8U);
    const float rowStep = 1.0f / static_cast<float>(img1.rows);

    float weightImage1 = 0.0f;
    float weightImage2 = 1.0f;

    for (int row = 0; row < img1.rows; ++row)
    {
        weightImage1 += rowStep;
        weightImage2 -= rowStep;

        for (int col = 0; col < img1.cols; ++col)
        {
            const float blended =
                weightImage1 * img1.at<uchar>(row, col) +
                weightImage2 * img2.at<uchar>(row, col);
            result.at<uchar>(row, col) = static_cast<uchar>(blended);
        }
    }
    return result;
}

// Gradiente horizontal: de image2 (izquierda) a image1 (derecha)
// Horizontal gradient: image2 at left, image1 at right
Mat blendHorizontalGradient(const Mat& image1, const Mat& image2)
{
    Mat img1, img2;
    cropToCommonSize(image1, image2, img1, img2);

    Mat result(img1.rows, img1.cols, CV_8U);
    const float colStep = 1.0f / static_cast<float>(img1.cols);

    for (int col = 0; col < img1.cols; ++col)
    {
        const float weightImage1 = colStep * static_cast<float>(col + 1);
        const float weightImage2 = 1.0f - weightImage1;

        for (int row = 0; row < img1.rows; ++row)
        {
            const float blended =
                weightImage1 * img1.at<uchar>(row, col) +
                weightImage2 * img2.at<uchar>(row, col);
            result.at<uchar>(row, col) = static_cast<uchar>(blended);
        }
    }
    return result;
}

// --- Nuevas tecnicas educativas / New educational techniques ---

Mat applyGaussianBlur(const Mat& source, int kernelSize)
{
    Mat result;
    GaussianBlur(source, result, Size(kernelSize, kernelSize), 0);
    return result;
}

Mat applyCannyEdges(const Mat& source, int lowThreshold, int highThreshold)
{
    Mat result;
    Canny(source, result, lowThreshold, highThreshold);
    return result;
}

Mat applyBinaryThreshold(const Mat& source, int thresholdValue)
{
    Mat result;
    threshold(source, result, thresholdValue, 255, THRESH_BINARY);
    return result;
}

Mat applyAdaptiveThreshold(const Mat& source)
{
    Mat result;
    adaptiveThreshold(
        source,
        result,
        255,
        ADAPTIVE_THRESH_GAUSSIAN_C,
        THRESH_BINARY,
        11,
        2);
    return result;
}

Mat applyMorphology(const Mat& source, int operation, int kernelSize)
{
    Mat result;
    const Mat element = getStructuringElement(MORPH_RECT, Size(kernelSize, kernelSize));

    if (operation == 0)
    {
        erode(source, result, element);
    }
    else
    {
        dilate(source, result, element);
    }
    return result;
}

Mat applyHistogramEqualization(const Mat& source)
{
    Mat result;
    equalizeHist(source, result);
    return result;
}

Mat applySobelEdges(const Mat& source)
{
    Mat gradX;
    Mat gradY;
    Mat absGradX;
    Mat absGradY;
    Mat result;

    Sobel(source, gradX, CV_16S, 1, 0, 3);
    Sobel(source, gradY, CV_16S, 0, 1, 3);
    convertScaleAbs(gradX, absGradX);
    convertScaleAbs(gradY, absGradY);
    addWeighted(absGradX, 0.5, absGradY, 0.5, 0, result);
    return result;
}

Mat applyLaplacianEdges(const Mat& source)
{
    Mat laplacian;
    Mat result;
    Laplacian(source, laplacian, CV_16S, 3);
    convertScaleAbs(laplacian, result);
    return result;
}

Mat applyResize(const Mat& source, double scale)
{
    Mat result;
    resize(source, result, Size(), scale, scale, INTER_LINEAR);
    return result;
}

Mat applyRotation(const Mat& source, double angleDegrees)
{
    const Point2f center(source.cols / 2.0f, source.rows / 2.0f);
    const Mat rotationMatrix = getRotationMatrix2D(center, angleDegrees, 1.0);
    Mat result;
    warpAffine(source, result, rotationMatrix, source.size());
    return result;
}

Mat convertBgrToHsv(const Mat& colorImage)
{
    Mat hsvImage;
    cvtColor(colorImage, hsvImage, COLOR_BGR2HSV);
    return hsvImage;
}

Mat drawContours(const Mat& source)
{
    Mat binary;
    threshold(source, binary, 127, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    Mat result;
    cvtColor(source, result, COLOR_GRAY2BGR);
    drawContours(result, contours, -1, Scalar(0, 255, 0), 2);
    return result;
}

Mat applySharpenFilter(const Mat& source)
{
    Mat result;
    const Mat kernel = (Mat_<float>(3, 3) <<
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    filter2D(source, result, CV_8U, kernel);
    return result;
}

Mat applyEmbossFilter(const Mat& source)
{
    Mat result;
    const Mat kernel = (Mat_<float>(3, 3) <<
        -2, -1, 0,
        -1, 1, 1,
        0, 1, 2);
    filter2D(source, result, CV_8U, kernel);
    return result;
}

void runSection(const string& title)
{
    cout << "\n=== " << title << " ===" << endl;
}

} // namespace

int main()
{
    cout << "Laboratorio OpenCV - 25-08-21 (21 de agosto de 2025)" << endl;
    cout << "OpenCV Image Processing Lab - August 21, 2025" << endl;

    const string pathPato = samples::findFile("pato.jpg");
    const string pathTigre = samples::findFile("tigre.png");
    const string pathEminem = samples::findFile("eminem.jpg");
    const string pathRola = samples::findFile("rola.jpg");

    const Mat grayPato = imread(pathPato, IMREAD_GRAYSCALE);
    const Mat grayTigre = imread(pathTigre, IMREAD_GRAYSCALE);
    const Mat grayEminem = imread(pathEminem, IMREAD_GRAYSCALE);
    const Mat colorRola = imread(pathRola, IMREAD_COLOR);

    if (grayPato.empty() || grayTigre.empty() || grayEminem.empty() || colorRola.empty())
    {
        cerr << "Error: no se pudieron cargar las imagenes de muestra." << endl;
        cerr << "Error: could not load sample images." << endl;
        return 1;
    }

    // --- Tecnicas originales / Original techniques ---
    runSection("1. Imagenes originales / Original images");
    showResult("01 - Pato (gris)", grayPato);
    showResult("02 - Tigre (gris)", grayTigre);

    runSection("2. Mezcla promedio / Average blend");
    showResult("03 - Mezcla promedio", blendAverage(grayPato, grayTigre));

    runSection("3. Aclarar imagen / Brighten image");
    showResult("04 - Pato aclarado (+80)", brightenImage(grayPato, 80));

    runSection("4. Gradiente vertical / Vertical gradient blend");
    showResult("05 - Gradiente vertical", blendVerticalGradient(grayPato, grayTigre));

    runSection("5. Gradiente horizontal / Horizontal gradient blend");
    showResult("06 - Gradiente horizontal", blendHorizontalGradient(grayPato, grayTigre));

    // --- Nuevas tecnicas / New techniques ---
    runSection("6. Desenfoque gaussiano / Gaussian blur");
    showResult("07 - Gaussian blur", applyGaussianBlur(grayEminem, 15));

    runSection("7. Deteccion de bordes Canny / Canny edge detection");
    showResult("08 - Canny edges", applyCannyEdges(grayEminem, 80, 160));

    runSection("8. Umbral binario / Binary threshold");
    showResult("09 - Binary threshold", applyBinaryThreshold(grayEminem, 127));

    runSection("9. Umbral adaptativo / Adaptive threshold");
    showResult("10 - Adaptive threshold", applyAdaptiveThreshold(grayEminem));

    runSection("10. Morfologia: erosion y dilatacion / Morphology");
    showResult("11 - Erosion", applyMorphology(grayEminem, 0, 3));
    showResult("12 - Dilatacion", applyMorphology(grayEminem, 1, 3));

    runSection("11. Equalizacion de histograma / Histogram equalization");
    showResult("13 - Histogram equalization", applyHistogramEqualization(grayEminem));

    runSection("12. Bordes Sobel y Laplaciano / Sobel and Laplacian edges");
    showResult("14 - Sobel edges", applySobelEdges(grayEminem));
    showResult("15 - Laplacian edges", applyLaplacianEdges(grayEminem));

    runSection("13. Redimensionar y rotar / Resize and rotate");
    showResult("16 - Resize 50%", applyResize(grayPato, 0.5));
    showResult("17 - Rotate 30 deg", applyRotation(grayPato, 30.0));

    runSection("14. Espacio de color BGR a HSV / BGR to HSV conversion");
    showResult("18 - BGR to HSV (rola.jpg)", convertBgrToHsv(colorRola));

    runSection("15. Deteccion de contornos / Contour detection");
    showResult("19 - Contours", drawContours(grayPato));

    runSection("16. Filtros sharpen y emboss / Sharpen and emboss filters");
    showResult("20 - Sharpen filter", applySharpenFilter(grayTigre));
    showResult("21 - Emboss filter", applyEmbossFilter(grayTigre));

    cout << "\nFin del laboratorio. Cierra las ventanas o presiona una tecla." << endl;
    cout << "Lab complete. Close windows or press a key." << endl;
    destroyAllWindows();
    return 0;
}
