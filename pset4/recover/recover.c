#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    // save input filename
    char *infile = argv[1];
    
    // open raw file
    FILE *fileptr = fopen(infile, "r");
    if (fileptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    // define 512 byte container
    uint8_t block[512];
    
    // initialize image counter
    int counter = 0;
    
    // loop until EOF (when fread will not return 512)
    while (fread(&block, 1, 512, fileptr) == 512)
    {
        // check if the block is the start of a jpeg
        if (block[0] == 0xff &&
            block[1] == 0xd8 &&
            block[2] == 0xff &&
            (block[3] & 0xf0) == 0xe0)
        {
            // create string with counter, and store in filename
            char filename[8];
            sprintf(filename, "%03i.jpg", counter++);
            
            // create and open new jpeg
            FILE *imgptr = fopen(filename, "w");
            if (imgptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                return 2;
            }
            
            // write first block to the new jpeg
            fwrite(&block, 512, 1, imgptr);
            
            // continue reading the following blocks until a new jpeg is detected
            int jpeg_complete;
            do
            {
                // read the block from the raw file. if jpeg_complete != 512 it has reached EOF
                jpeg_complete = fread(&block, 1, 512, fileptr);
                // check if recently read block is the start of a new jpeg
                if ((block[0] == 0xff &&
                    block[1] == 0xd8 &&
                    block[2] == 0xff &&
                    (block[3] & 0xf0) == 0xe0) || jpeg_complete != 512)
                {
                    // return pointer to the start of the block, and jump out of loop
                    fseek(fileptr, -512, SEEK_CUR);
                    jpeg_complete = 0;
                }
                else
                {
                    // write to the new jpeg
                    fwrite(&block, 512, 1, imgptr);
                }
                
            }
            while (jpeg_complete == 512);
            
            // close jpeg file
            fclose(imgptr);
        }
    }
    
    // close raw file
    fclose(fileptr);
    
    return 0;
}