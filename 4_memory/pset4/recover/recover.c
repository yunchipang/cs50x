#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // if argc incorrect
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    else
    {
        // open memory card
        FILE *input_pointer = fopen(argv[1], "r");

        if (input_pointer == NULL)
        {
            printf("Error: cannot open %s\n", argv[1]);
            return 2;
        }

        // initialize variables
        BYTE buffer[512];
        int count = 0;
        FILE *img_pointer = NULL;
        char jpegfile[8];

        // repeat until the end of the card
        while (fread(&buffer, 512, 1, input_pointer) == 1) // detect the end of the file
        {
            // if the 512-byte block is a jpeg
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // if not the first jpeg, close previous
                if (count != 0)
                {
                    fclose(img_pointer);
                }
                sprintf(jpegfile, "%03i.jpg", count); // get filename
                img_pointer = fopen(jpegfile, "w"); // open a new file
                count++;
            }

            // if jpeg found, write to file
            if (count != 0)
            {
                fwrite(&buffer, 512, 1, img_pointer);
            }
        }

        // close both input and output files
        fclose(input_pointer);
        fclose(img_pointer);

        return 0;
    }

}