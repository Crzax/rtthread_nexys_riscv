ffmpeg -f rawvideo -pix_fmt gray -s 128x128 -i GreyImage.dat GreyImage.bmp
ffmpeg -f rawvideo -pix_fmt rgb24 -s 128x128 -i FilterColourImage.dat FilterColourImage.bmp
