import os

files = ['artificial.ppm', 'big_building.ppm', 'big_tree.ppm', 'bridge.ppm', 'cathedral.ppm', 'deer.ppm', 'fireworks.ppm', 'flower_foveon.ppm', 'hdr.ppm', 'leaves_iso_200.ppm', 'leaves_iso_1600.ppm', 'nightshot_iso_100.ppm', 'nightshot_iso_1600.ppm', 'spider_web.ppm']
width = ['3072', '7216', '6088', '2749', '2000', '4043', '3136', '2268', '3072', '3008', '3008', '3136', '3136', '4256']
height = ['2048', '5412', '4550', '4049', '3008', '2641', '2352', '1512', '2048', '2000', '2000', '2352', '2352', '2848']

for i in range(0, len(files)):
    output = files[i].replace('ppm', 'jpeg')
    os.system('./base/compress_base ./images/rgb8bit/' + files[i] + ' ' + width[i] + ' ' + height[i] + ' 3 1 ./images/testj/' + output)
    os.system('./mmap-wrapper/compress_mmap ./images/rgb8bit/' + files[i] + ' ' + width[i] + ' ' + height[i] + ' 3 1 ./images/testj/mmap_' + output)