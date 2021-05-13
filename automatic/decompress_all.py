import os

files = ['artificial.jpeg', 'big_building.jpeg', 'big_tree.jpeg', 'bridge.jpeg', 'cathedral.jpeg', 'deer.jpeg', 'fireworks.jpeg', 'flower_foveon.jpeg', 'hdr.jpeg', 'leaves_iso_200.jpeg', 'leaves_iso_1600.jpeg', 'nightshot_iso_100.jpeg', 'nightshot_iso_1600.jpeg', 'spider_web.jpeg']

for i in range(0, len(files)):
    output = files[i].replace('jpeg', 'ppm')
    os.system('./base/decompress_base ./images/jpeg_rgb8bit/' + files[i] + ' ./images/test/' + output)
    os.system('./mmap-wrapper/decompress_mmap ./images/jpeg_rgb8bit/' + files[i] + ' ./images/test/' + output)