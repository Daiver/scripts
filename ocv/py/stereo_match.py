#!/usr/bin/env python

'''
Simple example of stereo image matching and point cloud generation.

Resulting .ply file cam be easily viewed using MeshLab ( http://meshlab.sourceforge.net/ )
'''

import numpy as np
import cv2
from Queue import Queue
import numpy as np

ply_header = '''ply
format ascii 1.0
element vertex %(vert_num)d
property float x
property float y
property float z
property uchar red
property uchar green
property uchar blue
end_header
'''

def write_ply(fn, verts, colors):
    verts = verts.reshape(-1, 3)
    colors = colors.reshape(-1, 3)
    verts = np.hstack([verts, colors])
    with open(fn, 'w') as f:
        f.write(ply_header % dict(vert_num=len(verts)))
        np.savetxt(f, verts, '%f %f %f %d %d %d')

steps = [[0, 1], [1, 0], [1, 1], [-1, 0], [0, -1], [-1, 1], [1, -1], [-1, -1]]
def expand(point, mask): 
    res = []
    for x in steps:
        t = [x[0] + point[0], x[1] + point[1]]
        if t[0] >= 0 and t[0] < mask.shape[0] and t[1] >= 0 and t[1] < mask.shape[1] and mask[t[0], t[1]] == 0:
            res.append(t)
    return res

def search_component(start, img, mask):
    q = Queue()
    q.put(start)
    res = [start]
    while not q.empty():
        p = q.get()
        for x in expand(p, mask):
            if abs(img[p[0], p[1]] - img[x[0], x[1]]) < 0.35:
                mask[x[0], x[1]] = 1
                res.append(x)
                q.put(x)
    minX = min(res)
    maxX = max(res)
    minY = min(res, key=lambda x: x[1])
    maxY = max(res, key=lambda x: x[1])
    return {'points' : res, '1':(minY[1], minX[0]), '2': (maxY[1], maxX[0])}

def assoc(img):
    mask = np.zeros(img.shape)
    res = []
    for i in xrange(img.shape[0]):
        for j in xrange(img.shape[1]):
            if mask[i, j] == 0:
                mask[i, j] = 1
                res.append(search_component((i, j), img, mask))
    img2 = np.zeros((img.shape[0], img.shape[1], 3))
    #img2[:] = img
    color = [0, 0, 200]
    i = 0
    for x in res:
        i += 1
        #print x['1']
        #print x['2']
        cv2.rectangle(img2, x['1'], x['2'], color)
        if len(x['points']) < 40: continue
        for y in x['points']:img2[y[0], y[1]]=(100*(i%3), 100*(i%4), 100*(i%5))
        cv2.imshow('.....', img2)
        #cv2.waitKey()
    cv2.imshow('...', img)
    cv2.imshow('.....', img2)
    #cv2.waitKey()


if __name__ == '__main__':
    print 'loading images...'
    imgL = cv2.pyrDown( cv2.imread('aloeL.jpg') )  # downscale images for faster processing
    imgR = cv2.pyrDown( cv2.imread('aloeR.jpg') )

    # disparity range is tuned for 'aloe' image pair
    window_size = 3
    min_disp = 16
    num_disp = 112-min_disp
    stereo = cv2.StereoSGBM(minDisparity = min_disp,
        numDisparities = num_disp,
        SADWindowSize = window_size,
        uniquenessRatio = 10,
        speckleWindowSize = 100,
        speckleRange = 32,
        disp12MaxDiff = 1,
        P1 = 8*3*window_size**2,
        P2 = 32*3*window_size**2,
        fullDP = False
    )


    print 'computing disparity...'
    disp = stereo.compute(imgL, imgR).astype(np.float32) / 16.0

    '''print 'generating 3d point cloud...',
    h, w = imgL.shape[:2]
    f = 0.8*w                          # guess for focal length
    Q = np.float32([[1, 0, 0, -0.5*w],
                    [0,-1, 0,  0.5*h], # turn points 180 deg around x-axis,
                    [0, 0, 0,     -f], # so that y-axis looks up
                    [0, 0, 1,      0]])
    points = cv2.reprojectImageTo3D(disp, Q)
    colors = cv2.cvtColor(imgL, cv2.COLOR_BGR2RGB)
    mask = disp > disp.min()
    out_points = points[mask]
    out_colors = colors[mask]'''
    #out_fn = 'out.ply'
    #write_ply('out.ply', out_points, out_colors)
    print '%s saved' % 'out.ply'
    assoc(disp)
    print (disp-min_disp)/num_disp
    cv2.imshow('left', imgL)
    cv2.imshow('right', imgR)
    cv2.imshow('disparity', (disp-min_disp)/num_disp)
    #cv2.waitKey()
    cv2.destroyAllWindows()
