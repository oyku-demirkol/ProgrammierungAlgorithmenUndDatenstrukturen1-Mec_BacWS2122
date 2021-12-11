#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Allocate memory for an image of specified dimensions
void allocimage (unsigned char ***p_image, int nx, int ny)
{
    if (nx==0 || ny==0) return;
    // Allocate memory for pointers to columns
    unsigned char **image;
    image = (unsigned char**) malloc (nx * sizeof (unsigned char*));
    // Allocate the actual memory for data column by column
    for (int i=0; i<nx; ++i)
        image[i] = (unsigned char*) malloc (ny * sizeof (unsigned char));
    // Return root pointer of 2D array via pointer parameter
    *p_image = image;
    return;
}

// Free memory structure of an image
void freeimage (unsigned char **image, int nx, int ny)
{
    if (nx==0 || ny==0) return;
    // First, release columns
    for (int i=0; i<nx; ++i)
        free (image[i]);
    // Then, release the array of pointers to the columns
    free (image);
    return;
}

// Function to get a string from user input (taken from 0307-bblsort.c)
void getstringfromuserinput (int size, char *s, const char *request)
{
    printf ("%s", request);
    fgets (s, size, stdin);
    int l = strlen(s);
    if (s[l-1] == '\n') s[l-1] = '\0';
    return;
}

// Read an image from a PGM file (binary type with magic number P5)
// Function calls allocimage for allocation of memory
void readpgm (char *s, unsigned char ***p_image, int *p_nx, int *p_ny)
{
    FILE *infile;           // Input file
    char inputline[300];    // Buffer for input lines (in header)
    int nx, ny;             // Image size
    unsigned char **image;  // Root pointer of 2D array

    // Open input file
    infile = fopen (s, "rb");
    // Check for success
    if (infile == NULL)
    {
        fprintf (stderr,
                 "readpgm: Bilddatei %s konnte nicht geoeffnet werden.\n",
                 s);
        *p_nx=0;
        *p_ny=0;
        *p_image = NULL;
        return;
    }

    // Read header
    // Check magic number in first line of header
    fgets (inputline, sizeof inputline, infile);
    if (inputline[0]!='P' || inputline[1]!='5')
    {
        fprintf (stderr,
                 "readpgm: Unbekanntes Bildformat %s, kann nur P5 verarbeiten.\n",
                 inputline);
        fclose (infile);
        *p_nx=0;
        *p_ny=0;
        *p_image = NULL;
        return;
    }
    // Skip over possible comment lines
    do
    {
        fgets (inputline, sizeof inputline, infile);
    }
    while (inputline[0]=='#');
    // Determine image dimensions
    sscanf(inputline, "%d %d", &nx, &ny);
    // Skip over last line of header (assumed to be "255\n")
    fgets (inputline, sizeof inputline, infile);

    // Allocate memory
    allocimage (&image, nx, ny);

    // Read data from binary part of image file
    for (int j=0; j<ny; ++j)
        for (int i=0; i<nx; ++i)
            image[i][j] = getc (infile);

    // Close input file
    fclose (infile);

    // Return image size and root pointer of 2D array to calling function
    // via pointer parameters
    *p_nx = nx;
    *p_ny = ny;
    *p_image = image;
    return;
}

// Write image data to a PGM file
void writepgm (char *s, unsigned char **image, int nx, int ny)
{
    FILE *outfile;            // Output file

    if (nx==0 || ny==0)
    {
        fprintf (stderr,
                 "writepgm: Bildgroesze 0, nichts geschrieben.\n");
        return;
    }

    // Open output file
    outfile = fopen (s, "wb");
    if (outfile == NULL)
    {
        fprintf (stderr,
                 "writepgm: Bilddatei %s konnte nicht geoeffnet werden.\n",
                 s);
        return;
    }

    // Write header
    fprintf (outfile, "P5\n");
    fprintf (outfile, "%d %d\n", nx, ny);
    fprintf (outfile, "255\n");

    // Write binary data
    for (int j=0; j<ny; ++j)
        for (int i=0; i<nx; ++i)
            putc (image[i][j], outfile);

    // Close file
    fclose (outfile);

    return;
}

