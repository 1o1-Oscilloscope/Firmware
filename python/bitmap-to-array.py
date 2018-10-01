import os
import numpy as np
import cv2

if __name__ == '__main__':
	screen_width = 96
	screen_height = 64
	scale = 6
	
	picture_path = 'graphics_logo.png'
	grey = cv2.imread(picture_path, 0)
	
	if grey is None:
		print "Error {} is not a valid picture!".format(picture_path)
		exit()
	
	grey = cv2.resize(grey, (screen_width, screen_height))
	threshold = cv2.adaptiveThreshold(grey, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)
	binary = threshold < 127
	
	rot_bin = np.rot90(binary, 1, (1, 0))
	image = list()
	
	for row in rot_bin:
		bin_string = "".join(["1" if i else "0" for i in row])
		split_string = [bin_string[i:i + 8] for i in range(0, len(bin_string), 8)]
		int_arr = [int(i, 2) for i in split_string]
		image.append(list(int_arr))
		print " ".join(["*" if i else " " for i in row])
	final_arr = np.rot90(np.asarray(image, dtype=np.uint8), 1, (0, 1)).transpose()
	
	template = ''
	with open("packed_graphics.c.template", "r") as f:
		template = f.read()
	
	output = template.format(",".join([str(i) for i in final_arr.flat]), len(final_arr), len(final_arr[0]))
	
	with open("../graphics/packed_graphics.c", "w") as f:
		f.write(output)
