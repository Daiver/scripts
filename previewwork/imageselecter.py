import cv2, os, sys, cv
import numpy as np
#83 81 27 85 86
dir_name = 'photos'
out_file_name = 'out.txt'

mark = -1
if __name__ == '__main__':
    if len(sys.argv) < 3:
        print 'USAGE: imageselector.py <source_dir> <dest_file>'
        exit()
    dir_name = sys.argv[1]
    out_file_name = sys.argv[2]
    files = os.listdir(dir_name)
    files.sort()
    i = 0
    img = None
    while True:
        fname = files[i]
        try:
            new_img = cv2.imread(os.path.join(dir_name, fname))
            img = new_img
        except:
            print 'cannot read file'

        if  img == None:
            img = np.zeros((10, 10))
            print 'cannot read file'

        img = cv2.resize(img, (250, 250))

        text_image = np.zeros((50, 200))
        cv2.putText(img, "%d mark %d" % (i, mark), (30, 30), 2, 0.7, (0, 0, 255))
        #cv2.imshow("text", text_image)
        cv2.imshow("", img)
        key = cv2.waitKey() % 0x100
        if key == 83: #right
            i += 1
        elif key == 81: #left
            i -= 1
        elif key == 85: #pg up
            i -= 10
        elif key == 86: #pg down
            i += 10
        elif key == 27: break #esc
        elif key == 32: # space
            if mark == -1: 
                mark = i
            else:
                with open(out_file_name, 'a') as f: f.write('%d_%d\n' % (mark, i) )
                mark = -1
        elif key == 8: mark = -1 #backspace
        if i < 0: i = 0
        if i >= len(files): i = len(files) - 1