// Function to invert an image
void invert (unsigned char **image, int nx, int ny)
{
    for (int i=0; i<nx; ++i)
        for (int j=0; j<ny; ++j)
            image[i][j] = 255 - image[i][j];

    return;
}
// Function to binarize an image
void binarize (unsigned char **image, int nx, int ny)
{
    int *t;
    printf("Schwellenwert(Threshold) t eingeben:\n"); //Konsoleneingabe
    scanf("%d",t);

    for(int i=0; i<nx; ++i)
    {
        for (int j=0; j<ny; ++j)
        {
            if(image[i][j]>= *t)
            {
                image[i][j]=255;
            }
            else
            {
                image[i][j]=0;
            }
        }
    }
    return;
}

void EinfacherGradientenoperator2 (unsigned char **image,unsigned char **gradientImage, int nx, int ny)

{


    for(int i=0; i<nx; ++i)
    {
        for (int j=0; j<ny; ++j)
        {
            if(i==0 || j==0 || i == nx-1 || j == ny-1 ) //mit Ausnahme der ersten und letzten Zeile und Spalte des Bildes
            {
                gradientImage[i][j] = 0;
            }
            else
            {
                double fx = (image[i+1][j]-image[i-1][j])/2;
                double fy  = (image[i][j+1]-image[i][j-1])/2;
                double gradientsize = sqrt(fx*fx+fy*fy); // pow(fx,2) = fx*fx
                int gradint = (int)gradientsize ; //gradientsize von double in int umzuwandeln

                if (gradint > 255 ) //Wenn dieser Wert 255 übersteigt, sollte er durch 255 ersetzt werden.
                {
                    gradint = 255;
                }
                gradientImage[i][j] = gradint ;

            }
        }
    }

    return ;
}

// Main function
int main (int argc, char* argv[])
{
    unsigned char **image;    // Pointer to hold image data
    int nx, ny;               // Variables for image dimensions

    char infilename [100];
    char outfilename [100];
    // Check whether file names are provided as command line arguments
    // Otherwise, ask user for input
    if (argc > 1)
    {
        strncpy (infilename, argv[1], 99);
        infilename[99] = '\0';
    }
    else
    {
        getstringfromuserinput (sizeof (infilename), infilename,
                                "Eingabedatei (pgm): ");
    }
    if (argc > 2)
    {
        strncpy (outfilename, argv[2], 99);
        outfilename[99] = '\0';
    }
    else
    {
        getstringfromuserinput (sizeof (outfilename), outfilename,
                                "Ausgabedatei (pgm): ");
    }


    // Read input image
    readpgm (infilename, &image, &nx, &ny);

    // Ask whether to invert the image
    printf ("Bild invertieren = 1\n");
    printf ("Bild binarisieren = 2\n");
    printf ("Bild gradient = 3\n");
    printf("Enter pls 1 , 2 or 3: \n");
    char inputline [100];
    fgets (inputline, sizeof (inputline), stdin);
    if (inputline[0] == '1' )
    {
        invert (image, nx, ny);
        // Write output image
        writepgm (outfilename, image, nx, ny);
    }
    else if(inputline[0] == '2' )
    {
        binarize (image, nx, ny);
        // Write output image
        writepgm (outfilename, image, nx, ny);
    }
    else if(inputline[0] == '3')
    {
        unsigned char **gradientImage;
        allocimage (&gradientImage, nx, ny);
        EinfacherGradientenoperator2 (image,gradientImage, nx, ny);
        writepgm(outfilename,gradientImage,nx,ny);  // Write output gradientImage
        freeimage(gradientImage,nx,ny);
    }
    // Release memory
    freeimage (image, nx, ny);


    return 0;
}


