import sys, os, shutil

source_dir = 'stereo'

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print 'usage copy.py <intervals.txt> <dest_dir>'
        exit()
    input_file = sys.argv[1]
    out_dir = sys.argv[2]
    for string in open(input_file):
        st, end = map(int, string.split('_'))
        for i in xrange(st, end + 1):
            shutil.copy2(os.path.join(source_dir, '%05d.jpg' % i), os.path.join(out_dir, '%05d.jpg' % i))
            #shutil.copy2(os.path.join(source_dir, '%05d-left.jpg' % st), os.path.join(out_dir, '%05d-left.jpg'))
            #shutil.copy2(os.path.join(source_dir, '%05d-right.jpg' % st), os.path.join(out_dir, '%05d-right.jpg'))
             
