# cpp-opencv-image-lab-25-08-21

**Fecha del proyecto / Project date:** **25-08-21** (21 de agosto de 2025 / August 21, 2025)

Laboratorio educativo de procesamiento de imágenes en C++ con OpenCV. Este repositorio comenzó como un ejercicio de clase y se reorganizó para explorar técnicas clásicas de visión por computadora paso a paso.

Educational C++ image processing lab using OpenCV. This project started as a classroom exercise and was reorganized to explore classic computer vision techniques step by step.

> **Nombre sugerido en GitHub / Suggested GitHub repo name:** `cpp-opencv-image-lab-25-08-21`  
> Renombra el repositorio remoto en GitHub → Settings → General → Repository name.

## Técnicas demostradas / Techniques demonstrated

### Originales (corregidas) / Original (fixed)

| # | Técnica | Descripción |
|---|---------|-------------|
| 1 | Mezcla promedio | Combina dos imágenes píxel a píxel |
| 2 | Aclarar imagen | Suma un valor constante con saturación a 255 |
| 3 | Gradiente vertical | Transición suave de arriba a abajo entre dos imágenes |
| 4 | Gradiente horizontal | Transición suave de izquierda a derecha entre dos imágenes |

### Nuevas / New

| # | Técnica | Descripción |
|---|---------|-------------|
| 5 | Desenfoque gaussiano | Suavizado con `GaussianBlur` |
| 6 | Detección Canny | Bordes con umbral doble |
| 7 | Umbral binario | Segmentación con `threshold` |
| 8 | Umbral adaptativo | Segmentación local con `adaptiveThreshold` |
| 9 | Erosión / dilatación | Operaciones morfológicas |
| 10 | Equalización de histograma | Mejora de contraste |
| 11 | Sobel / Laplaciano | Detección de bordes por derivadas |
| 12 | Redimensionar / rotar | Transformaciones geométricas |
| 13 | BGR → HSV | Conversión de espacio de color |
| 14 | Detección de contornos | `findContours` + dibujo |
| 15 | Filtros sharpen / emboss | Convolución con kernels personalizados |

## Requisitos / Requirements

- **Windows 10/11** (x64)
- **Visual Studio 2019** (toolset v142) o compatible
- **OpenCV 4.5.1** instalado en `C:\OpenCV\`
  - Headers: `C:\OpenCV\build\include`
  - Libraries: `C:\OpenCV\build\x64\vc15\lib`
  - Debug: `opencv_world451d.lib`
  - Release: `opencv_world451.lib`

## Imágenes de muestra / Sample images

Las imágenes están en `cpp-opencv-image-lab-25-08-21/`:

| Archivo | Uso principal |
|---------|---------------|
| `pato.jpg` | Mezclas, gradientes, contornos, rotación |
| `tigre.png` | Mezclas, gradientes, filtros |
| `eminem.jpg` | Blur, bordes, umbral, morfología, histograma |
| `rola.jpg` | Conversión BGR → HSV (color) |

## Compilar y ejecutar / Build and run

1. Clona el repositorio y abre `cpp-opencv-image-lab-25-08-21.sln` en Visual Studio.
2. Selecciona la configuración **Debug | x64** (o Release | x64).
3. Verifica que OpenCV esté en `C:\OpenCV\` o ajusta las rutas en el `.vcxproj`.
4. Compila con **Build → Build Solution** (Ctrl+Shift+B).
5. Copia `opencv_world451d.dll` (Debug) o `opencv_world451.dll` (Release) junto al `.exe`, o añade `C:\OpenCV\build\x64\vc15\bin` al PATH.
6. Ejecuta el proyecto. Cada técnica muestra una ventana; presiona una tecla para avanzar.

## Estructura del proyecto / Project structure

```
cpp-opencv-image-lab-25-08-21/
├── cpp-opencv-image-lab-25-08-21.sln
└── cpp-opencv-image-lab-25-08-21/
    ├── image_lab.cpp          # Código principal
    ├── cpp-opencv-image-lab-25-08-21.vcxproj
    ├── pato.jpg
    ├── tigre.png
    ├── eminem.jpg
    └── rola.jpg
```

## Correcciones aplicadas / Fixes applied

- División entera corregida en pesos de gradiente (`1.0f / rows` en lugar de `1 / rows`)
- Gradiente horizontal usa `scols` correctamente
- Mezcla de imágenes recorta al tamaño común mínimo antes de procesar
- El aclarado ya no modifica la imagen original usada en gradientes
- Todas las ventanas de resultados están activas (sin `imshow` comentados)
- Proyecto renombrado de `25-08-21` a `cpp-opencv-image-lab-25-08-21`

## Licencia / License

Proyecto educativo. Usa y modifica libremente para aprender.
