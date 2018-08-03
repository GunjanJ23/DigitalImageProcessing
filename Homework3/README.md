## The following steps will guide you to execute the files that are contained in Homework 3 folder.



1.Unzip the folder on your system.

2.The input images on which the computation is performed must be present in the current folder.

3.Open terminal. Do ```cd address of the folder```.
  
4.Type 'make'. Press Enter.

5.Now write: 

```
a.exe <inputfile.raw><outputfile.raw><bytesPerPixel><imageWidth><imageHeight>
```

Only in case: Mix noise in color image along with PSNR

```
Write: <inputfile.raw><outputfileofdenoisedimage.raw> <bytesPerPixel><imageWidth <imageHeight> <originalimage>
```

Only in case of Stitching

```
Write: <inputfile.raw> <middleFile.raw> <rightFile.raw> <outputFile.raw> <bytesPerPixel>
```

Only in case of texture classification and Image Segmentation

```
//g++ -std=c++0x 
```

6.Then Choose one:

- Color to Grayscale Conversion

- CMY conversion

- Bilinear interpolation

- Histogram equalization

- Image Filtering : Creating Oil Painting Effect

- Image Filtering :Creating Film Special Effect

- Mix noise in color image along with PSNR

- Warping

- Reconstruction of Warped Image

- Homography Transformation

- Stitching

- Dithering

- Dithering with four intensity values

- Error Diffusion

- Shrinking

- Thinning/ Skeletonizing

- Counting Game

- Sobel Operator

- LoG Operator

- Texture Classification

- ImageSegmentation

7.Enter the one you want to implement. Press Enter. The output will be saved in the current folder.

8.You can view the output image using ImageJ.
