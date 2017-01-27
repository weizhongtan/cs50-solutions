/**
 * Resizes an image by a floating point value between 0.0 and 100.0
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    float n = atof(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // save infile data for iterations later
    LONG old_biHeight = bi.biHeight;
    LONG old_biWidth = bi.biWidth;
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine new width and height according to scaling
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    
    // determine padding that needs to be added to outfile on each scanline
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine new image size values with and without headers
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + new_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int out_rows = 0;
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_biHeight); i < biHeight; i++)
    {
        // keep track of outfile pixel number
        int out_cols = 0;
        // define array which will contain data for new row in outfile
        RGBTRIPLE row[bi.biWidth];
        for (int j = 0; j < old_biWidth; j++)
        {
            RGBTRIPLE triple;
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // n >= 1 is a scaling up, therefore the 
            if (n >= 1)
            {
                // determine the number of times this pixel needs to be copied to the outfile
                while (out_cols / n < j + 1)
                {
                    // add data to the row array
                    row[out_cols] = triple;
                    out_cols++;
                }
            }
            else
            {
                if (j == 0)
                {
                    out_cols = -1;
                }
                if ((int) (j * n) != out_cols)
                {
                    // add data to the row array
                    out_cols = j * n;
                    row[out_cols] = triple;
                }
            }
        }

        // skip over padding, if any, reacy for the next scanline read on the next iteration of i
        fseek(inptr, old_padding, SEEK_CUR);
        
        /*
        *  Now that our entire row from the infile has been scaled
        *  appropriately and stored in the row array, we need to
        *  determine how many times this row need to be written
        *  into the outfile
        */
        
        // determine how many rows need to be written
        if (n >= 1)
        {
            // determine the number of times this row needs to be copied to the outfile
            while (out_rows / n < i + 1)
            {
                // iterate across row array and write each triple to the outfile
                for (int k = 0; k < bi.biWidth; k++)
                {
                    fwrite(&row[k], sizeof(RGBTRIPLE), 1, outptr);
                }
                
                // add new padding requirement to outfile
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr);
                }
                
                out_rows++;
            }
        }
        else
        {
            if (i == 0)
            {
                out_rows = -1;
            }
            if ((int) (i * n) != out_rows)
            {
                // iterate across row array and write each triple to the outfile
                for (int k = 0; k < bi.biWidth; k++)
                {
                    fwrite(&row[k], sizeof(RGBTRIPLE), 1, outptr);
                }
                
                // add new padding requirement to outfile
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr);
                }
                
                out_rows = i * n;
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
